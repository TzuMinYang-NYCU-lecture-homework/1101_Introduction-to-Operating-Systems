#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 	// for wait
#include <string>
#include <iostream>
#include <sstream>		// for stringstream
#include <vector>		// for vector
#include <algorithm> 	// for transform

#define MAX_LINE 80

using namespace std;

int main(void)
{
	string arg[MAX_LINE/2+1]; /*command line arguments*/
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


		void *inputBuffer = calloc(MAX_LINE, sizeof(char)); //malloc which will clear memory version 
		read(STDIN_FILENO, inputBuffer, MAX_LINE); //void * to string

		string input((char*)inputBuffer, MAX_LINE);
		free(inputBuffer); //free memory of buffer

		stringstream ss_input(input);
		int cur_arg_num = 0;

		while(ss_input >> arg[cur_arg_num++]);		//get command and args
		arg[cur_arg_num] = "";

		if(arg[0] == "exit") break;

		//string to char* const, for execvp()
		vector<char*> vec_char_arg;
		transform(begin(arg), begin(arg)+cur_arg_num-2, back_inserter(vec_char_arg), [](string& s){ s.push_back(0); return &s[0]; });
		vec_char_arg.push_back(nullptr);
		char** char_arg = vec_char_arg.data();


		pid_t pid;
		pid = fork();

		if(pid == 0) //child
		{
			execvp(arg[0].c_str(), char_arg);
			exit(0);
		}

		else if(pid > 0) //parent
			wait(NULL);

		else printf("Fork fail!!!\n");
	}

	return 0;
}


