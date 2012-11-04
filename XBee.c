//basic serial functions for using XBEE with the eagle bone
//Josh Dugan, Steve Shinn, Matt Moravec
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


//reads the next int sent to uart 2
int receiveIntXbee()
{	
	
	FILE* file = fopen("/dev/ttyO2", "r");
	int value;
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
	printf("wrote value: %d\n", value);
    	return 0;

}

//iniitializes uart 2 for the XBEE
int initializeXbee() {
	FILE* file = fopen("/sys/kernel/debug/omap_mux/spi0_d0", "w+");
	fprintf(file, "1");
	fclose(file);

	file = fopen("/sys/kernel/debug/omap_mux/spi0_sclk", "w+");
	fprintf(file, "21");
	fclose(file);

	return 0;
}

int main(int argc, char *argv[])
{
	initializeXBEE();
}
