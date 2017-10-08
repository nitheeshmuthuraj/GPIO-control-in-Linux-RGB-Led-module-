#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <poll.h>
#include<stdint.h>
#include<linux/input.h>
#define cycle_duration 20

#define tim 0.5

int global=1;

#define MOUSEFILE "/dev/input/event3"

#include "gpio.h"


int duty_cycle;
char buf[MAX_BUF];

int RED_LED ;
int GREEN_LED ;
int BLUE_LED ;

void *mouse_check(void* arg)
{
	int fdm;
	struct input_event ie;
	if((fdm=open(MOUSEFILE,O_RDONLY))==-1)
	    {
	            perror("opening device");
	            exit(EXIT_FAILURE);
	    }

while(global){
	read(fdm,&ie,sizeof(struct input_event));
  if(ie.code==272)global=0;
						}
return 0;

}


int IOSetup(int i1,int i2,int i3)
{


	RED_LED=gpio_pins(i1);
	GREEN_LED=gpio_pins(i2);
	BLUE_LED=gpio_pins(i3);


	gpio_export(GREEN_LED);
	gpio_set_dir(GREEN_LED, 1);

	gpio_export(BLUE_LED);
	gpio_set_dir(BLUE_LED, 1);

	gpio_export(RED_LED);
	gpio_set_dir(RED_LED, 1);

}


int main(int argc,char **argv)
{
int Red,Green,Blue;
duty_cycle=atoi(argv[1]);
int io1=atoi(argv[2]);
int io2=atoi(argv[3]);
int io3=atoi(argv[4]);
float i,j;
int k,t;

	pthread_t    thread_id;
	void   *thread_result;


t=(tim)*1000/(cycle_duration);
i=duty_cycle*cycle_duration/100;
j=(100-duty_cycle)*cycle_duration/100;

printf("%d\n %d\n %d\n",io1,io2,io3);

IOSetup(io1,io2,io3);


int len;

len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", RED_LED);
Red = open(buf, O_RDONLY | O_WRONLY| O_NONBLOCK);

len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value",GREEN_LED);
Green = open(buf, O_RDONLY | O_WRONLY| O_NONBLOCK);

len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value",BLUE_LED);
Blue = open(buf, O_RDONLY | O_WRONLY| O_NONBLOCK);
usleep(i*1000);

	pthread_create( &thread_id, NULL, mouse_check , NULL );

while(global)
{
	for(k=0;k<t;k++){
	write(Red,"1",1);
	usleep(i*1000);
	write(Red,"0",1);
	usleep(j*1000);
									}
usleep(tim*1000000);
if(global!=1) break;

for(k=0;k<t;k++){
	write(Green,"1",1);
	usleep(i*1000);
	write(Green,"0",1);
	usleep(j*1000);
}
usleep(tim*1000000);
if(global!=1) break;

for(k=0;k<t;k++){
	write(Blue,"1",1);
	usleep(i*1000);
	write(Blue,"0",1);
	usleep(j*1000);
}
usleep(tim*1000000);
if(global!=1) break;

for(k=0;k<t;k++){
	write(Red,"1",1);
	write(Green,"1",1);
	usleep(i*1000);
	write(Red,"0",1);
	write(Green,"0",1);
	usleep(j*1000);
}
usleep(tim*1000000);
if(global!=1) break;

for(k=0;k<t;k++){
	write(Red,"1",1);
	write(Blue,"1",1);
	usleep(i*1000);
	write(Red,"0",1);
	write(Blue,"0",1);
	usleep(j*1000);
}
usleep(tim*1000000);
if(global!=1) break;

for(k=0;k<t;k++){
	write(Green,"1",1);
	write(Blue,"1",1);
	usleep(i*1000);
	write(Green,"0",1);
	write(Blue,"0",1);
	usleep(j*1000);
}
usleep(tim*1000000);
if(global!=1) break;

for(k=0;k<t;k++){
	write(Red,"1",1);
	write(Green,"1",1);
	write(Blue,"1",1);
	usleep(i*1000);
	write(Red,"0",1);
	write(Green,"0",1);
	write(Blue,"0",1);
	usleep(j*1000);
}
usleep(tim*1000000);
if(global!=1) break;

}

pthread_join( thread_id,  &thread_result );
printf("Mouse Event has been detected & exiting the main function .. \n");
return 0;

}
