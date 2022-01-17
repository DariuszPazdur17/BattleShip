#pragma once
#include <string>
#include<iostream>

using namespace std;


const int BOARD_WIDTH = 15;
const int BOARD_HEIGHT = 10;
const int SHIP_TYPES = 5;

const char isWATER = 247; //ASCII Kod
const char isHIT = 'X';
const char isSHIP = 'S';
const char isMISS = '0';

struct POINT {
	
	//poziome i pionowe kordynaty
	int X;
	int Y;
};


struct SHIP {
	//nazwa statku
	string name;
	//dlugosc statku
	int length;
	//Kordynaty 
	POINT onGrid[5]; //0-4 max dlugosc
	//trafienie czy te¿ nie
	bool hitFlag[5];
}ship[SHIP_TYPES];



struct PLAYER {
	char grid[BOARD_WIDTH][BOARD_HEIGHT];
}player[3]; 


enum DIRECTION{ HORIZONTAL, VERTICAL };
struct PLACESHIPS {
	DIRECTION direction;
	SHIP shipType;
};

//Funkcje
void LoadShips();
void ResetBoard();
void DrawBoard(int);
PLACESHIPS UserInputShipPlacement();
bool UserInputAttack(int&, int&, int);
bool GameOverCheck(int);