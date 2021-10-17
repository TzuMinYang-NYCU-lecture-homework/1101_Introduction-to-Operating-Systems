#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;

    pid = fork(); //fork0
    printf("fork0 I'm %d. My parent is %d.\n", getpid(), getppid());
    if(pid == 0)
    {
        pid = fork(); //fork1
        printf("fork1 I'm %d. My parent is %d.\n", getpid(), getppid());
        if(pid > 0) wait(NULL);

        pid = fork(); //fork2
        printf("fork2 I'm %d. My parent is %d.\n", getpid(), getppid());
        if(pid > 0) wait(NULL);
    }

    else if(pid > 0)
    {
        wait(NULL);

        pid = fork(); //fork3
        printf("fork3 I'm %d. My parent is %d.\n", getpid(), getppid());
        if(pid > 0) wait(NULL);
    }

    else printf("Error!");

    pid = fork(); //fork4
    printf("fork4 I'm %d. My parent is %d.\n", getpid(), getppid());
    if(pid > 0) wait(NULL);

	//sleep(1000);
	return 0;
}