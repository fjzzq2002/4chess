#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <sstream>
#include <stack>
#include <iomanip>
using namespace std;
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
typedef long long ll;
typedef double ld;
typedef vector<int> vi;
#define fi first
#define se second
#define fe first
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
#define Edg int M=0,fst[SZ],vb[SZ],nxt[SZ];void ad_de(int a,int b){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;}void adde(int a,int b){ad_de(a,b);ad_de(b,a);}
#define Edgc int M=0,fst[SZ],vb[SZ],nxt[SZ],vc[SZ];void ad_de(int a,int b,int c){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;vc[M]=c;}void adde(int a,int b,int c){ad_de(a,b,c);ad_de(b,a,c);}
#define es(x,e) (int e=fst[x];e;e=nxt[e])
#define esb(x,e,b) (int e=fst[x],b=vb[e];e;e=nxt[e],b=vb[e])
#define VIZ {printf("digraph G{\n"); for(int i=1;i<=n;i++) for es(i,e) printf("%d->%d;\n",i,vb[e]); puts("}");}
#define VIZ2 {printf("graph G{\n"); for(int i=1;i<=n;i++) for es(i,e) if(vb[e]>=i)printf("%d--%d;\n",i,vb[e]); puts("}");}
#define SZ 666666
//platform below.
int m[233][233],c[233];
int play1()
{
	cout<<"玩家1请选择列：";
	int x; cin>>x; return x; 
}
int play2()
{
	cout<<"玩家2请选择列：";
	int x; cin>>x; return x;
}
int AI1()
{
	FILE*fp=fopen("tmp","w");
	for(int i=7;i>=1;--i,fprintf(fp,"\n"))
		for(int j=1;j<=7;j++)
			fprintf(fp,"%d ",m[j][i]);
	fprintf(fp,"1\n");
	fclose(fp);
	system("ai <tmp >op");
	fp=fopen("op","r");
	int x; fscanf(fp,"%d",&x);
	return x;
}
int AI2()
{
	FILE*fp=fopen("tmp","w");
	for(int i=7;i>=1;--i,fprintf(fp,"\n"))
		for(int j=1;j<=7;j++)
			fprintf(fp,"%d ",m[j][i]);
	fprintf(fp,"2\n");
	fclose(fp);
	system("ai <tmp >op");
	fp=fopen("op","r");
	int x; fscanf(fp,"%d",&x);
	return x;
}
/*
//If you prefer play second
#define P1 AI1
#define P2 play2
*/
//If you prefer play first
#define P1 play1
#define P2 AI2
string rec="";
void playit(int x)
{
	if(x==1)
	{
		int s=0;
		while(s<1||s>7||c[s]==7) s=P1();
		m[s][++c[s]]=1; rec.pb(s+'0');
	}
	else
	{
		int s=0;
		while(s<1||s>7||c[s]==7) s=P2();
		m[s][++c[s]]=2; rec.pb(s+'0');
	}
}
int full()
{
	bool ok=0;
	for(int i=1;i<=7;i++) ok|=c[i]!=7;
	return !ok;
}
int jud()
{
	for(int i=1;i<=7;i++)
	{
		for(int j=1;j<=7;j++)
		{
			if(m[i][j])
			{
				int x=m[i][j];
				if(m[i][j+1]==x&&m[i][j+2]==x&&m[i][j+3]==x) return x;
				if(m[i+1][j]==x&&m[i+2][j]==x&&m[i+3][j]==x) return x;
				if(m[i+1][j+1]==x&&m[i+2][j+2]==x&&m[i+3][j+3]==x) return x;
				if(j>=4&&m[i+1][j-1]==x&&
				m[i+2][j-2]==x&&m[i+3][j-3]==x) return x;
			}
		}
	}
}
int main()
{
	int cc=2,win=0;
	while(!full())
	{
		system("cls");
		for(int i=7;i>=1;--i)
		{
			for(int j=1;j<=7;j++)
			{
				if(m[j][i]==1)
					cout<<'*';
				else if(m[j][i]==2)
					cout<<'#';
				else cout<<'.';
				cout<<' ';
			}
			puts("");
		}
		if(win=jud())
		{
			cout<<win<<"号玩家赢了\n";
			break;
		}
		cc=3-cc; playit(cc);
	}
	if(!win) cout<<"平局\n";
	cout<<rec<<"\n"; 
}


