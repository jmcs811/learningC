#include "randomizer.h"

int main(int argc, const char *argv[])
{
	printMenu();
	return 0;
}

void printMenu() {
		char select[5] = {0};
		char *ptr = NULL;
		int selection;

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

		selection = getIntInput(select, 5);
		
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

// int getIntInput(char finalstring[], int length) {
// 	fflush(stdin);
// 	int c;
// 	int i = 0;
// 	while ((c = getchar()) != '\n' && c != EOF) {
// 		if (i < length - 1) {
// 			finalstring[i] = c;
// 			i++;
// 		} else {
// 			return 1;
// 		}
// 	}
// 	finalstring[i] = '\0';
// 	return 0;
// }

int getIntInput(char finalString[], int length) {

    if (!fgets(finalString, sizeof(finalString), stdin)){
        exit(-1);
    } else {
        if (!strchr(finalString, '\n')){
            while (fgets(finalString, sizeof(finalString), stdin) && !strchr(finalString, '\n'))
            ;
        } else {
            char *chk;
            int tmp = (int) strtol(finalString, &chk, 10);

            if (isspace(*chk) || *chk == 0) {
                return tmp;
            } else {
                printf("%s is not a valid int\n", finalString);
            }
        }
    }
    return 0;
}

void diceRoll() {
	char select[10] = {0};
	printf("Please Enter # of sides\n");
	int numSides = getIntInput(select, 10);

	printf("Please Enter # of Die\n");
	int numDie = getIntInput(select, 10);

	printf("Please Enter # of rolls\n");
	int numRolls = getIntInput(select, 10);

	//prompt user to save or not
	//if y save; if n dont
	printf("Want to save results (1 or 0)\n");
	int answer = getIntInput(select, 3);
	if (answer) {
		FILE *f = fopen("random.txt", "a+");
		fprintf(f, "=====\n");
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
		fprintf(f, "=====\n");
	}
	else if (!answer) {
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
		printf("Enter 1 or 0");
	}
}

void circleArea() {
	printf("Please enter the radius\n");
	char select[3] = {0};
	int radius = getIntInput(select, 3);
	float pi = (radius * radius) * 3.14;

	printf("The radius is %2f\n", pi);

	//save results
	printf("Would you like to save the results? (1 or 0)\n");
	int answer = getIntInput(select, 3);
	if (answer) {
		FILE *f = fopen("random.txt", "a+");
		fprintf(f, "=====\nThe radius is %.2f\n=====\n", pi);
	}
}

void cubeVol() {
	printf("Please enter the length of the side\n");

	char select[3] = {0};
	char *ptr;
	int sides = getIntInput(select, 3);

	printf("The volume is %d\n", (sides * sides * sides));

	//save results
	printf("Want to save the results?\n");
	int answer = getIntInput(select, 3);
	if (answer) {
		FILE *f = fopen("random.txt", "a+");
		fprintf(f, "=====\nThe volume is %d\n=====\n", (sides * sides * sides));
	}
}

void raisePower() {
	printf("Please enter base\n");

	char select[10] = {0};
	int base = getIntInput(select, 3);
	

	printf("Please enter power\n");
	int power = getIntInput(select, 3);

	int result = powered(base, power);

	printf("%d raised to the %d power is %d\n", base, power, result);

	//save results
	printf("Want to save the results?\n");
	int answer = getIntInput(select, 10);
	if (answer) {
		FILE *f = fopen("random.txt", "a+");
		fprintf(f, "=====\n%d raised to the %d power is %d\n=====\n", base, power, result);
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