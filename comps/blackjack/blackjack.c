#include "blackjack.h"
 
int main() {
    srand(time(NULL));
    Card *deck = calloc(52, sizeof(Card));
    Player *player = calloc(1, sizeof(Player));
    Player *dealer = calloc(1, sizeof(Player));
   
 
    if (deck == NULL || player == NULL || dealer == NULL) {
        return 1;
    }
   
    /*
    * Create the deck of cards
    * the player objects, and
    * start the main game loop
    */
    if (createDeck(deck) != 0) {
        shutdown(dealer, player, deck);
    }
 
    if(initPlayer(player) == 1) {
        shutdown(dealer, player, deck);
    }    
   
    if (initDealer(dealer) != 0) {
        shutdown(dealer, player, deck);
    }
 
    while(1) {
        if (gameLoop(dealer, player, deck) == -1) {
            break;
        }
 
        // Clear out player data except name
        if (resetGame(dealer, player, deck) != 0) {
            printf("Error restting game\n");
            shutdown(dealer, player, deck);
        }
 
    }
 
    printf("Thanks for playing\n");
 
    // free all of the mallocs
    shutdown(dealer, player, deck);
    return 0;
}
 
int createDeck(Card* deck) {
    /*
    * Instantiates the deck with 13 (2-11) of each
    * of the types of cards(hearts, diamonds, ...)
    */
    char *types[4] = {"Hearts", "Diamonds", "Spades", "Clubs"};
    int values[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};
    char *nameValues[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
 
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            deck->type = types[i];
            deck->value = values[j];
            deck->nameValue = nameValues[j];
            deck->choosen = 0;
            deck++;
        }
    }
    return 0;
}
 
/*
* Create the player instance
* set name and hand score
*/
int initPlayer(Player* player) {
    char *userName = malloc(BUFF_SIZE); // TODO: free at end
    if (userName == NULL) {
        return 1;
    }
    printf("Enter Username: ");
    fgets(userName, BUFF_SIZE, stdin);
    userName[strlen(userName)-1] = '\0';
    player->playerName = userName;
    player->handScore = 0;
    player->counter = 0;
    return 0;
}
 
/*
* do not need to set player name. only
* need to init the score and counter
*/
int initDealer(Player* dealer) {
    dealer->handScore = 0;
    dealer->counter = 0;
    return 0;
}
 
// start the main game loop
int gameLoop(Player *dealer, Player *player, Card *deck) {
 
    /*
    * Deal two cards to player and dealer
    * print both of the player cards but
    * only the last dealer card.
    */
   printUI(dealer, player, deck);
 
    for (int i = 0; i < 2; i++) {
        playerDraw(deck, player, dealer, 0);
        playerDraw(deck, player, dealer, 1);
    }
 
    /*
    * starts the logic of blackjack. The
    * player will hit until stand is called.
    * After that, the dealer will hit until
    * he has at least 17.
    */
    if (hitStandOrQuit(deck, player, dealer) == -1) {
        return -1;
    }
    return 0;
}
 
/*
* Will iterate over the numbers in the
* players current hand array and prints
* out the type and value. The number in
* the array corresponds to a card in the
* deck of cards.
*/
int printHand(Player *player, Card *deck) {
    for (int i = 0; i < player->counter; i++) {
        Card *temp = deck;
        temp += player->currentHand[i];
        printf("    %s of %s\n", temp->nameValue, temp->type);
    }
    return 0;
}
 
int shutdown(Player *dealer, Player *player, Card *deck) {
    free(player->playerName);
    free(player);
    free(deck);
    free(dealer);
    exit(EXIT_SUCCESS);
}
 
/*
* randomly pick a card and check if the card has been drawn
* if not, then add the number to the players current hand,
* and update the players handScore and set the choosen int
* to 1. Else, pick another number.
*/
int  playerDraw(Card *deck, Player *player, Player *dealer, int isDealer) {
    int num = drawNewCard(deck);
 
    if (isDealer) {
    dealer->handScore += deck[num].value;
    dealer->currentHand[dealer->counter] = num;
    dealer->counter++;
 
    if (dealer->handScore > 21) {
        if (numberOfAces(dealer, deck) > 0) {
            dealer->handScore -= 10;
        }
    }
    } else {
        player->handScore += deck[num].value;
        player->currentHand[player->counter] = num;
        player->counter++;
 
        if (player->handScore > 21) {
            if (numberOfAces(player, deck) > 0) {
                player->handScore -= 10;
            }
        }
    }

    printUI(dealer, player, deck);
    sleep(1);
    return num;
}
 
