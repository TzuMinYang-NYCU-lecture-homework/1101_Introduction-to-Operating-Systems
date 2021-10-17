#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    printf("Main Process ID : %d\n\n", getpid());
	pid_t pid;

    pid = fork();           //fork1
    
    if(pid > 0)         //fork1's parent
    {
        wait(NULL);

        pid = fork();        //fork2
        if(pid == 0)         //fork2's child, don't need to exit, because it need to do fork3
            printf("Fork %d. I'm the child %d, my parent is %d.\n", 2, getpid(), getppid());
        else if(pid > 0)     //fork2's parent, i.e., fork1's parent, don't need to exit, because it need to do fork3
            wait(NULL);
        
        pid = fork();        //fork3
        if(pid == 0)         //fork3's child
            printf("Fork %d. I'm the child %d, my parent is %d.\n", 3, getpid(), getppid());
        else if(pid > 0)     //fork3's parent
            wait(NULL);
    }


    else if(pid == 0)            //fork1's child
    {
        printf("Fork %d. I'm the child %d, my parent is %d.\n", 1, getpid(), getppid());

        pid = fork();       //fork4
        if(pid == 0)        //fork4's child
        {
            printf("Fork %d. I'm the child %d, my parent is %d.\n", 4, getpid(), getppid());

            pid = fork();   //fork5
            if(pid == 0)    //fork5's child
            {
                printf("Fork %d. I'm the child %d, my parent is %d.\n", 5, getpid(), getppid());
                exit(0);
            }

            else if(pid > 0) //fork5's parent, i.e., fork4's child
            {
                wait(NULL);
                exit(0);
            }

            //don't need to exit, because fork4's child already exit
        }

        else if(pid > 0)    //fork4's parent, i.e., fork1's child
        {
            wait(NULL);
            exit(0);
        }
    }

    else printf("Error!");

    

	return 0;
}