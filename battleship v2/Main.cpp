#include <iostream>
#include <string>
#include "ship.h"
using namespace std;


bool gameRunning = false;


int main()
{
	LoadShips();
	ResetBoard();

	//Faza gry-po³o¿enie swoich statków na mapie
	//Pêtla po ka¿dym graczu
	for (int aplyr = 1; aplyr < 3; ++aplyr)
	{
		//Petla po umieszczenie dowolnego typu statyku
		for (int thisShip = 0; thisShip < SHIP_TYPES; ++thisShip)
		{
			//Wyœwietla mapkê dla gracza
			system("cls");
			DrawBoard(aplyr);
			//Instrukcja 
			cout << "\n";
			cout << "Instrukcja (Gracz " << aplyr << ")\n\n";
			cout << "Musisz umiescic statki kamracie!.  Powinines to zrobic tak:\n";
			cout << "Umiesczenie  (0:Poziomo,1:Pionowo), wspolrzedna x, wspolrzedna y\n";
			cout << "Przyk³ad 0 6 3    Ta komedna umiesci twoj statek poziomo na wspolrzednych  X:6 Y:3 \n\n";
			cout << "Polozenie statku : " << ship[thisShip].name << "o dlugoœci: " << ship[thisShip].length << "\n";
			cout << "Gdzie chcesz go umiescic? ";

			//Get input from user and loop until good data is returned
			PLACESHIPS aShip;
			aShip.shipType.onGrid[0].X = -1;
			while (aShip.shipType.onGrid[0].X == -1)
			{
				aShip = UserInputShipPlacement();
			}

			//Uzyskaj dane wejœciowe od u¿ytkownika i zapêtlaj, dopóki nie zostan¹ zwrócone dobre dane
			aShip.shipType.length = ship[thisShip].length;
			aShip.shipType.name = ship[thisShip].name;

			//Dodaje pierwszy punkt siatki na planszy dla aktualnego gracza
			player[aplyr].grid[aShip.shipType.onGrid[0].X][aShip.shipType.onGrid[0].Y] = isSHIP;

			//Wyznacza wszystkie punkty siatki na podstawie d³ugoœci i szerokoœci
			for (int i = 1; i < aShip.shipType.length; ++i)
			{
				if (aShip.direction == HORIZONTAL) {
					aShip.shipType.onGrid[i].X = aShip.shipType.onGrid[i - 1].X + 1;
					aShip.shipType.onGrid[i].Y = aShip.shipType.onGrid[i - 1].Y;
				}
				if (aShip.direction == VERTICAL) {
					aShip.shipType.onGrid[i].Y = aShip.shipType.onGrid[i - 1].Y + 1;
					aShip.shipType.onGrid[i].X = aShip.shipType.onGrid[i - 1].X;
				}

				//dodaje pozosta³e punkty dla obecnego gracza
				player[aplyr].grid[aShip.shipType.onGrid[i].X][aShip.shipType.onGrid[i].Y] = isSHIP;
			}
			//Pêtla dla kazdego typu statku
		}
		//Pêtla dla ka¿dego gracza
	}

	//********* Koniec fazy rozstawiania statku *********************************
	//*****************************************************************************

	//Czas rozpoczac gre
	gameRunning = true;
	int thisPlayer = 1;
	do {
		//Teraz my atakujemy 
		//wyswietla sie plansza przeciwnika
		int enemyPlayer;
		if (thisPlayer == 1) enemyPlayer = 2;
		if (thisPlayer == 2) enemyPlayer = 1;
		system("cls");
		DrawBoard(enemyPlayer);

		//Atak gracza na okreslonych wspolrzednych 
		bool goodInput = false;
		int x, y;
		while (goodInput == false) {
			goodInput = UserInputAttack(x, y, thisPlayer);
		}

		//Sprawdza czy strza³ byl dobry
		if (player[enemyPlayer].grid[x][y] == isSHIP) player[enemyPlayer].grid[x][y] = isHIT;
		if (player[enemyPlayer].grid[x][y] == isWATER) player[enemyPlayer].grid[x][y] = isMISS;

		//Sprawdza czy gra sie zakonczyla
		//jestli 0 jest zwracane, to znaczy ze na planszy pozostaly statki
		int aWin = GameOverCheck(enemyPlayer);
		if (aWin != 0) {
			gameRunning = false;
			break;
		}
		//Atakujemy sie naprzemiennie 
		thisPlayer = (thisPlayer == 1) ? 2 : 1;
	} while (gameRunning);

	system("cls");
	cout << "\n\nGratulacje!!!  Graczu " << thisPlayer << " Wygrales gre!\n\n\n\n";

	system("pause");
	return 0;
}


