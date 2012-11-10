//sends data from the HMC5883L Magnetometer using the XBee radio
//Josh Dugan, Steve Shinn, Matt Moravec
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../XBee.h"


int main (int argc, char *argv[])
{
	// set up uart2 on the bone to connect to the XBee
	initializeXbee();
	short x_val, y_val, z_val;

	while(1){
		
		//read the axis valus from the sending XBee
		x_val = receiveShortXbee();
		z_val = receiveShortXbee();
		y_val = receiveShortXbee();

		fprintf(stderr, "x value = %hd, y value = %hd, z value = %hd\r", x_val, 			y_val, z_val);
	
	}
}
