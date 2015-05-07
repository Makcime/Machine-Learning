#include "gom_ai.h"

GOM_Ai::GOM_Ai(Player* Me, Player * Him, GameDeck* deck){
	// for (int i = 0; i < MAP_SIZE; ++i)
	// 	printf("%2d : %2d ; %2d ; %2d ; %d\n", i, nextMoves[i][0],
	// 		nextMoves[i][1], nextMoves[i][2], nextMoves[i][3]);

	this->pMe = Me;
	this->pHim = Him;
	this->pDeck = deck;
	this->nextGame = new int[MAP_SIZE];
}

int GOM_Ai::StaticEvaluation(int *game){
	int myMills = 0, hisMills = 0, myAlmostMills = 0, hisAlmostMills = 0;

	myMills = cntMills(game, 2);
	hisMills = 2 * cntMills(game, 1);

	myAlmostMills = cntAlmostMills(game, 2);
	hisAlmostMills = 2 * cntAlmostMills(game, 1);

	int hisPawns = pHim->getPawnsCnt();
	int myPawns = pMe->getPawnsCnt();
	// int eval = (myMills - hisMills) + (myPawns - hisPawns);
	int eval = 2*(myMills - hisMills) + (myAlmostMills - hisAlmostMills);

	// printf("Eval : %d\n", eval);
	return eval;

}

void GOM_Ai::GoForMinMax(int* game, int deep){
	// printDeck(game);
	// getchar();
	vector <int*> children;
	children = findChildren(game, 2);
	int value =0, maxValue = -1000;;
	for (vector<int*>::iterator child = children.begin(); 
				child != children.end(); ++child){
		value = MinMax((*child), deep+1);
		if(value > maxValue){
			this->nextGame = (*child);
			maxValue = value;
		}
	}
}

int GOM_Ai::MinMax(int* game, int deep){
	// printDeck(game);
	// getchar();
	vector <int*> children;
	if(deep == MAX_DEPTH){
		return StaticEvaluation(game);
	}
	// Maximise
	else if(!(deep %2)){
		// puts("Maximise");
		children = findChildren(game, 2);
		int value =0, maxValue = -1000;
		for (vector<int*>::iterator child = children.begin(); 
					child != children.end(); ++child){
			value = MinMax((*child), deep+1);
			if(value > maxValue){
				maxValue = value;
			}
		}
		return maxValue;
	}
	// Minimize
	else{
		// puts("Minimize");
		children = findChildren(game, 1);
		int value =0, minValue = 1000;
		for (vector<int*>::iterator child = children.begin(); 
					child != children.end(); ++child){
			value = MinMax((*child), deep+1);
			if(value < minValue){
				minValue = value;
			}
		}
		return minValue;
	}
}

void GOM_Ai::setDepth(int d){
	this->depth = d;
}


vector <int*> GOM_Ai::findChildren(int * game, int pl){
	vector <int*> children;

	if(this->phase == PLACEMENT){
		for (int i = 0; i < NODES; ++i){
			if(game[places[i]] == 0){
				int* newChild = new int[MAP_SIZE];
				for (int j = 0; j < MAP_SIZE; ++j)
					newChild[j] = game[j];
				newChild[places[i]] = pl;
				children.push_back(newChild);
			}
		}
		return children;	
	}
	else if(this->phase == MOUVEMENT);
		// pour chaque pion 2, un enfant pour chaque nextCase libre
}

void GOM_Ai::CheckMills(int *cnt, int *game){
	int p = 0;
	while(p<2){
		cnt[p] = 0;
		for (int i = 0; i < MILLS; ++i){
			if((game[Mills[i][0]] == p) &&
				(game[Mills[i][1]] == p) &&
				(game[Mills[i][2]] == p)){
				cnt[p]++;
			}
		}
		p++;
	}
}

int GOM_Ai::cntMills(int* game, int p){
	int cnt = 0;
	for (int i = 0; i < MILLS; ++i){
		if((game[Mills[i][0]] == p) &&
				(game[Mills[i][1]] == p) &&
				(game[Mills[i][2]] == p)){
				cnt++;
			}
		}
		return cnt;
}

int GOM_Ai::cntAlmostMills(int* game, int p){
	int cnt = 0;
	for (int i = 0; i < MILLS; ++i){
		if((game[Mills[i][0]] == p) &&
				(game[Mills[i][1]] == p) &&
				(game[Mills[i][2]] == 0)){
				cnt++;
			}
		else if((game[Mills[i][0]] == p) &&
				(game[Mills[i][1]] == 0) &&
				(game[Mills[i][2]] == p)){
				cnt++;
			}
		else if((game[Mills[i][0]] == 0) &&
				(game[Mills[i][1]] == p) &&
				(game[Mills[i][2]] == p)){
				cnt++;
			}

		}
		return cnt;
}

// int GOM_Ai::possibleMovesCnt(int* game, int p){
// 	int cnt = 0;
// 	for (int i = 0; i < MILLS; ++i){
// 		if((game[Mills[i][0]] == p) &&
// 				(game[Mills[i][1]] == p) &&
// 				(game[Mills[i][2]] == p)){
// 				cnt++;
// 			}
// 		}
// 		return cnt;
// }

void GOM_Ai::play(int phase, int* game){
	this->depth = 0;
	this->phase = phase;

	this->pawnToMove = NULL;
	this->pawnToRemove = NULL;
	this->whereToMove = NULL;

	for (int i = 0; i < MAP_SIZE; ++i){
		this->nextGame[i] = game [i];
	}

	// printDeck(game);
	// printDeck(this->nextGame);
	// printf("Min Max = %f\n", MinMax(game, 0));
	GoForMinMax(game, 0);
	printDeck(this->nextGame);
	// MinMax(game);

	compareGames(game);

	if(pawnToRemove){
		pHim->selectPawn(pawnToRemove);
	}
	if(pawnToMove){
		pMe->selectPawn(pawnToMove);
	}
	if(whereToMove){
		pDeck->selectVertex(whereToMove);
	}


}

void GOM_Ai::compareGames(int* initialGame){
	int j;
	if(this->phase == PLACEMENT)
		for (int i = 0; i < NODES; ++i){
			j = places[i];
			if(initialGame[j] < this->nextGame[j]){
				pDeck->selectVertex(j);
			}else if(initialGame[j] > this->nextGame[j]){
				if(initialGame[j] == 2){
					pMe->selectPawn(j);
				}else if(initialGame[j] == 1){
					pHim->selectPawn(j);
				}
			}
		}
	else if(this->phase == MOUVEMENT);
		// pour chaque pion 2, un enfant pour chaque nextCase libre
}

void GOM_Ai::printDeck(int * g){
	printf("\n|----------------------------|\n|");
	for (int i = 0; i < MAP_SIZE; ++i)
	{
		if((!(i%7)) & i!=0)
			printf("|\n|");
		if(g[i]>=0)
			printf(" %02d ",g[i]);
		else
			printf("    ");
	}
	puts("|\n|----------------------------|");
}