bool GameOverCheck(int enemyPLAYER)
{
	bool winner = true;
	//Petla poprzez kazdy z plansz
	for (int w = 0; w < BOARD_WIDTH; ++w) {
		for (int h = 0; h < BOARD_HEIGHT; ++h) {
			//Jesli sa jesczcze staki, gra sie nie zakonczyla 
			if (player[enemyPLAYER].grid[w][h] = isSHIP)
			{
				winner = false;
				return winner;
			}
		}
	}
	//Zwraca zwyciezce
	return winner;
}


bool UserInputAttack(int& x, int& y, int theplayer)
{
	cout << "\nGraczu " << theplayer << ", Podaj wspolrzedne do zatakowania : ";
	bool goodInput = false;
	cin >> x >> y;
	if (x < 0 || x >= BOARD_WIDTH) return goodInput;
	if (y < 0 || y >= BOARD_HEIGHT) return goodInput;
	goodInput = true;
	return goodInput;
}

PLACESHIPS UserInputShipPlacement()
{
	int d, x, y;
	PLACESHIPS tmp;
	tmp.shipType.onGrid[0].X = -1;
	//Potrzebne 3 inty od gracza
	cin >> d >> x >> y;
	if (d != 0 && d != 1) return tmp;
	if (x < 0 || x >= BOARD_WIDTH) return tmp;
	if (y < 0 || y >= BOARD_HEIGHT) return tmp;
	//Dobre dane 
	tmp.direction = (DIRECTION)d;
	tmp.shipType.onGrid[0].X = x;
	tmp.shipType.onGrid[0].Y = y;
	return tmp;
}

void LoadShips()
{
	//Ustawiamy podstawowe dane dla statków 
	//Wazne!! > Musimy dostosowac stakti do ich dlugosc -Default=5 (0-4)
	ship[0].name = "Cruiser"; ship[0].length = 2;
	ship[1].name = "Frigate"; ship[1].length = 3;
	ship[2].name = "Submarine"; ship[2].length = 3;
	ship[3].name = "Escort"; ship[3].length = 4;
	ship[4].name = "Battleship"; ship[4].length = 5;
}
void ResetBoard()
{
	//Petla po kazdym graczu 
	for (int plyr = 1; plyr < 3; ++plyr)
	{
		//Dla kazdej kratki ustawiamy ,,wode'
		for (int w = 0; w < BOARD_WIDTH; ++w) {
			for (int h = 0; h < BOARD_HEIGHT; ++h) {
				player[plyr].grid[w][h] = isWATER;
			}
		}
		
	}
}

void DrawBoard(int thisPlayer)
{
	//Rysuje plansze dla obecnego gracza
	cout << "PLAYER " << thisPlayer << "'s GAME BOARD\n";
	cout << "----------------------\n";

	//Petla przechodzaca przez plansze
	cout << "   ";
	for (int w = 0; w < BOARD_WIDTH; ++w) {
		if (w < 10)
			//Cyfyry do jednosci, dodaj 2 spacje 
			cout << w << "  ";
		else if (w >= 10)
			//Cyfry dziesiêtne, dodaj 1 spacje 
			cout << w << " ";
	}
	cout << "\n";

	//Petla przechdoaca przez kazda kratkê oraz ja wyswietla
	for (int h = 0; h < BOARD_HEIGHT; ++h) {
		for (int w = 0; w < BOARD_WIDTH; ++w) {

			//Jesli jest to pierwszy lewy punkt siatki to nalezy ustawic jako pierwszy 
			if (w == 0) cout << h << " ";
			//jesli h ma dlugosc 1 znaku to dodaje spacje 
			if (w < 10 && w == 0) cout << " ";
			//Wyswietla plansze
			//wyswitla statki 
			if (gameRunning == false) cout << player[thisPlayer].grid[w][h] << "  ";
			//Nie pokazuje statku lecz zadane obrazenia 
			if (gameRunning == true && player[thisPlayer].grid[w][h] != isSHIP)
			{
				cout << player[thisPlayer].grid[w][h] << "  ";
			}
			else if (gameRunning == true && player[thisPlayer].grid[w][h] == isSHIP)
			{
				cout << isWATER << "  ";
			}
			//Jestli dotarlismy do granicy to podaj linie 
			if (w == BOARD_WIDTH - 1) cout << "\n";
		}
	}
}