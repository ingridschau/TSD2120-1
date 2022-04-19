
int main(){
	fptr = fopen("inn.txt", "r");

	for (int teller = 0; teller < 10000; teller++)
	{
	antall++;
	fscanf(fptr, "%d", &tall);
	printf("tallet er : %d", tall1);
	sum += tall;

	}

	printf("Summen er %d %d\n", sum, tall);

	fclose(fptr);
	return 0;
}


/*
kritiske steder i kode?
hver tråd har hver sin fil å lese fra
oppdatering av balansen, kontovariabelen. hvis den ene tråden leser variabelen
trekker seg ut, den neste kommer så har man mistet en transaksjon


		int tall
		time t;
		//make file pointer, open file, do whatever, remember to close
		file *ptr;
*/
