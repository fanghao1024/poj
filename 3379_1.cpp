#include<cstring>
#include<cstdio>

int N,M,S,cnt;
const int max_n=500010;
int head[max_n],fa[max_n],siz[max_n],son[max_n],top[max_n],dep[max_n];
struct Edge{
	int to,nxt;
}edge[max_n<<1];
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void dfs1(int u,int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(!son[u]||siz[v]>siz[son[u]]) son[u]=v;
		}
	}
	
}
void dfs2(int x,int topx){
	top[x]=topx;
	if(!son[x]) return ;
	dfs2(son[x],topx);
	for(int i=head[x];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v!=fa[x]&&v!=son[x]) dfs2(v,v);
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			x=fa[top[x]];
		}else{
			y=fa[top[y]];
		}
	}
	return dep[x]>dep[y]?y:x;
}
int main(){
	scanf("%d%d%d",&N,&M,&S);
	memset(head,-1,sizeof(head));
	memset(son,0,sizeof(son));
	cnt=0;
	int x,y;
	for(int i=1;i<N;i++){
		scanf("%d %d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	dep[0]=0;
	fa[0]=0;
	siz[0]=0;
	dfs1(S,0);
	dfs2(S,S);
	for(int i=1;i<=M;i++){
		scanf("%d %d",&x,&y);
		if(x==y){
			printf("%d\n",x);
		}else{
			printf("%d\n",LCA(x,y));
		}
	}
	return 0;
}
