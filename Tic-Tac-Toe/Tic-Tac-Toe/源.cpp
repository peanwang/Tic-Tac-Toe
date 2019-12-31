#define  _CRT_SECURE_NO_WARNINGS
#include "board.h"
#include<cstdio>
#include<cctype>
Board::Position human(Board& board) {
	char c;
	do {
		printf("please enter your move %c:",Board::Player::human);
		scanf("%c", &c);
		while (getchar() != '\n');
		printf("\n");
	} while (!((c>'1' || c < '9') && board.isblank((c - '1') / 3, (c - '1') % 3) ));
	Board::Position point;
	point.i = (c - '1') / 3;
	point.j = (c - '1') % 3;
	return point;
}

int main()
{
	char c;
	printf("%Please enter computer first(enter C or c) or you first(enter H or h)?\n");
	do {
		scanf("%c", &c);
		while(getchar() !='\n');
		printf("\n");
	} while (!(tolower(c) == 'h' || tolower(c) == 'c'));
	Board board(c);
	board.display();
	while (true) {
		if (board.getter() == Board::Turn::human) {
			Board::Position point = human(board);
			board.move(point);
		}
		else {
			Board::Position bestpoint = board.BestMove();
			board.move(bestpoint);
			printf("Computer move to : %d\n\n", bestpoint.i * 3 + bestpoint.j+1);
		}
		board.display();
		switch(board.evaluate())
		{
		case Board::condition::computer:
			printf("Computer win!!");
			return 0;
		case Board::condition::human:
			printf("human win!!");
			return 0;
		case Board::condition::draw:
			printf("Draw!!");
			return 0;
		}
	}
}