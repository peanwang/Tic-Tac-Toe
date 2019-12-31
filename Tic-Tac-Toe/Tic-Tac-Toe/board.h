#pragma once
class Board
{
public:
	enum class Player
	{
		none = '-',
		human = 'X',
		computer = 'O'
	};
	// 标识棋盘位置
	struct Position {
		int i, j;
	};
///* 标识局势，
//		human 人类赢
//		computer 电脑赢
//		draw    平局
//		unsure   未确定
//*/
	enum class condition {
		human = 0,
		computer = 1,
		draw = 2,
		unsure = 3
	};
	enum class Turn
	{
		human = 0,
		computer = 1
	};
	// i == 0 ,人类先下
	// i == 1 ,电脑先下
	Board(char i);
	// 打印棋盘函数
	void display();
	//  point这个位置是否有棋子
	//  没有返回true
	//  有返回false
	bool isblank(Position point);
	bool isblank(int i, int j);
	//  下一个棋子在point这个点
	//  返回true表示成功
	//  返回false，表示该点有棋子
	int move(Position point);
	//  评估函数 判断局势
	//   返回human表示人类赢
	//   返回computer表示电脑赢
	//   返回draw表示平局
	//   返回unsure 表示未确定
	condition evaluate();
	//使用minimax算法，算出当前最优解
	Position BestMove();
	Turn getter() {
		return turn;
	}

private:
	enum class Player board[3][3];
	Turn turn;
	int time;

	//初始化
	void init();
///*
//	使用minimax算法，算出电脑最优解
//*/
	int minimax(int depth);
};

