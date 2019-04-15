#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1010;
int n;  //圆的个数
float minn = 10000;  //当前圆排列的最小长度
ll r[maxn];  //各个圆的半径
ll bestr[maxn];   //最优排列下圆的半径
double x[maxn];  //各个圆的圆心

//计算当前圆排列的长度
void compute()
{
    int i;
    float low = 0;  //圆位于原点右侧
    float heigh = 0;
    for(i=1; i<=n; i++)
    {
        if(x[i]-r[i]<low)  //寻找最左边的坐标，当圆位于原点左侧时才会更新
            low = x[i]-r[i];
        if(x[i]+r[i]>heigh)  //寻找最右边的坐标
            heigh = x[i]+r[i];
    }
    if(heigh-low<minn)  //如果当前圆排列的长度小于之前的最优值
         minn =  heigh - low;  //更新
}

//计算当前所选择圆的圆心
float center(int i)
{
    int j;
    float temp = 0.0;
    float valuex;
    for(j=1; j<i; j++)
    {
        valuex = x[j] + 2.0*sqrt(r[j]*r[i]);  //寻找当前层下最右边的圆心
        if(valuex>temp)
            temp = valuex;
    }
    return temp;
}

void backtrack(int i)
{
    if(i>n)  //如果到最后一个圆
    {
        compute();  //计算当前圆排列的最小长度
        int  j;
        for(j=1; j<=n; j++)
            bestr[j] = r[j];
    }
    else
    {
        int j;
        for(j=i; j<=n; j++)  //选择要排列的圆
        {
            swap(r[i], r[j]); //选择第j个圆
            float centerx = center(i);  //计算圆心
            if(centerx+r[i]<minn)  //下界约束，当前圆的长度<最优值，才能产生最优值
            {
                x[i] = centerx;  //记录圆心
                backtrack(i+1);  //搜索下一层
            }
            swap(r[i], r[j]);  //返回上一层
        }
    }
}
/*
void circle(int n1, ll r1[])
{
    n = n1;
    int i;
    for(i=1; i<=n; i++)
        r[i] = r1[i];
    backtrack(1);
}
*/
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&r[i]);
    }
    backtrack(1);
    /*
    ll r1[]={0, 4 ,2 ,7 ,6};
    circle(n1, r1);
    printf("圆的个数为：%d\n", n);
    printf("半径分别为：\n");
    int i;
    for(i=1; i<=n; i++)
        printf("%d ", r1[i]);
    printf("\n");
    printf("最优排列下，圆的半径为：\n");
    for(i=1; i<=n; i++)
        printf("%d ", bestr[i]);
    printf("\n");
    */
    printf("%.5lf\n", minn);//最小长度
    return 0;
}
