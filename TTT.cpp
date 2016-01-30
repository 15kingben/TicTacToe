#include <stdio.h>


/*State: 2D array of board
initiative

Actions: avaiable spots to place x's and o's

Transition Model: update board state

Initial State: Empty Board, x goes first

Goal State: End when 3 in a row, Horiz, Vert, Diag
			No Empty Squares + no Goal = draw

*/

const int BOARD_SIZE = 3;
const int WINNER_SIZE = BOARD_SIZE*2+2;
void printBoard(int[BOARD_SIZE][BOARD_SIZE]);
void editBoard(int[BOARD_SIZE][BOARD_SIZE], int, int&, int&);
int updateBoard(int [BOARD_SIZE][BOARD_SIZE], int[WINNER_SIZE], int , int , bool);
void printWinners(int [WINNER_SIZE]);

#include <iostream>
#include <cmath>
using namespace std;

int main(){



	cerr << "Pick a side: ('X' or 'O' )" << endl;
	char side;
	cin >> side;
	while(side != 'X' && side != 'O' && side != 'x' && side!= 'o'){
		cerr << "Please, pick a side: ('X' or 'O') " << endl;
		cin >> side;
	}

	cerr << "You have chosen " << ((side == 'x' || side == 'X') ? "X" : "O") << " as your side." << endl;

	cerr << "Please make a move: (1-9)" << endl;
	int move;
	cin >> move;
	while(!(abs(move-1) < 9)){
		cerr << "Please make a move: (1-9)" << endl;
		cin >> move;
	}

	int posx, posy;
	int peices = 0;


	//Array of Board, Initialized to Blank
	//-1 = Empty
	// 0 = "0"
	// 1 = "X"
	//                     top     middle      bottom
	int board[3][3] = {{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}};

	//Array of Places on Board Still Open
	bool actions[3][3] = {{true,true,true},{true,true,true}, {true,true,true}};
	
	//Array holding the winners on each row/diagonal
	//0-2: horiz
	//3-5: vert
	//6-7: diag
	int winner[BOARD_SIZE*2 + 2] = {0};

	//Boolean of who has initiative
	//true = X
	//FALSE = O
	bool init = true;

	pieces++;
	editBoard(board, move, posx, posy);
	cout << posx << " " << posy << endl;
	updateBoard(board, winner, posx, posy, true);
	printWinners(winner);
	cout << endl;

	printBoard(board);
}





int pickNext(int board[BOARD_SIZE][BOARD_SIZE], int winner[WINNER_SIZE], bool actions[BOARD_SIZE][BOARD_SIZE],  int x, int y, bool isPlayer, int maxDepth, int pieces	){

	updateBoard(board, winner, x, y, isPlayer);
	int winnerValue = updateWinner(winner, isPlayer);

	//If weve found a winner or are at max recursion depth, exit the program
	if(winnerValue != 0 || maxDepth == 0)
		return winnerValue;//+heuristic

	//The Minimax part
	int m = (isPlayer) ? 1 : -1;

	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			int max = 0;
			if(actions[i][j]){
				
				//copy everything--BADDDDD
				bool newActions[BOARD_SIZE][BOARD_SIZE];
				memcpy(actions, newActions, sizeof(bool) * BOARD_SIZE * BOARD_SIZE);
				newActions[i][j] = false;

				

				pickNext(,pieces++)
			}
		}
	}
}









//
//Update Board and check the terminal condition of a board
//must be done together so that we can optimize out terminal checks to just those affected
//1 = Player win 
//0 = draw
//-1 = Enemy win
//null: nonterminal
int updateBoard(int board[BOARD_SIZE][BOARD_SIZE], int winner[WINNER_SIZE], int x, int y, bool isPlayer){
	board[x][y] = (isPlayer) ? 1 : 0;
	int d = (isPlayer) ? 1 : -1;
	winner[3+x]+= d;
	winner[y]+= d;
	if(y==x){
		winner[BOARD_SIZE*2]+= d;
	}
	if(y==0 && x==2 || y == 2 && x == 0 || ( y == 1 && x == 1)){
		winner[BOARD_SIZE*2+1]+= d;
	}
	
}

//update winner array based on move
//if isPlayer, add, else subtract
int updateWinner(int winner[WINNER_SIZE], bool isPlayer){
	for(int i = 0; i < WINNER_SIZE; i++){
		if(winner[i] >= 3){
			return 1;
		}
		if(winner[i] <= -3){
			return -1;
		}
	}
	return 0;
}






//Syntax is correct for passing array as pointer
//Method prints board as X's and O's
//Is maybe inverted dependent on how you input the board
void printBoard(int board[BOARD_SIZE][BOARD_SIZE]){
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			if(board[i][j] == -1 )
				printf("_");
			else if(board[i][j] == 0)
				printf("0");
			else
				printf("1");
			printf(" ");
		}
		printf("\n");
	}
}

//utility function to turn number into board coordinates
void editBoard(int [BOARD_SIZE][BOARD_SIZE], int num, int &retx, int &rety){
	switch (num){
		case 1:
			retx = 0;
			rety = 0;
			break;
		case 2:
			retx = 0;
			rety = 1;
			break;
		case 3:
			retx = 0;
			rety = 2;
			break;
		case 4:
			retx = 1;
			rety = 0;
			break;
		case 5:
			retx = 1;
			rety = 1;
			break;
		case 6:
			retx = 1;
			rety = 2;
			break;
		case 7:
			retx = 2;
			rety = 0;
			break;
		case 8:
			retx = 2;
			rety = 1;
			break;
		case 9:
			retx = 2;
			rety = 2;
			break;
	}
}

void printWinners(int w[WINNER_SIZE]){
	for(int i = 0; i < WINNER_SIZE; i++){
		cout << " " << w[i] << " " ;
	}
}