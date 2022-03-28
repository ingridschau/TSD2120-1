#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <signal.h>

#define READ 0
#define WRITE 1



int main()
{
	//initialize a random number based on the time
	srand(time(NULL));
	
	//create two arrays to store the pipelines for communication 
	//between the child and parent processes
	int pipeFromChildToParent[2];
	int pipeFromParentToChild[2];

	int numberOfGuesses = 0;
	int correctNumber = 0;

	//create a process id for the child
	pid_t cpid;

	//create the pipes
	if (pipe(pipeFromChildToParent) == -1 || pipe(pipeFromParentToChild) == -1)
	{
		printf("Pipe failed.\n");
		return 1;
	}

	//create a process
	cpid = fork();

	//child process
	if (cpid == 0)
	{	
		//close the unused ends 
		close(pipeFromParentToChild[WRITE]);
		close(pipeFromChildToParent[READ]);
		
		//variables to store the requests and responses
		int readFromParent, writeToParent;
		
		//generate random number between 1 and 1000
		int generatedNumber = rand() % 1001;	
		

		while(writeToParent != 0) {
			
			//break loop if parent closes write end of second pipe
			if (!read(pipeFromParentToChild[READ], &readFromParent, sizeof(int)) > 0)
				break;
			
			//break loop if parent guesses correctly
			if (readFromParent == generatedNumber){
				writeToParent = 0;
				break;
			}
			//if not correct send a value 
			else if (readFromParent < generatedNumber)
				writeToParent = 1;
			else if (readFromParent > generatedNumber)
				writeToParent = -1;
			//write value over
			write(pipeFromChildToParent[WRITE], &writeToParent, sizeof(int));

		}
	
		//final print when the correct number is guessed
		printf("The correct number was %d\n", generatedNumber);	

		//close the pipes
		close(pipeFromParentToChild[READ]);
		close(pipeFromChildToParent[WRITE]);
	}

	//parent process
	else
	{
		//set the endpoints of the interval
		int min = 1;
		int max = 1000;

		//create variables for the guess and the input
		int parentGuess;
		int readFromChildToParent;
		
		//close the unused ends of the pipes
		close(pipeFromParentToChild[READ]);
		close(pipeFromChildToParent[WRITE]);

		while(1){
			//generate guess by parent, binary search style
			parentGuess = (min + max) / 2;
			
			//write the guess over to child process to check answer
			write(pipeFromParentToChild[WRITE], &parentGuess, sizeof(int));

			//break loop if child closes write end of first pipe
			if(read(pipeFromChildToParent[READ], &readFromChildToParent, sizeof(readFromChildToParent)) > 0)
			{
				//count number of guesses
				numberOfGuesses++;
				
				//change the values of min and max depending on the guess being
				//bigger or smaller than the generated number
				if (readFromChildToParent == 1)
					min = ((min + max) / 2) + 1;
				else if (readFromChildToParent == -1)
					max = ((min + max)/ 2) - 1;
				//if correct guess, break loop
				else if (readFromChildToParent == 0)
					break;

			}else
				break;
			
		}

	//print number of guesses
	printf("Number of guesses was %d\n", numberOfGuesses+1);	

	//close the ends of the pipes
	close(pipeFromParentToChild[WRITE]);
	close(pipeFromChildToParent[READ]);
	}
	
	return 0;
			
}

