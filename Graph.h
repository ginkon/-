#include<iostream>
#include<string>
#include<vector>
#include<map>
using namespace std;
class Castle//�Ǳ�����
{
public:
    int value;
    string name;
};
class EdgeNode//�ߵĽڵ�
{
    public:
    int adjVertex;//��ǰ��ͨ��ĵ�
    int weight;//���������ܵ����˺�
    struct EdgeNode * nextNode;//��һ���͵�ǰ������ͬ���ı�
} ;
class Vertexnode//ÿ���ڵ�
{
    public:
    int vertex;//�ڵ���
    EdgeNode * FirstEdge;//��ǰ�ڵ����ӵĵ�һ����
};
class Graph
{
public:
    Castle *Vertex;//�Ǳ�
    int VertexNum;//�����
    int EdgeNum;//�߸���
    Vertexnode *head;//�õ�ĵ�һ����
    void creat()//ͼ�ĳ�ʼ��
    {
        Vertex=new Castle [VertexNum];
        head=new Vertexnode [VertexNum];
        for(int i=0; i<VertexNum; i++)
            head[i].vertex=i,head[i].FirstEdge=NULL;
    }
    void add(int Star,int End,int w)//�ӱߣ������ͷ�巨
    {
        EdgeNode * temp=head[Star].FirstEdge;//���µ�һ����
        head[Star].FirstEdge=new EdgeNode;//��һ����ָ���µı�
        head[Star].FirstEdge->nextNode=temp;//�µıߵ���һ����ָ��ԭ���ĵ�һ����
        head[Star].FirstEdge->adjVertex=End;//������
        head[Star].FirstEdge->weight=w;
    }
};
