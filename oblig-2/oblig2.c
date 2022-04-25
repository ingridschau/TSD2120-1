#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//global int variable for account balance
int balance = 0;
//declare mutex and files to read as global variables
pthread_mutex_t mutex;
FILE *fpIncome, *fpExpense;

void *readIncome(void *args);
void *readExpense(void *args);

int main(int argc, char* argv[]){

	pthread_t threads[2];
	
	//initializing the mutex memory
	if(pthread_mutex_init(&mutex, NULL))
		printf("Error initialising mutex for balance.\n");
	
	//making the threads
	if(pthread_create(&threads[0], NULL, &readIncome, NULL))
		printf("Error creating income listener thread.\n");
	if(pthread_create(&threads[1], NULL, &readExpense, NULL))
		printf("Error creating expense listener thread.\n");

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);



	//deleting the mutex memory
	pthread_mutex_destroy(&mutex);

	printf("Remaining balance: %d", balance);

	return 0;
}

void *readIncome(void *args)
{
	int income = 0;

	if(fpIncome = fopen("inn.txt", "r"))
	{
		//iterate through the file, line by line
		while(fscanf(fpIncome, "%d", &income) != EOF)
		{
			pthread_mutex_lock(&mutex);
			balance = balance + income;
			pthread_mutex_unlock(&mutex);
		}
		fclose(fpIncome);
	}
	else
		printf("Error opening file \"inn.txt\".");
}

void *readExpense(void *args)
{
	int expense = 0;

	if(fpExpense = fopen("ut.txt", "r"))
	{
		//iterate through the file, line by line
		while(fscanf(fpExpense, "%d", &expense) != EOF)
		{
			//locks mutex, updates the balance, opens mutex
			pthread_mutex_lock(&mutex);
			balance = balance - expense;
			pthread_mutex_unlock(&mutex);
		}
		fclose(fpExpense);
	}else
		printf("Error opening file \"ut.txt\".");

}

