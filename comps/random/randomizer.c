#include "randomizer.h"

int main(int argc, const char *argv[])
{
	printMenu();
	return 0;
}

void printMenu() {
		char select[5] = {0};
		char *ptr = NULL;
		int selection = 10;

	while (1)
	{
		printf("==================================\n");
		printf("===============MENU===============\n");
		printf("==================================\n");
		printf("1. Dice Roller\n");
		printf("2. Area of Circle\n");
		printf("3. Volume of a Cube\n");
		printf("4. Power\n");
		printf("5. Exit\n");
		printf("Choose an option\n");

		int ok = 0;
		ok = getIntInput(select, 2);
		if (ok == 0) {
			selection = strtol(select, &ptr, 10);
		}

		switch (selection) {
		case 1:
			srand(time(NULL));
			diceRoll();
			break;
		case 2:
			circleArea();
			break;
		case 3:
			cubeVol();
			break;
		case 4:
			raisePower();
			break;
		case 5:
			exit(EXIT_SUCCESS);
			break;
		default:
			printf("Please choose a number\n");
			break;
		}
	}
}

int getIntInput(char finalstring[], int length) {
	fflush(stdin);
	int c;
	int i = 0;
	while ((c = getchar()) != '\n' && c != EOF) {
		if (i < length - 1) {
			finalstring[i] = c;
			i++;
		} else {
			return 1;
		}
	}
	finalstring[i] = '\0';
	return 0;
}

void diceRoll() {
	char select[10] = {0};
	char *ptr;
	printf("Please Enter # of sides\n");
	getIntInput(select, 10);
	int numSides = strtol(select, &ptr, 10);

	printf("Please Enter # of Die\n");
	getIntInput(select, 10);
	int numDie = strtol(select, &ptr, 10);

	printf("Please Enter # of rolls\n");
	getIntInput(select, 10);
	int numRolls = strtol(select, &ptr, 10);

	//prompt user to save or not
	//if y save; if n dont
	printf("Want to save results\n");
	getIntInput(select, 3);
	if (select[0] == 'y') {
		FILE *f = fopen("random.txt", "a+");
		printf("=====\n");
		for (int i = 0; i < numRolls; i++)
		{
			printf("Roll %d\n", i + 1);
			fprintf(f, "Roll %d\n", i + 1);
			for (int j = 1; j <= numDie; j++)
			{
				int random = (rand() % (numSides + 1 - 1) + 1);
				printf("Die %d = %d\n", j, random);
				fprintf(f, "Die %d = %d\n", j, random);
			}
		}
		printf("=====\n");
	}
	else if (select[0] == 'n') {
		//print results
		for (int i = 0; i < numRolls; i++) {
			printf("Roll %d\n", i + 1);
			for (int j = 1; j <= numDie; j++)
			{
				int random = (rand() % (numSides + 1 - 1) + 1);
				printf("Die %d = %d\n", j, random);
			}
		}
	}
	else {
		printf("Enter y or n");
	}
}

void circleArea() {
	printf("Please enter the radius\n");

	char select[3] = {0};
	char *ptr;
	getIntInput(select, 3);
	int radius = strtol(select, &ptr, 10);
	float pi = (radius * radius) * 3.14;

	printf("The radius is %2f\n", pi);

	//save results
	printf("Would you like to save the results?\n");
	getIntInput(select, 3);
	if (select[0] == 'y') {
		FILE *f = fopen("random.txt", "a+");
		fprintf(f, "=====\nThe radius is %.2f\n=====\n", pi);
	}
}

void cubeVol() {
	printf("Please enter the length of the side\n");

	char select[3] = {0};
	char *ptr;
	getIntInput(select, 3);
	int sides = strtol(select, &ptr, 10);

	printf("The volume is %d\n", (sides * sides * sides));

	//save results
	printf("Want to save the results?\n");
	getIntInput(select, 3);
	if (select[0] == 'y')
	{
		FILE *f = fopen("random.txt", "a+");
		fprintf(f, "=====\nThe volume is %d\n=====\n", (sides * sides * sides));
	}
}

void raisePower() {
	printf("Please enter base\n");

	char select[10] = {0};
	char *ptr;
	getIntInput(select, 3);
	int base = strtol(select, &ptr, 10);

	printf("Please enter power\n");
	getIntInput(select, 3);
	int power = strtol(select, &ptr, 10);

	int answer = powered(base, power);

	printf("%d raised to the %d power is %d\n", base, power, answer);

	//save results
	printf("Want to save the results?\n");
	getIntInput(select, 3);
	if (select[0] == 'y')
	{
		FILE *f = fopen("random.txt", "a+");
		fprintf(f, "=====\n%d raised to the %d power is %d\n=====\n", base, power, answer);
	}
}

int powered(int base, int power) {
	//base case is exponet = 0; return 1
	if (power == 0) {
		return 1;
	}
	else {
		return base * powered(base, power - 1);
	}
}