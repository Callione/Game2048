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
	void add2();//用于初始化
	//传入的参数是方向'u''d''l''r'
	void move(char);
	void merge(char);//只能融合相邻元素，中间间隔0的相邻元素无法被merge，所以调用之前先move

	void move_left(void);
	void move_up(void);
	void flip(char);//水平或垂直翻转 'h'为水平  'v'为垂直


	bool isFull(void);
	bool canMerge(void);
};


bool Board::canMerge(){

	//水平方向的检测，检查每一行
	for (int i = 0; i < length; i++) {
		for(int j = 0; j < length - 1;) {
			while (j < length && grid[i][j] == 0)j++;//跳过前置0元
			if (j >= length - 1)break;
			int next = j+1;
			while (next < length && grid[i][next] == 0)next++;//next可以找到最靠近的非0元
			if (next < length && grid[i][j] == grid[i][next]) return true;
			
			if (next < length)j = next;
			else break;
		}
	}
	//垂直方向的检测，检查每一列
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length - 1;) {
			while (j < length && grid[j][i] == 0)j++;//跳过前置0元
			if (j >= length - 1)break;
			int next = j + 1;
			while (next < length && grid[next][i] == 0)next++;//next可以找到最靠近的非0元
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
				//从左往右找相同元素
				if (grid[i][j] && grid[i][j] == grid[i][j + 1]) {
					grid[i][j] *= 2;
					grid[i][j + 1] = 0;
					score += grid[i][j];
				}
			}
			else if (direction == 'r') {
				//从右往左找相同元素
				if (grid[i][length-1-j] && grid[i][length-1-j] == grid[i][length-2-j ]) {
					grid[i][length-1-j] *= 2;
					grid[i][length-2-j] = 0;
					score += grid[i][length - 1 - j];
				}
			}
			else if (direction == 'u') {
				//从上往下找相同元素
				if (grid[j][i] && grid[j][i] == grid[j+1][i]) {
					grid[j][i] *= 2;
					grid[j+1][i] = 0;
					score += grid[j][i];
				}
			}
			else if (direction == 'd') {
				//从下往上找相同元素
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
		//对第i列元素，进行上移操作
		std::vector<int>tmp;
		for (int j = 0; j < length; j++) {
			if (grid[j][i])tmp.push_back(grid[j][i]);
		}//按顺序记录非0元

		for (int j = 0; j < length; j++) {
			if (j < tmp.size())grid[j][i] = tmp[j];
			else grid[j][i] = 0;
		}
	}
}

void Board::move_left() {
	
	for (int i = 0; i < length; i++) {
		//对于第i行的元素，进行左移操作
		std::vector<int>tmp;
		for (int j = 0; j < length; j++) {
			if (grid[i][j])tmp.push_back(grid[i][j]);
		}//按顺序记录非0元
		
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
	//如果有空白格子，则任选一个位置
	if (x.empty())return;
	int r = std::rand() % x.size();
	grid[x[r]][y[r]] = 2;
}

void Board::add2or4() {
	//先遍历grid，将空白格子的坐标记录在x,y中
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
	//如果有空白格子，则任选一个位置
	if (x.empty())return;
	int r = std::rand() % x.size();

	//新添加的值有1/5的概率为4，为2的概率是4/5
	int val = std::rand() % 5;
	if (val != 4)val = 2;

	//添加新值
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
				//尽量数字输出在格子中间
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

