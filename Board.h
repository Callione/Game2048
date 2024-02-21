#ifndef BOARD_H
#define BOARD_H

#include<iostream>
#include<vector>
#include<random>
//#include<ctime>

class Board {
private:
	std::vector<std::vector<int>> grid;
	int score;
	int length;
public:
	Board(){
		length = 4;
		grid = std::vector<std::vector<int>>(length, std::vector<int>(length, 0));
		add2();
		add2();
		score = 0;
	}
	int getScore()const { return score; };
	void printGrid();
	void add2or4();
	void add2();//���ڳ�ʼ��
	//����Ĳ����Ƿ���'u''d''l''r'
	void move(char);
	void merge(char);//ֻ���ں�����Ԫ�أ��м���0������Ԫ���޷���merge�����Ե���֮ǰ��move

	void move_left(void);
	void move_up(void);
	void flip(char);//ˮƽ��ֱ��ת 'h'Ϊˮƽ  'v'Ϊ��ֱ


	bool isFull(void);
	bool canMerge(void);
};


bool Board::canMerge(){

	//ˮƽ����ļ�⣬���ÿһ��
	for (int i = 0; i < length; i++) {
		for(int j = 0; j < length - 1;) {
			while (j < length && grid[i][j] == 0)j++;//����ǰ��0Ԫ
			if (j >= length - 1)break;
			int next = j+1;
			while (next < length && grid[i][next] == 0)next++;//next�����ҵ�����ķ�0Ԫ
			if (next < length && grid[i][j] == grid[i][next]) return true;
			
			if (next < length)j = next;
			else break;
		}
	}
	//��ֱ����ļ�⣬���ÿһ��
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length - 1;) {
			while (j < length && grid[j][i] == 0)j++;//����ǰ��0Ԫ
			if (j >= length - 1)break;
			int next = j + 1;
			while (next < length && grid[next][i] == 0)next++;//next�����ҵ�����ķ�0Ԫ
			if (next < length && grid[j][i] == grid[next][i]) return true;

			if (next < length)j = next;
			else break;
		}
	}
	return false;
}

void Board::merge(char direction) {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length-1; j++) {
			if (direction == 'l') {
				//������������ͬԪ��
				if (grid[i][j] && grid[i][j] == grid[i][j + 1]) {
					grid[i][j] *= 2;
					grid[i][j + 1] = 0;
					score += grid[i][j];
				}
			}
			else if (direction == 'r') {
				//������������ͬԪ��
				if (grid[i][length-1-j] && grid[i][length-1-j] == grid[i][length-2-j ]) {
					grid[i][length-1-j] *= 2;
					grid[i][length-2-j] = 0;
					score += grid[i][length - 1 - j];
				}
			}
			else if (direction == 'u') {
				//������������ͬԪ��
				if (grid[j][i] && grid[j][i] == grid[j+1][i]) {
					grid[j][i] *= 2;
					grid[j+1][i] = 0;
					score += grid[j][i];
				}
			}
			else if (direction == 'd') {
				//������������ͬԪ��
				if (grid[length-1-j][i] && grid[length-1-j][i] == grid[length-2-j][i]) {
					grid[length-1-j][i] *= 2;
					grid[length-2-j][i] = 0;
					score += grid[length - 1 - j][i];
				}
			}
		}
	}
}

void Board::move(char direction) {
	if (direction == 'l')move_left();
	else if (direction == 'r') {
		flip('h');
		move_left();
		flip('h');
	}
	else if (direction == 'u')move_up();
	else if (direction == 'd') {
		flip('v');
		move_up();
		flip('v');
	}
}

bool Board::isFull() {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			if (grid[i][j] == 0)return false;
		}
	}
	return true;
}
void Board::flip(char direction) {
	int tmp;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length/2; j++) {
			if(direction == 'h')//'h' for horizontal flip
			{	tmp = grid[i][j];
				grid[i][j] = grid[i][length - 1 - j];
				grid[i][length - 1 - j] = tmp;
			}
			else if (direction == 'v')//'v' for vertical flip
			{
				tmp = grid[j][i];
				grid[j][i] = grid[length - 1 - j][i];
				grid[length - 1 - j][i] = tmp;
			}
		}
	}
}
void Board::move_up() {
	for (int i = 0; i < length; i++) {
		//�Ե�i��Ԫ�أ��������Ʋ���
		std::vector<int>tmp;
		for (int j = 0; j < length; j++) {
			if (grid[j][i])tmp.push_back(grid[j][i]);
		}//��˳���¼��0Ԫ

		for (int j = 0; j < length; j++) {
			if (j < tmp.size())grid[j][i] = tmp[j];
			else grid[j][i] = 0;
		}
	}
}

void Board::move_left() {
	
	for (int i = 0; i < length; i++) {
		//���ڵ�i�е�Ԫ�أ��������Ʋ���
		std::vector<int>tmp;
		for (int j = 0; j < length; j++) {
			if (grid[i][j])tmp.push_back(grid[i][j]);
		}//��˳���¼��0Ԫ
		
		for (int j = 0; j < length; j++) {
			if (j < tmp.size())grid[i][j] = tmp[j];
			else grid[i][j] = 0;
		}

	}
}
void Board::add2() {
	std::vector<int>x;
	std::vector<int>y;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			if (grid[i][j] == 0) {
				x.push_back(i);
				y.push_back(j);
			}
		}
	}
	//����пհ׸��ӣ�����ѡһ��λ��
	if (x.empty())return;
	int r = std::rand() % x.size();
	grid[x[r]][y[r]] = 2;
}

void Board::add2or4() {
	//�ȱ���grid�����հ׸��ӵ������¼��x,y��
	std::vector<int>x;
	std::vector<int>y;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			if (grid[i][j]==0) {
				x.push_back(i);
				y.push_back(j);
			}
		}
	}
	//����пհ׸��ӣ�����ѡһ��λ��
	if (x.empty())return;
	int r = std::rand() % x.size();

	//����ӵ�ֵ��1/5�ĸ���Ϊ4��Ϊ2�ĸ�����4/5
	int val = std::rand() % 5;
	if (val != 4)val = 2;

	//�����ֵ
	grid[x[r]][y[r]] = val;
}
void Board::printGrid() {
	int val;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++)
		{
			std::cout << "|-----";
		}
		std::cout << '|' << std::endl;

		for (int j = 0; j < length; j++) {
			std::cout << "|";
			if (grid[i][j]) {
				val = grid[i][j];
				//������������ڸ����м�
				if (val < 10)std::cout << "  " << val << "  ";
				else if (val < 100)std::cout << "  " << val << " ";
				else if (val < 1000)std::cout << " " << val << " ";
				else if (val < 10000)std::cout << " " << val;
				else std::cout << val;
			}
			else std::cout << "     ";
		}
		std::cout << "|" << std::endl;
	}
	for (int j = 0; j < length; j++)
	{
		std::cout << "|-----";
	}
	std::cout << '|' << std::endl;
}

#endif 

