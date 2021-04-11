#include "pch.h"
#include <iostream>
#include <thread>
#include <array>
#include <string>
#include <fstream>
#include <chrono>
#include <random>
#include <cstdio>

using namespace std;

char answer;

bool checkedCase;

bool winner;

int turn = 0;

bool firstTime = true;

string player1Name;
int player1Wins;
int player1Loss;
int player1Draw;

string player2Name;
int player2Wins;
int player2Loss;
int player2Draw;

int grid[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

string gridDisplay[3][3] = { {"a", "d", "g"}, {"b", "e", "h"}, {"c", "f", "i"} };

string gridDisplay2[3][3] = { {"a", "d", "g"}, {"b", "e", "h"}, {"c", "f", "i"} };

void printGrid();
void resetGrids();
void clearScreen();
void printTitle();
void randomAI();
void mainMenu();
void playing(int currentPlayer);
void playingWithAI(int currentPlayer);
int checkingGrid(int coord1, int coord2, int currentPlayer);
bool checkingCasePlayed(int coord1, int coord2, int currentPlayer);
void playCase(int coord1, int coord2, int currentPlayer);
void playCaseWithAI(int coord1, int coord2, int currentPlayer);
void savePlayerStats(string playerName, int win, int loss, int draw);
void setupPlayers(string &playerName, int &win, int &loss, int &draw);
bool displayStats(string playerName);
void delayScroll(int delayMS, int lineCount);


void resetGrids() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			gridDisplay[i][j] = gridDisplay2[i][j];
			grid[i][j] = 0;
		}
	}
}

void printGrid() {
	cout << "	" << gridDisplay[0][0] << " | " << gridDisplay[1][0] << " | " << gridDisplay[2][0] << endl;
	cout << "	" << "---------" << endl;
	cout << "	" << gridDisplay[0][1] << " | " << gridDisplay[1][1] << " | " << gridDisplay[2][1] << endl;
	cout << "	" << "---------" << endl;
	cout << "	" << gridDisplay[0][2] << " | " << gridDisplay[1][2] << " | " << gridDisplay[2][2] << "\n" << endl;
}

void printTitle() {
	cout << "                             _             \n";
	this_thread::sleep_for(chrono::milliseconds(180));
	cout << "                            (_)            \n";
	this_thread::sleep_for(chrono::milliseconds(180));
	cout << "  _ __ ___   ___  _ __ _ __  _  ___  _ __  \n";
	this_thread::sleep_for(chrono::milliseconds(180));
	cout << " | '_ ` _ \\ / _ \\| '__| '_ \\| |/ _ \\| '_ \\ \n";
	this_thread::sleep_for(chrono::milliseconds(180));
	cout << " | | | | | | (_) | |  | |_) | | (_) | | | |\n";
	this_thread::sleep_for(chrono::milliseconds(180));
	cout << " |_| |_| |_|\\___/|_|  | .__/|_|\\___/|_| |_|\n";
	this_thread::sleep_for(chrono::milliseconds(180));
	cout << "                      | |                  \n";
	this_thread::sleep_for(chrono::milliseconds(180));
	cout << "                      |_|                  \n";
}

void clearScreen() {
	cout << string(5, '\n');
}

