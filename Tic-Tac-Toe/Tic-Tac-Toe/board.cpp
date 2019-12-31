#include "board.h"
#include<cstdio>
#include<algorithm>
#include<cctype>

Board::Board(char i)
{
	this->init();
	if (tolower(i) == 'h')
		this->turn = Turn::human;
	else
		this->turn = Turn::computer;
}

void Board::init()
{
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			this->board[i][j] = Player::none;
	this->time = 0;
}

int Board::minimax(int depth)
{
	condition current = evaluate();
	
	if (current == condition::computer)
		return 10-depth;
	else if (current == condition::human)
		return -10+depth;
	else if (current == condition::draw)
		return -depth;
	if (this->turn == Turn::computer) {
		int best = -1000;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (this->board[i][j] == Player::none) {
					this->board[i][j] = Player::computer;
					this->turn  = Turn::human;
					this->time++;
					best = std::max(best, minimax( depth + 1));
					this->board[i][j] = Player::none;
					this->turn = Turn::computer;
					this->time--;
				}
			}
		}
		return best;
	}
	else {
		int best = 1000;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (this->board[i][j] == Player::none) {
					this->board[i][j] = Player::human;
					this->turn = Turn::computer;
					this->time++;
					best = std::min(best,minimax(depth+1));
					this->board[i][j] =Player::none;
					this->turn = Turn::human;
					this->time--;
				}
			}
		}
		return best;
	}
}


Board::Position Board::BestMove()
{
	Position bestmove{-1,-1};
	int score = -2000;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (this->board[i][j] == Player::none) {
				this->board[i][j] = Player::computer;
				this->turn = Turn::human;
				this->time++;
				int temp = minimax(0);

				if (temp > score) {
					score = temp;
					bestmove.i = i;
					bestmove.j = j;
				}
				this->board[i][j] = Player::none;
				this->turn = Turn::computer;
				this->time--;
			}
		}
	}
	return bestmove;
}

int Board::move(Position point)
{
	if (!isblank(point))
		return 0;
	if (this->turn == Turn::computer) {
		this->board[point.i][point.j] = Player::computer;
		this->turn = Turn::human;
	}
	else {
		this->board[point.i][point.j] = Player::human;
		this->turn = Turn::computer;
	}
	this->time++;
	return 1;
}


Board::condition Board::evaluate()
{
	for (int i = 0; i < 3; i++) {
		if (this->board[i][0] != Player::none && this->board[i][0] == this->board[i][1] && this->board[i][0] == this->board[i][2]) {
			if (this->board[i][0] == Player::computer)
				return condition::computer;
			else if (this->board[i][0] == Player::human)
				return condition::human;
		}
		if (this->board[0][i] != Player::none && this->board[0][i] == this->board[1][i] && this->board[0][i] == this->board[2][i]) {
			if (this->board[0][i] == Player::computer)
				return condition::computer;
			else if (this->board[0][i] == Player::human)
				return condition::human;
		}
	}
	if (this->board[0][0] != Player::none && this->board[0][0] == this->board[1][1] && this->board[0][0] == this->board[2][2]) {
		if (this->board[0][0] == Player::computer)
			return condition::computer;
		else if (this->board[0][0] == Player::human)
			return condition::human;
	}
	if (this->board[0][2] != Player::none && this->board[0][2] == this->board[1][1] && this->board[0][2] == this->board[2][0]) {
		if (this->board[0][2] == Player::computer)
			return condition::computer;
		else if (this->board[0][2] == Player::human)
			return condition::human;
	}
	if (this->time == 9)
		return condition::draw;
	else
		return condition::unsure;
}


void Board::display()
{
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			switch (this->board[i][j]) {
			case Player::none:
				printf(" %d ", i * 3 + j + 1);
				break;
			case Player::computer:
				printf(" O ");
				break;
			case Player::human:
				printf(" X ");
				break;
			}
			if (j < 2)
				printf("|");
			else
				printf("\n");
		}
		if (i < 2)
			printf("---+---+---\n");
		else
			printf("\n");
	}
}

bool Board::isblank(Position point)
{
	if (this->board[point.i][point.j] == Player::none)
		return true;
	else
		return false;
}

bool Board::isblank(int i, int j)
{
	Position p;
	p.i = i;
	p.j = j;
	return isblank(p);
}





