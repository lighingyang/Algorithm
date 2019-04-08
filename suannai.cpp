#include<bits/stdc++.h>
using namespace std;
int ans=0;
int a,b;
int c;
int vis[110][110];
struct node{
    int i;
    int j;
    int sp;
    node(int ii,int jj,int ss){
        i =ii;
        j =jj;
        sp =ss;
    }
};

queue<node> q;

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

void bfs(){
    while(!q.empty()){
        q.pop();
    }
    node n(0,0,0);
    q.push(n);
    while(!q.empty()){
        node nn = q.front();
        q.pop();
        int ii=nn.i;
        int jj=nn.j;
        int ss=nn.sp;
        //cout<<ii<<" "<<jj<<" "<<ss<<endl;
        if(vis[ii][jj]) continue;
        if(ii==c||jj==c) {
            ans = ss;
            return ;
        }
        //aµ¹¹â
        if(ii>0){
            node n(0,jj,ss+1);
            q.push(n);
        }
        //bµ¹¹â
        if(jj>0){
            node n(ii,0,ss+1);
            q.push(n);
        }
        //aµ¹Âú
        if(ii<a){
            node n(a,jj,ss+1);
            q.push(n);
        }
        //bµ¹Âú
        if(jj<b){
            node n(ii,b,ss+1);
            q.push(n);
        }
        //a->b,b²»Âú
        if(ii>0&&b-jj>ii){
            node n(0,ii+jj,ss+1);
            q.push(n);
        }
        //a->b,bÂú
        if(ii>0&&b-jj<=ii){
            node n(ii-(b-jj),b,ss+1);
            q.push(n);
        }
        //b->a,a²»Âú
        if(a-ii>jj&&jj>0){
            node n(ii+jj,0,ss+1);
            q.push(n);
        }
        //b->a,aÂú
        if(a-ii<=jj&&jj>0){
            node n(a,jj-(a-ii),ss+1);
            q.push(n);
        }
        vis[ii][jj] = 1;
    }
    return ;
}

int main(){
    freopen("1.txt","r",stdin);
    while(cin>>a>>b>>c){
        ans=0;
        memset(vis,0,sizeof(vis));
        int tt =gcd(a,b);
        if(c%tt!=0){
            cout<<"impossible"<<endl;
            continue;
        }
        bfs();
        cout<<ans<<endl;
    }
    return 0;
}
