// Example for the Force Sensitive Resistor with XBee.
// Sends the analog value from the resistor to another XBee.
// Josh Dugan, Steve Shinn, Matt Moravec

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "XBee.h"

#define SYSFS_GPIO_DIR "/sys/class/gpio"

// Read analog value and print to console
int readAnalog() {
	FILE* file = fopen("/sys/devices/platform/omap/tsc/ain6", "r");
	int num = 0;
	fscanf (file, "%d", &num);
	fclose (file);
	printf("\rAnalog num: %d    ", num);
	fflush(stdout);
	return num;
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
	
	// initialize XBee
	initializeXbee();
	
	// Keep going; CTRL+C to exit
	while (1) {
		int analogValue = readAnalog();
		sendIntXbee(analogValue);
		
		sleep(0.5);
	}
}

