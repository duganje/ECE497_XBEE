// Example for the Joystick with XBee.
// Sends the analog value from the resistor to another XBee.
// Josh Dugan, Steve Shinn, Matt Moravec

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include "../XBee.h"

 /****************************************************************
 * Constants
 ****************************************************************/
 
#undef DEBUG
#define GPIO_DIR "/sys/class/gpio"
#define AIN_DIR "/sys/devices/platform/omap/tsc"
#define gpioIn 7
#define gpioOut 48
#define xAxisIn 4
#define yAxisIn 6
#define MAX_BUF 64

FILE *fp;

/****************************************************************
 * Global variables
 ****************************************************************/
int keepgoing = 1;	// Set to 0 when ctrl-c is pressed

/****************************************************************
 * gpio_export
 ****************************************************************/
int gpio_export(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];

	fd = open(GPIO_DIR "/export", O_WRONLY);
	if (fd < 0) {
		perror("gpio/export");
		return fd;
	}

	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf, len);
	close(fd);

	return 0;
}

/****************************************************************
 * signal_handler
 ****************************************************************/
// Callback called when SIGINT is sent to the process (Ctrl-C)
void signal_handler(int sig)
{
	printf( "Ctrl-C pressed, cleaning up and exiting..\n" );
	keepgoing = 0;
}

/****************************************************************
 * ain_export
 ****************************************************************/
int ain_export(unsigned int ain)
{
	int fd, len;
	char buf[MAX_BUF];

	fd = open(AIN_DIR "/export", O_WRONLY);
	if (fd < 0) {
		perror("gpio/export");
		return fd;
	}

	len = snprintf(buf, sizeof(buf), "%d", ain);
	write(fd, buf, len);
	close(fd);

	return 0;
}

// Read x axis value
int read_x_Axis() {
FILE* file = fopen("/sys/devices/platform/omap/tsc/ain6", "r");
int num = 0;
fscanf (file, "%d", &num);
fclose (file);
printf(" x-Axis num: %d ", num);
fflush(stdout);
return num;
}

// Read y axis value
int read_y_Axis() {
FILE* file = fopen("/sys/devices/platform/omap/tsc/ain4", "r");
int num = 0;
fscanf (file, "%d", &num);
fclose (file);
printf("\r y-axis num: %d ", num);
fflush(stdout);
return num;
}

void main(int argc, char** argv)
{
	// initialize XBee
	initializeXbee();
	int xValue;
	int yValue;

	//initialize pins
	gpio_export(gpioIn);
	gpio_export(gpioOut);
	ain_export(yAxisIn);
	ain_export(xAxisIn);

	while(1)
	{
		xValue = read_x_Axis();
		yValue = read_y_Axis();
		sendIntXbee(xValue);
		sendIntXbee(yValue);
//		sendIntXbee(gpio);
		sleep(0.1); 
	}
}



