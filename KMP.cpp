KMP算法
#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<map>
#define Mid int mid = (l+r)>>1
#define lson i<<1,l,mid
#define rson (i<<1)+1,mid+1,r
using namespace std;
const int maxn = 1e6+10;
char mo[maxn];
char pre[maxn];
int Next[maxn];
int ans=0;
void getNext(){
    int len = strlen(mo);
    int k=-1;
    int j=0;
    Next[0]=-1;
    while(j<len-1){
        if(k==-1||mo[k]==mo[j]){
            Next[++j]=++k;
        }
        else{
            k = Next[k];
        }
    }
    return ;
}

void KMP(){
    getNext();
    int len1 = strlen(mo);
    int len2 = strlen(pre);
    int i=0,j=0;
    while(i<len2&&j<len1){
        if(j==-1||pre[i]==mo[j]){
            if(j==len1-1){
                ans++;
                j=Next[j];
            }
            else{
                i++;j++;
            }
        }
        else{
            j = Next[j];
        }
    }
    return ;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        ans=0;
        scanf("%s%s",mo,pre);
        KMP();
        cout<<ans<<endl;
    }
    return 0;
}
/*