/*
* returns a number from 0 - 51 that
* corresponds to a card in the deck.
*/
int drawNewCard(Card *deck) {
    int num;
    Card *temp = deck;
    while(1) {
        num = randomNum(0,51);
        temp = deck;
        temp += num;;
        if (temp->choosen == 1) {
            continue;
        }
        break;
    }
    deck[num].choosen = 1;
    return num;
}
 
/*
* prompt user to enter 1 of 4 commands
* hit: will draw a new card and update the
* player struct.
*
* stand: will end the players turn
*
* score: will print the players hand score
* and print the cards in the players hand
*
* quit: will end the game
*/
int hitStandOrQuit(Card *deck, Player *player, Player *dealer) {
    while(1) {
        char buffer[BUFF_SIZE] = {0};
 
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strlen(buffer)-1] = '\0';
 
       if (strcmp(buffer, "stand") == 0 || strcmp(buffer, "2") == 0) {
            break;
 
        } else if (strcmp(buffer, "hit") == 0 || strcmp(buffer, "1") == 0) {
            playerDraw(deck, player, dealer, 0);
            if (player->handScore > 21) {
                printLoseUI(dealer, player, deck);
                return 0;
            }
        } else if (strcmp(buffer, "quit") == 0 || strcmp(buffer, "3") == 0) {
            return -1;
        }
    }
 
    while(1) {
        if (dealer->handScore < 17) {
            //printf("Dealer draws: ");
            playerDraw(deck, player, dealer, 1);
        } else { break; }
    }
  
    // check who won
    if (dealer->handScore > player->handScore && dealer->handScore <= 21) {
        printLoseUI(dealer, player, deck);
        return 0;
    } else {
        printWinUI(dealer, player, deck);
        return 0;
    }
    sleep(2);
    return dealer->handScore;
}
 
void printUI(Player *dealer, Player *player, Card *deck) {
    clearTerm();
    printf("****************************************\n");
    printf("***************BlackJACK****************\n");
    printf("****************************************\n");
    printf("\n Dealer Score: %d    ", dealer->handScore);
    printf("%s's Score: %d\n\n",player->playerName, player->handScore);
    printf(" Dealers Hand:\n");
    printHand(dealer, deck);
    printf("\n %s's Hand:\n", player->playerName);
    printHand(player, deck);
    printf("\n[1]hit  [2]stand  [3]quit\n");
 
}

void printWinUI(Player *dealer, Player *player, Card *deck) {
    clearTerm();
    printf("****************************************\n");
    printf("***************BlackJACK****************\n");
    printf("****************************************\n");
    printf("  You Win! You Win! You Win! You Win!\n");
    printf("  You Win! You Win! You Win! You Win!\n");
    printf("\n Dealer Score: %d    ", dealer->handScore);
    printf("%s's Score: %d\n\n",player->playerName, player->handScore);
    printf(" Dealers Hand:\n");
    printHand(dealer, deck);
    printf("\n %s's Hand:\n", player->playerName);
    printHand(player, deck);
    sleep(5);
}

void printLoseUI(Player *dealer, Player *player, Card *deck) {
    clearTerm();
    printf("****************************************\n");
    printf("***************BlackJACK****************\n");
    printf("****************************************\n");
    printf("You Lose! You Lose! You Lose! You Lose!\n");
    printf("You Lose! You Lose! You Lose! You Lose!\n");
    printf("\n Dealer Score: %d    ", dealer->handScore);
    printf("%s's Score: %d\n\n",player->playerName, player->handScore);
    printf(" Dealers Hand:\n");
    printHand(dealer, deck);
    printf("\n %s's Hand:\n", player->playerName);
    printHand(player, deck);
    sleep(5);
}
 
int resetGame(Player *dealer, Player *player, Card *deck) {
    //reset choosen values
    for (int i = 0; i < 51; i++) {
        Card *temp = deck;
        temp += i;
        temp[i].choosen = 0;
        if (temp->nameValue == "Ace") {
            temp->value = 11;
        }
    }

    // reset player structs
    resetPlayer(player);
    resetPlayer(dealer);
    return 0;
}
 
int resetPlayer(Player *player) {
    for (int i = 0; i < player->counter; i++) {
        player->currentHand[i] = 0;
    }
    player->handScore = 0;
    player->counter = 0;
    return 0;
}
 
int numberOfAces(Player *player, Card *deck) {
    int counter = 0;
    for (int i = 0; i < player->counter; i++) {
        Card *temp = deck;
        temp += player->currentHand[i];
        if (temp->value == 11) {
            temp->value = 1;
            counter++;
            break;
        }
    }
    return counter;
}
 
/*
* Returns a random number between the
* lower and upper params that are passed
*/
int randomNum(int lower, int upper) {
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}
 
void clearTerm() {
    printf("\e[1;1H\e[2J");
}