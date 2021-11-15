//Program to find the offset and page number of a virtual address

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<math.h>

#define PAGE_SIZE 4096

//Helper functions
bool is_virtual_address_valid(char *);
bool are_all_characters_digits(char *);
bool fits_in_32_bits(char *);

int main(int argc, const char *argv[])
{
        //Virtual address, page number and offset respectively
        unsigned int va;
        unsigned int pn;
        unsigned int o;
        //Variable to hold virtual address
        char *vas = (char *)argv[1];
        bool e;
        
        //If two arguments were not given at command line inform user of expected usage and exit 
        if(argc != 2)
        {
                printf("Usage: ./a.out virtual_address\nTerminating program\nTry again\n");
                return 1;
        }

        //Running loop till user wishes to exit or valid virtual address entered
        while(is_virtual_address_valid(vas) == false)
        {

                //Ask for further action
                printf("Press 0 to terminate the program\nOR\nPress 1 to enter the virtual address again\n");
                scanf("%d", &e);

                //Take further action
                if(e)
                        scanf("%s", vas);
                else
                        return 1;
         }
        
        //Converting virtual address data type from string to int 
        va = atoi(vas);
        //Finding offset and page number respectively
        o = va % PAGE_SIZE;
        pn = va / PAGE_SIZE;

        printf("The address %u contains:\npage number = %u\noffset = %u\n", va, pn, o);

        return 0;
}


bool is_virtual_address_valid(char * va)
{
        const char *error = "Entered virtual adress is invalid";

        if(are_all_characters_digits(va) && fits_in_32_bits(va))
                return true;
        else
        {
                printf("%s\n", error);
                return false;
        }
}

bool are_all_characters_digits(char * va)
{
        const char *error = "Atleast one character entered is not a digit from 0 to 9";
        unsigned int l = strlen(va);
        //Checking whether every character is a digit in input string
        for(int i = 0; i != l; i++)
        {
                //If not digit print error and return false 
                if(isdigit(va[i]) == false)
                {
                        printf("%s\n", error);
                        return false;
                }
        }
        return true;
}

bool fits_in_32_bits(char *va)
{       const char *error = "Virtual address is more than 32 bits long";
        //Converting input string to 64 bit value to safely compare with 2^32 - 1
        unsigned long int temp = atol(va);
        if(temp > pow(2, 32) - 1)
        {
                printf("%s\n", error);
                return false;
        }
        return true;
}
