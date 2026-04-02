#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUMBER_LINE (1 << 0)
#define MARK_END (1 << 1)
#define SHOW_SIZE (1 << 2)

int stringcompare(char* a, char* b);


char* fileName = NULL;
char flags = 0x0;
long size = 0;
long currLine = 1;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		printf("jcat: No args passed: Please use as jcat [-flags] <filename..>\n");
		return 1;
	}

	for(int i = 0; i < argc; ++i)
	{
		if(i == 0) continue;
		if(stringcompare(argv[i], "-n"))
		{
			flags |= NUMBER_LINE; 
			continue;
		}
		if(stringcompare(argv[i], "-E"))
		{;
			flags |= MARK_END;
			continue;
		}
		if(stringcompare(argv[i], "-s"))
		{
			flags |= SHOW_SIZE;
			continue;
		}
		if(*(argv[i]) != '-')
		{
			if(fileName == NULL)
			{
				fileName = argv[i];
				continue;
			}
			else
			{
				printf("jcat: More than one file name provided, terminating program.\n");
				return 1; 
			}
		}
	}

	if(fileName == NULL)
	{
		printf("jcat: No file provided, terminating program.\n");
		return 1;
	}
	FILE* fileptr = fopen(fileName, "r");
	if(fileptr == NULL)
	{
		printf("jcat: Could not find file: \'%s\'\n", argv[argc-1]);
		return 2;
	}

	char currChar = 0;
	int startNew = 1;
	int currIndex = 0;

	while((currChar = fgetc(fileptr)) != EOF)
	{
		if((flags & NUMBER_LINE) && startNew)
		{
			printf("%ld  ", currLine);
			startNew = 0;
		}
		if(currChar == '\n')
		{
			currLine++;
			startNew = 1;
			if(flags & MARK_END)
			{
				printf("$");
			}
		}
		printf("%c", currChar);
		currIndex++;
		size++;
	}
	rewind(fileptr);
	if(flags & SHOW_SIZE)
	{
		fseek(fileptr, 0, SEEK_END);
		long sizeByte = ftell(fileptr);
		printf("jcat: File length is %ld characters: size: %.2f KB(%ld bytes)\n", size, (float)(sizeByte/1024), sizeByte);
	}
	fclose(fileptr);
	return 0;
}


int stringcompare(char* a, char* b)
{
	char* x = a;
	char* y = b;
	while(*x != '\0')
	{
		x++;
		y++;
		if(*y == '\0' && *x != '\0') return 0;
	}
	if(*y != '\0') return 0;
	x = a;
	y = b;
	while(*x != '\0')
	{
		if(*x != *y) return 0;
		x++;
		y++;
	}
	return 1;
}
