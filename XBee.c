// Basic serial functions for using XBEE with the eagle bone
// Josh Dugan, Stephen Shinn, Matt Moravec

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
    	return value;
}

//write value to uart 2
int sendIntXbee(int value)
{
	FILE* file = fopen("/dev/ttyO2", "w+");
	fprintf(file, "%d", value);
	fclose(file);
    	return 0;
}

int sendShortXbee(short value)
{
	FILE* file = fopen("/dev/ttyO2", "w+");
	fprintf(file, "%hd", value);
	fclose(file);
    	return 0;
}

short receiveShortXbee()
{	
	short value;
	FILE* file = fopen("/dev/ttyO2", "r");
	fscanf(file, "%hd", &value);
	fclose(file);
    	return value;
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

