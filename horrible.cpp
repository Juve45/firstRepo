#include <bits/stdc++.h>

#define dbg(x) cerr<<#x": "<<x<<"\n"
#define dbg_v(x, n) do{cerr<<#x"[]: ";for(int _=0;_<n;++_)cerr<<x[_]<<" ";cerr<<'\n';}while(0)
#define dbg_ok cerr<<"OK!\n"
#define nmax 100010

using namespace std;

int n;

struct arbint{
	long long sum,lazy;
} ai[4*nmax];

void actualizare(int a, int b, int val, int nod, int st, int dr)
{
	if (b<st||a>dr)
		return;
	if (st!=dr)
	{
		ai[2*nod].lazy+=ai[nod].lazy;
		ai[2*nod+1].lazy+=ai[nod].lazy;
		ai[nod].lazy=0;
	}
	else{
		ai[nod].sum += ai[nod].lazy;
		ai[nod].lazy=0;
		return;
	}
	if (a<=st&&dr<=b)
	{
		ai[nod].lazy+=val;
		return;
	}
	int mid=(st+dr)/2;
	actualizare(a,b,val,2*nod,st,mid);
	actualizare(a,b,val,2*nod+1,mid+1,dr);
	ai[nod].sum = ai[2*nod].sum+ai[2*nod+1].sum + ai[2*nod].lazy*(mid-st+1) + ai[2*nod+1].lazy*(dr-mid); 
}

long long interogare(int a, int b, int nod, int st, int dr)
{
	if (b<st||a>dr)
		return 0;
	ai[nod].sum=ai[nod].sum+ai[nod].lazy*(dr-st+1);
	if (st!=dr)
	{
		ai[2*nod].lazy+=ai[nod].lazy;
		ai[2*nod+1].lazy+=ai[nod].lazy;
		ai[nod].lazy=0;
	}
	else
	{
		ai[nod].lazy=0;
		return ai[nod].sum;
	}
	if (a<=st&&dr<=b)
		return ai[nod].sum;

	int mid=(st+dr)/2;
	long long ret=0;
	ret=interogare(a,b,2*nod,st,mid)+interogare(a,b,2*nod+1,mid+1,dr);
	return ret;
}

void solve()
{

	for(int i=0;i<4*nmax-2;i++)
		ai[i].sum = ai[i].lazy = 0;

	int c, i;
	//cin >> n >> c;
	scanf("%d%d", &n, &c);
	for (i=1; i<=c; i++)
	{
		int op;
		scanf("%d", &op);
		//cin >> op;
		if (!op)
		{
			int p,q,v;
			scanf("%d%d%d", &p, &q, &v);
			actualizare(p,q,v,1,1,n);
		}
		else
		{
			int p,q;
			scanf("%d%d", &p, &q);
			//cin >> p >> q;
			//cout << interogare(p,q,1,1,n) << '\n';
			printf("%lld\n", interogare(p,q,1,1,n));
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	int T;
  
	scanf("%d", &T);
	for (int t=1; t<=T; t++)
		solve();
}
