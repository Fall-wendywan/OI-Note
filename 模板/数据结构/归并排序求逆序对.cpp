#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e5 + 5;
int N, n, a, b, c[MAXN], num[MAXN];
// struct Segtree{
//     int l, r, 
// }
long long ans = 0;
void gb( int l, int r ){
	if( l == r ) return;
	int mid = ( l + r ) / 2;
	gb( l, mid );
	gb( mid + 1, r );
	
	int i = l, j = mid + 1;
	for( int k = l; k <= r; k ++ ){
		if( j > r || ( i <= mid && num[i] <= num[j] ) ){
			c[k] = num[i];
			i ++;
		}
		else{
			c[k] = num[j];
			ans += mid - i + 1;
			j ++;
		}
	}
	for( int x = l; x <= r; x ++ ) {
		num[x] = c[x];
	}
}
signed main(){
    freopen( "inversion.in", "r", stdin );
    freopen( "inversion.out", "w", stdout );
    cin >> N;
    for( int i = 1; i <= MAXN - 1; i ++ ) num[i] = i;
    for( int i = 1; i <= N; i ++ ){
        cin >> a >> b;
        swap( num[a], num[b] );
        n = max({ n, a, b });
    }

    // for( int i = 1; i <= N; i ++ ){
    //     swap( num[a], num[b[i]] );
    // }
    // for( int i = 1; i <= n; i ++ ) cerr << num[i] << " ";
    gb( 1, n );

    cout << ans;
    return 0;
}