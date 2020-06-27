#include<queue>
#include<set>
class Castle;
class EdgeNode;
class Vertexnode;
class Graph;
const int INF=1e9;
void dijkstra(Graph &Game, int s,int t,int *dis,int *path)//disΪ��̾��룬pathΪ��ǰ����ĸ����߹��������·��
{
	int i,j,k,minn;
	int * v = new int [Game.VertexNum];//��ǵ��Ƿ��ܹ�
	for(int i=0;i<Game.VertexNum;i++)//��ʼ��
        dis[i]=INF,v[i]=0,path[i]=-1;
	v[s] = 1;
	dis[s]=0;
	for(EdgeNode *p=Game.head[s].FirstEdge;p!=NULL;p=p->nextNode)//������������ڵĵ�
	{
	    path[p->adjVertex]=s;//��¼·������ʱ�����·��
		dis[p->adjVertex] = p->weight;//����㵽�����ľ���Ϊ��ʱ�����·��
	}
	for(i = 0;i < Game.VertexNum;i ++)
	{
		minn = INF;
		k = -1;
		for(j = 0;j < Game.VertexNum;j ++)//�ҳ����·����С�ĵ�ڵ�
		{
			if(v[j] == 0 && dis[j] < minn)
			{
				k = j;
				minn = dis[j];
			}
		}
		if(k == -1)//û���ҵ�˵�����ܵĶ��ܹ���
            return ;

		v[k] = 1;
		for(EdgeNode *p=Game.head[k].FirstEdge;p!=NULL;p=p->nextNode)//����k�����ӵı�
		{
			if(v[p->adjVertex] == 0 && dis[p->adjVertex] > p->weight + dis[k])//���ܲ��ܸ��̣����Ը��̾͸ı����·��ֵ
			{
			    path[p->adjVertex]=k;//��¼·��
				dis[p->adjVertex] = p->weight + dis[k];//��k�ľ��������·�ܵ����˺�
			}
		}
	}

}
void print(Graph & Game,int *path,int now)//�ݹ����·��
{
    if(now==0)
    {
        cout<<Game.Vertex[now].name;
        return ;
    }
    print(Game,path,path[now]);
    cout<<" -> "<<Game.Vertex[now].name;
}
void dfs(Graph &Game,int now,int *v,int life,vector<int> &path,vector<int> &ans,int &maxvalue,int value=0)//maxvalueΪ��ǰ���ҵ��ĲƸ���ߵ�·����valueΪ��ǰ�ĲƸ���lifeΪ����
{//path��¼·����ansΪ���Ž��·��
    if(life<=0)return ;
    path.push_back(now);//��¼·��
    if(now==Game.VertexNum-1)
    {
        if(value>maxvalue||(value==maxvalue&&path.size()<ans.size()))//�жϵ�ǰ�ѵ��ĲƸ����֮ǰ�ĸ��ã����߹���·�̾����١�
        {
            maxvalue=value;
            ans=path;//����·��
        }
        path.erase(path.begin()+path.size()-1);//Ϊ�˻���ɾ���õ�ļ�¼
        return ;
    }
    for(EdgeNode *p=Game.head[now].FirstEdge;p!=NULL;p=p->nextNode)//������
    {
        if(v[p->adjVertex]>=Game.VertexNum&&p->weight==0)continue;//����һ����Ĵ������Ϊ�ڵ����
        if(v[p->adjVertex]==0)//��������û�߹����Ƹ�ֵ����ȥ
            value+=Game.Vertex[p->adjVertex].value;
        v[p->adjVertex]++;//�߹��Ĵ���+1
        dfs(Game,p->adjVertex,v,life-p->weight,path,ans,maxvalue,value);//�ݹ�
        v[p->adjVertex]--;//����
        if(v[p->adjVertex]==0)//�����ǰ��û�߹���ɾ��֮ǰ���ϵĲƸ�ֵ������
            value-=Game.Vertex[p->adjVertex].value;
    }
    path.erase(path.begin()+(int)path.size()-1);//Ϊ�˻���ɾ���õ�ļ�¼
    return ;
}
void OptimumRoute1(Graph & Game)
{
    int *dis = new int[Game.VertexNum], *path = new int[Game.VertexNum];//��̾���ͼ�¼·��
    dijkstra(Game,0,Game.VertexNum-1,dis,path);
    cout<<"ʣ��Ѫ�����·��Ϊ:";
    print(Game,path,Game.VertexNum-1);//���·��
    cout<<endl<<"ʣ��Ѫ��Ϊ"<<100-dis[Game.VertexNum-1]<<endl;
    delete dis;delete path;
	}
void OptimumRoute2(Graph & Game)
{
	int *v = new int[Game.VertexNum];
	for (int i = 0; i < Game.VertexNum; i++)
		v[i] = 0;
	v[0] = 1;
	vector<int>Path, ans;//path������ʱ��¼·����ans����Ƹ�ֵ���ŵ�·��
	int maxvalue = 0;
	dfs(Game, 0, v, 100, Path, ans, maxvalue, Game.Vertex[0].value);
	cout << "ȡ�òƸ�����·��Ϊ:";
	for (int i = 0; i < (int)ans.size(); i++)//���·��
	{
		if (i != 0)cout << " -> ";
		cout << Game.Vertex[ans[i]].name;
	}
	cout << endl << "�Ƹ�ֵΪ" << maxvalue << endl;
}

