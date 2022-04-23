#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *fp1, *fp2;
	char line1[50], line2[50];
	char *n1, *n2;

	fp1 = fopen("inn.txt" , "r");
	fp2 = fopen("ut.txt", "r");

	if ((fp1 == NULL) || (fp2 == NULL))
	{
		printf("ERROR");
		exit(1);
	}
	while(1)
	{
		n1 = fgets(line1, sizeof(line1), fp1);
		n2 = fgets(line2, sizeof(line2), fp2);

		if ((n1 == NULL) || (n2 == NULL))
		{
			break;
		}
		printf("%s%s", line1, line2);
	}
	return 0;	
}
