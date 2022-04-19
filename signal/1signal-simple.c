#include <unistd.h>
#include <stdlib.h>
#include
#include

//crtl-c - får signal

void signal_callback_handler(int signum)
{
	printf("\nCaught signal %d\n", signum);
}

int main()
{
	//hva skal gjøres når sigint kommer
	singal (SIGINT, signal_callback_handler);

	while(1)
	{
		printf("Program processing stuff here.\n");
		sleep(3);
	}