void mainMenu() {
	clearScreen();
	printTitle();

	cout << "\n";
	cout << "What do you want to do?\n";
	cout << "1. Play\n";
	cout << "2. See statistics\n";
	cout << "3. Play against AI\n";
	cout << "4. Reset statistics\n";

	string answer;
	bool accepted = false;

	while (!accepted) {
		cin >> answer;

		if (answer == "1") {
			string whatever;
			getline(cin, whatever);

			accepted = true;

			int currentPlayer = 1;

			delayScroll(15, 30);

			setupPlayers(player1Name, player1Wins, player1Loss, player1Draw);

			setupPlayers(player2Name, player2Wins, player2Loss, player2Draw);

			delayScroll(15, 30);

			cout << player1Name << " - " << player1Wins << " Wins" << endl;
			cout << "- vs. -" << endl;
			cout << player2Name << " - " << player2Wins << " Wins" << endl;

			cout << "\n";

			cout << "Here is our brand new grid!\n\n";
			
			resetGrids();

			playing(currentPlayer);
		}
		else if (answer == "2") {
			cout << "\n";
			cout << "Whose statistics do you want to see?\n";

			string answer;
			cin >> answer;

			accepted = true;

			cout << "\n";

			displayStats(answer);

			this_thread::sleep_for(chrono::milliseconds(3000));

			mainMenu();

		}
		else if (answer == "3") {
			string whatever;
			getline(cin, whatever);

			accepted = true;

			int currentPlayer = 1;

			cout << "\n";

			setupPlayers(player1Name, player1Wins, player1Loss, player1Draw);

			cout << "\n";

			cout << player1Name << " - " << player1Wins << " Wins" << endl;
			cout << "- vs. -" << endl;
			cout << "AI" << " - " << 42 << " Wins" << endl;

			cout << "\n";

			cout << "Here is our brand new grid!\n\n";

			resetGrids();

			playingWithAI(currentPlayer);

		}
		else if (answer == "4") {

			cout << "\n";
			cout << "Whose statistics do you want to reset?\n";

			string answer;
			cin >> answer;

			accepted = true;

			fstream file;
			string fileName = answer + ".txt";
			file.open(fileName, ios::out);

			file << 0 << endl;
			file << 0 << endl;
			file << 0 << endl;

			file.close();
			cout << "The statistics of this player have been reset\n";

			this_thread::sleep_for(chrono::milliseconds(2000));

			mainMenu();

		}
		else {
			cout << "You can't do this. You can only answer 1, 2, 3 or 4.\n";
		}
	}
}

void delayScroll(int delayMS, int lineCount) {
	for (int i = 0; i < lineCount; i++)
	{
		cout << "" << endl;
		this_thread::sleep_for(chrono::milliseconds(delayMS));
	}
}

void setupPlayers(string &playerName, int &win, int &loss, int &draw) {


	fstream file;
	
	if (firstTime == true) {
		cout << "Who is our first player?\n";
		firstTime = false;
	}
	else {
		cout << "Who is our second player?\n";
		firstTime = true;
	}

	getline(cin, playerName);

	if (playerName == "") {
		playerName == "John";
	}

	for (int i = 0; i < playerName.length(); i++) {
		if (playerName[i] == '/' || playerName[i] == '\\' || playerName[i] == '?' || playerName[i] == ':' || playerName[i] == '<' || playerName[i] == '>' || playerName[i] == '*' || playerName[i] == '|' || playerName[i] == '"') {
			playerName[i] = ' ';
		}
	}

	string filename = playerName + ".txt";

	file.open(filename, ios::in);

	if (file.is_open()) {
		file >> win;
		file >> loss;
		file >> draw;
	}
	else {
		win = 0;
		loss = 0;
		draw = 0;
	}

}

void savePlayerStats(string playerName, int win, int loss, int draw) {

	fstream file;
	string filename = playerName + ".txt";
	file.open(filename, ios::out);

	file << win << endl;
	file << loss << endl;
	file << draw << endl;

	file.close();
}

bool displayStats(string playerName) {
	
	fstream file;
	string filename = playerName + ".txt";
	file.open(filename, ios::in);

	bool accepted = false;

	int win;
	int loss;
	int draw;

	if (file.is_open()) {
		file >> win;
		file >> loss;
		file >> draw;

		cout << playerName << ":\n";
		cout << "Wins: " << win << endl;
		cout << "Loss: " << loss << endl;
		cout << "Draw: " << draw << endl;
		return true;
	}
	else {
		cout << "No player is named " << playerName << endl;
		return false;
	}
}

