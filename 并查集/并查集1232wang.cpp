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
    while(elem[r]!=r)  //数据不大，路径不压缩也不会超时，就少写点代码呗 
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

