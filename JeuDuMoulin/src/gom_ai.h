/**
 * @file ai.h
 * @brief 
 *
 * @author Marlier Maxime <marlier.maxime@gmail.com>
 *
 **/

#ifndef GOM_AI		
#define GOM_AI

#include "player.h"	
#include "graph.h"
#include "gameDeck.h"

#define MAX_DEPTH 5
#define NODES 23

#define MILLS 16

class GOM_Ai
{

private:
	//*
	int nextMoves[MAP_SIZE][4]{{3,21,-1,-1},
	{-1,-1,-1,-1},{-1,-1,-1,-1},{0,6,10,-1},{-1,-1,-1,-1},
	{-1,-1,-1,-1},{3,27,-1,-1},{-1,-1,-1,-1},{10,22,-1,-1},
	{-1,-1,-1,-1},{3,8,12,17},{-1,-1,-1,-1},{10,26,-1,-1},
	{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{23,17,-1,-1},
	{10,16,18,-1},{17,25,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},
	{0,22,42,-1},{8,21,23,36},{16,22,30,-1},{-1,-1,-1,-1},
	{18,26,32,-1},{12,25,27,40},{6,26,48,-1},{-1,-1,-1,-1},
	{-1,-1,-1,-1},{23,31,-1,-1},{30,32,38,-1},{25,31,-1,-1},
	{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{22,38,-1,-1},
	{-1,-1,-1,-1},{31,36,40,45},{-1,-1,-1,-1},{26,38,-1,-1},
	{-1,-1,-1,-1},{21,45,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},
	{38,42,45,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{27,45,-1,-1}
	};

	int places [NODES] =
	{0,3,6,8,10,12,16,17,18,21,22,23,26,27,30,31,32,36,38,40,42,45,48};
	//*/

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

	int *nextGame; // [MAP_SIZE] = {0};

	int depth = 0;
	int phase;

	Pawn* pawnToMove = NULL;
	Pawn* pawnToRemove = NULL;
	vertex* whereToMove = NULL;

	Player *pMe, *pHim;
	GameDeck* pDeck;


	int MillCnt[2] = {0};

	enum phase{PLACEMENT, MOUVEMENT, REMOVING, EOG};

public:

	int StaticEvaluation(int *game);
	int MinMax(int* game, int deep);
	int MinMax(int* game, int deep, int alpha, int beta);
	void GoForMinMax(int* game, int deep);


	GOM_Ai(Player* Me, Player * Him, GameDeck* deck);

	void setDepth(int d);

	vector <int*> findChildren(int *game, int pl);
	void CheckMills(int *cnt, int *game);

	void play(int phase, int* game);

	void compareGames(int* initialGame);

	void printDeck(int * g);

	int cntMills(int* game, int p);
	int cntAlmostMills(int* game, int p);




};

#endif
