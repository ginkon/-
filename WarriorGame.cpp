// WarriorGame.cpp : 定义控制台应用程序的入口点。
//
#include<stdafx.h>
#include <iostream>
#include <string>
#include<windows.h>
#include <fstream>
#include "Graph.h"
#include "WarriorGame.h"
using namespace std;

bool LoadMap(Graph &);//读入地图
void DrawMap(Graph &);//显示地图
void MainMenu();//主菜单
void SubMenu();//子菜单
bool IsValidChoise(int choise);//判断菜单选择是否合法
void StartGame(Graph &);//开始游戏
void OptimumRoute(Graph &);//最优路线


int main()
{
	Graph Game;
	int choise;

	if (!LoadMap(Game))//读入地图
		exit(1);
	DrawMap(Game);//显示地图
	do
	{
		MainMenu();//主菜单
		do
		{
			cout << "请输入您的选择(1-3):";
			cin >> choise;
			if (!IsValidChoise(choise))//判读输入是否有误
			{
				cout << "您的输入有误，请重新输入！" << endl;
				cin.clear();//清除错误状态
				cin.ignore();
			}
		} while (!IsValidChoise(choise));
		switch (choise)
		{
		case 1:
			StartGame(Game);//开始游戏
			break;
		case 2:
			OptimumRoute(Game);//最优路线
			break;
		case 3:
			cout << "游戏结束！" << endl;
		}
	} while (choise != 3);
	return 0;
}

//读入地图
bool LoadMap(Graph &G)
{
	ifstream input("map.txt");//文件读入
	if (!(input >> G.VertexNum >> G.EdgeNum))return false;
	G.creat();//地图初始化
	for (int i = 0;i<G.VertexNum;i++)
		input >> G.Vertex[i].name >> G.Vertex[i].value;//输入数据
	for (int i = 0, x, y, z;i<G.EdgeNum;i++)
	{
		input >> x >> y >> z;
		G.add(x, y, z);//加边
		G.add(y, x, z);
	}

	return true;
}

//显示地图
void DrawMap(Graph & Game)
{
	cout << "------------每个城堡所能到达的地方如下--------------" << endl;
	for (int i = 0;i<Game.VertexNum;i++)
	{
		cout << Game.Vertex[i].name << "->";
		for (EdgeNode *p = Game.head[i].FirstEdge;p != NULL;p = p->nextNode)
			cout << Game.Vertex[p->adjVertex].name << " ";
		cout << endl;
	}
	cout << "----------------------------------------------------" << endl;
}

//主菜单
void MainMenu()
{
	cout << "------------------------主菜单----------------------" << endl;
	cout << "|                    1. 开始游戏                   |" << endl;
	cout << "|                    2. 最优路线                   |" << endl;
	cout << "|                    3. 离开游戏                   |" << endl;
	cout << "----------------------------------------------------" << endl;
}

//子菜单
void SubMenu()
{
	cout << "-----------------------子菜单-----------------------" << endl;
	cout << "|                  1. 生命值最高路线               |" << endl;
	cout << "|                  2. 财富值最高路线               |" << endl;
	cout << "|                  3. 返回上层菜单                 |" << endl;
	cout << "----------------------------------------------------" << endl;
}

//判断菜单选择是否合法
bool IsValidChoise(int choise)
{
	if (choise != 1 && choise != 2 && choise != 3)
		return false;
	return true;
}

void OptimumRoute(Graph & Game)//最优路线
{
	int choise;
	do
	{
		SubMenu();
		do
		{
			cout << "请输入您的选择（1-3）：";
			cin >> choise;
			if (!IsValidChoise(choise))//判读输入是否有误
			{
				cout << "您的输入有误，请重新输入！" << endl;
				cin.clear();//清除错误状态
				cin.ignore();
			}
		} while (!IsValidChoise(choise));
		switch (choise)
		{
		case 1:
			OptimumRoute1(Game);//最优路线
			break;
		case 2:
			OptimumRoute2(Game);//最优路线
			break;
		case 3:
			break;
		}
	} while (choise != 3);

}


//开始游戏
void StartGame(Graph & Game)
{
	int now = 0, value = Game.Vertex[now].value, life = 100;//now为当前节点，value为当前所得财富，life为当前生命
	vector<int>path;//记录路径
	bool *v = new bool[Game.VertexNum];//标记城堡是否走过
	for (int i = 0;i<Game.VertexNum;i++)
		v[i] = false;
	v[now] = true;
	string temp;
	do {
		path.push_back(now);//走过的点加入路径的记录中
		if (now == Game.VertexNum - 1)//终点为最后输入的点，到终点后胜利
		{
			cout << "您获得了胜利，游戏结束" << endl;
			cout << "最终财富值为" << value << "最终血量为" << life << endl;
			cout << "您的路线为:";
			for (int i = 0;i<path.size();i++)//输出路径
			{
				if (i != 0)cout << " -> ";
				cout << Game.Vertex[path[i]].name;
			}
			cout << endl;
			break;
		}
		cout << "---------------------------------------------------" << endl;
		cout << "                   输入-1提前结束" << endl;
		cout << "                   当前位置为 " << Game.Vertex[now].name << " 城堡" << endl;
		cout << "          勇士血量 " << life << " 财富值 " << value << endl;
		cout << Game.Vertex[now].name << "从当前点出发出发可以到达:";
		for (EdgeNode *p = Game.head[now].FirstEdge;p != NULL;p = p->nextNode)
			cout << Game.Vertex[p->adjVertex].name << " ";
		cout << endl << "----------------------------------------------------" << endl;
		cout << "选择你要前往的城堡" << endl;
		cin >> temp;//输入要前往的城堡名字
		bool flag = false;//标记能否前往输入的城堡
		for (EdgeNode *p = Game.head[now].FirstEdge;p != NULL;p = p->nextNode)//遍历当前结点所连的边
			if (Game.Vertex[p->adjVertex].name == temp)//找到所输入的节点
			{
				life -= p->weight;
				now = p->adjVertex;
				flag = true;//可以到达
				break;
			}
		if (life <= 0)//生命<=0
		{
			cout << "角色死亡,游戏结束" << endl;
			break;
		}
		if (temp != "-1"&&flag == false)//当前点找不到通向输入城堡的边，当前点无法通向输入城堡。
		{
			cout << "输入错误,请重新输入" << endl;
			continue;
		}
		if (v[now] == 0)//如果这个点之前没来过来，说明财富值还没有被拿走
			v[now] = 1, value += Game.Vertex[now].value;//拿走财富值，标记这个点来过
	} while (temp != "-1");
	delete v;
	system("pause");
}