int checkingGrid(int coord1, int coord2, int currentPlayer) {
	for (int i = 0; i < sizeof(grid); i++) {
		if (grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2] && grid[i][0] == currentPlayer) {
			i = 5;
			winner = true;
			return 2;
		}
		else {
			winner = false;
		}
	}
	if (winner == false) {
		for (int i = 0; i < sizeof(grid); i++) {
			if (grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i] && grid[0][i] == currentPlayer) {
				i = 5;
				winner = true;
				return 2;
			}
			else {
				winner = false;
			}
		}
		if (winner == false) {
			if (grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2] && grid[0][0] == currentPlayer) {
				winner = true;
				return 2;
			}
			else if (grid[2][0] == grid[1][1] && grid[1][1] == grid[0][2] && grid[1][1] == currentPlayer) {
				winner = true;
				return 2;
			}
			else if (turn == 8) {
				return 3;
			}
			else {
				return 1;
			}
		}
	}
}

void playCase(int coord1, int coord2, int currentPlayer) {
	grid[coord1][coord2] = currentPlayer;

	int win = checkingGrid(coord1, coord2, currentPlayer);

	if (currentPlayer == 1) {
		gridDisplay[coord1][coord2] = "X";
		currentPlayer = 2;
		turn++;
	}
	else {
		gridDisplay[coord1][coord2] = "0";
		currentPlayer = 1;
		turn++;
	}

	//1 is no winner yet
	//2 is winner
	//3 is draw

	if (win == 1) {
		playing(currentPlayer);
	}
	else if (win == 2) {
		printGrid();
		cout << "We have a winner!\n";
		turn = 0;

		if (currentPlayer == 2) {
			player1Wins++;
			player2Loss++;
		}
		else {
			player2Wins++;
			player2Loss++;
		}

		savePlayerStats(player1Name, player1Wins, player1Loss, player1Draw);
		savePlayerStats(player2Name, player2Wins, player2Loss, player2Draw);

		cout << "\n";

		displayStats(player1Name);
		cout << "\n";

		displayStats(player2Name);

		this_thread::sleep_for(chrono::milliseconds(1000));
		
		mainMenu();

	}
	else {
		printGrid();
		cout << "It's a draw!\n";
		turn = 0;

		player1Draw++;
		player2Draw++;
		savePlayerStats(player1Name, player1Wins, player1Loss, player1Draw);
		savePlayerStats(player2Name, player2Wins, player2Loss, player2Draw);

		cout << "\n";

		displayStats(player1Name);
		cout << "\n";

		displayStats(player2Name);

	}
}

bool checkingCasePlayed(int coord1, int coord2, int currentPlayer) {

	if (grid[coord1][coord2] != 0) {
		return false;
	}
	else {
		return true;
	}
}

void playing(int currentPlayer) {

	printGrid();

	if (currentPlayer == 1) {
		cout << "Where do you want to play player " << player1Name << " ?\n";
	}
	else {
		cout << "Where do you want to play player " << player2Name << " ?\n";
	}

	bool accepted = false;

	while (!accepted) {
		
		string firstAnswer;

		getline(cin, firstAnswer);

		answer = firstAnswer[0];

		switch (answer) {
		case 'a':
			checkedCase = checkingCasePlayed(0, 0, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCase(0, 0, currentPlayer);
			}
			break;
		case 'b':
			checkedCase = checkingCasePlayed(1, 0, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCase(1, 0, currentPlayer);
			}
			break;
		case 'c':
			checkedCase = checkingCasePlayed(2, 0, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCase(2, 0, currentPlayer);
			}
			break;
		case 'd':
			checkedCase = checkingCasePlayed(0, 1, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCase(0, 1, currentPlayer);
			}
			break;
		case 'e':
			checkedCase = checkingCasePlayed(1, 1, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCase(1, 1, currentPlayer);
			}
			break;
		case 'f':
			checkedCase = checkingCasePlayed(2, 1, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCase(2, 1, currentPlayer);
			}
			break;
		case 'g':
			checkedCase = checkingCasePlayed(0, 2, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCase(0, 2, currentPlayer);
			}
			break;
		case 'h':
			checkedCase = checkingCasePlayed(1, 2, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCase(1, 2, currentPlayer);
			}
			break;
		case 'i':
			checkedCase = checkingCasePlayed(2, 2, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCase(2, 2, currentPlayer);
			}
			break;
		default:
			cout << "You can't play here. Where do you want to play?\n";
		}
	}
}

