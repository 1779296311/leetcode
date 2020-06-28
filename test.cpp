/********************************************* 
*     ------------------------                 
*     ------------------------                 
*     file name: test.cpp
*     author   : @JY    
*     data     : 2019--09--03
**********************************************/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;
typedef pair<ll, ll> pll;
const int mod = 1e9 + 7;
const int N = 5e5 + 10;
const int INF = 0x3f3f3f3f;
ll qpow(ll base, ll n){ll ans = 1; while (n){if (n & 1) ans = ans * base % mod; base = base * base % mod; n >>= 1;} return ans;}
ll gcd(ll a, ll b){return b ? gcd(b, a % b) : a;}
ll a[N]={8,2,1,7,9}, b[N], c[N], t=49;
int n=5, m=1, old_r;
 
ll cal(int l, int r){
	r = min(r, n);
	int num = min(m, (r - l + 1) >> 1);
	for (int i = l; i <= r; ++ i) b[i] = a[i];
	sort(b + l, b + r + 1);
	ll ans = 0;
	for (int i = 0; i < num; ++ i) {
		ans += (b[r - i] - b[l + i]) * (b[r - i] - b[l + i]);
	}
	return ans;
}
int main()
{
		int l, r, p;
		l = r = 1;
		b[l] = a[l];
		int ans = 0;
		while (l <= n){
			p = 1;
			while (p){
				ll num = cal(l, r + p);
				if (num <= t){
					r = min(r + p, n);
					if (r == n) break;
					p <<= 1;
				}else p >>= 1;
			}
			++ ans;
			l = r + 1;
		    r = l;
		}
		cout << ans << '\n';
	return 0;
}
