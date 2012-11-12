// Example for the Force Sensitive Resistor with XBee.
// Sends the analog value from the resistor to another XBee.
// Josh Dugan, Steve Shinn, Matt Moravec

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../XBee.h"

// Read analog value and print to console
int readAnalog() {
	FILE* file = fopen("/sys/devices/platform/omap/tsc/ain6", "r");
	int num = 0;
	fscanf (file, "%d", &num);
	fclose (file);
	printf("Sent analog num: %d     \r", num);
	fflush(stdout);
	return num;
}

// Main
void main(int argc, char **argv, char **envp) {
	
	// initialize XBee
	initializeXbee();
	int analogValue;
	
	// Keep going; CTRL+C to exit
	while (1) {
		analogValue = readAnalog();
		sendIntXbee(analogValue);
		
		sleep(0.1);
	}
}