void randomAI() {
	random_device rd;

	bool accepted = false;


	while (!accepted) {
		int randomY = rd() % 3;
		int randomX = rd() % 3;
		if (grid[randomX][randomY] == 0) {
			playCaseWithAI(randomX, randomY, 2);
			accepted = true;
		}
	}

}

void playingWithAI(int currentPlayer) {

	printGrid();

	cout << "Where do you want to play player " << player1Name << " ?\n";

	bool accepted = false;

	while (!accepted) {

		string firstAnswer;

		getline(cin, firstAnswer);

		answer = firstAnswer[0];		
		
		switch (answer) {
		case 'a':
			checkedCase = checkingCasePlayed(0, 0, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCaseWithAI(0, 0, currentPlayer);
			}
			break;
		case 'b':
			checkedCase = checkingCasePlayed(1, 0, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCaseWithAI(1, 0, currentPlayer);
			}
			break;
		case 'c':
			checkedCase = checkingCasePlayed(2, 0, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCaseWithAI(2, 0, currentPlayer);
			}
			break;
		case 'd':
			checkedCase = checkingCasePlayed(0, 1, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCaseWithAI(0, 1, currentPlayer);
			}
			break;
		case 'e':
			checkedCase = checkingCasePlayed(1, 1, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCaseWithAI(1, 1, currentPlayer);
			}
			break;
		case 'f':
			checkedCase = checkingCasePlayed(2, 1, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCaseWithAI(2, 1, currentPlayer);
			}
			break;
		case 'g':
			checkedCase = checkingCasePlayed(0, 2, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCaseWithAI(0, 2, currentPlayer);
			}
			break;
		case 'h':
			checkedCase = checkingCasePlayed(1, 2, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCaseWithAI(1, 2, currentPlayer);
			}
			break;
		case 'i':
			checkedCase = checkingCasePlayed(2, 2, currentPlayer);
			if (checkedCase == false) {
				cout << "You can't play here because someone already did so.\n";
			}
			else {
				accepted = true;
				playCaseWithAI(2, 2, currentPlayer);
			}
			break;
		default:
			cout << "You can't play here. Where do you want to play?\n";

		}
	}
}

void playCaseWithAI(int coord1, int coord2, int currentPlayer) {
	grid[coord1][coord2] = currentPlayer;

	int win = checkingGrid(coord1, coord2, currentPlayer);

	if (currentPlayer == 1) {
		gridDisplay[coord1][coord2] = "X";
		currentPlayer = 2;
		turn++;
	}
	else {
		gridDisplay[coord1][coord2] = "0";
		currentPlayer = 1;
		turn++;
	}

	//1 is no winner yet
	//2 is winner
	//3 is draw

	if (win == 1) {
		if (currentPlayer == 1) {
			playingWithAI(currentPlayer);
		}
		else {
			randomAI();
		}
	}
	else if (win == 2) {
		printGrid();
		cout << "We have a winner!\n";
		cout << "Playing agaisnt an AI does not appear in your statistics.\n";
		turn = 0;

		this_thread::sleep_for(chrono::milliseconds(1000));

		firstTime = true;

		mainMenu();

	}
	else {
		printGrid();
		cout << "It's a draw!\n";
		cout << "Playing agaisnt an AI does not appear in your statistics.\n";
		turn = 0;

		this_thread::sleep_for(chrono::milliseconds(1000));

		firstTime = true;

		mainMenu();

	}
}

int main() {

	mainMenu();

}