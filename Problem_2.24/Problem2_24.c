//Program to copy contents of one file to another

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

#define MAX_FILENAME_LENGTH 100 
int main()
{
	int s;
	int d;
	int r;
	int w;
	char op;
	
	char source[MAX_FILENAME_LENGTH];
	char destination[MAX_FILENAME_LENGTH];
	
	const char *prompt_s = "Enter name of the source file : ";
	const char *prompt_d = "Enter name of the destination file : ";
	
	const char *se = "Could not open source file";
	const char *de = "Could not open destination file";
	const char *re = "Could not read from source file";
	const char *we = "Could not write to destination file";
	
	const char *pr = "Destination file already exists\nPress 0 to overwrite the contents of that file\nPress 1 to terminate program\n";
	const char *success = "Successfully copied contents of source file to destination file\n";
	
	//predefined variable to store error number of any system call
	extern int errno;
	
	//Taking input
	write(0, prompt_s, strlen(prompt_s));
	scanf("%s", source);
	write(0, prompt_d, strlen(prompt_d));
	scanf("%s", destination);

	//Open the source file
	s = open(source, O_RDONLY);
	if(s == -1)
	{	
		perror(se);
		exit(1);
	}

	//Open the destination file
	d = open(destination, O_CREAT|O_WRONLY|O_EXCL /*set the flags so that file gets created if does not exist and we can tell if the file already exists*/);
	//If the opening failed and file exists
	if(d == -1 && errno == EEXIST)
	{	
		//Ask user for action
		write(0, pr, strlen(pr));
		read(0, &op, 1);
		
		if(op == '1')
		{
			close(s);
			exit(1);
		}
		
		//opening and truncating contents of destination file to zero bytes
		d = open(destination, O_TRUNC|O_WRONLY);
		
		if(d == -1)
		{
			perror(de);
			close(s);
			exit(1);
		}
	}
	else if(d == -1)
	{
		perror(de);
		close(s);
		exit(1);
	}


	//Copying character at a time from source to destination
	char c;
	while(1)
	{
		//Read character
		r = read(s, &c, 1);
		//Check if read failed
		if(r == -1)
		{
			perror(re);
			close(s);
			close(d);
			exit(1);
		}
		//Write character
		w = write(d, &c, 1);
		//Check if write failed
		if(w == -1)
		{
			perror(we);
			close(s);
			close(d);
			exit(1);
		}
		if(r == 0)
			break;
	}  

	close(d);
	close(s);

	write(0, success, strlen(success));
	
	return 0;

}
