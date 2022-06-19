#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include<sys/wait.h>

char **parse_cmdline( const char *cmdline )
{
	int s = strlen(cmdline);
	char array[s];
	strcpy(array, cmdline);
	
	char *ptr = strtok(array, " ");
	
	int size = 2;
	
	int i = 0;
	
	char **ptr1 = (char *)calloc (size, sizeof (char *));
	
	while (ptr != NULL) 
	{	
		ptr1[i] = (char * )calloc(strlen(ptr), sizeof(char));
		
		strcpy(ptr1[i], ptr);
		
		i++;
		
		size += 1;
		
		ptr1 = realloc(ptr1, ((size + 1) * sizeof(char *)));
		
		ptr = strtok(NULL, " ");
    	}
	
	ptr1[i-1] = NULL;
	
	return ptr1;
}

int main( )
{
	
	while(1)
	{
		int size = 100;
	
		char *arr = malloc(size);
		
		ssize_t  res;
		
		int offset = 0;
	
		printf("$ ");
		
		while(1)
		{
			res = read(STDIN_FILENO, &arr[offset], 1);
			
			if(res == 0)
			{
				return 0;
			
			}
			else if(res < 0)
			{
				perror("reading: ");
				return 0;
			}
			
			
			else if( (offset+1) > size)
			{
				size += 100;
				
				arr = realloc(arr, size);
			}
			
			else if(arr[offset] == '\n')
			{
				break;
			}
			offset++;
			
		}	
		
		int broqch = 0;
		int j = 0;
		char masive[200];
		
		for(int i = 0; arr[i] != '\0'; i++)// cikul za mahaneto na /bin/ za vtoriq argument na execv
		{
			if(broqch >= 2)
			{
				masive[j] = arr[i];
				j++;
			}
			if(arr[i] == '/')
			{
				broqch++;
			}
		}
		
		char **strMasive = parse_cmdline(masive);
		
		char **arrMasive = parse_cmdline(arr);	
		
		free(arr);
		
		pid_t child_pid = fork();
			
		int status;
		
		if(child_pid == 0)
		{
			if(execv(arrMasive[0], strMasive) < 0 )
			{
				perror(arrMasive[0]);
				
				exit(0);
				
				return 0;
			}
			else
			{
				exit(0);
					
				return 0;
			}
		}
		
		else if(child_pid > 0)
		{
			waitpid(child_pid, &status, 0); 
			
		}
		else if (child_pid < 0)
		{
			perror("fork: ");
			return 0;
		}
		
	}
	
	

	return 0;
}