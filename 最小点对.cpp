HDU 1007 Quoit Design （最小点对，模板题）
题目很明显，答案就是最小点对距离的一半。

最小点对的算法就是分治，

把所以点分成两部分，然后合起来，重点是怎么样合起来。

算法思想不再赘述，记得有很多资料说这个的。

大致思想就是按照x坐标排序，分成左右两部分，求左半部分的最小距离，右半部分的最小距离，d=min(d1,d2)。还有就是分界线两侧小于d的点的距离可能是最小点对。

#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<math.h>
using namespace std;


//*************************************
//模板
//**************************************
const int N = 100005;
const double MAX = 10e100;
const double eps=0.00001;
struct Point
{
    double x,y;
    int index;
};
Point a[N],b[N],c[N];

double closest(Point *,Point *,Point *,int,int);
double dis(Point,Point);
int merge(Point *,Point *,int ,int ,int);
int cmp_x(const void *,const void *);
int cmp_y(const void *,const void *);
//inline double min(double ,double);

int main()
{
    int n,i;
    double d;
    while(scanf("%d",&n)!=EOF,n)
    {
        for(i = 0;i < n;i++)
          scanf("%lf %lf",&a[i].x,&a[i].y);
        qsort(a,n,sizeof(a[0]),cmp_x);//快排，按照 x 坐标 
        for(i = 0;i < n;i++)
            a[i].index = i;
        memcpy(b,a,n*sizeof(a[0]));
        qsort(b,n,sizeof(b[0]),cmp_y);
        d = closest(a,b,c,0,n-1);
        printf("%.2lf\n",d/2);
    }    
    return 0;
}    


double closest(Point a[],Point b[],Point c[],int p,int q)
{//a是按照 x 坐标从小到大排序的，b 是按照 y 坐标从小到大排序的
//求 a 从 p 点到 q 点的最小点对距离 
    if(q - p == 1) return dis(a[p],a[q]);//两个点 
    if(q - p == 2) //三个点的情况 
    {
        double x1 = dis(a[p],a[q]);
        double x2 = dis(a[p+1],a[q]);
        double x3 = dis(a[p],a[p+1]);
        if(x1 < x2 && x1 < x3) return x1;
        else if(x2 < x3) return x2;
        else return x3;
    } 
    int i,j,k,m = (p+q) / 2;//按照横坐标分成两部分 
    double d1,d2;
    
    //把 点分成两部分，左边的存在 c[p~m],右边的存在 c[m+1~q],两部分均按照 y 排序 
    for(i = p,j = p,k = m + 1;i <= q;i++)
          if(b[i].index <= m) c[j++] = b[i];
          else c[k++] = b[i];
    d1 = closest(a,c,b,p,m);//左半部分的最小点对距离 
    d2 = closest(a,c,b,m+1,q);//右半部分的最小点对距离 
    double dm = min(d1,d2);//取两者的较小值 
    //数组 c 左右部分分别是对　ｙ坐标有序的，合并回　ｂ 
    merge(b,c,p,m,q);
    for(i = p,k = p ; i <= q;i++)
         if(fabs(b[i].x - b[m].x) < dm) c[k++] = b[i];
         //找出离划分基准左右不超过dm的部分，且仍然对 y 有序 
    for(i = p;i < k;i++)
       for(j = i+1;j < k && c[j].y -c[i].y < dm;j++)
       {
           double temp = dis(c[i],c[j]);
           if(temp < dm) dm = temp;
       }       
    return dm;
}    

double dis(Point p,Point q)//求两点的距离 
{
    double x1 = p.x - q.x, y1 = p.y - q.y;
    return sqrt(x1 * x1 +  y1 * y1);
}
int cmp_x(const void *p,const void *q)//把点按照 x 坐标排序 
{
    double temp = ((Point *)p)->x - ((Point *)q)->x;
    if(temp > 0) return 1;
    else if(fabs(temp) < eps) return 0;
    else return -1;
}    
int cmp_y(const void *p,const void *q)//把点按照 y 坐标排序 
{
    double temp = ((Point *)p)->y - ((Point *)q)->y;
    if(temp > 0) return 1;
    else if(fabs(temp) < eps) return 0;
    else return -1;
}    

int merge(Point p[],Point q[],int s,int m,int t)
{//把 q[s~m],q[m+1~t]合并回 p , 而且按照 y 排序。q[s~m],q[m+1~t]已经是按照 y 排序的了 
    int i,j,k;
    for(i = s, j = m+1, k = s;i <= m && j <= t;)
    {
        if(q[i].y > q[j].y) p[k++] = q[j],j++;
        else p[k++] = q[i],i++;
    } 
    while( i <= m) p[k++] = q[i++];
    while( j <= t) p[k++] = q[j++];
    memcpy(q+s,p+s,(t-s+1)*sizeof(p[0]));//把 p 复制 给 q 
    return 0;   
} 
/*
inline double min(double p,double q)
{
    return (p>q)?(q):(p);
}  */
