// Example for the Force Sensitive Resistor with XBee.
// Lights an LED on GPIO60 based on the received value.
// Josh Dugan, Steve Shinn, Matt Moravec

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../XBee.h"

#define SYSFS_GPIO_DIR "/sys/class/gpio"

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
		lightLedIfStrong(analogValue);
	}
}
