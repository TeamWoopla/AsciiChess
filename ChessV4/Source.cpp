/*
TODO :
#decide on the user input mechanism.
#add a clock?
#add a chack function to see if u can go to the place
that you want to go to.
*cant override a piece unless u are a horse.
*being eated function.
*hazraha.
#define a class every move for every piece.
#hazraha.
#isDead function

#or - 600 , el - 550;

*/

#include <stdio.h>
#include "conio.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>
#include <ctime>
#include "Header.h"

using namespace std;

int turn = 0; // A number for the turn, used to detect line of the 2D array 
int sChoiceX = 4, sChoiceY = 4, eChoiceY = 4, eChoiceX = 4; // el this is your part, to get the x, y
bool gameOver, move1 = false, startEnd = true;
string fromW, toW;
int userX = 5, userY = 4;
enum eDirecton { STOP, ENTER, LEFT, RIGHT, UP, DOWN };
eDirecton dir;

char board[8][8] = {
	{ 'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R' },
	{ 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
	{ '.', '.', '.', '.', '.', '.', '.', '.' },
	{ '.', '.', '.', '.', '.', '.', '.', '.' },
	{ '.', '.', '.', '.', '.', '.', '.', '.' },
	{ '.', '.', '.', '.', '.', '.', '.', '.' },
	{ 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
	{ 'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R' }
};

Pieces F[2][16] = { { true },{ false } };

void Setup() {
	gameOver = false;
	int t, i;
	for (i = 0; i < 16; i++) {
		F[0][i].setDead(false);
		if (i < 8) {
			F[0][i].setY(0);
			F[0][i].setX(i);
		}
		else {
			F[0][i].setY(1);
			F[0][i].setX(i - 8);
			F[0][i].setType('P');
		}
	}
	F[0][0].setType('R');
	F[0][1].setType('H');
	F[0][2].setType('B');
	F[0][3].setType('Q');
	F[0][4].setType('K');
	F[0][5].setType('B');
	F[0][6].setType('H');
	F[0][7].setType('R');

	for (t = 0; t < 16; t++) {
		F[1][t].setDead(false);
		if (t < 8) {
			F[1][t].setY(7);
			F[1][t].setX(t);
		}
		else {
			F[1][t].setY(6);
			F[1][t].setX(t - 8);
			F[1][t].setType('P');
		}
	}
	F[1][0].setType('R');
	F[1][1].setType('H');
	F[1][2].setType('B');
	F[1][3].setType('Q');
	F[1][4].setType('K');
	F[1][5].setType('B');
	F[1][6].setType('H');
	F[1][7].setType('R');
}

void Draw() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	int i, i1;
	printf("\n\n\n");
	for (i = 0; i < 8; i++) {
		printf("\t\t\t");
		for (i1 = 0; i1 < 8; i1++) {
			SetConsoleTextAttribute(hConsole, 14);
			for (int z = 0; z < 16; z++) {
				if ((F[0][z].getX() == i1) && (F[0][z].getY() == i)) {
					SetConsoleTextAttribute(hConsole, 15);
				}
				else if ((F[1][z].getX() == i1) && (F[1][z].getY() == i)) {
					SetConsoleTextAttribute(hConsole, 5);
				}
			}
			if (startEnd == false) if ((i1 == sChoiceX) && (i == sChoiceY)) SetConsoleTextAttribute(hConsole, 230);
			if ((i1 == userX) && (i == userY)) SetConsoleTextAttribute(hConsole, 44);
			cout << " " << board[i][i1] << " ";
			SetConsoleTextAttribute(hConsole, 15);
			cout << "  ";
		}
		printf("\n\n");
	}
	printf("\t\t\t     ");
	if (turn == 0) SetConsoleTextAttribute(hConsole, 150);
	cout << "P1 -  White";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "      ";
	if (turn == 1) SetConsoleTextAttribute(hConsole, 150);
	cout << "P2 - Purple";
	SetConsoleTextAttribute(hConsole, 15);
	cout << endl;

}

void Input() {
	switch (_getch()) {
	case 'a':
		dir = LEFT;
		break;
	case 'd':
		dir = RIGHT;
		break;
	case 'w':
		dir = UP;
		break;
	case 's':
		dir = DOWN;
		break;
	case 13:
		dir = ENTER;
		break;
	default:
		dir = STOP;
		break;
	}
}

bool Slant() {
	int i, j;
	bool a = false, a1 = false, a2 = false, a3 = false;
	for (i = sChoiceY, j = sChoiceX; j >= 0 && i >= 0; i--, j--) {
		if ((i == eChoiceY) && (j == eChoiceX)) return true;
		if (a) { j = -10; i = -10; }
		if (board[i - 1][j - 1] != '.') a = true;
	}
	for (i = sChoiceY, j = sChoiceX; j >= 0 && i < 8; i++, j--) {
		if ((i == eChoiceY) && (j == eChoiceX)) return true;
		if (a1) { j = -10; i = 10; }
		if (board[i + 1][j - 1] != '.') a1 = true;
	}
	for (i = sChoiceY, j = sChoiceX; j < 8 && i >= 0; i--, j++) {
		if ((i == eChoiceY) && (j == eChoiceX)) return true;
		if (a2) { j = 10; i = -10; }
		if (board[i - 1][j + 1] != '.') a2 = true;
	}
	for (i = sChoiceY, j = sChoiceX; j < 8 && i < 8; i++, j++) {
		if ((i == eChoiceY) && (j == eChoiceX)) return true;
		if (a3) { j = 10; i = 10; }
		if (board[i + 1][j + 1] != '.') a3 = true;
	}
	return false;
}
// Working :D

bool SLine() {
	int i, j = sChoiceX, j2 = sChoiceY;
	bool a = false, a1 = false, a2 = false, a3 = false;
	for (i = sChoiceY; i >= 0; i--) {
		if ((i == eChoiceY) && (j == eChoiceX)) return true;
		if (a) i = -10;
		if (board[i - 1][j] != '.') a = true;
	}
	for (i = sChoiceX; i >= 0; i--) {
		if ((i == eChoiceX) && (j2 == eChoiceY)) return true;
		if (a1) i = -10;
		if (board[j2][i - 1] != '.') a1 = true;
	}
	for (i = sChoiceY; i < 8; i++) {
		if ((i == eChoiceY) && (j == eChoiceX)) return true;
		if (a2) i = 10;
		if (board[i + 1][j] != '.') a2 = true;
	}
	for (i = sChoiceX; i < 8; i++) {
		if ((i == eChoiceX) && (j2 == eChoiceY)) return true;
		if (a3) i = 10;
		if (board[j2][i + 1] != '.') a3 = true;
	}
	return false;
}
// Working :D

bool Pawn() {
	if (turn == 0) { // White or Black
		if ((eChoiceY == (sChoiceY + 1)) && (eChoiceX == sChoiceX)) { // Is the chosen spot is 1 blocks a head.
			if (board[eChoiceY][eChoiceX] == '.') return true; // Is the spot clear
			else return false;
		}
		if (sChoiceY == 1) { // First move or not
			if ((eChoiceY == (sChoiceY + 2)) && (eChoiceX == sChoiceX)) { // Is the chosen spot is 2 blocks a head.
				if (board[eChoiceY][eChoiceX] == '.') return true; // Is the spot clear
				else return false;
			}
		}
		if (((eChoiceY == (sChoiceY + 1)) && (eChoiceX == (sChoiceX + 1))) || ((eChoiceY == (sChoiceY + 1)) && (eChoiceX == (sChoiceX - 1)))) { // Is the chosen spot in the first slant of the start choise 
			if (board[eChoiceY][eChoiceX] != '.') return true; // Is the spot clear
			else return false;
		}
	}
	else {
		if ((eChoiceY == (sChoiceY - 1)) && (eChoiceX == sChoiceX)) { // Is the chosen spot is 1 blocks a head.
			if (board[eChoiceY][eChoiceX] == '.') return true; // Is the spot clear
			else return false;
		}
		if (sChoiceY == 6) { // First move or not
			if ((eChoiceY == (sChoiceY - 2)) && (eChoiceX == sChoiceX)) { // Is the chosen spot is 2 blocks a head.
				if (board[eChoiceY][eChoiceX] == '.') return true; // Is the spot clear
				else return false;
			}
		}
		if (((eChoiceY == (sChoiceY - 1)) && (eChoiceX == (sChoiceX + 1))) || ((eChoiceY == (sChoiceY - 1)) && (eChoiceX == (sChoiceX - 1)))) { // Is the chosen spot in the first slant of the start choise 
			if (board[eChoiceY][eChoiceX] != '.') return true; // Is the spot clear
			else return false;
		}
	}
	return false;
}
// Working :D

bool King() {
	if (((eChoiceY == (sChoiceY + 1)) && (eChoiceX == sChoiceX)) ||
		((eChoiceY == (sChoiceY - 1)) && (eChoiceX == sChoiceX)) ||
		((eChoiceX == (sChoiceX + 1)) && (eChoiceY == sChoiceY)) ||
		((eChoiceX == (sChoiceX - 1)) && (eChoiceY == sChoiceY)) ||
		((eChoiceX == (sChoiceX - 1)) && (eChoiceY == sChoiceY + 1)) ||
		((eChoiceX == (sChoiceX + 1)) && (eChoiceY == sChoiceY - 1)) ||
		((eChoiceY == (sChoiceY - 1)) && (eChoiceX == sChoiceX - 1)) ||
		((eChoiceY == (sChoiceY + 1)) && (eChoiceX == sChoiceX + 1))) {
		return true;
	}
	return false;
}
// Working :D

bool Horse() {
	if (((eChoiceY == (sChoiceY + 2)) && (eChoiceX == sChoiceX + 1)) ||
		((eChoiceY == (sChoiceY + 2)) && (eChoiceX == sChoiceX - 1)) ||
		((eChoiceY == (sChoiceY + 1)) && (eChoiceX == sChoiceX - 2)) ||
		((eChoiceY == (sChoiceY + 1)) && (eChoiceX == sChoiceX + 2)) ||
		((eChoiceY == (sChoiceY - 2)) && (eChoiceX == sChoiceX + 1)) ||
		((eChoiceY == (sChoiceY - 2)) && (eChoiceX == sChoiceX - 1)) ||
		((eChoiceY == (sChoiceY - 1)) && (eChoiceX == sChoiceX - 2)) ||
		((eChoiceY == (sChoiceY - 1)) && (eChoiceX == sChoiceX + 2)))
		return true;

	return false;
}
// Working :D

void Kill() {
	int i, i1;
	int reTurn;
	if (turn == 0) reTurn = 1;
	else reTurn = 0;
	for (i = 0; i < 16; i++) {
		if ((eChoiceX == F[reTurn][i].getX()) && (eChoiceY == F[reTurn][i].getY())) {
			F[reTurn][i].setDead(true);
		}
	}
}
// Working :D

bool Side() {
	int i, i1;
	for (i = 0; i < 16; i++) {
		if ((eChoiceX == F[turn][i].getX()) && (eChoiceY == F[turn][i].getY())) {
			return false;
		}
	}
	return true;
}
// Working :D

void Logic() {
	switch (dir) {
	case LEFT:
		userX--;
		break;

	case RIGHT:
		userX++;
		break;

	case UP:
		userY--;
		break;

	case DOWN:
		userY++;
		break;
	case ENTER:
		if (startEnd) {
			cout << "Start" << endl;
			sChoiceY = userY;
			sChoiceX = userX;
			startEnd = false;
			cout << "X: " << userX << " Y: " << " " << userY << endl;
			system("pause");
		}
		else {
			cout << "End" << endl;
			eChoiceY = userY;
			eChoiceX = userX;
			startEnd = true;
			move1 = true;
			cout << "X: " << userX << " Y: " << " " << userY << endl;
			system("pause");
		}

	default:
		dir = STOP;
		break;
	}
	if (userX == -1) userX = 7;
	else if (userX == 8) userX = 0;
	else if (userY == -1) userY = 7;
	else if (userY == 8) userY = 0;
	if (move1) {
		int i, i1;
		for (i = 0; i < 16; i++) {
			if ((sChoiceX == F[turn][i].getX()) && (sChoiceY == F[turn][i].getY())) {
				switch (F[turn][i].getType()) {
				case 'P':
					cout << "it's P" << endl;
					if (Pawn() && Side()) {
						board[sChoiceY][sChoiceX] = '.';
						board[eChoiceY][eChoiceX] = 'P';
						Kill();
						F[turn][i].setX(eChoiceX);
						F[turn][i].setY(eChoiceY);
						if (turn == 0) turn = 1;
						else turn = 0;
					}
					else cout << "Opss I dont move like that..." << endl;
					break;
				case 'R':
					cout << "it's R" << endl;
					if (SLine() && Side()) {
						board[sChoiceY][sChoiceX] = '.';
						board[eChoiceY][eChoiceX] = 'R';
						Kill();
						F[turn][i].setX(eChoiceX);
						F[turn][i].setY(eChoiceY);
						if (turn == 0) turn = 1;
						else turn = 0;
					}
					else cout << "Opss I dont move like that..." << endl;
					system("pause");
					break;
				case 'H':
					cout << "it's H" << endl;
					if (Horse() && Side()) {
						board[sChoiceY][sChoiceX] = '.';
						board[eChoiceY][eChoiceX] = 'H';
						Kill();
						F[turn][i].setX(eChoiceX);
						F[turn][i].setY(eChoiceY);
						if (turn == 0) turn = 1;
						else turn = 0;
					}
					else cout << "Opss I dont move like that..." << endl;
					break;
				case 'B':
					cout << "it's B" << endl;
					if (Slant() && Side()) {
						board[sChoiceY][sChoiceX] = '.';
						board[eChoiceY][eChoiceX] = 'B';
						Kill();
						F[turn][i].setX(eChoiceX);
						F[turn][i].setY(eChoiceY);
						if (turn == 0) turn = 1;
						else turn = 0;
					}
					else cout << "Opss I dont move like that..." << endl;
					system("pause");
					break;
				case 'Q':
					cout << "it's Q" << endl;
					if ((Slant() || SLine()) && Side()) {
						board[sChoiceY][sChoiceX] = '.';
						board[eChoiceY][eChoiceX] = 'Q';
						Kill();
						F[turn][i].setX(eChoiceX);
						F[turn][i].setY(eChoiceY);
						if (turn == 0) turn = 1;
						else turn = 0;
					}
					else cout << "Opss I dont move like that..." << endl;
					system("pause");
					break;
				case 'K':
					cout << "it's K" << endl;
					if (King() && Side()) {
						board[sChoiceY][sChoiceX] = '.';
						board[eChoiceY][eChoiceX] = 'K';
						Kill();
						F[turn][i].setX(eChoiceX);
						F[turn][i].setY(eChoiceY);
						if (turn == 0) turn = 1;
						else turn = 0;
					}
					else cout << "Opss I dont move like that..." << endl;
					break;
				default:
					break;
				}
			}
		}
		move1 = false;
	}
}

int main() {

	Setup();
	Draw();
	while (!gameOver) {
		Input();
		Logic();
		Draw();
	}

	return 0;
	// 79676975
}