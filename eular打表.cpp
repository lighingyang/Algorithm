欧拉函数打表

原理：
利用欧拉函数和它本身不同质因数的关系，用筛法计算出某个范围内所有数的欧拉函数值。
欧拉函数和它本身不同质因数的关系：
欧拉函数ψ（N）=N{∏p|N}（1－1/p）
 
亦即:
 
（P是数N的质因数）
如：
ψ（10）=10×（1－1/2）×（1－1/5）=4；
ψ（30）=30×（1－1/2）×（1－1/3）×（1－1/5）=8；
ψ（49）=49×（1－1/7）=
 
=42。

const int maxn = 1e6+10;
int eular[maxn];
void init(){
    eular[1]=1;
    for(int i=2;i<maxn;i++){
        eular[i] = i;
    }
    for(int i=2;i*i<maxn;i++){
        if(eular[i]==i){
            for(int j=i;j<maxn;j+=i){
                eular[j] = eular[j]/i*(i-1);
            }
        }
    }
}
