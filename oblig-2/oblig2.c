#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//global int variable for account balance
int balance = 0;
//declare mutex and files to read as global variables
pthread_mutex_t mutex;
FILE *fpIncome, *fpExpense;

void *readIncome(void *args)
{
	int income = 0;

	fpIncome = fopen("inn.txt", "r");
	
	//iterate through the file, line by line
	while(fscanf(fpIncome, "%d", &income)==1)
	{
		pthread_mutex_lock(&mutex);
		balance = balance + income;
		pthread_mutex_unlock(&mutex);
	}
	fclose(fpIncome);
}

void *readExpense(void *args)
{
	int expense = 0;

	fpExpense = fopen("ut.txt", "r");

	//iterare through the file, line by line
	while(fscanf(fpExpense, "%d", &expense)==1)
	{
		//locks mutex, updates the balance, opens mutex
		pthread_mutex_lock(&mutex);
		balance = balance - expense;
		pthread_mutex_unlock(&mutex);
	}
	fclose(fpExpense);
}

int main(int argc, char* argv[]){

	pthread_t threads[2];
	
	//initializing the mutex memory
	pthread_mutex_init(&mutex, NULL);
	
	//making the threads
	pthread_create(&threads[0], NULL, &readIncome, NULL);
	pthread_create(&threads[1], NULL, &readExpense, NULL);

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);



	//deleting the mutex memory
	pthread_mutex_destroy(&mutex);

	printf("Remaining balance: %d", balance);

	return 0;
}

