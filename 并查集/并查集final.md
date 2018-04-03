每周课堂第一期--数据结构篇(1)  并查集



个人理解：数据结构是指有结构的，规定操作以维持结构，完成某种算法目的的数据形式。对于ACMer来说，用它们来帮助理解、分解题目，形成解题思路（套模板），以其空间复杂度来降低时间复杂度。

数据结构篇是为了帮助大家理解，熟悉算法竞赛中常用的数据结构概念，基础用法，模板套路而开设的。

废话不多说，接下来就以比较简单的一个数组就能描述的   并查集   开篇吧。

# 并查集

### 定义

并查集是一种树型的数据结构。树的每个节点就表示集合中的一个元素，树根对应的元素就是该集合的代表（祖先）。

### 用途

判断元素是否属于相同集合。求连通子图、求最小生成树的 Kruskal 算法和求最近公共祖先（Least Common Ancestors, LCA）等。

### 基本操作

顾名思义，并：合并，查：查询，集：集合

1. init(s)：建立一个新的并查集，其中包含 s 个单元素集合。

2. merge(x, y)：把元素 x 和元素 y 所在的集合合并，要求 x 和 y 所在的集合不相交，如果相交则不合并。

3. find(x)：找到元素 x 所在的集合的代表，该操作也可以用于判断两个元素是否位于同一个集合，只要将它们各自的代表比较一下就可以了。

   ​

talk is cheap , show me the code （￣～￣）



### 模板

```c++
#include <iostream>  
using namespace std;  
#define N 100005  
  
//不需要节点数的话，简单的一维数组就能表示并查集了
struct set  
{  
    int parent;  //记录父亲节点  
    int rank;    //记录集合的节点数  
}elem[N];  
  
int MAX;  //记录最大集合的节点数
  
void init()  
{  
    int i;  
    //设置每个元素的所在集合代表/根节点/祖先为自己,即每个元素自成一个集合，集合节点数为1
    for(i=0;i<=N;i++)  
    {  
        elem[i].parent=i;  
        elem[i].rank=1;  
    }  
}  
  
int find(int x)  
{  
    int root,temp;  
    temp=x;  
    while(x!=elem[x].parent)    //寻找所在集合代表/根节点/祖先，O(n)  
        x=elem[x].parent;  
    root=x;  
    x=temp;  
  /*
  把该路径上元素的父亲，全部赋值为所在集合代表/根节点/祖先的值（即压缩路径：剪枝，状态压缩思想）
  压缩后，再查找该集合其他元素的所在集合代表/根节点/祖先就能一步到位了，加快查询速度
  PS:路径压缩了就没了，所以可压缩的前提是问题不要求你输出路径
  */
    while (x!=elem[x].parent)   //判断是否抵达所在集合代表/根节点/祖先
    {  
        temp=elem[x].parent;   //暂存该元素的链接的下一路径点/父亲
        elem[x].parent=root;  //把该元素直接连到所在集合代表/根节点/祖先，完成压缩
        x=temp;             //继续沿路径走下去
    }  
    return root;  
}  
  
void merage(int a,int b)   //合并两个集合  
{  
    int x,y;  
    x=find(a);  //找到该元素的所在集合代表/根节点/祖先
    y=find(b);  
    //调整集合的集合节点数
    if(elem[x].rank>=elem[y].rank)  
    {  
        elem[y].parent=elem[x].parent;  
        elem[x].rank+=elem[y].rank;  
        if(MAX<elem[x].rank)  
            MAX=elem[x].rank;  
    }  
    else  
    {  
        elem[x].parent=elem[y].parent;  
        elem[y].rank+=elem[x].rank;  
        if(MAX<elem[y].rank)  
            MAX=elem[y].rank;  
    }  
}  
  
int main()  
{  
    int n;  // 有关系的对数 / 关系图的边数 / 家族血缘关系数  
    int a,b,x,y;  
    while (scanf("%d",&n)!=EOF)  
    {  
        //初始化集合，最大集合节点数
        init();  
        MAX=-1;   
        while (n--)  
        {  
            scanf("%d%d",&a,&b); // 输入两个有关系的元素 / 边 / 血缘关系
            x=find(a);  //找元素所在集合的代表/祖先
            y=find(b);  
            if(x!=y)      
                merage(a,b);//a和b不是一个集合的，合并这两个集合  
        }  
        if(MAX!=-1)  
            printf("%d/n",MAX);   //输出最大集合的节点数  
        else  
            printf("1/n");   //此时n=0，证明都是没关系的 
    }  
    return 0;  
}
```

