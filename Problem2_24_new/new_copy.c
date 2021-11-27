#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdbool.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>

#define STDOUT 0
#define USER_RESPONSE_MAX_LENGTH 100

char ur[USER_RESPONSE_MAX_LENGTH];/*Array store the last user esponse*/

char* user_prompt(char *);/*Function to store user's response to a prompt*/
bool copy(int s, int d);/*Function to copy contents of one open file to another empty open file*/

int main()
{
	//Accepting name of source file from user
	char s[USER_RESPONSE_MAX_LENGTH];
	strcpy(s, user_prompt("Enter the path of the source file : "));
	
	//If source file does not exist or read permission not granted on source file
	if(!access(s, F_OK|R_OK) == false)
	{
		perror("");/*Display error as indicated by access function*/
		exit(1);
	}
	
	int fds = open(s,O_RDONLY);/*Opening source file in read only mode*/

	//Accepting name of destination file from user
	char d[USER_RESPONSE_MAX_LENGTH]; 
	strcpy(d, user_prompt("Enter the path of the destination file : "));
	
	int flag = O_WRONLY|O_CREAT;/*Variable indicates conditions for opening destination file. Can be modified later*/	
	//If destination file already exists exit or truncate destination file according to user's wish
	if((!access(d, F_OK)) == true)
	{

		bool e = user_prompt("Destination file exists\nPress 0 to truncate file\nPress 1 to abort ");
		if(e)
		{
			close(fds);
			exit(1);
		}
		else/*modify flag so that destination file will get truncated to zero when being opened*/
			flag |= O_TRUNC;
		//If destination file does not have write permission display error and exit
		if((!access(d, W_OK)) == false)
		{
			perror("Destination file");
			exit(1);
		}
	}
	int fdd = open(d, flag);/*Open destination file*/

	//Copy contents of source file to destination file
	bool c = copy(fds, fdd);	
	
	//Close the files
	close(fdd);
	close(fds);

	//Writing success message to output
	const char *success = "Successfully copied contents of source file to destination file\n";
	write(STDOUT, success, strlen(success));

	exit(0);
}

char* user_prompt(char *m)/*Argument is the prompt to be written to stdout*/
{
	write(STDOUT, m, strlen(m));/*write prompt to standard output*/
	//Storing user response 
	short int nb = read(STDOUT, ur, USER_RESPONSE_MAX_LENGTH);
	ur[nb - 1] = '\0';/*Adding null chracter at the end*/
	return ur;
}

bool copy(int s, int d)/*Arguments are file descriptors*/
{
	char c;
	while(1)
	{
		short int nb = read(s, &c, sizeof(char));/*Read 1 byte from source file*/
		if(nb == 0)/*If EOF reached*/
			break;
		nb = write(d, &c, sizeof(char));/*Write 1 byte to destination file*/	
	}
	return true;
}