Problem Description
Give you a sequence and ask you the kth big number of a inteval.
 
 

Input
The first line is the number of the test cases. 
For each test case, the first line contain two integer n and m (n, m <= 100000), indicates the number of integers in the sequence and the number of the quaere. 
The second line contains n integers, describe the sequence. 
Each of following m lines contains three integers s, t, k. 
[s, t] indicates the interval and k indicates the kth big number in interval [s, t]
 
 

Output
For each test case, output m lines. Each line contains the kth big number.
 
 

Sample Input
1 10 1 1 4 2 3 5 6 7 8 9 0 1 3 2
 
 

Sample Output
2

/*
HDU  2665 Kth number
划分树


*/


#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

const int MAXN=100010;
int tree[30][MAXN];//表示每层每个位置的值
int sorted[MAXN];//已经排序的数
int toleft[30][MAXN];//toleft[p][i]表示第i层从1到i有多少个数分入左边

void build(int l,int r,int dep)
{
    if(l==r)return;
    int mid=(l+r)>>1;
    int same=mid-l+1;//表示等于中间值而且被分入左边的个数
    for(int i=l;i<=r;i++)
      if(tree[dep][i]<sorted[mid])
         same--;
    int lpos=l;
    int rpos=mid+1;
    for(int i=l;i<=r;i++)
    {
        if(tree[dep][i]<sorted[mid])//比中间的数小，分入左边
             tree[dep+1][lpos++]=tree[dep][i];
        else if(tree[dep][i]==sorted[mid]&&same>0)
        {
            tree[dep+1][lpos++]=tree[dep][i];
            same--;
        }
        else  //比中间值大分入右边
            tree[dep+1][rpos++]=tree[dep][i];
        toleft[dep][i]=toleft[dep][l-1]+lpos-l;//从1到i放左边的个数

    }
    build(l,mid,dep+1);
    build(mid+1,r,dep+1);

}


//查询区间第k大的数，[L,R]是大区间，[l,r]是要查询的小区间
int query(int L,int R,int l,int r,int dep,int k)
{
    if(l==r)return tree[dep][l];
    int mid=(L+R)>>1;
    int cnt=toleft[dep][r]-toleft[dep][l-1];//[l,r]中位于左边的个数
    if(cnt>=k)
    {
        //L+要查询的区间前被放在左边的个数
        int newl=L+toleft[dep][l-1]-toleft[dep][L-1];
        //左端点加上查询区间会被放在左边的个数
        int newr=newl+cnt-1;
        return query(L,mid,newl,newr,dep+1,k);
    }
    else
    {
         int newr=r+toleft[dep][R]-toleft[dep][r];
         int newl=newr-(r-l-cnt);
         return query(mid+1,R,newl,newr,dep+1,k-cnt);
    }
}


int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    int n,m;
    int s,t,k;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        memset(tree,0,sizeof(tree));//这个必须
        for(int i=1;i<=n;i++)//从1开始
        {
            scanf("%d",&tree[0][i]);
            sorted[i]=tree[0][i];
        }
        sort(sorted+1,sorted+n+1);
        build(1,n,0);
        while(m--)
        {
            scanf("%d%d%d",&s,&t,&k);
            printf("%d\n",query(1,n,s,t,0,k));
        }
    }
    return 0;
}
