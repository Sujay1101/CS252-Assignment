//Program to copy contents of one file to another
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main(char argc, char *argv[])
{
	int s;
	int d;
	int r;
	int w;
	short int op;
	const char *usage = "Usage : ./a.out sourcefile_name destinationfile_name";
	const char *se = "Could not open source file";
	const char *de = "Could not open destination file";
	const char *re = "Could not read from source file";
	const char *we = "Could not write to destination file";
	const char *pr = "Destination file already exists\nPress 0 to overwrite the contents of that file\nPress 1 to terminate program\n";
	const char *success = "Successfully copied contents of source file to destination file\n";
	extern int errno;

	if(argc != 3)
	{
		write(0, usage, strlen(usage));
		exit(1);
	}

	//Open the source file
	s = open(argv[1], O_RDONLY);
	if(s == -1)
	{	
		perror(se);
		exit(1);
	}

	//Open the destination file
	d = open(argv[2], O_CREAT|O_WRONLY|O_EXCL /*set the flags so that file gets created if does not exist and tells if the file already exists*/);
	//If the opening failed and file exists
	if(d == -1 && errno == EEXIST)
	{
		//Ask user for action
		write(0, pr, strlen(pr));
		scanf("%hi", &op);
		//Terminate program OR Truncate file to zero
		if(op == 0)
		{
			//Closing inappropritely opened file
			close(d);
			//opening properly
			d = open(argv[2], O_TRUNC|O_WRONLY);
			if(d == -1)
			{
				perror("");
				close(s);
				exit(1);
			}
		}
		else
			exit(1);
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
