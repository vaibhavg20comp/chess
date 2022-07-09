// ChessJedi.c

#include "stdio.h"
#include "defs.h"
#include "stdlib.h"
#include<stdbool.h>
#include "init.c"
#include "pvtable.c"
#include "hashkeys.c"
#include "board.c"
#include "data.c"
#include "bitboards.c"
#include "evaluate.c"
#include "makemove.c"
#include "movegen.c"
#include "perft.c"
#include "misc.c"
#include "search.c"
#include "validate.c"
#include "pvtable.c"
#include "io.c"
#include "attack.c"



// sample position
#define WAC1 "r1b1k2r/ppppnppp/2n2q2/2b5/3NP3/2P1B3/PP3PPP/RN1QKB1R w KQkq - 0 1"

int main() {	

	AllInit();		
	// denotes the mode of game 1 single player 2 double player
	int num_players,hardness;
	printf("\n Enter the mode:\n");
	printf("1.Play against Computer\n");
	printf("2.Play against a friend \n");
	scanf("%d",&num_players);
	bool sethardness=false;
	while(num_players==1 && !sethardness){
		printf("Enter hardness level \n 1.Easy 2.Medium 3.Hard \n > ");
		scanf("%d",&hardness);
		if(hardness==1 || hardness==2 || hardness==3){
			sethardness=true;
		}else{
			printf("Invalid Input!!!! Try again!\n");
		}
	}
	S_BOARD board[1];
	board->PvTable->pTable = NULL;
	InitPvTable(board->PvTable);
	
	S_MOVELIST list[1];
	S_SEARCHINFO info[1];
	ParseFen(START_FEN,board);
	
	char input[6];
	int Move = NOMOVE;
	int PvNum = 0;
	int Max = 0;
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }
	while(TRUE) {
		PrintBoard(board);
		
		printf("Please enter a move > ");
		fgets(input, 6, stdin);
		printf("%s",input);
		if(input[0]=='q') {
			break;
		} else if(input[0]=='t') {
			TakeMove(board);			
		} else if(input[0]=='s') {
			info->depth = 5;
			SearchPosition(board, info);
		} else{
			Move = ParseMove(input, board);
			if(Move != NOMOVE) {
				StorePvMove(board, Move);
				MakeMove(board,Move);
			} else {
				printf("Move Not Parsed:%s\n",input);
				fflush(stdin);
				continue;
			}
		}
		if(num_players==1){
			switch (hardness){
				case 1:
					info->depth=4;
					break;
				case 2:
					info->depth=6;
					break;
				case 3:
					info->depth=8;
					break;
			}
			int Move=getbestMove(board,info);
			StorePvMove(board,Move);
			MakeMove(board,Move);
		}	
		
		fflush(stdin);
	}
	
	free(board->PvTable->pTable);
	
	return 0;
}








