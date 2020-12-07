/********************************************* 
*     ------------------------                 
*     ------------------------                 
*     file name: test.cpp
*     author   : @JY    
*     data     : 2019--09--03
**********************************************/
#include <bits/stdc++.h>
using namespace std;
class SegmentTree{
private:
    int n;
    vector<long long> tree, lazya, lazym;
    const long long MOD = 1e9 + 7;

public:
    SegmentTree(int n): n(n), tree(4 * n, 0ll), lazya(4 * n, 0ll), lazym(4 * n, 1ll){}
    void add(int index, int val){
        update(0, 0, n - 1, index, index, val, 1);
    }
    void update_add(int uL, int uR, int inc){
        update(0, 0, n-1, uL, uR, inc, 1);
    }
    void update_mul(int uL, int uR, int mul){
        update(0, 0, n-1, uL, uR, 0, mul);
    }

    int query(int index){
        return query(0, 0, n-1, index);
    }

private:
    void push_down(int treeID, int treeL, int treeR){
        if(lazya[treeID] != 0 || lazym[treeID] != 1){
            // 区间更新
            tree[treeID] = (tree[treeID] * lazym[treeID] + (treeR - treeL + 1)* lazya[treeID]) % MOD;

            // 懒更新
            if(treeL != treeR){
                lazym[2 * treeID + 1] = lazym[2 * treeID + 1] * lazym[treeID] % MOD;
                lazya[2 * treeID + 1] = lazya[2 * treeID + 1] * lazym[treeID] % MOD;
                lazya[2 * treeID + 1] = (lazya[2 * treeID + 1] + lazya[treeID]) % MOD;

                lazym[2 * treeID + 2] = lazym[2 * treeID + 2] * lazym[treeID] % MOD;
                lazya[2 * treeID + 2] = lazya[2 * treeID + 2] * lazym[treeID] % MOD;
                lazya[2 * treeID + 2] = (lazya[2 * treeID + 2] + lazya[treeID]) % MOD;
            }
            lazya[treeID] = 0;
            lazym[treeID] = 1;
        }
    }
    void update(int treeID, int treeL, int treeR, int uL, int uR, int inc, int mul){
        push_down(treeID, treeL, treeR);
        if (treeL > uR || treeR < uL) return;
        if(uL <= treeL && uR >= treeR){
            // 区间更新
            tree[treeID] = (tree[treeID] + tree[treeID] * (mul - 1) + (treeR - treeL + 1) * inc) % MOD;

            // 懒更新
            if(treeL != treeR){
                lazym[2 * treeID + 1] = lazym[2 * treeID + 1] * mul % MOD;
                lazya[2 * treeID + 1] = lazya[2 * treeID + 1] * mul % MOD;
                lazya[2 * treeID + 1] = (lazya[2 * treeID + 1] + inc) % MOD;

                lazym[2 * treeID + 2] = lazym[2 * treeID + 2] * mul % MOD;
                lazya[2 * treeID + 2] = lazya[2 * treeID + 2] * mul % MOD;
                lazya[2 * treeID + 2] = (lazya[2 * treeID + 2] + inc) % MOD;
            }
            return;
        }
        int mid = (treeL + treeR) / 2;
        update(2 * treeID + 1, treeL, mid, uL, uR, inc, mul);
        update(2 * treeID + 2, mid + 1, treeR, uL, uR, inc, mul);
        tree[treeID] = (tree[treeID * 2 + 1] + tree[treeID * 2 + 2]) % MOD;
        return;
    }

    int query(int treeID, int treeL, int treeR, int index){

        push_down(treeID, treeL, treeR);

        if(treeL == treeR) return tree[treeID];

        int mid = (treeL + treeR) / 2;
        if(index <= mid) return query(2 * treeID + 1, treeL, mid, index);
        return query(2 * treeID + 2, mid + 1, treeR, index);
    }
};

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
ll qpow(ll base, ll n)
{
    ll ans = 1;
    while (n) {
        if (n & 1)
            ans = ans * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return ans;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll a[N] = { 8, 2, 1, 7, 9 }, b[N], c[N], t = 49;
int n = 5, m = 1, old_r;

ll cal(int l, int r)
{
    r = min(r, n);
    int num = min(m, (r - l + 1) >> 1);
    for (int i = l; i <= r; ++i)
        b[i] = a[i];
    sort(b + l, b + r + 1);
    ll ans = 0;
    for (int i = 0; i < num; ++i) {
        ans += (b[r - i] - b[l + i]) * (b[r - i] - b[l + i]);
    }
    return ans;
}
int main()
{
    int a = 500, b = 500;
    for(int i=a; i; i = (i-1) & a)cout<<i<<"   ";
    cout<<endl;
    for(int i=b; i; i&=(i-1))cout<<i<<"    ";
    //std::vector<int> a = {1, 2, 3};
    //std::vector<int> b = {2, 2, 3};
    //std::set<std::vector<int>> mp;
    //mp.insert(a);
    //mp.insert(b);
    //std::cout<<mp.size()<<std::endl;
    //int l, r, p;
    //l = r = 1;
    //b[l] = a[l];
    //int ans = 0;
    //while (l <= n) {
        //int asd;
        //int ass;
        //int aad;
        //int asa;
        //p = 1;
            //ll num = cal(l, r + p);
        //while (p) {
            //ll num = cal(l, r + p);
            //if (num <= t) {
                //r = min(r + p, n);
                //if (r == n)
                    //break;
                //p <<= 1;
            //} else
                //p >>= 1;
        //}
        //++ans;
        //l = r + 1;
        //r = l;
    //}
    //cout << ans << '\n';
    return 0;
}
