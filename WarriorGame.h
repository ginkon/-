#include<queue>
#include<set>
class Castle;
class EdgeNode;
class Vertexnode;
class Graph;
const int INF=1e9;
void dijkstra(Graph &Game, int s,int t,int *dis,int *path)//dis为最短距离，path为当前点从哪个点走过来是最短路径
{
	int i,j,k,minn;
	int * v = new int [Game.VertexNum];//标记点是否跑过
	for(int i=0;i<Game.VertexNum;i++)//初始化
        dis[i]=INF,v[i]=0,path[i]=-1;
	v[s] = 1;
	dis[s]=0;
	for(EdgeNode *p=Game.head[s].FirstEdge;p!=NULL;p=p->nextNode)//遍历和起点相邻的点
	{
	    path[p->adjVertex]=s;//记录路径，暂时的最短路径
		dis[p->adjVertex] = p->weight;//从起点到这个点的距离为暂时的最短路径
	}
	for(i = 0;i < Game.VertexNum;i ++)
	{
		minn = INF;
		k = -1;
		for(j = 0;j < Game.VertexNum;j ++)//找出最短路径最小的点节点
		{
			if(v[j] == 0 && dis[j] < minn)
			{
				k = j;
				minn = dis[j];
			}
		}
		if(k == -1)//没有找到说明能跑的都跑过了
            return ;

		v[k] = 1;
		for(EdgeNode *p=Game.head[k].FirstEdge;p!=NULL;p=p->nextNode)//遍历k所连接的边
		{
			if(v[p->adjVertex] == 0 && dis[p->adjVertex] > p->weight + dis[k])//看能不能更短，可以更短就改变最短路径值
			{
			    path[p->adjVertex]=k;//记录路径
				dis[p->adjVertex] = p->weight + dis[k];//到k的距离加这条路受到的伤害
			}
		}
	}

}
void print(Graph & Game,int *path,int now)//递归输出路径
{
    if(now==0)
    {
        cout<<Game.Vertex[now].name;
        return ;
    }
    print(Game,path,path[now]);
    cout<<" -> "<<Game.Vertex[now].name;
}
void dfs(Graph &Game,int now,int *v,int life,vector<int> &path,vector<int> &ans,int &maxvalue,int value=0)//maxvalue为当前的找到的财富最高的路径，value为当前的财富，life为生命
{//path记录路径，ans为最优解的路径
    if(life<=0)return ;
    path.push_back(now);//记录路径
    if(now==Game.VertexNum-1)
    {
        if(value>maxvalue||(value==maxvalue&&path.size()<ans.size()))//判断当前搜到的财富否比之前的更好，且走过的路程尽量少。
        {
            maxvalue=value;
            ans=path;//保存路径
        }
        path.erase(path.begin()+path.size()-1);//为了回溯删除该点的记录
        return ;
    }
    for(EdgeNode *p=Game.head[now].FirstEdge;p!=NULL;p=p->nextNode)//遍历边
    {
        if(v[p->adjVertex]>=Game.VertexNum&&p->weight==0)continue;//进入一个点的次数最多为节点个数
        if(v[p->adjVertex]==0)//如果这个点没走过，财富值加上去
            value+=Game.Vertex[p->adjVertex].value;
        v[p->adjVertex]++;//走过的次数+1
        dfs(Game,p->adjVertex,v,life-p->weight,path,ans,maxvalue,value);//递归
        v[p->adjVertex]--;//回溯
        if(v[p->adjVertex]==0)//如果当前点没走过，删除之前加上的财富值，回溯
            value-=Game.Vertex[p->adjVertex].value;
    }
    path.erase(path.begin()+(int)path.size()-1);//为了回溯删除该点的记录
    return ;
}
void OptimumRoute1(Graph & Game)
{
    int *dis = new int[Game.VertexNum], *path = new int[Game.VertexNum];//最短距离和记录路径
    dijkstra(Game,0,Game.VertexNum-1,dis,path);
    cout<<"剩余血量最多路线为:";
    print(Game,path,Game.VertexNum-1);//输出路径
    cout<<endl<<"剩余血量为"<<100-dis[Game.VertexNum-1]<<endl;
    delete dis;delete path;
	}
void OptimumRoute2(Graph & Game)
{
	int *v = new int[Game.VertexNum];
	for (int i = 0; i < Game.VertexNum; i++)
		v[i] = 0;
	v[0] = 1;
	vector<int>Path, ans;//path在搜索时记录路径，ans保存财富值最优的路径
	int maxvalue = 0;
	dfs(Game, 0, v, 100, Path, ans, maxvalue, Game.Vertex[0].value);
	cout << "取得财富最多的路线为:";
	for (int i = 0; i < (int)ans.size(); i++)//输出路径
	{
		if (i != 0)cout << " -> ";
		cout << Game.Vertex[ans[i]].name;
	}
	cout << endl << "财富值为" << maxvalue << endl;
}

