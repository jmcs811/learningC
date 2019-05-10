#include "blackjack.h"
 
//void createDeck(Card* deck);
// Max num of cards for 2 player
// game is 18 cards.... pretty sure
int previousCards[MAX_CARDS_DRAWN];
 
int main() {
    srand(time(NULL));
    Card *deck = malloc(sizeof(Card)* 52 );
    Player *player = malloc(sizeof(Player));
    Player *dealer = malloc(sizeof(Player));
   
 
    if (deck == NULL || player == NULL || dealer == NULL) {
        return 1;
    }
   
    /*
    * Create the deck of cards
    * the player objects, and
    * start the main game loop
    */
    createDeck(deck);
    if(createPlayer(player) == 1) {
        shutdown(dealer, player, deck);
        return 0;
    }    
    //createPlayer(dealer);
    startGame(dealer, player, deck);
    printHand(player, deck);
    shutdown(dealer, player, deck);
    return 0;
}
 
void shutdown(Player *dealer, Player *player, Card *deck) {
    free(player->playerName);
    free(player);
    free(deck);
    free(dealer);
    return;
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
int createPlayer(Player* player) {
    char *userName = malloc(20); // TODO: free at end
    if (userName == NULL) {
        return 1;
    }
    printf("Enter Username: ");
    scanf("%s", userName);
    player->playerName = userName;
    player->handScore = 0;
    player->counter = 0;
    return 0;
}
 
int createDealer(Player* dealer) {
    // char *dealerName = malloc(7);
    // strcpy(dealer, "dealer\0");
    // dealer->playerName = dealerName;
    dealer->handScore = 0;
    dealer->counter = 0;
    return 0;
}
 
// start the main game loop
int startGame(Player *dealer, Player *player, Card *deck) {
    printf("Welcome to Blackjack!\n");
    printf("Starting Game....\n");
 
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
    * player will hit until stands. After
    * the dealer will hit until he has at
    * least 17
    */
    hitOrStand(deck, player, dealer);
    printf("Thanks for playing\n");
    return 0;
}
 
int  playerDraw(Card *deck, Player *player, int printCard) {
    int num = drawNewCard(deck);
    //printf("%s of %s\n", deck[num].nameValue, deck[num].type);
    player->handScore += deck[num].value;
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
 
void hitOrStand(Card *deck, Player *player, Player *dealer) {
    printf("%s's score is %d\n", player->playerName, player->handScore);
    while(1) {
        char buffer[BUFF_SIZE] = {0};
        printf("Hit or Stand or Score\n");
 
        fgets(buffer, sizeof(buffer), stdin);
        if (strcmp(buffer, "score\n") == 0) {
            printf("%s's score is %d\n", player->playerName, player->handScore);
            printHand(player, deck);
        } else if (strcmp(buffer, "stand\n") == 0) {
            break;
        } else if (strcmp(buffer, "hit\n")== 0) {
            playerDraw(deck, player, 1);
            if (player->handScore > 21) {
                printf("Game Over!\n You Busted!!!\n Your score was %d\n", player->handScore);
                break;
            }
            printf("New score is %d\n", player->handScore);
        }
    }
 
    int dealerScore = dealerLoop(deck, dealer);
 
    // check who won
    if (dealerScore > player->handScore && dealerScore <= 21) {
        printf("Dealer Wins\n You Lose\n You Lose\n You Lose\n You Lose\n");
        return;
    } else {
        printf("You Win!!!\nYou Win!!!\nYou Win!!!\nYou Win!!!\nYou Win!!!\n");
        return;
    }
}
 
int dealerLoop(Card *deck, Player *dealer) {
    while(1) {
        if (dealer->handScore < 17) {
            playerDraw(deck, dealer, 1);
            printf("Dealer draws: %s of %s\n", deck->nameValue, deck->type);
        } else { break; }
    }
    printf("Dealer Score is %d\n", dealer->handScore);
    return dealer->handScore;
}
 
/*
* Will iterate over the numbers in the
* players current hand array and prints
* out the type and value. The number in
* the array corresponds a card in the
* deck of cards.
*/
void printHand(Player *player, Card *deck) {
    printf("***Players Hand***\n");
    for (int i = 0; i <= player->counter-1; i++) {
        Card *temp = deck;
        temp += player->currentHand[i];
        printf("%s of %s\n", temp[i].nameValue, temp[i].type);
    }
    printf("******************\n");
}
 
/*
* Returns a random number between the
* lower and upper params that are passed
*/
int randomNum(int lower, int upper) {
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}