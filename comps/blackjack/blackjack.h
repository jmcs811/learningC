#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

#define MAX_CARDS_DRAWN 18
 
// structs
typedef struct Player {
    char* playerName;
    int handScore;
    int currentHand[11];    
} Player;
 
typedef struct Card {
    char* type;
    int value;
    int choosen;
    char* nameValue;
} Card;
 
 
// protos
void createDeck(Card* deck);
int createPlayer(Player* player);
int startGame(Player *player, Card *deck, Player *dealer);
int randomNum(int, int);
int drawNewCard(Card *deck);
int valueInArray(int, int*);
int randomNum(int, int);
void hit();