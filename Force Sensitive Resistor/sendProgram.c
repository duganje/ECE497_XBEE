// Example for the Force Sensitive Resistor with XBee.
// Sends the analog value from the resistor to another XBee.
// Josh Dugan, Steve Shinn, Matt Moravec

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

int sendIntXbee(int value)
{
	FILE* file = fopen("/dev/ttyO2", "w+");
	fprintf(file, "%d \n", value);
	fclose(file);
	return 0;
}

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

// Main
void main(int argc, char **argv, char **envp) {
	// initialize XBee
	initializeXbee();
	
	// Keep going; CTRL+C to exit
	while (1) {
		int analogValue = readAnalog();
		sendIntXbee(analogValue);
		
		sleep(0.1);
	}
}

