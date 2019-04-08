题意：给一个长为n的字符串，问字符串的前缀是不是周期串，如果是周期串，输出前缀的最后一个字母的位置和最短周期

思路：kmp字符串匹配的性质运用。

对于前i个字符，如果f[i]不等于零，说明在此字符串的前缀中，有一部分[0，f[i]]和本字符串[i-f[i],i]的这一部分是相同的。如果这i个字符组成一个周期串，那么错开的一部分[f[i],i]恰好是一个循环节。（换句话说，如果满足f[i]不等于零 && [f[i],i]是循环节这两点，就可以说明前i个字符组成一个周期串）

code：

#include
#include
#include
using namespace std;

const int maxn = 1000005;

int f[maxn];
char s[maxn];
int n;

void kmp(char* p,int* f){
f[0] = 0; f[1] = 0;
for(int i = 1; i < n; i++){
int j = f[i];
while(j && p[j]!=p[i]) j = f[j];
f[i+1] = p[i] == p[j] ? j+1 : 0;
}
}

int main(){
int cas = 0;
while(scanf("%d",&n)){
if(n == 0) break;
scanf("%s",s);
kmp(s,f);
printf("Test case #%d\n",++cas);
for(int i = 2; i <= n; i++){
if(f[i] != 0 && i%(i-f[i])==0){
printf("%d %d\n",i,i/(i-f[i]));
}
}
printf("\n");
}
return 0;
}
