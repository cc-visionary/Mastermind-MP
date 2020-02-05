/*
	Name   : LIM, Christopher Go
	ID No. : 11935103
	Block  : S-14

	To compile the program:             enter "gcc mastermind.c -o mastermind -lwinmm" on the command line where the file is located
	To run the program after compiling: enter "mastermind" on the command line where the file is located

	Additional Note: Please make the command line in Full Screen when running the program since it is designed to be that way
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <MMsystem.h>
#include <time.h>

// Colors
#define WHITE    "\033[01;37m" // 0
#define BLUE     "\033[22;34m" // 1
#define GREEN    "\033[22;32m" // 2
#define CYAN     "\033[22;36m" // 3
#define RED      "\033[22;31m" // 4
#define MAGENTA  "\033[22;35m" // 5
#define BROWN    "\033[22;33m" // 6
#define ORANGE   "\033[01;31m" // 7
#define YELLOW   "\033[01;33m" // 8
#define LIME     "\033[01;32m" // 9
#define GRAY     "\033[01;30m" // 10

void welcomeScreen(); // runs a graphical animation w/ music for welcome screen/splashscreen (runs at the start of the program)
int  menuOptions(); // shows the ascii art of menu options
void playGame(int players, int guesses, int* nPegs); // runs the mastermind game
int  guessChecker(int guess, int code, int* nPegs); // checks the guess and outputs the color derived from the number inputed by the user and shows the score
void resultScreen(int player); // shows the players who won or no one won if no one won at all. [further update: show full mastermind board of each player]
void editSettings(int* players, int* guesses, int* nPegs); // enables you to edit the settings
void changeColor(int digit, int* nPegs); // changes the text color of console depending on color code
void endProgram(); // runs a graphical animation w/ music for ending the program (runs at the end of the program)

int main() {
	srand(time(0));
	int nMenuOption; // stores the value of the menu option
	int nGuesses = 10, nPlayers = 2;  // stores the value of number of guesses and players
	int run = 1;  // flag for checking if the program will continue or not
	int nPegs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // stores the corresponding number for each color
	welcomeScreen(); // this shows a visually appealing welcome screen
	while(run) {
		nMenuOption = menuOptions();  
		if(nMenuOption == 1) { // Game
			playGame(nPlayers, nGuesses, nPegs);
		} else if(nMenuOption == 2) { // Settings
			editSettings(&nPlayers, &nGuesses, nPegs);
		} else if(nMenuOption == 3) {
			endProgram();
			run = 0;
		}
	}
	changeColor(0, 0); // sets the console text color to white
	
	return 0;
}

int menuOptions() {
	int option;

	system("cls");
	// output:
	// What do you want to do?
	//  1 - New Game
	//  2 - Settings
	//  3 - Exit
	printf(" _    _ _           _         _                                                 _     _              _      ___  \n");
	printf("| |  | | |         | |       | |                                               | |   | |            | |    |__ \\ \n");
	printf("| |  | | |__   __ _| |_    __| | ___    _   _  ___  _   _  __      ____ _ _ __ | |_  | |_ ___     __| | ___   ) |\n");
	printf("| |/\\| | '_ \\ / _` | __|  / _` |/ _ \\  | | | |/ _ \\| | | | \\ \\ /\\ / / _` | '_ \\| __| | __/ _ \\   / _` |/ _ \\ / / \n");
	printf("\\  /\\  / | | | (_| | |_  | (_| | (_) | | |_| | (_) | |_| |  \\ V  V / (_| | | | | |_  | || (_) | | (_| | (_) |_|  \n");
	printf(" \\/  \\/|_| |_|\\__,_|\\__|  \\__,_|\\___/   \\__, |\\___/ \\__,_|   \\_/\\_/ \\__,_|_| |_|\\__|  \\__\\___/   \\__,_|\\___/(_)  \n");
	printf("                                         __/ |                                                                   \n");
	printf("                                        |___/                                                                    \n");
	Sleep(500);
	printf("    __             _   _                 _____                                                                   \n");
	printf("   /  |           | \\ | |               |  __ \\                                                                  \n");
	printf("   `| |   ______  |  \\| | _____      __ | |  \\/ __ _ _ __ ___   ___                                              \n");
	printf("    | |  |______| | . ` |/ _ \\ \\ /\\ / / | | __ / _` | '_ ` _ \\ / _ \\                                             \n");
	printf("   _| |_          | |\\  |  __/\\ V  V /  | |_\\ \\ (_| | | | | | |  __/                                             \n");
	printf("   \\___/          \\_| \\_/\\___| \\_/\\_/    \\____/\\__,_|_| |_| |_|\\___|                                             \n");
	printf("                                                                                                                 \n");
	Sleep(500);
	printf("                                                                                                                 \n");
	printf("    _____            _____      _   _   _                                                                        \n");
	printf("   / __  \\          /  ___|    | | | | (_)                                                                       \n");
	printf("   `' / /'  ______  \\ `--.  ___| |_| |_ _ _ __   __ _ ___                                                        \n");
	printf("     / /   |______|  `--. \\/ _ \\ __| __| | '_ \\ / _` / __|                                                       \n");
	printf("   ./ /___          /\\__/ /  __/ |_| |_| | | | | (_| \\__ \\                                                       \n");
	printf("   \\_____/          \\____/ \\___|\\__|\\__|_|_| |_|\\__, |___/                                                       \n");
	printf("                                                 __/ |                                                           \n");
	printf("                                                |___/                                                            \n");
	Sleep(500);
	printf("    _____            _____     _ _                                                                               \n");
	printf("   |____ |          |  ___|   (_) |                                                                              \n");
	printf("       / /  ______  | |____  ___| |_                                                                             \n");
	printf("       \\ \\ |______| |  __\\ \\/ / | __|                                                                            \n");
	printf("   .___/ /          | |___>  <| | |_                                                                             \n");
	printf("   \\____/           \\____/_/\\_\\_|\\__|                                                                            \n");  
	Sleep(500);
	printf("\n\n"); 

	do {
		printf("Menu Option: ");
		scanf("%d", &option);
	} while(option < 1 || option > 3);
	PlaySound("songs\\menu_select.wav", NULL, SND_FILENAME | SND_ASYNC);

	return option;
}

void playGame(int players, int guesses, int* nPegs) {
	int nCode = 0; // stores the randomized code
	int noWinner = 1; // flag for checking if there is a winner or not
	int nGuess = 1111;   // problem occurs when the values guesses and players is changed in Settings
	int i, j, temp, multiplier; // iterator 1, iterator 2, temporary variable, multiplier for code generator and hint generator 
	char* wColors[] = {"White", "Blue", "Green", "Cyan", "Red", "Magenta", "Brown", "Orange", "Yellow", "Lime", "Gray"}; // stores peg color name
	char* color; // temporary color
	// nCode = rand() % 10000 doesn't work well because sometimes the answer becomes only upto the hundredths place
	for(i = 0, multiplier = 1; i < 4; i++, multiplier *= 10) nCode += (rand() % 9 + 1) * multiplier;
	system("cls");
	printf("Colors:"); // loops color choice (in order even though the peg numbers have been changed)
	for(i = 1; i <= 9; i++) {
		temp = -1;
		for(j = 0; j < 9 && temp == -1; j++) if(nPegs[j] == i) temp = j;
		switch(temp) {
			case 0: color = BLUE; break;
			case 1: color = GREEN; break;
			case 2: color = CYAN; break;
			case 3: color = RED; break;
			case 4: color = MAGENTA; break;
			case 5: color = BROWN; break;
			case 6: color = ORANGE; break;
			case 7: color = YELLOW; break;
			case 8: color = LIME; break;
		}
		printf(" %s (%d) %s", color, nPegs[temp], wColors[temp + 1]);
		if(i != 9) printf(",");
		else printf("\n%s", WHITE);
	}
	printf("Reveal Option: 0\n");
	multiplier = 1000;
	for(int i = 0; i < guesses && noWinner; i++) {
		printf("Guess %d/%d:\n", i + 1, guesses);
		for(int p = 0; p < players && noWinner; p++) { // loops to get guesses of players based 
			do {
				if(nGuess == 0) {
					if(multiplier == 0) {
						printf("No more hint available\n");
					} else {
						if(multiplier == 1000) printf("\t\tCode: %d***\n", nCode / multiplier);
						else if(multiplier == 100) printf("\t\tCode: %d**\n", nCode / multiplier);
						else if(multiplier == 10) printf("\t\tCode: %d*\n", nCode / multiplier);
						else if(multiplier == 1) printf("\t\tCode: %d\n", nCode / multiplier);
						multiplier /= 10;
					}				
				}
				else if(nGuess <= 1000 || nGuess >= 10000 || nGuess % 1000 / 100 == 0 || nGuess % 100 / 10 == 0 || nGuess % 10 == 0) PlaySound("songs\\error.wav", NULL, SND_FILENAME | SND_ASYNC);
				printf("  Player %d: ", p + 1); // on how many players there are
				scanf("%d", &nGuess);
			} while(nGuess <= 1000 || nGuess >= 10000 || nGuess % 1000 / 100 == 0 || nGuess % 100 / 10 == 0 || nGuess % 10 == 0);
			if(guessChecker(nGuess, nCode, nPegs)) { // checks guess if correct and outputs the score
				PlaySound("songs\\win.wav", NULL, SND_FILENAME | SND_ASYNC); // play win soundsystem("color F0");
				resultScreen(p + 1);
				Sleep(100);
				system("color 30");
				Sleep(100);
				system("color 60");
				Sleep(100);
				system("color C0");
				Sleep(100);
				system("color B0");
				Sleep(100);
				system("color 10");
				Sleep(100);
				printf("\n\n\t\t\t\t\t\t\t\t\tThe code is [ (%d) %s . (%d) %s . (%d) %s . (%d) %s ]\n", nCode / 1000, wColors[nPegs[nCode / 1000] + 1], nCode % 1000 / 100, 
					wColors[nPegs[nCode % 1000 / 100] + 1], nCode % 100 / 10, wColors[nPegs[nCode % 100 / 10] + 1], nCode % 10, wColors[nPegs[nCode % 10] + 1]);
				system("color 80");
				Sleep(100);
				system("color 90");
				Sleep(100);
				system("color 70");
				Sleep(100);
				system("color D0");
				printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\tWon in %d Guess(es)\n", i + 1);
				noWinner = 0;
				Sleep(100);
				system("color 50");
				Sleep(100);
				system("color E0");
				Sleep(100);
				system("color 20");
				Sleep(100);
				system("color A0");
				Sleep(100);
				system("color 0F");
				Sleep(5000);
			} else {
				if(i == guesses - 1 && p == players - 1) {
					PlaySound("songs\\no_win.wav", NULL, SND_FILENAME | SND_ASYNC); // play lose sound
					resultScreen(0);
					printf("\n\n\t\t\t\t\t\t\t\t\tThe code is [ (%d) %s . (%d) %s . (%d) %s . (%d) %s ]\n", nCode / 1000, wColors[nPegs[nCode / 1000] + 1], nCode % 1000 / 100, 
						wColors[nPegs[nCode % 1000 / 100] + 1], nCode % 100 / 10, wColors[nPegs[nCode % 100 / 10] + 1], nCode % 10, wColors[nPegs[nCode % 10] + 1]);
					noWinner = 0;
					Sleep(5000);
				}
			}
		}
	}
}

void editSettings(int* players, int* guesses, int* nPegs) {
	int nSettingsOption;
	int invalid; // invalid flag for color assignment
	int isNumAvail[] = {1, 1, 1, 1, 1, 1, 1, 1, 1}; // number flag to avoid repeatable values in colors assignment
	// output:
	// Settings Options:
	//  1 - Number of Guesses
	//  2 - Number of Players
	//  3 - Change Peg Colors
	//  4 - Exit
	system("cls");
	printf(" _____      _   _   _                   _____       _   _                                                   \n");
	printf("/  ___|    | | | | (_)                 |  _  |     | | (_)                _                                 \n");
	printf("\\ `--.  ___| |_| |_ _ _ __   __ _ ___  | | | |_ __ | |_ _  ___  _ __  ___(_)                                \n");
	printf(" `--. \\/ _ \\ __| __| | '_ \\ / _` / __| | | | | '_ \\| __| |/ _ \\| '_ \\/ __|                                  \n");
	printf("/\\__/ /  __/ |_| |_| | | | | (_| \\__ \\ \\ \\_/ / |_) | |_| | (_) | | | \\__ \\_                                 \n");
	printf("\\____/ \\___|\\__|\\__|_|_| |_|\\__, |___/  \\___/| .__/ \\__|_|\\___/|_| |_|___(_)                                \n");
	printf("                             __/ |           | |                                                            \n");
	printf("                            |___/            |_|                                                            \n");
	Sleep(500);
	printf("    __             _   _                 _                        __   _____                                \n");
	printf("   /  |           | \\ | |               | |                      / _| |  __ \\                               \n");
	printf("   `| |   ______  |  \\| |_   _ _ __ ___ | |__   ___ _ __    ___ | |_  | |  \\/_   _  ___  ___ ___  ___  ___  \n");
	printf("    | |  |______| | . ` | | | | '_ ` _ \\| '_ \\ / _ \\ '__|  / _ \\|  _| | | __| | | |/ _ \\/ __/ __|/ _ \\/ __| \n");
	printf("   _| |_          | |\\  | |_| | | | | | | |_) |  __/ |    | (_) | |   | |_\\ \\ |_| |  __/\\__ \\__ \\  __/\\__ \\ \n");
	printf("   \\___/          \\_| \\_/\\__,_|_| |_| |_|_.__/ \\___|_|     \\___/|_|    \\____/\\__,_|\\___||___/___/\\___||___/ \n");
	printf("                                                                                                            \n");
	Sleep(500);
	printf("                                                                                                            \n");
	printf("    _____            _   _                 _                        __  ______ _                            \n");
	printf("   / __  \\          | \\ | |               | |                      / _| | ___ \\ |                           \n");
	printf("   `' / /'  ______  |  \\| |_   _ _ __ ___ | |__   ___ _ __    ___ | |_  | |_/ / | __ _ _   _  ___ _ __ ___  \n");
	printf("     / /   |______| | . ` | | | | '_ ` _ \\| '_ \\ / _ \\ '__|  / _ \\|  _| |  __/| |/ _` | | | |/ _ \\ '__/ __| \n");
	printf("   ./ /___          | |\\  | |_| | | | | | | |_) |  __/ |    | (_) | |   | |   | | (_| | |_| |  __/ |  \\__ \\ \n");
	printf("   \\_____/          \\_| \\_/\\__,_|_| |_| |_|_.__/ \\___|_|     \\___/|_|   \\_|   |_|\\__,_|\\__, |\\___|_|  |___/ \n");
	printf("                                                                                        __/ |               \n");
	printf("                                                                                       |___/                \n");
	Sleep(500);
	printf("    _____            _____ _                             ______            _____       _                    \n");
	printf("   |____ |          /  __ \\ |                            | ___ \\          /  __ \\     | |                   \n");
	printf("       / /  ______  | /  \\/ |__   __ _ _ __   __ _  ___  | |_/ /__  __ _  | /  \\/ ___ | | ___  _ __ ___     \n");
	printf("       \\ \\ |______| | |   | '_ \\ / _` | '_ \\ / _` |/ _ \\ |  __/ _ \\/ _` | | |    / _ \\| |/ _ \\| '__/ __|    \n");
	printf("   .___/ /          | \\__/\\ | | | (_| | | | | (_| |  __/ | | |  __/ (_| | | \\__/\\ (_) | | (_) | |  \\__ \\    \n");
	printf("   \\____/            \\____/_| |_|\\__,_|_| |_|\\__, |\\___| \\_|  \\___|\\__, |  \\____/\\___/|_|\\___/|_|  |___/    \n");
	printf("                                              __/ |                 __/ |                                   \n");
	printf("                                             |___/                 |___/                                    \n");
	Sleep(500);
	printf("      ___            _____     _ _                                                                          \n");
	printf("     /   |          |  ___|   (_) |                                                                         \n");
	printf("    / /| |  ______  | |____  ___| |_                                                                        \n");
	printf("   / /_| | |______| |  __\\ \\/ / | __|                                                                       \n");
	printf("   \\___  |          | |___>  <| | |_                                                                        \n");
	printf("       |_/          \\____/_/\\_\\_|\\__|                                                                       \n");
	Sleep(500);                                                                                                           
	                                                                                                           
	do {
		printf("\n\nSettings Option: ");
		scanf("%d", &nSettingsOption);
	} while(nSettingsOption < 1 || nSettingsOption > 4);
	system("cls");
	if(nSettingsOption == 1) {
		// output: Enter Number of Guesses:
		printf(" _____      _              _   _                 _                        __   _____                                   \n");
		printf("|  ___|    | |            | \\ | |               | |                      / _| |  __ \\                                _ \n");
		printf("| |__ _ __ | |_ ___ _ __  |  \\| |_   _ _ __ ___ | |__   ___ _ __    ___ | |_  | |  \\/_   _  ___  ___ ___  ___  ___  (_)\n");
		printf("|  __| '_ \\| __/ _ \\ '__| | . ` | | | | '_ ` _ \\| '_ \\ / _ \\ '__|  / _ \\|  _| | | __| | | |/ _ \\/ __/ __|/ _ \\/ __|    \n");
		printf("| |__| | | | ||  __/ |    | |\\  | |_| | | | | | | |_) |  __/ |    | (_) | |   | |_\\ \\ |_| |  __/\\__ \\__ \\  __/\\__ \\  _ \n");
		printf("\\____/_| |_|\\__\\___|_|    \\_| \\_/\\__,_|_| |_| |_|_.__/ \\___|_|     \\___/|_|    \\____/\\__,_|\\___||___/___/\\___||___/ (_)\n\n\n");
		scanf("%d", guesses);
	} else if(nSettingsOption == 2) {
		// output: Enter Number of Players:
		printf(" _____      _              _   _                 _                        __  ______ _                               \n");
		printf("|  ___|    | |            | \\ | |               | |                      / _| | ___ \\ |                            _ \n");
		printf("| |__ _ __ | |_ ___ _ __  |  \\| |_   _ _ __ ___ | |__   ___ _ __    ___ | |_  | |_/ / | __ _ _   _  ___ _ __ ___  (_)\n");
		printf("|  __| '_ \\| __/ _ \\ '__| | . ` | | | | '_ ` _ \\| '_ \\ / _ \\ '__|  / _ \\|  _| |  __/| |/ _` | | | |/ _ \\ '__/ __|    \n");
		printf("| |__| | | | ||  __/ |    | |\\  | |_| | | | | | | |_) |  __/ |    | (_) | |   | |   | | (_| | |_| |  __/ |  \\__ \\  _ \n");
		printf("\\____/_| |_|\\__\\___|_|    \\_| \\_/\\__,_|_| |_| |_|_.__/ \\___|_|     \\___/|_|   \\_|   |_|\\__,_|\\__, |\\___|_|  |___/ (_)\n");
		printf("                                                                                              __/ |                  \n");
		printf("                                                                                             |___/                   \n\n\n");
		scanf("%d", players);
	} else if(nSettingsOption == 3) {
		invalid = 1;
		do {
			printf("%s Enter Color for Blue: ", BLUE);
			scanf("%d", &nPegs[0]);
			if(nPegs[0] < 1 || nPegs[0] > 9) printf("Number can only be from 1-9.\n\n");
			else {
				if(isNumAvail[nPegs[0] - 1] == 0) printf("Number already taken by other color.\n\n");
				else invalid = 0;
			}
		} while(invalid);
		isNumAvail[nPegs[0] - 1] = 0;
		
		invalid = 1;
		do {
			printf("%s Enter Color for Green: ", GREEN);
			scanf("%d", &nPegs[1]);
			if(nPegs[1] < 1 || nPegs[1] > 9) printf("Number can only be from 1-9.\n\n");
			else {
				if(isNumAvail[nPegs[1] - 1] == 0) printf("Number already taken by other color.\n\n");
				else invalid = 0;
			}
		} while(invalid);
		isNumAvail[nPegs[1] - 1] = 0;

		invalid = 1;
		do {
			printf("%s Enter Color for Cyan: ", CYAN);
			scanf("%d", &nPegs[2]);
			if(nPegs[2] < 1 || nPegs[2] > 9) printf("Number can only be from 1-9.\n\n");
			else {
				if(isNumAvail[nPegs[2] - 1] == 0) printf("Number already taken by other color.\n\n");
				else invalid = 0;
			}
		} while(invalid);
		isNumAvail[nPegs[2] - 1] = 0;

		invalid = 1;
		do {
			printf("%s Enter Color for Red: ", RED);
			scanf("%d", &nPegs[3]);
			if(nPegs[3] < 1 || nPegs[3] > 9) printf("Number can only be from 1-9.\n\n");
			else {
				if(isNumAvail[nPegs[3] - 1] == 0) printf("Number already taken by other color.\n\n");
				else invalid = 0;
			}
		} while(invalid);
		isNumAvail[nPegs[3] - 1] = 0;

		invalid = 1;
		do {
			printf("%s Enter Color for Magenta: ", MAGENTA);
			scanf("%d", &nPegs[4]);
			if(nPegs[4] < 1 || nPegs[4] > 9) printf("Number can only be from 1-9.\n\n");
			else {
				if(isNumAvail[nPegs[4] - 1] == 0) printf("Number already taken by other color.\n\n");
				else invalid = 0;
			}
		} while(invalid);
		isNumAvail[nPegs[4] - 1] = 0;

		invalid = 1;
		do {
			printf("%s Enter Color for Brown: ", BROWN);
			scanf("%d", &nPegs[5]);
			if(nPegs[5] < 1 || nPegs[5] > 9) printf("Number can only be from 1-9.\n\n");
			else {
				if(isNumAvail[nPegs[5] - 1] == 0) printf("Number already taken by other color.\n\n");
				else invalid = 0;
			}
		} while(invalid);
		isNumAvail[nPegs[5] - 1] = 0;
		
		invalid = 1;
		do {
			printf("%s Enter Color for Orange: ", ORANGE);
			scanf("%d", &nPegs[6]);
			if(nPegs[6] < 1 || nPegs[6] > 9) printf("Number can only be from 1-9.\n\n");
			else {
				if(isNumAvail[nPegs[6] - 1] == 0) printf("Number already taken by other color.\n\n");
				else invalid = 0;
			}
		} while(invalid);
		isNumAvail[nPegs[6] - 1] = 0;

		invalid = 1;
		do {
			printf("%s Enter Color for Yellow: ", YELLOW);
			scanf("%d", &nPegs[7]);
			if(nPegs[7] < 1 || nPegs[7] > 9) printf("Number can only be from 1-9.\n\n");
			else {
				if(isNumAvail[nPegs[7] - 1] == 0) printf("Number already taken by other color.\n\n");
				else invalid = 0;
			}
		} while(invalid);
		isNumAvail[nPegs[7] - 1] = 0;

		invalid = 1;
		do {
			printf("%s Enter Color for Lime: ", LIME);
			scanf("%d", &nPegs[8]);
			if(nPegs[8] < 1 || nPegs[8] > 9) printf("Number can only be from 1-9.\n\n");
			else {
				if(isNumAvail[nPegs[8] - 1] == 0) printf("Number already taken by other color.\n\n");
				else invalid = 0;
			}
		} while(invalid);
		isNumAvail[nPegs[8] - 1] = 0;

		changeColor(0, 0);
	}
}

void endProgram() { // plays at the start of the program
	PlaySound("songs\\theme_song.wav", NULL, SND_FILENAME | SND_ASYNC);
	system("cls");
	// output: Thank you for Playing Master Mind!
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t     _________  ___  ___  ________  ________   ___  __             ___    ___ ________  ___  ___                              \n");
	printf("\t\t\t\t\t\t    |\\___   ___\\\\  \\|\\  \\|\\   __  \\|\\   ___  \\|\\  \\|\\  \\          |\\  \\  /  /|\\   __  \\|\\  \\|\\  \\                             \n");
	printf("\t\t\t\t\t\t    \\|___ \\  \\_\\ \\  \\\\\\  \\ \\  \\|\\  \\ \\  \\\\ \\  \\ \\  \\/  /|_        \\ \\  \\/  / | \\  \\|\\  \\ \\  \\\\\\  \\                            \n");
	printf("\t\t\t\t\t\t         \\ \\  \\ \\ \\   __  \\ \\   __  \\ \\  \\\\ \\  \\ \\   ___  \\        \\ \\    / / \\ \\  \\\\\\  \\ \\  \\\\\\  \\                           \n");
	printf("\t\t\t\t\t\t          \\ \\  \\ \\ \\  \\ \\  \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\\\ \\  \\        \\/  /  /   \\ \\  \\\\\\  \\ \\  \\\\\\  \\                          \n");
	printf("\t\t\t\t\t\t           \\ \\__\\ \\ \\__\\ \\__\\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\__\\\\ \\__\\     __/  / /      \\ \\_______\\ \\_______\\                         \n");
	printf("\t\t\t\t\t\t            \\|__|  \\|__|\\|__|\\|__|\\|__|\\|__| \\|__|\\|__| \\|__|    |\\___/ /        \\|_______|\\|_______|                         \n");
	printf("\t\t\t\t\t\t                                                                 \\|___|/                                                      \n");
	printf("\t\t\t\t\t\t                                                                                                                              \n");
	printf("\t\t\t\t\t\t                                                                                                                              \n");
	printf("\t\t\t\t\t\t ________ ________  ________          ________  ___       ________      ___    ___ ___  ________   ________                   \n");
	printf("\t\t\t\t\t\t|\\  _____\\\\   __  \\|\\   __  \\        |\\   __  \\|\\  \\     |\\   __  \\    |\\  \\  /  /|\\  \\|\\   ___  \\|\\   ____\\                  \n");
	printf("\t\t\t\t\t\t\\ \\  \\__/\\ \\  \\|\\  \\ \\  \\|\\  \\       \\ \\  \\|\\  \\ \\  \\    \\ \\  \\|\\  \\   \\ \\  \\/  / | \\  \\ \\  \\\\ \\  \\ \\  \\___|                  \n");
	printf("\t\t\t\t\t\t \\ \\   __\\\\ \\  \\\\\\  \\ \\   _  _\\       \\ \\   ____\\ \\  \\    \\ \\   __  \\   \\ \\    / / \\ \\  \\ \\  \\\\ \\  \\ \\  \\  ___                \n");
	printf("\t\t\t\t\t\t  \\ \\  \\_| \\ \\  \\\\\\  \\ \\  \\\\  \\|       \\ \\  \\___|\\ \\  \\____\\ \\  \\ \\  \\   \\/  /  /   \\ \\  \\ \\  \\\\ \\  \\ \\  \\|\\  \\               \n");
	printf("\t\t\t\t\t\t   \\ \\__\\   \\ \\_______\\ \\__\\\\ _\\        \\ \\__\\    \\ \\_______\\ \\__\\ \\__\\__/  / /      \\ \\__\\ \\__\\\\ \\__\\ \\_______\\              \n");
	printf("\t\t\t\t\t\t    \\|__|    \\|_______|\\|__|\\|__|        \\|__|     \\|_______|\\|__|\\|__|\\___/ /        \\|__|\\|__| \\|__|\\|_______|              \n");
	printf("\t\t\t\t\t\t                                                                      \\|___|/                                                 \n");
	printf("\t\t\t\t\t\t                                                                                                                              \n");
	printf("\t\t\t\t\t\t                                                                                                                              \n");
	printf("\t\t\t\t\t\t _____ ______   ________  ________  _________  _______   ________          _____ ______   ___  ________   ________  ___       \n");
	printf("\t\t\t\t\t\t|\\   _ \\  _   \\|\\   __  \\|\\   ____\\|\\___   ___\\\\  ___ \\ |\\   __  \\        |\\   _ \\  _   \\|\\  \\|\\   ___  \\|\\   ___ \\|\\  \\      \n");
	printf("\t\t\t\t\t\t\\ \\  \\\\\\__\\ \\  \\ \\  \\|\\  \\ \\  \\___|\\|___ \\  \\_\\ \\   __/|\\ \\  \\|\\  \\       \\ \\  \\\\\\__\\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\_|\\ \\ \\  \\     \n");
	printf("\t\t\t\t\t\t \\ \\  \\\\|__| \\  \\ \\   __  \\ \\_____  \\   \\ \\  \\ \\ \\  \\_|/_\\ \\   _  _\\       \\ \\  \\\\|__| \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\ \\\\ \\ \\  \\    \n");
	printf("\t\t\t\t\t\t  \\ \\  \\    \\ \\  \\ \\  \\ \\  \\|____|\\  \\   \\ \\  \\ \\ \\  \\_|\\ \\ \\  \\\\  \\|       \\ \\  \\    \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\_\\\\ \\ \\__\\   \n");
	printf("\t\t\t\t\t\t   \\ \\__\\    \\ \\__\\ \\__\\ \\__\\____\\_\\  \\   \\ \\__\\ \\ \\_______\\ \\__\\\\ _\\        \\ \\__\\    \\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\_______\\|__|   \n");
	printf("\t\t\t\t\t\t    \\|__|     \\|__|\\|__|\\|__|\\_________\\   \\|__|  \\|_______|\\|__|\\|__|        \\|__|     \\|__|\\|__|\\|__| \\|__|\\|_______|   ___ \n");
	printf("\t\t\t\t\t\t                            \\|_________|                                                                                 |\\__\\\n");
	printf("\t\t\t\t\t\t                                                                                                                         \\|__|\n");

	for(int i = 0; i < 5; i++) {
		system("color F0");
		Sleep(100);
		system("color 30");
		Sleep(100);
		system("color 60");
		Sleep(100);
		system("color C0");
		Sleep(100);
		system("color B0");
		Sleep(100);
		system("color 10");
		Sleep(100);
		system("color 80");
		Sleep(100);
		system("color 90");
		Sleep(100);
		system("color 70");
		Sleep(100);
		system("color D0");
		Sleep(100);
		system("color 50");
		Sleep(100);
		system("color E0");
		Sleep(100);
		system("color 20");
		Sleep(100);
		system("color A0");
		Sleep(100);
	}
	system("cls");
	system("color 0F");
}

void welcomeScreen() { // plays at the end of program
	PlaySound("songs\\theme_song.wav", NULL, SND_FILENAME | SND_ASYNC); // theme song plays in loop
	system("cls"); // clears the screen
	printf("\n\n\n\n\n\n\n");
	
	// Output: Welcome to Master Mind! - Christopher Lim Block S-14
    printf("\t\t\t\t\t ___       __   _______   ___       ________  ________  _____ ______   _______           _________  ________                                              \n");
    printf("\t\t\t\t\t|\\  \\     |\\  \\|\\  ___ \\ |\\  \\     |\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\         |\\___   ___\\\\   __  \\                        \n");
    printf("\t\t\t\t\t\\ \\  \\    \\ \\  \\ \\   __/|\\ \\  \\    \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|        \\|___ \\  \\_\\ \\  \\|\\  \\          \n");
    printf("\t\t\t\t\t \\ \\  \\  __\\ \\  \\ \\  \\_|/_\\ \\  \\    \\ \\  \\    \\ \\  \\\\\\  \\ \\  \\\\|__| \\  \\ \\  \\_|/__           \\ \\  \\ \\ \\  \\\\\\  \\       \n");
    printf("\t\t\t\t\t  \\ \\  \\|\\__\\_\\  \\ \\  \\_|\\ \\ \\  \\____\\ \\  \\____\\ \\  \\\\\\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\           \\ \\  \\ \\ \\  \\\\\\  \\  \n");
    printf("\t\t\t\t\t   \\ \\____________\\ \\_______\\ \\_______\\ \\_______\\ \\_______\\ \\__\\    \\ \\__\\ \\_______\\           \\ \\__\\ \\ \\_______\\                 \n");
    printf("\t\t\t\t\t    \\|____________|\\|_______|\\|_______|\\|_______|\\|_______|\\|__|     \\|__|\\|_______|            \\|__|  \\|_______|                               \n");
    printf("\n\n\n");
    printf("\t\t\t\t\t _____ ______   ________  ________  _________  _______   ________          _____ ______   ___  ________   ________  ___      \n");
    printf("\t\t\t\t\t|\\   _ \\  _   \\|\\   __  \\|\\   ____\\|\\___   ___\\\\  ___ \\ |\\   __  \\        |\\   _ \\  _   \\|\\  \\|\\   ___  \\|\\   ___ \\|\\  \\                        \n");
    printf("\t\t\t\t\t\\ \\  \\\\\\__\\ \\  \\ \\  \\|\\  \\ \\  \\___|\\|___ \\  \\_\\ \\   __/|\\ \\  \\|\\  \\       \\ \\  \\\\\\__\\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\_|\\ \\ \\  \\  \n");
    printf("\t\t\t\t\t \\ \\  \\\\|__| \\  \\ \\   __  \\ \\_____  \\   \\ \\  \\ \\ \\  \\_|/_\\ \\   _  _\\       \\ \\  \\\\|__| \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\ \\\\ \\ \\  \\       \n");
    printf("\t\t\t\t\t  \\ \\  \\    \\ \\  \\ \\  \\ \\  \\|____|\\  \\   \\ \\  \\ \\ \\  \\_|\\ \\ \\  \\\\  \\|       \\ \\  \\    \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\_\\\\ \\ \\__\\ \n");
    printf("\t\t\t\t\t   \\ \\__\\    \\ \\__\\ \\__\\ \\__\\____\\_\\  \\   \\ \\__\\ \\ \\_______\\ \\__\\\\ _\\        \\ \\__\\    \\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\_______\\|__|       \n");
    printf("\t\t\t\t\t    \\|__|     \\|__|\\|__|\\|__|\\_________\\   \\|__|  \\|_______|\\|__|\\|__|        \\|__|     \\|__|\\|__|\\|__| \\|__|\\|_______|   ___                           \n");
    printf("\t\t\t\t\t                            \\|_________|                                                                                 |\\__\\                                       \n");
    printf("\t\t\t\t\t                                                                                                                         \\|__|                                         \n");
    printf("\n\n\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t          _____ _          _     _              _                 _     _           \n");
	printf("\t\t\t\t\t\t\t\t\t\t\t         /  __ \\ |        (_)   | |            | |               | |   (_)          \n");
	printf("\t\t\t\t\t\t\t\t\t\t\t ______  | /  \\/ |__  _ __ _ ___| |_ ___  _ __ | |__   ___ _ __  | |    _ _ __ ___  \n");
	printf("\t\t\t\t\t\t\t\t\t\t\t|______| | |   | '_ \\| '__| / __| __/ _ \\| '_ \\| '_ \\ / _ \\ '__| | |   | | '_ ` _ \\ \n");
	printf("\t\t\t\t\t\t\t\t\t\t\t         | \\__/\\ | | | |  | \\__ \\ || (_) | |_) | | | |  __/ |    | |___| | | | | | |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t          \\____/_| |_|_|  |_|___/\\__\\___/| .__/|_| |_|\\___|_|    \\_____/_|_| |_| |_|\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t                                         | |                                        \n");
	printf("\t\t\t\t\t\t\t\t\t\t\t                                         |_|                                        \n");
	printf("\t\t\t\t\t\t\t\t\t\t\t                                  ______ _            _      _____        __    ___ \n");
	printf("\t\t\t\t\t\t\t\t\t\t\t                                  | ___ \\ |          | |    /  ___|      /  |  /   |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t                                  | |_/ / | ___   ___| | __ \\ `--. ______`| | / /| |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t                                  | ___ \\ |/ _ \\ / __| |/ /  `--. \\______|| |/ /_| |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t                                  | |_/ / | (_) | (__|   <  /\\__/ /      _| |\\___  |\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t                                  \\____/|_|\\___/ \\___|_|\\_\\ \\____/       \\___/   |_/\n");
	                                                                                    
	for(int i = 0; i < 5; i++) {
		system("color E0");
		Sleep(100);
		system("color C0");
		Sleep(100);
		system("color 20");
		Sleep(100);
		system("color F0");
		Sleep(100);
		system("color B0");
		Sleep(100);
		system("color A0");
		Sleep(100);
		system("color 60");
		Sleep(100);
		system("color 70");
		Sleep(100);
		system("color 90");
		Sleep(100);
		system("color 80");
		Sleep(100);
		system("color 10");
		Sleep(100);
		system("color 30");
		Sleep(100);
		system("color D0");
		Sleep(100);
		system("color 50");
		Sleep(100);
	}
	system("color 0F");
}

void resultScreen(int player) { // output who wins
	system("cls");
	printf("\n\n\n\n\n\n\n");                                                         
	if(player == 1) { 		
		// output: Player 1 Wins!
		printf("\t\t\t\t\t\t\t\t\t______ _                         __    _    _ _           _ \n");
		printf("\t\t\t\t\t\t\t\t\t| ___ \\ |                       /  |  | |  | (_)         | |\n");
		printf("\t\t\t\t\t\t\t\t\t| |_/ / | __ _ _   _  ___ _ __  `| |  | |  | |_ _ __  ___| |\n");
		printf("\t\t\t\t\t\t\t\t\t|  __/| |/ _` | | | |/ _ \\ '__|  | |  | |/\\| | | '_ \\/ __| |\n");
		printf("\t\t\t\t\t\t\t\t\t| |   | | (_| | |_| |  __/ |    _| |_ \\  /\\  / | | | \\__ \\_|\n");
		printf("\t\t\t\t\t\t\t\t\t\\_|   |_|\\__,_|\\__, |\\___|_|    \\___/  \\/  \\/|_|_| |_|___(_)\n");
		printf("\t\t\t\t\t\t\t\t\t                __/ |                                       \n");
		printf("\t\t\t\t\t\t\t\t\t               |___/                                        \n");
	} else if(player == 2) { 
		// output: Player 2 Wins!
		printf("\t\t\t\t\t\t\t\t\t______ _                         _____   _    _ _           _ \n");
		printf("\t\t\t\t\t\t\t\t\t| ___ \\ |                       / __  \\ | |  | (_)         | |\n");
		printf("\t\t\t\t\t\t\t\t\t| |_/ / | __ _ _   _  ___ _ __  `' / /' | |  | |_ _ __  ___| |\n");
		printf("\t\t\t\t\t\t\t\t\t|  __/| |/ _` | | | |/ _ \\ '__|   / /   | |/\\| | | '_ \\/ __| |\n");
		printf("\t\t\t\t\t\t\t\t\t| |   | | (_| | |_| |  __/ |    ./ /___ \\  /\\  / | | | \\__ \\_|\n");
		printf("\t\t\t\t\t\t\t\t\t\\_|   |_|\\__,_|\\__, |\\___|_|    \\_____/  \\/  \\/|_|_| |_|___(_)\n");
		printf("\t\t\t\t\t\t\t\t\t                __/ |                                         \n");
		printf("\t\t\t\t\t\t\t\t\t               |___/                                          \n");
	} else if(player == 3) { // just in case player number is changed 
		// output: Player 3 Wins!
		printf("\t\t\t\t\t\t\t\t\t______ _                         _____   _    _ _           _ \n");
		printf("\t\t\t\t\t\t\t\t\t| ___ \\ |                       |____ | | |  | (_)         | |\n");
		printf("\t\t\t\t\t\t\t\t\t| |_/ / | __ _ _   _  ___ _ __      / / | |  | |_ _ __  ___| |\n");
		printf("\t\t\t\t\t\t\t\t\t|  __/| |/ _` | | | |/ _ \\ '__|     \\ \\ | |/\\| | | '_ \\/ __| |\n");
		printf("\t\t\t\t\t\t\t\t\t| |   | | (_| | |_| |  __/ |    .___/ / \\  /\\  / | | | \\__ \\_|\n");
		printf("\t\t\t\t\t\t\t\t\t\\_|   |_|\\__,_|\\__, |\\___|_|    \\____/   \\/  \\/|_|_| |_|___(_)\n");
		printf("\t\t\t\t\t\t\t\t\t                __/ |                                         \n");
		printf("\t\t\t\t\t\t\t\t\t               |___/                                          \n");
	} else if(player == 4) { // just in case player number is changed 
		// output: Player 4 Wins!
		printf("\t\t\t\t\t\t\t\t\t______ _                           ___   _    _ _           _ \n");
		printf("\t\t\t\t\t\t\t\t\t| ___ \\ |                         /   | | |  | (_)         | |\n");
		printf("\t\t\t\t\t\t\t\t\t| |_/ / | __ _ _   _  ___ _ __   / /| | | |  | |_ _ __  ___| |\n");
		printf("\t\t\t\t\t\t\t\t\t|  __/| |/ _` | | | |/ _ \\ '__| / /_| | | |/\\| | | '_ \\/ __| |\n");
		printf("\t\t\t\t\t\t\t\t\t| |   | | (_| | |_| |  __/ |    \\___  | \\  /\\  / | | | \\__ \\_|\n");
		printf("\t\t\t\t\t\t\t\t\t\\_|   |_|\\__,_|\\__, |\\___|_|        |_/  \\/  \\/|_|_| |_|___(_)\n");
		printf("\t\t\t\t\t\t\t\t\t                __/ |                                         \n");
		printf("\t\t\t\t\t\t\t\t\t               |___/                                          \n");
	} else if(player == 5) { // just in case player number is changed 
		// output: Player 5 Wins!
		printf("\t\t\t\t\t\t\t\t\t______ _                         _____   _    _ _           _ \n");
		printf("\t\t\t\t\t\t\t\t\t| ___ \\ |                       |  ___| | |  | (_)         | |\n");
		printf("\t\t\t\t\t\t\t\t\t| |_/ / | __ _ _   _  ___ _ __  |___ \\  | |  | |_ _ __  ___| |\n");
		printf("\t\t\t\t\t\t\t\t\t|  __/| |/ _` | | | |/ _ \\ '__|     \\ \\ | |/\\| | | '_ \\/ __| |\n");
		printf("\t\t\t\t\t\t\t\t\t| |   | | (_| | |_| |  __/ |    /\\__/ / \\  /\\  / | | | \\__ \\_|\n");
		printf("\t\t\t\t\t\t\t\t\t\\_|   |_|\\__,_|\\__, |\\___|_|    \\____/   \\/  \\/|_|_| |_|___(_)\n");
		printf("\t\t\t\t\t\t\t\t\t                __/ |                                         \n");
		printf("\t\t\t\t\t\t\t\t\t               |___/                                          \n");
	} else {
		PlaySound("songs\\no_win.wav", NULL, SND_FILENAME | SND_ASYNC);
		printf("\t\t\t\t\t\t\t\t\t _   _         _____              _    _                         \n");
		printf("\t\t\t\t\t\t\t\t\t| \\ | |       |  _  |            | |  | |                        \n");
		printf("\t\t\t\t\t\t\t\t\t|  \\| | ___   | | | |_ __   ___  | |  | | ___  _ __              \n");
		printf("\t\t\t\t\t\t\t\t\t| . ` |/ _ \\  | | | | '_ \\ / _ \\ | |/\\| |/ _ \\| '_ \\             \n");
		printf("\t\t\t\t\t\t\t\t\t| |\\  | (_) | \\ \\_/ / | | |  __/ \\  /\\  / (_) | | | |  _   _   _ \n");
		printf("\t\t\t\t\t\t\t\t\t\\_| \\_/\\___/   \\___/|_| |_|\\___|  \\/  \\/ \\___/|_| |_| (_) (_) (_)\n");
	}
	Sleep(2000);
}

int guessChecker(int guess, int code, int* nPegs) { // checks and gives the score/hint and returns the value whether
	int cPlacement = 0, cNumber = 0; // correct placement, correct number
	int tempVar; // temporary variable
	int reverseGuess = 0, multiplier = 1000; // reverse guess, multiplier for reverse guess
	int tempGuess, tempCode; // temporary guess variable, temporary code variable
	
	PlaySound("songs\\select_item.wav", NULL, SND_FILENAME | SND_ASYNC); // plays sfx every valid guess entered
	printf("\t\t ");
	for(tempVar= 0; tempVar< 2; tempVar++) { // output formatting
		printf(" -");
		for(tempGuess = guess; tempGuess > 0; tempGuess /= 10) printf("--");
	}
	printf("\n\t\t | ");
	for(tempGuess = guess; tempGuess > 0; tempGuess /= 10) {
		reverseGuess += (tempGuess % 10) * multiplier;
		multiplier /= 10;
	}
	for(tempGuess = reverseGuess; tempGuess > 0; tempGuess /= 10) { // output peg
		changeColor(tempGuess % 10, nPegs);
		printf("O "); 
	}
	changeColor(0, nPegs);
	printf("| ");
	for(tempCode = code, tempGuess = guess; tempCode > 0 && tempGuess > 0; tempCode /= 10, tempGuess /= 10) { // checks if a digit in guess has a exactly the same place in a digit in the code
		if(tempGuess % 10 == tempCode % 10) cPlacement++;
	}
	for(tempCode = code; tempCode > 0; tempCode /= 10) { // checks if a digit in guess is in the code (not necessarily same place)
		tempVar= 0;
		for(tempGuess = guess; tempGuess > 0 && !tempVar; tempGuess /= 10) if(tempGuess % 10 == tempCode % 10) tempVar= 1; 
		if(tempVar) cNumber++;
	}
	tempVar= 0;
	while(tempVar< cPlacement) { // output "score" of correct digits in correct place
		printf("%sO ", GRAY);
		tempVar++;
	}

	while(tempVar< cNumber) { // output "score" of correct digits (not necessarily in the correct place)
		printf("%sO ", WHITE);
		tempVar++;
	}
	while(tempVar< 4) {
		printf("  ");
		tempVar++;
	}
	changeColor(0, nPegs);
	printf("|\n\t\t ");
	for(tempVar= 0; tempVar< 2; tempVar++) {
		printf(" -");
		for(tempGuess = guess; tempGuess > 0; tempGuess /= 10) printf("--");
	}
	printf("\n");
	return guess == code;
}

void changeColor(int digit, int* nPegs) { // changes the text color of the console
	int d;                    // stores the color code to know which color to change
	if(digit > 0 && digit < 10) { 
		for(int i = 0; i < 9; i++) { // this is useful if the corresponding number  
			if(digit == nPegs[i]) {  // for each color is changed through the settings
				d = i + 1;
				break;
			}
		}
	} else {
		d = digit;
	}
	
	if(d == 0) printf(WHITE);
	else if(d == 1) printf(BLUE);
	else if(d == 2) printf(GREEN);
	else if(d == 3) printf(CYAN);
	else if(d == 4) printf(RED);
	else if(d == 5) printf(MAGENTA);
	else if(d == 6) printf(BROWN);
	else if(d == 7) printf(ORANGE);
	else if(d == 8) printf(YELLOW);
	else if(d == 9) printf(LIME);
	else if(d == 10) printf(GRAY);
}