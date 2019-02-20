#include <stdlib.h>
#include <stdio.h>

//102_1
int power(int base, int exponet) {
    if (exponet == 0) {
        return 1;
    } else {
        return base * power(base, exponet - 1);
    }
}

//102_1
int add(int a, int b) {
    return a + b;
}

//102_2
//char *str[strlength], int #ofstrings
void printString(char* str[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", str[i]);
    }
}

//102_5
void getUserInput(char finalString[], int length) {

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
//102_6
// void flushStdIn() {

// }