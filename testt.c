


#include <stdio.h>


#include <stdbool.h>





int main()
{
	
	int count = 0, a;	
	

	FILE *file;
	
	char line[2];
	

	if(fopen_s(&file, "Data.txt", "a")==NULL)
		fclose(file);

	fopen_s(&file, "Data.txt", "r");
	
	
	fgets(line, 2, file);

	if (feof(file))
		printf("first-run \n");
	else {
		printf("run \n");// f << i;
	}
	fclose(file);


	printf("Enter the value :");
	scanf_s("%d", &a);




	if (a == 42)
		printf("The Ultimate Question\n");
	else {
		a++;	printf("Value = %d\n", a);
	}


	fopen_s(&file, "Data.txt", "a");	fprintf(file, "s");
	

	system("PAUSE");
	return 0;
	


	
	
}