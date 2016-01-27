#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
using namespace std;

const int inf = 2000000000;
int N , M , ednum;
struct
{
	int U , V , C;
}Edge[100000];
struct
{
	int v , c , po , pre;
}edrec[100000];
int ed[1005] , Que[1005] , Level[1005] , now[1005];
int Belong[1005] , flin[1005] , flou[1005];
int F[205][205];

void AddEdge( int u , int v , int c )
{
	ednum++;
	edrec[ednum].v = v;
	edrec[ednum].c = c;
	edrec[ednum].po = ednum+1;
	edrec[ednum].pre = ed[u];
	ed[u] = ednum;
	
	ednum++;
	edrec[ednum].v = u;
	edrec[ednum].c = c;
	edrec[ednum].po = ednum-1;
	edrec[ednum].pre = ed[v];
	ed[v] = ednum;
}
void Init()
{
	scanf("%d%d" , &N , &M);
	memset(ed , 0 , sizeof(ed));
	ednum = 0;
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d%d" , &Edge[i].U , &Edge[i].V , &Edge[i].C);
		AddEdge( Edge[i].U , Edge[i].V , Edge[i].C );
	}
}

int Min( int a , int b ) { if( a < b ) return a; else return b; }
int GetLevel( int Source , int Sink , int NumV )
{
    for(int i=1;i<=NumV;i++) now[i] = ed[i];
	memset(Level , 0 , sizeof(Level));
	int Bot = 1 , Top = 0;
	Que[++Top] = Source;
	Level[Source] = 1;
	
	while( Bot <= Top )
	{
		for(int q=ed[Que[Bot]];q;q=edrec[q].pre)
		if( edrec[q].c>0 && Level[edrec[q].v]==0 )
		{
			Que[++Top] = edrec[q].v;
			              Level[edrec[q].v] = Level[Que[Bot]]+1;
		}
		Bot++;
	}
    return Level[Sink];
}
int Dfs( int v , int Sink , int Delta )
{
	if( v == Sink ) return Delta;
		
	for(now[v];now[v];now[v] = edrec[now[v]].pre)
		if( edrec[now[v]].c>0 && Level[edrec[now[v]].v]==Level[v]+1 )
		{
			int D = Dfs( edrec[now[v]].v , Sink , Min(Delta,edrec[now[v]].c) );
			if( D > 0 )
			{
				         edrec[now[v]].c       -= D;
				edrec[edrec[now[v]].po].c += D;
				return D;
			}
		}
	return 0;
}

int MaxFlow( int Source , int Sink , int NumV )
{
	int Res = 0;
	while( GetLevel( Source, Sink , NumV ) != 0 )
	{
		int D;
		while( (D=Dfs(Source,Sink,inf)) > 0 ) Res += D; 
	}
	return Res;
}

void Work()
{
	for(int i=1;i<=N;i++) Belong[i] = 1;
	for(int i=1;i<=N;i++)
	for(int j=1;j<=N;j++) F[i][j] = 2000000000;
			
	for(int t=1;t<=N-1;t++)
	{
		int Source = -1 , Sink = -1;
		for(int i=1;i<=N-1;i++)
		for(int j=i+1;j<=N;j++) if( Belong[i]==Belong[j] )
		{
			Source = i; Sink = j;
		}
		
		int Flow = MaxFlow( Source , Sink , N+(t-1)*2 );
		int Id = Belong[Source];
		for(int i=1;i<=N;i++) if( Belong[i]==Id && Level[i]==0 ) Belong[i] = t+1;
		
		memset(flin , 0 , sizeof(flin));
		memset(flou , 0 , sizeof(flou));
		int Num = 0;
		for(int i=1;i<=M;i++) if( (Level[Edge[i].U]!=0)+(Level[Edge[i].V]!=0) == 1 )
		{
			if( Level[Edge[i].U] != 0 ) flou[Edge[i].U] += Edge[i].C; else flou[Edge[i].V] += Edge[i].C;
			if( Level[Edge[i].V] == 0 ) flin[Edge[i].V]  += Edge[i].C; else flin[Edge[i].U]  += Edge[i].C;
		}
		else Edge[++Num] = Edge[i];
			
		M = Num;
		int a = N+2*t-1 , b = N+2*t;
		Edge[++M].U = a;
		Edge[    M].V = b;
		Edge[    M].C = Flow;
		for(int i=1;i<=N+2*t;i++)
		{
			if( flou[i] > 0 )
			{
				Edge[++M].U = i; Edge[M].V = a; Edge[M].C = flou[i];
			}
			if( flin[i] > 0 )
			{
				Edge[++M].U = b; Edge[M].V = i; Edge[M].C = flin[i];
			}
		}
		
		memset(ed , 0 , sizeof(ed));
		ednum = 0;
		for(int i=1;i<=M;i++) AddEdge( Edge[i].U , Edge[i].V , Edge[i].C );
			
		for(int i=1;i<=N;i++) if( Level[i] > 0 )
		for(int j=1;j<=N;j++) if( Level[j] == 0 ) F[i][j] = Min( F[i][j] , Flow );
	}
}

void Output()
{
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++) F[i][j] = Min( F[i][j] , F[j][i] );
	int Q;
	scanf("%d" , &Q);
	for(int t=1;t<=Q;t++)
	{
		int Range; 
		scanf("%d" , &Range);
		int Res =0;
		for(int i=1;i<=N-1;i++)
			for(int j=i+1;j<=N;j++) Res += F[i][j]<=Range;
	    printf("%d\n" , Res);
	}
}
	

int main()
{
	freopen("mincut.in","r",stdin);
	freopen("mincut.out","w",stdout);
	int Test;
	scanf("%d" , &Test);
	for(int T=1;T<=Test;T++)
	{
	   if( T > 1 ) printf("\n");
	   Init();
	   Work();
	   Output();
	}
	return 0;
}
