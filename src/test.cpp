#include "makeMonotone.hpp"
#include "utils.hpp"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define int long long
#define ld long double
#define sz(x) (int)x.size()

const int MOD = 1e9 + 7;
const int MAX_N = 2e5 + 5;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<Point> arr(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        arr[i] = Point(x, y);
    }
    DCEL dcel = DCEL(arr);
    makeMonotone(dcel);

    return 0;
}