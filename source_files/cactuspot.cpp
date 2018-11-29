/*
	Our names here
	
	cactuspot.cpp
	
	Game summary
*/

void displayScore();
int awardPoints(int);
int getScore(int lineChoice);
void printInstructions();
void playGame(int[][3], bool[][3]);
void generateTicket(int[][3], bool[][3]);
void displayTicket(int[][3], bool[][3]);
void endGame(int);
bool manageHighScore(int);



int main() {
	int ticket[3][3], revealed[3][3];
	const minOP = 1;
	const maxOP =4;
	int userOP;
	do {
		cout << "\t\tCactpot Main Menu\n"" << endl;
		cout<< "1) See Rules" << endl;
		cout << "2) Play Game" << endl;
		cout << "3)See Highest Score" << endl;
		cout << "4)Quit" << endl;
		cin >> userOP
		
		switch(userOP) {
			case 1:
				printInstruction();
				break;
			case 2:
				playGame(ticket, revealed);
				break;
			case 3:
				displayScore();
				break;
			case 4:
				cout << "Quitting game...";
				break;
			default:
				cout << "Error. Must choose from 1 to 4.";
				break;
		}
	} while(userOP != maxOP);
	
	system("pause");
	return 0;
}

void displayScore() {
	
	//TODO
	
}

/*
	int awardPoints(int sum)

	Based on the sum of the numbers in the player's 
	selected line, "sum", assigns the player a score. 
*/
int awardPoints(int sum) {
	int pointTable[] = {10000, 36, 720, 360, 80, 252, 
	108, 72, 54, 180, 72, 180, 119, 36, 306, 1080, 
	144, 1800, 3600};

	/*
	The payout table starts at 6, so its fine to just
	subtract six to get the value we want
	*/
	int award = pointTable[sum - 6];

	return award;

}

int getScore(int lineChoice) {
	int sum;
	
	//TODO: determine the sum, given line choice
	
	awardPoints;
}

void printInstructions() {
	cout << "\tRules...\n" endl;
	cout << "Every lottery ticket has nine cells – a 3x3 matrix, "
	<< "and eight lines – vertical, horizontal, and diagonal. Each "
	<< "cell hides a random number from one to nine – no repeats. "
	<< "When a game starts, eight of these nine numbers are hidden." << endl;
	cout << "1. Select Three Numbers: To begin, you must select "
	<< "three cells from the eight with hidden values on the ticket, "
	<< "and uncover their numbers." << endl;
	cout << "2. Select a Line: Next, the you must select one of eight "
	<< "lines ─ vertical, horizontal, or diagonal." << endl;
	cout << "3. Receive a Reward: Once you have selected a line, all its "
	<< "numbers are uncovered and you are awarded Gold Point Rewards." << endl;
	cout << "You are able to play as many times as you wish.\n" 
	<< "Have Fun!" << endl;
}

void playGame(ticket[][3], revealed[][3]) {
	int lnChoice, score;
	//Generate the ticket and then randomly pick a spot to reveal
	generateTicket(ticket, revealed);
	
	//Prompt the user to pick three cells to reveal
	gameBegin();
	
	//Prompt the user to pick one of eight sets of cells, reveal the cells, then return the line number
	lnChoice = lineSelect();
	
	//Based on the line number, get a sum of all numbers in the line, feed it to the awardPoints function, 
	//then return the points awarded
	score = getScore(lnChoice);
	
	//Based on the user's points, handle a new high score if necessary, then end the game.
	endGame(Score);
}

void prepTicket(int ticket[][3], bool revealed[][3]) {
	for (int i = 0;i < 3;i++) {
		for (int k = 0;k < 3;k++) {
			ticket[i][k] = -1;
		}
	}
	
	for (int i = 0;i < 3;i++) {
		for (int k = 0;k < 3;k++) {
			revealed[i][k] = false;
		}
	}
}

//Generates a new cactus pot ticket
void generateTicket(int ticket[][3], bool revealed[][3]) {
	//random number generator variables
	int random, altrandom;
	
	//
	int recentNumbers[9], slottedCount = 0, oldSlotted;
	
	//Get the ticket ready for generation
	prepTicket(ticket, revealed);
	srand(time(NULL));
	
	//Randomly generate the numbers on the ticket
	for (int i = 0;i < 3;i++) {
		for (int k = 0;k < 3;k++) {
			if (ticket[i][k] == 1) {
				do {
					oldSlotted = slottedCount
					random = rand() % 10;
					
					//Check to see if random has been used before
					for (int j = 0;j < slottedCount;j++) {
						if (random == recentNumbers[j]) {
							j = 10;
						}
					}
				
					//Normally the loop ends at 9, so a 10 should only occur if it got matched
					if (j != 10) {
						tickets[i][k] = random;
						recentNumbers[slottedCount] = random;
						slottedCount++;
					}
				} while (oldSlotted == slottedCount);//until the number in "slottedCount" changes
			}
		}
	}
	
	//Randomly pick the spot in we want to reveal
	random = rand() % 3;
	altrandom = rand() % 3;
	revealed[random][altrandom] = true;
}

//Displays the game ticket to the console
void displayTicket(ticket[][3], revealed[][3]) {
	//TODO
}


void displayHighScore();

void displayHighScore() {
	//Some code
}



void endGame(int score) {
	if (manageHighScore(score)) {
		cout << "Congratulations you got the new high score!";
	}
	
	cout << "Game 0ver.";
	system("pause");
}

//Determines if the player got a highscore, and replaces the old one if needed
bool manageHighScore(int newScore) {
	//TODO
}