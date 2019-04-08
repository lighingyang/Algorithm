#include <bits/stdc++.h>
#define maxn 1000000using 
namespace std;
struct Trie
{
    int next[26];///表示下一个节点是否存在，    
    int val;///节点的数据域,可根据需要进行改变
} tree[maxn];
int nxt;///nxt表示节点的编号
char str[26];///存储输入的字符串
int add()
{                                 ///建立新的节点    
    memset(&tree[nxt], 0, sizeof(Trie));
    return nxt++;
}
void Insert(char *s)///插入以及建树
{
    int rt = 0, len = strlen(s);
    for(int i = 0; i < len; i++)
    {
        int c = s[i] - 'a';
        if(!tree[rt].next[c])
        {
            ///如果树中还不存在这个节点，就开辟新的节点            
            tree[rt].next[c] = add();
        }
        rt = tree[rt].next[c];
    }
    tree[rt].val++;///维护数据域（这个表示出现的次数）
}
bool Find(char *s)
{
    //查找字符串是否存在    
    int rt = 0, len = strlen(s);
    for(int i = 0; i < len; i++)
    {
        int c = s[i] - 'a';
        if(!tree[rt].next[c])
            return false;
        rt = tree[rt].next[c];
    }
    if(tree[rt].val)
        return true;
    return false;
}
int main()
{
    int T;
    memset(&tree[0], 0, sizeof(Trie));
    nxt = 1;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%s", str);
        Insert(str);
    }
    while(~scanf("%s", str))
    {
        if(Find(str))
            puts("exist");
        else
            puts("none");
    }
    return 0;
}
