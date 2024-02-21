#ifndef GAME2048_H
#define GAME2048_H
#include <iostream>
#include "Board.h"
#include <ctime>

class Game2048 {
public:
	Game2048() { endTime = startTime = std::time(0); startGame(); }
	~Game2048() {};
	void startGame(void);
	char query(void);
	int  get_Score(void);
	void action(char);
	void addNumber(void);
	void print_grid(void);
	bool GameOver(void);
	time_t get_startTime()const { return startTime; }
	int get_Duration()const{ return endTime-startTime; }
private:
	Board board;
	time_t startTime;
	time_t endTime;
};
void Game2048::addNumber() {
	board.add2or4();
}

bool Game2048::GameOver() {
	if (board.isFull() && !board.canMerge())return true;
	else return false;
}

void Game2048::print_grid() {
	board.printGrid();
}

int Game2048::get_Score() {
	return board.getScore();
}

char Game2048::query() {
	char cmd;
	std::cout << "(\u2191:u) (\u2193:d) (\u2190:l) (\u2192:r) (quit:q):";
	std::cin >> cmd;
	//循环直至得到有效字符
	while (cmd != 'q' && cmd != 'u' && cmd != 'd' && cmd != 'l' && cmd != 'r') {
		std::cout << "(\u2191:u) (\u2193:d) (\u2190:l) (\u2192:r) (quit:q):";
		std::cin >> cmd;
	}
	return cmd;
}

void Game2048::action(char cmd) {
	board.move(cmd);
	board.merge(cmd);
	board.move(cmd);
}
void Game2048::startGame() {
	std::cout << "Welcome to the game of 2048!" << std::endl;
	char cmd;
	while (!GameOver()) {
		print_grid();
		std::cout << "Your score:" << get_Score() << std::endl;
		//获取指令
		cmd = query();
		if (cmd == 'q')break;
		else action(cmd);
		addNumber();
	}
	endTime = time(0);
	std::cout << "Game Over";
}
#endif

