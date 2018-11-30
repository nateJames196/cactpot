/*
	Our names here

	cactuspot.cpp

	Console based app that allows the player to play the lottery
	game "Cactus pot"
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;


//Function declarations
void displayScore();
int awardPoints(int);
int getScore(int lineChoice, int[][3]);
void printInstructions();
void playGame(int[][3], bool[][3]);
void generateTicket(int[][3], bool[][3]);
void displayTicket(int[][3], bool[][3]);
void endGame(int);
void beginGame(int[][3], bool[][3]);
bool manageHighScore(int, string&);
int lineSelect(int[][3], bool[][3]);
void prepTicket(int[][3], bool[][3]);

//Used to fill in the unrevealed slots on the ticket
const char TEMP_SLOTS[][3] = {
	{'C', 'A', 'C'}, 
	{'T', 'U', 'S'},
	{'P', 'O', 'T'}
};

int main() {
	//Menu management variables
	const int minOP = 1;
	const int maxOP = 4;
	int userOP;

	//Ticket management variables
	int ticket[3][3];
	bool revealed[3][3];
	do {
		cout << "\t\tCactpot Main Menu\n" << endl;
		cout << "1) See Rules" << endl;
		cout << "2) Play Game" << endl;
		cout << "3) See Highest Score" << endl;
		cout << "4) Quit" << endl;
		cin >> userOP;

		switch (userOP) {
		case 1:
			printInstructions();
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
	} while (userOP != maxOP);

	system("pause");
	return 0;
}

void displayScore() {
	int score;
	string userName;
	ifstream infile;  //file open 
	infile.open("highscore.txt");

	if (getline(infile, userName)) {
		infile.ignore();
		infile >> score;

		cout << "Current Highscore: " << score << ", by " << userName << endl;
	}
	else {
		cout << endl << "There Is No Highscore....." << endl << endl;
	}
	infile.close();
}

/*
	int awardPoints(int sum)

	Based on the sum of the numbers in the player's
	selected line, "sum", assigns the player a score.
*/
int awardPoints(int sum) {
	int pointTable[] = { 10000, 36, 720, 360, 80, 252,
	108, 72, 54, 180, 72, 180, 119, 36, 306, 1080,
	144, 1800, 3600 };

	/*
	The payout table starts at 6, so its fine to just
	subtract six to get the value we want
	*/
	int award = pointTable[sum - 6];

	return award;

}

/*
	void printInstructions()

	Prints out the game's instructions to the screen
*/
void printInstructions() {
	cout << "\tRules...\n" << endl;
	cout << "Every lottery ticket has nine cells – a 3x3 matrix, "
		<< "and eight lines – vertical, horizontal, and diagonal. Each "
		<< "cell hides a random number from one to nine – no repeats. "
		<< "When a game starts, eight of these nine numbers are hidden." << endl;
	cout << "1. Select Three Numbers: To begin, you must select "
		<< "three cells from the eight with hidden values on the ticket, "
		<< "and uncover their numbers." << endl;
	cout << "2. Select a Line: Next, the you must select one of eight "
		<< "lines - vertical, horizontal, or diagonal." << endl;
	cout << "3. Receive a Reward: Once you have selected a line, all its "
		<< "numbers are uncovered and you are awarded Gold Point Rewards." << endl;
	cout << "You are able to play as many times as you wish.\n"
		<< "Have Fun!" << endl;
}

/*
	void playGame(int ticket[][3], bool revealed[][3])

	Guides the player through each stage of the game
*/
void playGame(int ticket[][3], bool revealed[][3]) {
	int choice, score;
	//Generate the ticket and then randomly pick a spot to reveal
	generateTicket(ticket, revealed);

	//Prompt the user to pick three cells to reveal
	beginGame(ticket, revealed);

	//Prompt the user to pick one of eight sets of cells, reveal the cells, then return the line number
	choice = lineSelect(ticket, revealed);

	//Based on the line number, get a sum of all numbers in the line, feed it to the awardPoints function, 
	//then return the points awarded
	score = getScore(choice, ticket);

	//Based on the user's points, handle a new high score if necessary, then end the game.
	endGame(score);
}

void beginGame(int ticket[][3], bool revealed[][3]) {
	//Local constants
	string cells[][3] = {
		{"A1", "B1", "C1"},
		{"A2", "B2", "C2"},
		{"A3", "B3", "C3"}
	};
	string prompts[] = { "1st", "2nd", "3rd" };

	//Management variables
	int donetracker;
	string cellchoice;

	//First, display the ticket
	displayTicket(ticket, revealed);

	//Ask the player for three cells
	for (int i = 0; i < 3; i++) {
		//Make sure not to move on until a new cell has been revealed
		do {
			donetracker = -1;
			cout << "Please enter the col# and row# of the " << prompts[i] << " cell you want to reveal: ";
			cin >> cellchoice;
			for (int k = 0; k < 3; k++) {
				for (int j = 0; j < 3; j++) {
					//"cells" and "revealed" are parallel
					if (cellchoice == cells[k][j]) {
						if (!revealed[k][j]) {//if it isn't revealed, reveal it and end the loop
							revealed[k][j] = true;
							donetracker = 1;
							displayTicket(ticket, revealed);
						}
						else {//if it is revealed, 
							cout << "Error ... That cell is already revealed. Please choose a different one." << endl;
							donetracker = 0;
						}
						break;
					}
				}
			}

			//Don't display another error if we already showed one.
			if (donetracker == -1) {
				cout << "Error ... Invalid cell. Please try again." << endl;
			}
		} while (donetracker != 1);
	}
}

