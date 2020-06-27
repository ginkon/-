#include<iostream>
#include<string>
#include<vector>
#include<map>
using namespace std;
class Castle//城堡属性
{
public:
    int value;
    string name;
};
class EdgeNode//边的节点
{
    public:
    int adjVertex;//当前边通向的点
    int weight;//走这条边受到的伤害
    struct EdgeNode * nextNode;//下一条和当前边有相同起点的边
} ;
class Vertexnode//每个节点
{
    public:
    int vertex;//节点编号
    EdgeNode * FirstEdge;//当前节点连接的第一条边
};
class Graph
{
public:
    Castle *Vertex;//城堡
    int VertexNum;//点个数
    int EdgeNum;//边个数
    Vertexnode *head;//该点的第一条边
    void creat()//图的初始化
    {
        Vertex=new Castle [VertexNum];
        head=new Vertexnode [VertexNum];
        for(int i=0; i<VertexNum; i++)
            head[i].vertex=i,head[i].FirstEdge=NULL;
    }
    void add(int Star,int End,int w)//加边，链表的头插法
    {
        EdgeNode * temp=head[Star].FirstEdge;//存下第一条边
        head[Star].FirstEdge=new EdgeNode;//第一条边指向新的边
        head[Star].FirstEdge->nextNode=temp;//新的边的下一条边指向原本的第一条边
        head[Star].FirstEdge->adjVertex=End;//存数据
        head[Star].FirstEdge->weight=w;
    }
};
