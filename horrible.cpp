#include <bits/stdc++.h>

#define dbg(x) cerr<<#x": "<<x<<"\n"
#define dbg_v(x, n) do{cerr<<#x"[]: ";for(long long _=0;_<n;++_)cerr<<x[_]<<" ";cerr<<'\n';}while(0)
#define dbg_ok cerr<<"OK!\n"
#define nmax 100010

using namespace std;

long long n;

struct arbint{
	long long sum,lazy;
} ai[4*nmax];

void actualizare(long long a, long long b, long long val, long long nod, long long st, long long dr)
{
	if (b<st||a>dr)
		return;

	if (a<=st&&dr<=b)
	{
		ai[nod].lazy += val;
		return;
	}

	long long mid=(st+dr)/2;

	if (st!=dr)
	{
		ai[2*nod].lazy += ai[nod].lazy;
		ai[2*nod+1].lazy += ai[nod].lazy;
		ai[nod].sum = ai[2*nod].sum+ai[2*nod+1].sum + ai[2*nod].lazy*(mid-st+1) + ai[2*nod+1].lazy*(dr-mid); 
	}
	else{
		ai[nod].sum += ai[nod].lazy;
		//return;
	}	
	ai[nod].lazy = 0;
	
	actualizare(a,b,val,2*nod,st,mid);
	actualizare(a,b,val,2*nod+1,mid+1,dr);
	ai[nod].sum = ai[2*nod].sum+ai[2*nod+1].sum + ai[2*nod].lazy*(mid-st+1) + ai[2*nod+1].lazy*(dr-mid); 
}

long long interogare(long long a, long long b, long long nod, long long st, long long dr)
{
	if (b<st||a>dr)
		return 0;

	long long mid=(st+dr)/2;

	if (st!=dr)
	{
		ai[2*nod].lazy+=ai[nod].lazy;
		ai[2*nod+1].lazy+=ai[nod].lazy;
		ai[nod].lazy=0;
		ai[nod].sum = ai[2*nod].sum+ai[2*nod+1].sum + ai[2*nod].lazy*(mid-st+1) + ai[2*nod+1].lazy*(dr-mid); 
	}
	else
	{
		ai[nod].sum += ai[nod].lazy;
		ai[nod].lazy=0;
		return ai[nod].sum;
	}

	if (a<=st&&dr<=b)
		return ai[nod].sum;

	long long ret=0;
	ret=interogare(a,b,2*nod,st,mid)+interogare(a,b,2*nod+1,mid+1,dr);
	return ret;
}

void solve()
{

	for(long long i=0;i<4*nmax-2;i++)
		ai[i].sum = ai[i].lazy = 0;

	long long c, i;
	//cin >> n >> c;
	scanf("%lld%lld", &n, &c);
	for (i=1; i<=c; i++)
	{
		long long op;
		scanf("%lld", &op);
		//cin >> op;
		if (!op)
		{
			long long p,q,v;
			scanf("%lld%lld%lld", &p, &q, &v);
			actualizare(p,q,v,1,1,n);
		}
		else
		{
			long long p,q;
			scanf("%lld%lld", &p, &q);
			//cin >> p >> q;
			//cout << interogare(p,q,1,1,n) << '\n';
			printf("%lld\n", interogare(p,q,1,1,n));
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	long long T;
	
	scanf("%lld", &T);
	for (long long t=1; t<=T; t++)
		solve();
}

	
