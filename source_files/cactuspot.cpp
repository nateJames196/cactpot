/*
	Our names here
	
	cactuspot.cpp
	
	Game summary
*/

void printInstructions();
void playGame();
void displayScore();
int awardPoints(int);

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
				playGame();
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