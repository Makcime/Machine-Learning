 /**
 * @file gameOfMill.h
 * @brief 
 *
 * @author Marlier Maxime <marlier.maxime@gmail.com>
 *
 **/

#ifndef GAMEOFFMILL		
#define GAMEOFFMILL

#include "gameDeck.h"
#include "player.h"
#include "gom_ai.h"

#define PAWN_NUMBER 9
#define BEERS 14
#define BG "../data/images/background.png"

#define MILLS 16


class GameOfMill
{

private:
	string beers[BEERS] = {
	"barbar",
	"bernardus",
	"carapils",
	"chimay",
	"chouffe",
	"duff",
	"jupiler",
	"karmeliet",
	"kwak",
	"leffe",
	"orval",
	"rochefort",
	"vedett",
	"westmalle",
	 };

	int Mills[MILLS][3] = {
	{0,3,6},
	{8,10,12},
	{16,17,18},
	{21,22,23},
	{25,26,27},
	{30,31,32},
	{36,38,40},
	{42,45,48},
	{0,21,42},
	{8,22,36},
	{16,23,30},
	{3,10,17},
	{31,38,45},
	{18,25,32},
	{12,26,40},
	{6,27,48}
	// {0,8,16},
	// {6,12,18},
	// {30,36,42},
	// {32,40,48}
	};

	int gameState[MAP_SIZE] = {0};

	GameDeck* deck;
	Player* playerOne;
	Player* playerTwo;
	GOM_Ai* computerPlayer;
	Player* currentPlayer;
	Player* opponentPlayer;
	int playerCnt;

	ofImage bg;

	enum phase{PLACEMENT, MOUVEMENT, REMOVING, EOG};

	int gamePhase;

	// bool endOfGame;

public:
	GameOfMill();
	~GameOfMill();

	void draw();

	void selectPawn();
	void selectPawnToRm();
    void selectPlace();
    void Play();
    void Go();
    void select();
    void newPhase();
    void CheckMills(Player* pl);

    void pawnCapture();
	
};

#endif
