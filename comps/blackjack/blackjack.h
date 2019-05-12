#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
 
#define MAX_CARDS_DRAWN 11
#define BUFF_SIZE 20
 
// structs
typedef struct Player {
    char* playerName;
    int handScore;
    int currentHand[MAX_CARDS_DRAWN];  
    int counter;
} Player;
 
typedef struct Card {
    char* type;
    char* nameValue;
    int value;
    int choosen;
} Card;
 
 
// protos
void createDeck(Card* deck);
int initPlayer(Player* player);
int initDealer(Player* dealer);
int gameLoop(Player *dealer,  Player *player, Card *deck);
int randomNum(int, int);
int drawNewCard(Card *deck);
int randomNum(int, int);
void hit();
void printHand(Player *player, Card *deck);
void shutdown(Player *dealer, Player *player, Card *deck);
int  playerDraw(Card *deck, Player *player, int printCard);
int hitOrStand(Card *deck, Player *player, Player *dealer);
int dealerLoop(Card *deck, Player *dealer);
int resetGame(Player *dealer, Player *player, Card *deck);
int resetPlayer(Player *player);