int lineSelect(int ticket[][3], bool revealed[][3]) {
	int choice;

	//Prompt the user for their choice of line
	do {
		cout << "Please select from one of the following lines, (1-8):"
			<< "Line 1: Row 1 \nLine 2: Row 2\nLine 3: Row 3\n"
			<< "Line 4: A1, B2, C3\n"
			<< "Line 5: Col A \nLine 6: Col B\nLine 7: Col C\n"
			<< "Line 8: A3, B2, C3";
		cin >> choice;
		if (choice > 8 || choice < 1) {
			cout << "Error ... Invalid line." << endl;
		}
	} while (choice > 8 || choice < 1);

	//Reveal all the cells in the line
	switch (choice) {
	case 1:
	case 2:
	case 3:
		revealed[choice - 1][0] = true;
		revealed[choice - 1][1] = true;
		revealed[choice - 1][2] = true;
	case 4:
		revealed[0][0] = true;
		revealed[1][1] = true;
		revealed[2][2] = true;
	case 5:
	case 6:
	case 7:
		revealed[0][choice - 5] = true;
		revealed[1][choice - 5] = true;
		revealed[2][choice - 5] = true;
	default:
		revealed[0][2] = true;
		revealed[1][1] = true;
		revealed[2][0] = true;
	}
	displayTicket;
	return choice;
}

int getScore(int lineChoice, int ticket[][3]) {
	int sum = 0;

	switch (lineChoice) {
	case 1:
	case 2:
	case 3:
		sum += ticket[lineChoice - 1][0];
		sum += ticket[lineChoice - 1][1];
		sum += ticket[lineChoice - 1][2];
	case 4:
		sum += ticket[0][0];
		sum += ticket[1][1];
		sum += ticket[2][2];
	case 5:
	case 6:
	case 7:
		sum += ticket[0][lineChoice - 5];
		sum += ticket[1][lineChoice - 5];
		sum += ticket[2][lineChoice - 5];
	default:
		sum += ticket[0][2];
		sum += ticket[1][1];
		sum += ticket[2][0];
	}
	return awardPoints(sum);
}

//Generates a new cactus pot ticket
void generateTicket(int ticket[][3], bool revealed[][3]) {
	//random number generator variables
	int random, altrandom;

	int recentNumbers[9], slottedCount = 0, oldSlotted;

	//Get the ticket ready for generation
	prepTicket(ticket, revealed);
	srand(time(NULL));

	//Randomly generate the numbers on the ticket
	cout << endl << endl << "Generating ticket";
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			cout << '.';
			do {
				oldSlotted = slottedCount;
				random = rand() % 10;

				//Check to see if random has been used before
				int j;
				for (j = 0; j < slottedCount; j++) {
					if (random == recentNumbers[j]) {
						j = 99;
					}
				}

				//Normally the loop ends at 9, so a 10 should only occur if it got matched
				if (j < 9) {
					ticket[i][k] = random;
					recentNumbers[slottedCount] = random;
					slottedCount++;
				}
			} while (oldSlotted == slottedCount);//until the number in "slottedCount" changes
		}
	}
	cout << "Done!" << endl << endl;

	//Randomly pick the spot in we want to reveal
	random = rand() % 3;
	altrandom = rand() % 3;
	revealed[random][altrandom] = true;
}

/*
	void prepTicket(int ticket[][3], bool revealed[][3])

	Prepares a newly declared ticket for generation
*/
void prepTicket(int ticket[][3], bool revealed[][3]) {
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			ticket[i][k] = -1;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			revealed[i][k] = false;
		}
	}
}

/*
	void displayTicket(int ticket[][3], bool revealed[][3])

	Displays an existing ticket to the screen with column and row numbers
*/
void displayTicket(int ticket[][3], bool revealed[][3]) {
	cout << "Your Ticket: " << endl;
	cout << "Col#:  A|B|C" << endl;
	cout << "Row#: " << endl;
	for (int i = 0; i < 3; i++) {
		cout << setw(6) << i + 1 << "|";
		for (int k = 0; k < 3; k++) {
			if (revealed[i][k])
				cout << ticket[i][k];
			else
				cout << TEMP_SLOTS[i][k];
			cout << "|";
		}
		cout << endl;
	}
}

/*
	void endGame(int score)

	Checks to see if the user has a high score, and displays a short congratulatory
	message if they do. Ends the ongoing game with a "Game Over" message
*/
void endGame(int score) {
	string name;
	cout << "Final Score: " << score;
	if (manageHighScore(score, name)) {
		cout << "Congratulations, " << name << "!";
	}

	cout << "Game Over.";
	system("pause");
}

//Determines if the player got a highscore, and replaces the old one if needed
bool manageHighScore(int newScore, string& name) {
	int oldScore = -1;
	ifstream infile;
	ofstream outfile;
	infile.open("highscore.txt");

	//Check if we can read from the file
	if (getline(infile, name)) {
		//If we can, grab the score too
		infile.ignore();
		infile >> oldScore;
	}
	infile.close();

	//if the file had nothing in it, oldScore will be -1, which is always less than "newScore"
	if (oldScore < newScore) {
		cout << "You got a new high score! Please enter your name: ";
		getline(cin, name);

		outfile.open("highscore.txt", ios::out);
		outfile << name << endl << newScore;
		return true;
	}
	else {
		return false;
	}
}
