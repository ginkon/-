// WarriorGame.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include<stdafx.h>
#include <iostream>
#include <string>
#include<windows.h>
#include <fstream>
#include "Graph.h"
#include "WarriorGame.h"
using namespace std;

bool LoadMap(Graph &);//�����ͼ
void DrawMap(Graph &);//��ʾ��ͼ
void MainMenu();//���˵�
void SubMenu();//�Ӳ˵�
bool IsValidChoise(int choise);//�жϲ˵�ѡ���Ƿ�Ϸ�
void StartGame(Graph &);//��ʼ��Ϸ
void OptimumRoute(Graph &);//����·��


int main()
{
	Graph Game;
	int choise;

	if (!LoadMap(Game))//�����ͼ
		exit(1);
	DrawMap(Game);//��ʾ��ͼ
	do
	{
		MainMenu();//���˵�
		do
		{
			cout << "����������ѡ��(1-3):";
			cin >> choise;
			if (!IsValidChoise(choise))//�ж������Ƿ�����
			{
				cout << "���������������������룡" << endl;
				cin.clear();//�������״̬
				cin.ignore();
			}
		} while (!IsValidChoise(choise));
		switch (choise)
		{
		case 1:
			StartGame(Game);//��ʼ��Ϸ
			break;
		case 2:
			OptimumRoute(Game);//����·��
			break;
		case 3:
			cout << "��Ϸ������" << endl;
		}
	} while (choise != 3);
	return 0;
}

//�����ͼ
bool LoadMap(Graph &G)
{
	ifstream input("map.txt");//�ļ�����
	if (!(input >> G.VertexNum >> G.EdgeNum))return false;
	G.creat();//��ͼ��ʼ��
	for (int i = 0;i<G.VertexNum;i++)
		input >> G.Vertex[i].name >> G.Vertex[i].value;//��������
	for (int i = 0, x, y, z;i<G.EdgeNum;i++)
	{
		input >> x >> y >> z;
		G.add(x, y, z);//�ӱ�
		G.add(y, x, z);
	}

	return true;
}

//��ʾ��ͼ
void DrawMap(Graph & Game)
{
	cout << "------------ÿ���Ǳ����ܵ���ĵط�����--------------" << endl;
	for (int i = 0;i<Game.VertexNum;i++)
	{
		cout << Game.Vertex[i].name << "->";
		for (EdgeNode *p = Game.head[i].FirstEdge;p != NULL;p = p->nextNode)
			cout << Game.Vertex[p->adjVertex].name << " ";
		cout << endl;
	}
	cout << "----------------------------------------------------" << endl;
}

//���˵�
void MainMenu()
{
	cout << "------------------------���˵�----------------------" << endl;
	cout << "|                    1. ��ʼ��Ϸ                   |" << endl;
	cout << "|                    2. ����·��                   |" << endl;
	cout << "|                    3. �뿪��Ϸ                   |" << endl;
	cout << "----------------------------------------------------" << endl;
}

//�Ӳ˵�
void SubMenu()
{
	cout << "-----------------------�Ӳ˵�-----------------------" << endl;
	cout << "|                  1. ����ֵ���·��               |" << endl;
	cout << "|                  2. �Ƹ�ֵ���·��               |" << endl;
	cout << "|                  3. �����ϲ�˵�                 |" << endl;
	cout << "----------------------------------------------------" << endl;
}

//�жϲ˵�ѡ���Ƿ�Ϸ�
bool IsValidChoise(int choise)
{
	if (choise != 1 && choise != 2 && choise != 3)
		return false;
	return true;
}

void OptimumRoute(Graph & Game)//����·��
{
	int choise;
	do
	{
		SubMenu();
		do
		{
			cout << "����������ѡ��1-3����";
			cin >> choise;
			if (!IsValidChoise(choise))//�ж������Ƿ�����
			{
				cout << "���������������������룡" << endl;
				cin.clear();//�������״̬
				cin.ignore();
			}
		} while (!IsValidChoise(choise));
		switch (choise)
		{
		case 1:
			OptimumRoute1(Game);//����·��
			break;
		case 2:
			OptimumRoute2(Game);//����·��
			break;
		case 3:
			break;
		}
	} while (choise != 3);

}


//��ʼ��Ϸ
void StartGame(Graph & Game)
{
	int now = 0, value = Game.Vertex[now].value, life = 100;//nowΪ��ǰ�ڵ㣬valueΪ��ǰ���òƸ���lifeΪ��ǰ����
	vector<int>path;//��¼·��
	bool *v = new bool[Game.VertexNum];//��ǳǱ��Ƿ��߹�
	for (int i = 0;i<Game.VertexNum;i++)
		v[i] = false;
	v[now] = true;
	string temp;
	do {
		path.push_back(now);//�߹��ĵ����·���ļ�¼��
		if (now == Game.VertexNum - 1)//�յ�Ϊ�������ĵ㣬���յ��ʤ��
		{
			cout << "�������ʤ������Ϸ����" << endl;
			cout << "���ղƸ�ֵΪ" << value << "����Ѫ��Ϊ" << life << endl;
			cout << "����·��Ϊ:";
			for (int i = 0;i<path.size();i++)//���·��
			{
				if (i != 0)cout << " -> ";
				cout << Game.Vertex[path[i]].name;
			}
			cout << endl;
			break;
		}
		cout << "---------------------------------------------------" << endl;
		cout << "                   ����-1��ǰ����" << endl;
		cout << "                   ��ǰλ��Ϊ " << Game.Vertex[now].name << " �Ǳ�" << endl;
		cout << "          ��ʿѪ�� " << life << " �Ƹ�ֵ " << value << endl;
		cout << Game.Vertex[now].name << "�ӵ�ǰ������������Ե���:";
		for (EdgeNode *p = Game.head[now].FirstEdge;p != NULL;p = p->nextNode)
			cout << Game.Vertex[p->adjVertex].name << " ";
		cout << endl << "----------------------------------------------------" << endl;
		cout << "ѡ����Ҫǰ���ĳǱ�" << endl;
		cin >> temp;//����Ҫǰ���ĳǱ�����
		bool flag = false;//����ܷ�ǰ������ĳǱ�
		for (EdgeNode *p = Game.head[now].FirstEdge;p != NULL;p = p->nextNode)//������ǰ��������ı�
			if (Game.Vertex[p->adjVertex].name == temp)//�ҵ�������Ľڵ�
			{
				life -= p->weight;
				now = p->adjVertex;
				flag = true;//���Ե���
				break;
			}
		if (life <= 0)//����<=0
		{
			cout << "��ɫ����,��Ϸ����" << endl;
			break;
		}
		if (temp != "-1"&&flag == false)//��ǰ���Ҳ���ͨ������Ǳ��ıߣ���ǰ���޷�ͨ������Ǳ���
		{
			cout << "�������,����������" << endl;
			continue;
		}
		if (v[now] == 0)//��������֮ǰû��������˵���Ƹ�ֵ��û�б�����
			v[now] = 1, value += Game.Vertex[now].value;//���߲Ƹ�ֵ��������������
	} while (temp != "-1");
	delete v;
	system("pause");
}
