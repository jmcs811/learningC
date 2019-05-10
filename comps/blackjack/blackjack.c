#include "blackjack.h"
#include "time.h"
 
//void createDeck(Card* deck);
// Max num of cards for 2 player
// game is 18 cards.... pretty sure
int previousCards[MAX_CARDS_DRAWN];
 
int main() {
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
		shutdown(player, deck, dealer);
        return;
    }    
    //createPlayer(dealer);
    startGame(player, deck, dealer);
}

void shutdown(Player *player, Card *deck, Player *dealer) {
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
 
    // deck = deck - 52;
    // for (int i = 0; i < 52; i++) {
    //     printf(deck->type);
    //     printf(deck->nameValue);
    //     deck++;
    // }
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

	return 0;
} 

int createDealer(Player* dealer) {
    char *dealerName = "Big Dick Bret";
    dealer->playerName = dealerName;
    dealer->handScore = 0;

	return 0;
} 

// start the main game loop
int startGame(Player *player, Card *deck, Player *dealer) {
    int counter = 0;
    int deckIndex;
    printf("Welcome to Blackjack!\n");
    printf("Starting Game....\n");

    // TODO: deal 2 cards to player
	// grab random element from deck
	// add to players total / set choosen to 1
	// grab another random element from deck
	// add to players total / set choosen to 1
    for (int i = 0; i < 2; i++) {
        playerDraw(deck, player);
		sleep(1);
        dealerDraw(deck, dealer);
		sleep(1);
    }

    printf("%d\n", player->handScore);
    printf("%d\n", dealer->handScore);

    // TODO: deal 2 cards to dealer
    
    // TODO:hit or standloop
    while(1) {
        printf("Hit or stand?\n");
        break;
    }

    /*
    * if dealer is under 17
    * keep hitting until he is 
    * over 17
    */
   
    printf("Thanks for playing\n");
}

void dealerDraw(Card *deck, Player *dealer) {
	int num = drawNewCard(deck);
	printf("%s of %s\n", deck[num].nameValue, deck[num].type);
	dealer->handScore += deck[num].value;
}

void playerDraw(Card *deck, Player *player) {
    int num = drawNewCard(deck);
    printf("%s of %s\n", deck[num].nameValue, deck[num].type);
    //player->handScore = player->handScore + deck[num].value;
	player->handScore += deck[num].value;
}

/*
* returns a number from 0 - 51 that 
* corresponds to a card in the deck.
* It checks if that number has been
* previously drawn if it hasn't add 
* it to the array of previously drawn
* cards and return the choosen value.
* Else, break
*/
int drawNewCard(Card *deck) {
    int num;
    while(1) {
        num = randomNum(0,51);
		Card *temp = deck;
		temp += num;;
        if (deck->choosen == 1) {
            printf("dupe\n");
            continue;
        }
        break;
    }
    return num;
}

void hit() {

}

/*
* Will iterate over the numbers in the 
* players current hand array and prints
* out the type and value. The number in
* the array corresponds a card in the 
* deck of cards.
*/
void printHand(int arr[], Card* deck) {
    for (int i = 0; i <= MAX_CARDS_DRAWN; i++) {
        printf("%s", deck[i].type);
    }
}


/*
* when given an int and and int array
* this function returns 1 if the given
* int is in the array. If not it returns 0
*/
int valueInArray(int value, int arr[]) {
    for (int i = 0; i < MAX_CARDS_DRAWN; i++) {
        if (arr[i] == value) {return 1;}
    }
    return 0;
}
 
/*
* Returns a random number between the
* lower and upper params that are passed
*/
int randomNum(int lower, int upper) {
    srand(time(NULL));
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}