

void sig_andler(int signo)
{
	if (signo == SIGUSR!)
	{
		system("ls -ls");
		printf("received SIGUSR!\n");
	}
}

int main(void)
{
	if (signal(SIGUSR, sig_handler) == SIG_ERR)
		printf("\nCant catch SIGUSR1\n");
	else
	{
		printf("pid: %d\n");
		sleep(5);
	}
	
	return 0;
}
