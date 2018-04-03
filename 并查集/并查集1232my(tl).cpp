#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	int n,m,p[1001]; 
	while(scanf("%d",&n) && n){
		scanf("%d",&m);
		for(int i=1;i<=n;++i){
			p[i] = i;
		}
		for(int i=0;i<m;++i){
			int a,b;
			scanf("%d%d",&a,&b);
			if(p[a] != p[b]){
				int t = b;
				while(p[t]!=t){
					int tt = p[t];
					p[t] = p[a];
					t = tt;
				}
				p[t] = p[a];
			}
		}
		for(int i=1;i<=n;++i){
			int t = i;
			while(p[t]!=t){
				t = p[t];
			}
			p[i] = t;
//			cout << i << ":   " << p[i]<<endl;
		}
		sort(p+1,p+n+1);
		int res=0;
		for(int i=1;i<=n;++i){
			if(p[i] != p[i-1]){
				res++;
			}
		}
		cout << res-1 << endl;
	} 
	
}

