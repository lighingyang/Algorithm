/*
问题 C: 调酒壶里的酸奶
时间限制: 1 Sec  内存限制: 128 MB
提交: 461  解决: 186
[提交] [状态] [命题人:外部导入]
题目描述
最近小w学了一手调酒的技巧，这么帅的操作，说不定能靠这个俘获女神的芳心，为了在女神面前露一手，他想在学校里建一个"pub"，但是显然学校不可能让他真的建一个"pub"，那么他退而求次，想建一个"Yogurt shop"，不能用酒，那用酸奶也行啊！
今天女神终于来光顾小w的酸奶店了！兴奋的小w拿出自己准备已久每天都仔细擦干净的装备——调酒壶、果汁机、隔冰器和计量杯、砧板、小刀....准备露一手给女神看看
但是女神却没有那么多耐心，女神只是觉得，自己买一瓶大酸奶喝不完，小瓶酸奶不够喝，所以在小w的酸奶店，说不定她可以想买多少就买多少。
于是女神告诉了小w她想要多少体积的酸奶，而小w却依旧想秀一下自己的操作，于是他决定用仅有的两个调酒壶为女神倒出女神想要的酸奶....
小w的两个调酒壶体积是不同的(一开始都是空的)，小w每次可以选择一个调酒壶倒入另一个调酒壶（若A倒入B，A倒完或B倒满则停止），或者选择一个调酒壶倒光，或者选择一个调酒壶去接满酸奶.....
满心失望的小w想找一朵花，一瓣一瓣的撕下来，问问花朵女神到底喜不喜欢他...虽然这个答案是显而易见的，但是他还是想找一朵花...然而找花未果，反正花瓣不是偶数就是奇数，那他索性就用自己的操作次数作为花瓣个数吧！（找不到花我还不能脑补一朵吗...）
但是小w已经没有心情去想答案了...那么你能告诉他，需要多少步操作才能倒出女神想要的酸奶吗？


输入
输入包含多组数据，每行三个正整数a,b,c分别表示两个调酒壶的容量以及女神想要的酸奶体积,a,b的范围都在[0,100]，c<=max(a,b)   


输出
一行包含一个整数表示完成要求的最少操作次数，若达不到则输出"impossible"（没有双引号）


样例输入
复制样例数据
10 15 11
6 5 4
样例输出
impossible
4

提示
 我不知道为什么酸奶可以倒进调酒壶，我也不知道为什么女神不喜欢小w，我只知道凭小w的想象力，游泳池都行更别说一朵花了！

*/
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
