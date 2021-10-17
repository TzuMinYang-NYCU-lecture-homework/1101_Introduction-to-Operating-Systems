#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 	// for calloc
#include <string.h> 	// for strcmp
#include <sys/wait.h> 	// for wait

#define MAX_LINE 80

int main(void)
{
	char *arg[MAX_LINE/2+1]; /*command line arguments*/
	int should_run = 1; /*flag to determine when to exit program*/
	
	while(should_run){
		printf("osh>");
		fflush(stdout);
		
		/**
		* your code!
		* After reading user input, the step are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		*/
		char *inputBuffer = calloc(MAX_LINE, sizeof(char)); //malloc which will clear memory version 
		char *command = calloc(MAX_LINE, sizeof(char));

		read(STDIN_FILENO, inputBuffer, MAX_LINE);
		//printf("%d %ld %d\n", STDIN_FILENO, sizeof(inputBuffer), MAX_LINE);
		//printf("%s", inputBuffer);

		int i;
		for(i = 0; i < 10; i++)
			printf("%d\n", inputBuffer[i]);
		printf("\n");

		int is_command = 1, current_arg_num = 0, current_tmp_arg_len = 0;
		char tmp_arg[MAX_LINE] = {0};
		arg[0] = "";
		for(i = 0; i < MAX_LINE; i++)
		{
			printf("i = %d, input = %d\n", i, inputBuffer[i]);
			if(inputBuffer[i] == '\0')
			{
				break;
			}

			if(is_command == 1)
			{
				if(inputBuffer[i] == ' ' || inputBuffer[i] == '\n') is_command = 0;
				else command[i] = inputBuffer[i];
			}

			else
			{
				if(inputBuffer[i] == ' ' || inputBuffer[i] == '\n')
				{
					tmp_arg[current_tmp_arg_len] = '\0';
					arg[current_arg_num++] = tmp_arg;
					printf("argnum %d\n", current_arg_num);

					current_tmp_arg_len = 0;
				}
				else tmp_arg[current_tmp_arg_len++] = inputBuffer[i];
			}
		}
		/*for(i = 0; i < 10; i++)
			printf("i:%d, %d\n", i, command[i]);*/
			
		printf("command: %s\n", command);
		for(i = 0; i < current_arg_num; i++)
			printf("i:%d, %s\n", i, arg[i]);

		if(!strcmp(command, "exit"))
		{
			free(inputBuffer);
			should_run = 0;
			continue;
		}

		pid_t pid;
		pid = fork();

		if(pid == 0) //child
		{
			
			//execvp()
		}
			

		else if(pid > 0) //parent
			wait(NULL);

		else printf("Fork fail!!!\n");

		free(inputBuffer);
	}

	return 0;
}


