// Example for the Force Sensitive Resistor with XBee.
// Lights an LED on GPIO60 based on the received value.
// Josh Dugan, Steve Shinn, Matt Moravec

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "XBee.h"

//reads the next int sent to uart 2
int receiveIntXbee()
{	
	int value;
	FILE* file = fopen("/dev/ttyO2", "r");
	fscanf(file, "%d", &value);
	fclose(file);
	printf("read value: %d\n", value);
    	return 0;
}

//write value to uart 2
int sendIntXbee(int value)
{
	FILE* file = fopen("/dev/ttyO2", "w+");
	fprintf(file, "%d", &value);
	fclose(file);
    	return 0;

}

int sendShortXbee(short value)
{
	FILE* file = fopen("/dev/ttyO2", "w+");
	fprintf(file, "%d", &value);
	fclose(file);
    	return 0;
}

int receiveShortXbee()
{	
	short value;
	FILE* file = fopen("/dev/ttyO2", "r");
	fscanf(file, "%d", &value);
	fclose(file);
	printf("read value: %d\n", value);
    	return 0;
}

//iniitializes uart 2 for the XBEE
int initializeXbee() {
	//set pin 21 to uart 2 TX - output
	FILE* file = fopen("/sys/kernel/debug/omap_mux/spi0_d0", "w+");
	fprintf(file, "1");
	fclose(file);

	//set pin 22 to uart 2 RX - input
	file = fopen("/sys/kernel/debug/omap_mux/spi0_sclk", "w+");
	fprintf(file, "21");
	fclose(file);
	return 0;

}

// Light the LED if the analog value is low (ie, strong force)
void lightLedIfStrong(analogValue) {
	FILE *file;
	file = fopen("/sys/class/gpio/gpio60/value","w+");
	
	if (analogValue < 100) {
		fprintf(file, "1");
	} else {
		fprintf(file, "0");
	}

	fclose(file);
}

// Main
void main(int argc, char **argv, char **envp) {
	// Export gpio60
	FILE *fp;
	char set_value[5];
	fp = fopen(SYSFS_GPIO_DIR "/export", "ab");
	rewind(fp);
	strcpy(set_value, "60");
	fwrite(&set_value, sizeof(char), 2, fp);
	fclose(fp);

	// Set gpio60 direction
	FILE *file;
	file = fopen("/sys/class/gpio/gpio60/direction","w+");
	fprintf(file,"%s","out");
	fclose(file);
	
	// Initialize XBee
	initializeXbee();
	
	// Keep going
	while (1) {
	int analogValue = receiveIntXbee();

	// Do anything based on analog value
	if (analogValue < 1000)
		lightLedIfStrong();
	}
}