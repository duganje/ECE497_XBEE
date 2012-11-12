//sends data from the HMC5883L Magnetometer using the XBee radio
// used with receiveMag.c 
//Josh Dugan, Steve Shinn, Matt Moravec
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "XBee.h"
#include "i2c-dev.h"


int main (int argc, char *argv[])
{
	// set up uart2 on the bone to connect to the XBee
	initializeXbee();

	int i2cbus = 3;
	int address = 30;
	int daddress;
	short x_val, y_val, z_val;

	//set to continuous measurement mode
	i2cset(i2cbus, address, 2, 0);


	//continuously read and print the values for each axis
	while(1){
		//get x-axis value
		x_val = ((i2cget(i2cbus, address, 3) << 8) + i2cget(i2cbus, address, 4));

		//transmit x-axis value
		sendShortXbee(x_val);	

		//small wait
		usleep(50000);			

		//get z-axis value
		z_val = ((i2cget(i2cbus, address, 5) << 8) + i2cget(i2cbus, address, 6));

		//transmit z-axis value
		sendShortXbee(z_val);

		//small wait
		usleep(50000);	

		//get y-axis value
		y_val = ((i2cget(i2cbus, address, 7) << 8) + i2cget(i2cbus, address, 8));
		
		//transmit y-axis value
		sendShortXbee(y_val);

		fprintf(stderr, "x value = %hd, y value = %hd, z value = %hd        \r", 				x_val, y_val, z_val);

		//small wait
		usleep(50000);		

	}	

	return 0;
		
	

}
