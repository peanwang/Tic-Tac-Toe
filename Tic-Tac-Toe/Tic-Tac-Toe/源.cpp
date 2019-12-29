#include<cstdio>
#include<algorithm>

typedef struct {
	int board[3][3];
	int turn;
}state;

typedef struct {
	int i, j;
}Move;

void init(state* s) {
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			s->board[i][j] = -1;
	s->board[1][1] = 0;
	s->turn = 1;
}

void display(state* s) {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			switch (s->board[i][j]) {
			case -1:
				printf(" %d ", i * 3 + j + 1);
				break;
			case 0:
				printf(" O ");
				break;
			case 1:
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

int move(state *s, int i, int j) {
	if (s->board[i][j] != -1)
		return 0;
	s->board[i][j] = s->turn++ % 2;
	return 1;
}

void human(state *s) {
	char c;
	do {
		printf("%c: ", "OX"[s->turn % 2]);
		c = getchar();
		while (getchar() != '\n');
		printf("\n");
	} while (c<'1' || c> '9' || !move(s, (c - '1') / 3, (c - '1') % 3));
}

int evaluate(const state* s) {
	for (int i = 0; i < 3; i++) {
		if (s->board[i][0] != -1 && s->board[i][0] == s->board[i][1] && s->board[i][0] == s->board[i][2])
			return s->board[i][0] == 0 ? 1 : -1;
		if (s->board[0][i] != -1 && s->board[0][i] == s->board[1][i] && s->board[0][i] == s->board[2][i])
			return s->board[0][i] == 0 ? 1 : -1;
	}
	if (s->board[0][0] != -1 && s->board[0][0] == s->board[1][1] && s->board[0][0] == s->board[2][2])
		return s->board[0][0] == 0 ? 1 : -1;
	if (s->board[0][2] != -1 && s->board[0][2] == s->board[1][1] && s->board[0][2] == s->board[2][0])
		return s->board[0][2] == 0 ? 1 : -1;
	return 0;
}


int minimax(state* s) {
	int score = evaluate(s);

	if (score == 1)
		return 10;		// O win

	if (score == 1)
		return -1;		// X win

	if (s->turn % 2 == 0) {
		int best = -1000;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (s->board[i][j] == -1) {
					s->board[i][j] = 0;
					s->turn++;
					best = std::max(best,
						minimax(s));
					s->board[i][j] = -1;
					s->turn--;
				}
			}
		}
		return best;
	}
	else {
		int best = 1000;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (s->board[i][j] == -1) {
					s->board[i][j] = 1;
					s->turn++;
					best = std::min(best,
						minimax(s));
					s->board[i][j] = -1;
					s->turn--;
				}
			}
		}
		return best;
	}
}

Move findBestMove(state* s) {
	int bestVal = -1000;
	Move bestmove;
	bestmove.i = -1;
	bestmove.j = -1;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (s->board[i][j] == -1) {
				s->board[i][j] = 0;

				int moveval = minimax(s);
				s->board[i][j] = -1;

				if (moveval > bestVal) {
					bestVal = moveval;
					bestmove.i = i;
					bestmove.j = j;
				}
			}
		}
	}
	return bestmove;
}

int main() {
	state s;
	init(&s);
	display(&s);
	while (s.turn < 9) {
		human(&s);
		display(&s);
		Move bestmove = findBestMove(&s);
		move(&s, bestmove.i, bestmove.j);
		display(&s);
		switch (evaluate(&s)) {
		case 1:
			printf("O win\n");
			return 0;
		case -1:
			printf("X win\n");
			return 0;
		}
	}
	printf("Draw\n");
}


