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
struct sta
{
int p,m[12][12],c[12],s;
sta() {memset(m,0,sizeof m);memset(c,0,sizeof c);}
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
	return 0;
}
bool cango(int x) {return c[x]<7;}
sta go(int x)
{
	sta nx=*this;
	nx.m[x][++nx.c[x]]=p;
	nx.p=3-nx.p; --nx.s;
	return nx;
}
bool end()
{
	bool ok=0;
	for(int i=1;i<=7;i++) ok|=c[i]!=7;
	if(!ok||s<=0) return 1;
	if(jud()) return 1;
	return 0;
}
void dbg()
{
	for(int i=7;i>=1;--i)
	{
		for(int j=1;j<=7;j++)
		{
			if(m[j][i]==1) cout<<'*';
			else if(m[j][i]==2) cout<<'#';
			else cout<<'.';
			cout<<' ';
		}
		puts("");
	}
	puts("");
}
};
#define ND 2333333
int ch[ND][8]; sta ss[ND]; int an=0;
int did[ND]; ld win[ND];
int alc(sta x) {ss[++an]=x; return an;}
const ld C=1.1;
int jc(int cur,ld K)
{
	for(int i=1;i<=7;i++)
	{
		sta w=ss[cur];
		if(w.cango(i))
		{
			w=w.go(i);
			if(w.jud()==ss[cur].p)
				return i;
		}
	}
	int t=0,chh;
	for(int k=1;k<=7;k++)
	{
		if(!ss[cur].cango(k)) continue;
		if(chh=ch[cur][k])
			t+=did[chh]; ++t;
	}
	int a=1;
	ld maxn=-1e18;
	for(int k=1;k<=7;k++)
	{
		if(!ss[cur].cango(k)) continue;
		ld w=1; int n=1;
		if(chh=ch[cur][k])
			n+=did[chh],w+=win[chh];
		ld p=w/(ld)n+K*sqrt(log(t)/n);
		if(p>maxn) {maxn=p; a=k;}
	}
	return a;
}
int ww,pss=0; ld wss=0;
void try_play()
{
	static int ps[SZ]; int sn=0;
	int cur=1,tat=0;
	while(!ss[cur].end())
	{
		++tat;
		int s=jc(cur,C),nx,chh;
		if(chh=ch[cur][s]) nx=chh;
		else ch[cur][s]=nx=alc(ss[cur].go(s));
		cur=nx, ps[++sn]=cur;
	}
	int x=ss[cur].jud();
	ld g=x?(x==ww):0.5;
	wss+=g; ++pss;
	for(int i=1;i<=sn;i++)
		++did[ps[i]],win[ps[i]]+=g;
}
sta g;
char TMP[23333];
int main()
{
	for(int i=7;i>=1;--i)
	{
		for(int j=1;j<=7;j++)
			scanf("%d",&g.m[j][i]);
	}
	for(int i=1;i<=7;i++)
		while(g.m[i][g.c[i]+1]) ++g.c[i];
	cin>>ww; g.p=ww; g.s=14; alc(g); int t=clock();
	while((clock()-t)<2*CLOCKS_PER_SEC) try_play();
	ld cb=wss/pss*100;
	sprintf(TMP,"title AI%d: %.3f%% win prob  out of %d matches",ww,cb,pss);
	system(TMP); int l=jc(1,0);
	printf("%d\n",l);
}

