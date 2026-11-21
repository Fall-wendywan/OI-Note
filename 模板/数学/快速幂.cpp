#include<bits/stdc++.h>
#define int long long
using namespace std;
int a, b, MOD;
int qpow( int a, int b ){
    int res = 1;
    while( b != 0 ){
        if( b % 2 == 1 ) res = res * a % MOD;
        a = a * a % MOD;
        b /= 2;
    }
    return res;
}
signed main(){
    cin >> a >> b >> MOD;
    cout << a << "^" << b << " mod " << MOD << "=" << qpow( a, b );
    return 0;
}