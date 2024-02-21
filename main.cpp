#include <iostream>
#include <ctime>
#include<fstream>
#include<string>
#include "Game2048.h"

using std::endl;
using std::cout;
using std::srand;
using std::time;
using std::ofstream;
using std::string;


/*
*****************逻辑流程*******************
首先设计Board类

Board最核心的成员函数是move()和merge()
move()需要实现的是将元素向某一侧方向移动，
merge()实现的是在某一方向上相邻且相同的元素进行合并，同时修改得分
此外还有两个执行判断的函数,isFull()和canMerge()，分别判断网格是否填满，和是否有可以合并的元素。

Game2048类里需要记录游戏开始和终止的时间
构造函数里调用startGame()开始游戏
GameOver()函数用于判断游戏是否可以继续，当网格填满且无法合并时游戏结束。
action()函数根据输入的方向指令(direction)来进行移动合并操作
具体地action(direction){
   board.move(direction);
   board.merge(direction);
   board.move(direction);
}
board会朝direction方向先进行移动，使得相同的元素在该方向上相邻
然后在该方向上扫描相邻元素是否相同，如果相同进行合并。
最后再次朝该方向移动使得元素在该方向上紧密排列


startGame() {
	输出："Welcome to the game of 2048!"
	char cmd;//cmd用来获取用户输入的指令
	//只有游戏可以继续，就循环进行
	while (!GameOver()) {
		//输出网格和得分
		print_grid();
		std::cout << "Your score:" << get_Score() << std::endl;
		
		//获取指令
		cmd = query();
		if (cmd == 'q')break;
		
		//根据用户输入的指令来执行操作
		else action(cmd);
		//向网格中添加数字
		addNumber();
	}
	//退出游戏时记录游戏终止时间
	endTime = time(0);
	std::cout << "Game Over";
*/


int main() {
	srand(time(0));
	ofstream file("game2048.csv", ofstream::app);
	Game2048 game;
	time_t a = game.get_startTime();
	string s = std::ctime(&a);
	s = s.erase(s.find('\n'));
	//cout << s << ',' << game.get_Duration() << ',' << game.get_Score() << '\n';
	file << s << ',' << game.get_Duration() << ',' << game.get_Score() << '\n';
	return 0;
}
