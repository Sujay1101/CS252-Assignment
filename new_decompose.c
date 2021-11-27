#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define PAGE_SIZE 4096

int main(int argc, char *argv[])
{
	//Check if input valid
	if(argc != 2)
	{
		printf("Usage : ./a.out virtual_address");
		return 1;
	}

	//Convert input to long integer using strtol function
	char *ptr = NULL;
	unsigned long int n = strtol(argv[1], &ptr, 10);

	//Check if input valid 32 bit integer
	if(*ptr != '\0')/*If all input characters were not digits*/
	{
		printf("Virtual address has characters which are not digits. Please try again\n");
		return 1;
	}
	else if((n >> 32) != 0)/*input was greater than 32 bits*/
	{
		printf("Virtual address exceeds 32 bits. Please try again\n");
		return 1;
	}

	//Find page number and offset
	unsigned int pn = n/PAGE_SIZE;
	unsigned int o = n%PAGE_SIZE;

	//Print page number and offset to standard output
	printf("The address %ld contains \nPage number = %u\nOffset = %u\n", n, pn, o);

	return 0;
	 
}
