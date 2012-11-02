//basic serial functions for using XBEE with the eagle bone
//Josh Dugan, Steve Shinn, Matt Moravec
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


//reads the next int sent to uart 2
int read_int_serial()
{	
	
	FILE* file = fopen("/dev/ttyO2", "r");
	int value;
	fscanf(file, "%d", &value);
	fclose(file);
	printf("read value: %d\n", value);
    	return 0;
}

//write value to uart 2
int write_int_serial(int value)
{
	FILE* file = fopen("/dev/ttyO2", "w+");
	fprintf(file, "%d", &value);
	fclose(file);
	printf("wrote value: %d\n", value);
    	return 0;

}

//iniitializes uart 2 for the XBEE
int initializeXBEE() {
	int fd, len;
	char buf[64];

	fd = open("/sys/kernel/debug/omap_mux/spi0_d0", "w+");
	if (fd < 0) {
		perror("omap_mux/spi0_d0");
		return fd;
	}

	len = snprinf(buf, sizeof(buf), "%d", 1);
	write(fd, buf, len);
	close(fd);

	fd = open("/sys/kernel/debug/omap_mux/spi0_sclk", "w+");
	if (fd < 0) {
		perror("omap_mux/spi0_sclk");
		return fd;
	}

	len = snprinf(buf, sizeof(buf), "%d", 21);
	write(fd, buf, len);
	close(fd);

	return 0;

}
