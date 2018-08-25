#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

#define INF pow(2,30)

void buildNext(char* m,vector<int>& vec){
    
    vec[0]=-1;
    
    int j=1,k=-1;

    for(int j=0;j<strlen(m);){
        if(k==-1 || *(m+k) == *(m+j)) {
            ++k;
            ++j;
            vec[j]=k;
        }
        else{
            k = vec[k]; 
        }   
    }
}

int search(char* n,char* m){
    if(!strcmp(n,m))
        return 0;
    int len1=strlen(n);
    int len2=strlen(m);
    if(len2>=len1)
        return -1;
    
    vector<int> next(strlen(m));
    buildNext(m,next);
//     cout<< next.size()<<","<<next.capacity()<<endl;
//    for(int tmp : next){
//        cout<<tmp<<endl;
//    }
    char* mStart = m;
    char* nStart = n;

    while(*m !='\0' && *n !='\0'){
        if(*n == *m){
            n++;
            m++;
        }
        else{
             //m = mStart+next[m-mStart];

        }
           
    }
    if(*m == '\0')
        return (n-nStart)-len2;
    else if(*n =='\0')
        return -1;
    return -1;
}


typedef struct GNode
{
	int number;	// 顶点编号
	struct GNode *next;
} GNode;
 
typedef struct Vertex
{
	int number;
	int weight;		// 在计算最短路径时为该结点到源点的距离
	int f;			// 标记结点是否已经搜寻最短路径完毕
	struct Vertex *p;
} Vertex;

typedef struct Graph
{
	GNode *LinkTable;
	Vertex *vertex;
	int VertexNum;
} Graph;

void initialize(Graph *g, int s)
{
	Vertex *vs = g->vertex;
	for (int i = 0; i < g->VertexNum; i++)
	{
		Vertex *v = vs + i;
		v->p = NULL;
		v->weight = INF;
		v->f = 0;
	}
	(vs + s - 1)->weight = 0;
}
 
// 松弛操作，检查<s, ..., v>的距离是否比<s, ..., u, v>大，是则更新<s, ..., v>为<s, ..., u, v>
void relax(Vertex *u, Vertex *v, int w)
{
	if (u->weight == INF || w == INF)	return;
	if (v->weight > u->weight + w)
	{
		v->weight = u->weight + w;
		v->p = u;
	}
}


/**
* Dijkstra算法，要求所有边的权重均为非负值，结点的编号从1开始
*/
void dijkstra(Graph *g, int **w, int s)
{
	initialize(g, s);
 
	Vertex *vs = g->vertex;
	GNode *linkTable = g->LinkTable;
	for (int i = 1; i < g->VertexNum; i++)
	{
		int min = INT_MAX;
		int number = 0;
		// 找到目前距离s最短的顶点，该顶点搜索最短距离结束
		for (int j = 0; j < g->VertexNum; j++)
		{
			if (min > (vs + j)->weight && (vs + j)->f == 0)
			{
				min = (vs + j)->weight;
				number = j + 1;
			}
		}
		if (number == 0)	return;
		(vs + number - 1)->f = 1;
		// 加入到各个与number相连的顶点中做松弛更新操作
		GNode *node = (linkTable + number - 1)->next;
		Vertex *u = vs + number - 1;
		while (node != NULL)
		{
			Vertex *v = vs + node->number - 1;
			int weight = *((int*)w + (number - 1)*g->VertexNum + node->number - 1);
			relax(u, v, weight);
			node = node->next;
		}
	}
}


 




int main(int args,char** argvs){

    Graph graph;
	graph.VertexNum = 5;
	Vertex v[5];
	Vertex v1; v1.number = 1; v1.p = NULL; v[0] = v1;
	Vertex v2; v2.number = 2; v2.p = NULL; v[1] = v2;
	Vertex v3; v3.number = 3; v3.p = NULL; v[2] = v3;
	Vertex v4; v4.number = 4; v4.p = NULL; v[3] = v4;
	Vertex v5; v5.number = 5; v5.p = NULL; v[4] = v5;
	graph.vertex = v;
 
	GNode nodes[5];
	GNode n1; n1.number = 1;
	GNode n2; n2.number = 2;
	GNode n3; n3.number = 3;
	GNode n4; n4.number = 4;
	GNode n5; n5.number = 5;
	GNode a; a.number = 2; GNode b; b.number = 4; n1.next = &a; a.next = &b; b.next = NULL;
	GNode c; c.number = 3; GNode x; x.number = 4; GNode z; z.number = 5; n2.next = &c; c.next = &x; x.next = &z; z.next = NULL;
	GNode d; d.number = 2; n3.next = &d; d.next = NULL;
	GNode f; f.number = 5; GNode g; g.number = 3; n4.next = &f; f.next = &g; g.next = NULL;
	GNode h; h.number = 1; GNode i; i.number = 3; n5.next = &h; h.next = &i; i.next = NULL;
	nodes[0] = n1;
	nodes[1] = n2;
	nodes[2] = n3;
	nodes[3] = n4;
	nodes[4] = n5;
	graph.LinkTable = nodes;
 
	int w[5][5] = { 0,		6,		INF,	7,		INF,
					INF,	0,		5,		8,		4,
					INF,	2,		0,		INF,	INF,
					INF,	INF,	3,		0,		9,
					2,		INF,	7,		INF,	0 };
	int s = 1;
	dijkstra(&graph, (int **)w, s);
	for (int i = 0; i < graph.VertexNum; i++)
	{
		if (i != s - 1)
		{
			Vertex *v = graph.vertex + i;
			printf("路径长度为%d , 路径为 : ", v->weight);
			while (v->p != NULL)
			{
				printf("%d <- ", v->number);
				v = v->p;
			}
			printf("%d\n", s);
		}
	}


    

}