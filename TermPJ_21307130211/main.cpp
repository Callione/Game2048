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
*****************�߼�����*******************
�������Board��

Board����ĵĳ�Ա������move()��merge()
move()��Ҫʵ�ֵ��ǽ�Ԫ����ĳһ�෽���ƶ���
merge()ʵ�ֵ�����ĳһ��������������ͬ��Ԫ�ؽ��кϲ���ͬʱ�޸ĵ÷�
���⻹������ִ���жϵĺ���,isFull()��canMerge()���ֱ��ж������Ƿ����������Ƿ��п��Ժϲ���Ԫ�ء�

Game2048������Ҫ��¼��Ϸ��ʼ����ֹ��ʱ��
���캯�������startGame()��ʼ��Ϸ
GameOver()���������ж���Ϸ�Ƿ���Լ������������������޷��ϲ�ʱ��Ϸ������
action()������������ķ���ָ��(direction)�������ƶ��ϲ�����
�����action(direction){
   board.move(direction);
   board.merge(direction);
   board.move(direction);
}
board�ᳯdirection�����Ƚ����ƶ���ʹ����ͬ��Ԫ���ڸ÷���������
Ȼ���ڸ÷�����ɨ������Ԫ���Ƿ���ͬ�������ͬ���кϲ���
����ٴγ��÷����ƶ�ʹ��Ԫ���ڸ÷����Ͻ�������


startGame() {
	�����"Welcome to the game of 2048!"
	char cmd;//cmd������ȡ�û������ָ��
	//ֻ����Ϸ���Լ�������ѭ������
	while (!GameOver()) {
		//�������͵÷�
		print_grid();
		std::cout << "Your score:" << get_Score() << std::endl;
		
		//��ȡָ��
		cmd = query();
		if (cmd == 'q')break;
		
		//�����û������ָ����ִ�в���
		else action(cmd);
		//���������������
		addNumber();
	}
	//�˳���Ϸʱ��¼��Ϸ��ֹʱ��
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
