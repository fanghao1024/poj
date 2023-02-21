#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
ll dp[15][10][15];
int dig[15];
int a,b;
ll ans[2][15];
ll dfs(int pos,int val,ll cnt,int lead,int limit){
	if(pos==0) return cnt;
	if(!lead&&!limit&&dp[pos][val][cnt]!=-1) return dp[pos][val][cnt];
	int len=limit?dig[pos]:9;
	ll ans=0,t=0;
	for(int i=0;i<=len;i++){
		if(i!=val) t=cnt;
		else{
			if(lead&&!val) t=0;
			else t=cnt+1;
		}
		ans+=dfs(pos-1,val,t,lead&!i,limit&i==len);
	}
	if(!lead&&!limit) dp[pos][val][cnt]=ans;
	return ans;
}
void solve(int m,int idx){
	if(m==0) return ;
	int pos=0;
	while(m){
		dig[++pos]=m%10;
		m/=10;
	}
	for(int i=0;i<=9;i++){
		ans[idx][i]=dfs(pos,i,0,1,1);
	}
}
int main(){
	memset(dp,-1,sizeof(dp));
	while(scanf("%d %d",&a,&b)&&(a+b)){
		if(a>b) swap(a,b);
		solve(a-1,0);
		solve(b,1);
		for(int i=0;i<=9;i++){
			if(i) printf(" ");
			printf("%lld",ans[1][i]-ans[0][i]);
		}
		printf("\n");
	}
	return 0;
}
