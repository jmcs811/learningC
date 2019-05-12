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
    createDeck(deck);

    if(initPlayer(player) == 1) {
        shutdown(dealer, player, deck);
        return 0;
    }    
    
    initDealer(dealer);

    printf("Welcome to Blackjack!\n");
    printf("Starting Game....\n");
    while(1) {
        if (gameLoop(dealer, player, deck) == -1) {
            break;
        }

        // prints players hand after game is over
        printf("***Players Hand***\n");
        printHand(player, deck);

        // prints dealers hand on exit
        printf("***Dealers Hand***\n");
        printHand(dealer, deck);

        // Clear out player data except name
        resetGame(dealer, player, deck);

    }

    printf("Thanks for playing\n");

    // free all of the mallocs
    shutdown(dealer, player, deck);
    return 0;
}

void createDeck(Card* deck) {
    /*
    * Instantiates the deck with 13 (2-11) of each
    * of the types of cards(hearts, diamonds, ...)
    */
    char *types[4] = {"Hearts", "Diamonds", "Spades", "Clubs"};
    int values[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};
    char *nameValues[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "King", "Queen", "Ace"};
 
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            deck->type = types[i];
            deck->value = values[j];
            deck->nameValue = nameValues[j];
            deck->choosen = 0;
            deck++;
        }
    }
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
    for (int i = 0; i < 2; i++) {
        printf("%s draws: ", player->playerName);
        playerDraw(deck, player, 1);
 
        if (i == 0) {
            printf("Dealer draws: ???\n");
            playerDraw(deck, dealer, 0);
            //sleep(1);
        } else {
            printf("Dealer draws: ");
            playerDraw(deck, dealer, 1);
        }
    }
 
    /*
    * starts the logic of blackjack. The
    * player will hit until stand is called.
    * After that, the dealer will hit until
    * he has at least 17.
    */
    if (hitOrStand(deck, player, dealer) == -1) {
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
void printHand(Player *player, Card *deck) {
    //printf("***Players Hand***\n");
    for (int i = 0; i < player->counter; i++) {
        Card *temp = deck;
        temp += player->currentHand[i];
        printf("%s of %s\n", temp->nameValue, temp->type);
    }
    printf("******************\n");
}
 
void shutdown(Player *dealer, Player *player, Card *deck) {
    free(player->playerName);
    free(player);
    free(deck);
    free(dealer);
    return;
}
 
/*
* randomly pick a card and check if the card has been drawn 
* if not, then add the number to the players current hand, 
* and update the players handScore and set the choosen int 
* to 1. Else, pick another number. 
*/
int  playerDraw(Card *deck, Player *player, int printCard) {
    int num = drawNewCard(deck);

    // check for aces. use 1 if 11 will cause a bust
    if (num == 12 || num == 25 || num == 38 || num == 51) {
        if (player->handScore + 11 > 21) {
            player->handScore += 1;
        } else { player->handScore += deck[num].value; }
    } else {
        player->handScore += deck[num].value;
    }
    
    player->currentHand[player->counter] = num;
    player->counter++;
    if (printCard == 1) {
        printf("%s of %s\n", deck[num].nameValue, deck[num].type);
    }
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
* prompt user to enter 1 of 3 commands
* hit: will draw a new card and update the
* player structre. 
*
* stand: will end the players turn
*
* score: will print the players hand score
* and print the cards in the players hand
*/
int hitOrStand(Card *deck, Player *player, Player *dealer) {
    printf("%s's score is %d\n", player->playerName, player->handScore);
    while(1) {
        printf("hit or stand or score or quit\n");
        char buffer[BUFF_SIZE] = {0};
 
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strlen(buffer)-1] = '\0';

        if (strcmp(buffer, "score") == 0) {
            printf("%s's score is %d\n", player->playerName, player->handScore);
            printHand(player, deck);

        } else if (strcmp(buffer, "stand") == 0) {
            break;

        } else if (strcmp(buffer, "hit") == 0) {
            playerDraw(deck, player, 1);
            if (player->handScore > 21) {
                printf("Game Over!\n You Busted!!!\n Your score was: %d\n \
                Dealers score was: %d\n", player->handScore, dealer->handScore);
                return 0;
            }
            printf("New score is %d\n", player->handScore);

        } else if (strcmp(buffer, "quit") == 0) {
            return -1;
        }
    }
 
    int dealerScore = dealerLoop(deck, dealer);
 
    // check who won
    if (dealerScore > player->handScore && dealerScore <= 21) {
        printf("Dealer Wins\n You Lose\n You Lose\n You Lose\n You Lose\n");
        return 0;
    } else {
        printf("You Win!!!\nYou Win!!!\nYou Win!!!\nYou Win!!!\nYou Win!!!\n");
        return 0;
    }
    sleep(2);
    return 0;
}

/*
* if the dealers hand score is under 17
* the dealer will continue to draw until
* he is over 17 or he busts
*/
int dealerLoop(Card *deck, Player *dealer) {
    while(1) {
        if (dealer->handScore < 17) {
            printf("Dealer draws: ");
            playerDraw(deck, dealer, 1);
        } else { break; }
    }
    printf("Dealer Score is %d\n", dealer->handScore);
    return dealer->handScore;
}

int resetGame(Player *dealer, Player *player, Card *deck) {
    //reset choosen values
    for (int i = 0; i < 52; i++) {
        Card *temp = deck;
        temp += i;
        temp[i].choosen = 0;
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
 
/*
* Returns a random number between the
* lower and upper params that are passed
*/
int randomNum(int lower, int upper) {
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}