再来个图示帮助理解(`･ω･´)

## 图示

​                                        ![img](https://mmbiz.qpic.cn/mmbiz_png/3FFeGmWg0oiacibO5RZrBSqMWFvhsYjiaT7cZ7iaWvf071fV7vxhHeVh7R55l7ckx9G4GvtPAbLaDTARv93X3dXdzw/0?wx_fmt=png)

​                                        1.并查集就是这样的树形结构

​                                        

![img](https://mmbiz.qpic.cn/mmbiz_png/3FFeGmWg0oiacibO5RZrBSqMWFvhsYjiaT7kiaonXab1ITh8SMFh0iaSIIzHLvhaLG6lo6qjtv7Xib3fXf5KNlvibOzWQ/0?wx_fmt=png)

​                                        2.查找和压缩路径

![img](https://mmbiz.qpic.cn/mmbiz_png/3FFeGmWg0oiacibO5RZrBSqMWFvhsYjiaT7We1D6OaibJadohBo2lycuuKe3tjR3icYmDLgehiaxjXDMbSFZricibC9JQg/0?wx_fmt=png)

​                                        3.合并集集合

OK,现在让我们来试试手≖‿≖✧

![img](https://mmbiz.qpic.cn/mmbiz_jpg/3FFeGmWg0oiacibO5RZrBSqMWFvhsYjiaT75Z7sobHCYnesRz5ibDCpu0evCMB4Licn59ZgHndsU8xtBTiaicxPeX1IZw/0?wx_fmt=jpeg)

## 简单例题

```c++
/*hdu1232畅通工程 
畅通工程 
Time Limit: 4000/2000 MS (Java/Others) Memory Limit: 65536/32768 K (Java/Others) 
Total Submission(s): 52315 Accepted Submission(s): 27902

Problem Description 
某省调查城镇交通状况，得到现有城镇道路统计表，表中列出了每条道路直接连通的城镇。省政府“畅通工程”的目标是使全省任何两个城镇间都可以实现交通（但不一定有直接的道路相连，只要互相间接通过道路可达即可）。问最少还需要建设多少条道路？

Input 
测试输入包含若干测试用例。每个测试用例的第1行给出两个正整数，分别是城镇数目N ( < 1000 )和道路数目M；随后的M行对应M条道路，每行给出一对正整数，分别是该条道路直接连通的两个城镇的编号。为简单起见，城镇从1到N编号。 
注意:两个城市之间可以有多条道路相通,也就是说 
3 3 
1 2 
1 2 
2 1 
这种输入也是合法的 
当N为0时，输入结束，该用例不被处理。

Output 
对每个测试用例，在1行里输出最少还需要建设的道路数目。

Sample Input

4 2 
1 3 
4 3 
3 3 
1 2 
1 3 
2 3 
5 2 
1 2 
3 5 
999 0 
0

Sample Output

1 
0 
2 
998

*/


/* 赤裸裸的并查集 ， 默写模板就好了*/

#include<stdio.h>  
int elem[1002];  
      
void init(int n)
{
    for(int i=1;i<=n;i++)  
        elem[i] = i;    
}  
      
int find(int x)  
{  
    int r=x;  
    //数据不大，路径不压缩也不会超时，就少写点代码呗 
    while(elem[r]!=r)  
        r=elem[r];  
    return r;  
}  
void merge(int x,int y)  
{  
    int fx,fy;  
    fx = find(x);  
    fy = find(y);  
    if(fx != fy)  
        elem[fx]=fy;  
}  
      
      
int main()  
{  
    int n,m,x,y;  
    while(scanf("%d",&n),n)  
    {       
        init(n);
        scanf("%d",&m);     
        while(m--)  
        {  
            scanf("%d %d",&x,&y);  
            merge(x,y);  
        }  
        int count=-1;
        for(int i=1;i<=n;i++) 
        {
            if(elem[i]==i)  
                count++;  
        } 
        printf("%d\n",count);  
    }  
}  
```

哈，太简单了不过瘾吧。丢个题集做做，来更深地体会并查集吧~~和模板培养感情~~。(๑•́ ₃•̀๑)╭

专题做题，集中时间训练，效果更佳噢。

### 题集

```
HDU

简单并查集

1213 How Many Tables     
1232 畅通工程   

简单最小生成树

1233 还是畅通工程  
1863 畅通工程    
1874 畅通工程再续  
1875 继续畅通工程 
1162 Eddy's picture  
1102 Constructing Roads 
1301 Jungle Roads
（可以通过最小生成树练习并查集）

稍微有点难度并查集

1272 小希的迷宫  
1325 Is It A Tree?  
1856 More is better

有点难度的并查集

1116    Play on Words
1829    A Bug's Life
1198    Farm Irrigation
3635    Dragon Balls
2473    Junk-Mail Filter
3172    Virtual Friends
3047    Zjnu Stadium
3038    How Many Answers Are Wrong
1558    Segment set
1598    find the most comfortable road
3461    Code Lock
2818    Building Block
3367    Pseudoforest
3234    Exclusive-OR
```



欢迎刷题的同学，将以上题目的AC的代码注释上心得体会，投稿邮箱530598936@qq.com，就可以在下一期分享给大家。有AC不了的同学,也可以发来代码，附上问题，热心学长们帮你调试、分析噢。也欢迎提建议，写文章投稿到上述邮箱噢。

By the way,求招会排版的同学来美化文章，工资是学长们的小心心。

公众号的资料（代码，md文档，表情包）可以在github上获取噢。

地址： https://github.com/keeeepgo/2018_acm_rep

第一期到这里就结束啦。ACMers，我们下周一或周二见。

### 参考

> <https://zhidao.baidu.com/question/293001297.html>
>
> <https://blog.csdn.net/dm_vincent/article/details/7655764>
>
> <https://blog.csdn.net/xiaotaoqibao/article/details/5767173>
>
> <https://blog.csdn.net/oliver233/article/details/70162173>
>
> <https://blog.csdn.net/oliver233/article/details/70162173>
>
> <https://segmentfault.com/a/1190000004023326>