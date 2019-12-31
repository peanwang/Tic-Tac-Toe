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
	// ��ʶ����λ��
	struct Position {
		int i, j;
	};
///* ��ʶ���ƣ�
//		human ����Ӯ
//		computer ����Ӯ
//		draw    ƽ��
//		unsure   δȷ��
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
	// i == 0 ,��������
	// i == 1 ,��������
	Board(char i);
	// ��ӡ���̺���
	void display();
	//  point���λ���Ƿ�������
	//  û�з���true
	//  �з���false
	bool isblank(Position point);
	bool isblank(int i, int j);
	//  ��һ��������point�����
	//  ����true��ʾ�ɹ�
	//  ����false����ʾ�õ�������
	int move(Position point);
	//  �������� �жϾ���
	//   ����human��ʾ����Ӯ
	//   ����computer��ʾ����Ӯ
	//   ����draw��ʾƽ��
	//   ����unsure ��ʾδȷ��
	condition evaluate();
	//ʹ��minimax�㷨�������ǰ���Ž�
	Position BestMove();
	Turn getter() {
		return turn;
	}

private:
	enum class Player board[3][3];
	Turn turn;
	int time;

	//��ʼ��
	void init();
///*
//	ʹ��minimax�㷨������������Ž�
//*/
	int minimax(int depth);
};

