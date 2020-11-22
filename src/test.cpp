#include "makeMonotone.hpp"
#include "monotoneTriangulation.hpp"
#include "utils.hpp"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define ld long double
#define sz(x) (int)x.size()

const int MOD = 1e9 + 7;
const int MAX_N = 2e5 + 5;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ifstream cin("in1");
    ofstream fout("out1");

    int n;
    cin >> n;
    vector<Point> arr(n);
    int mxi = 0;
    long double mxy = -100000000;
    for (int i = 0; i < n; i++) {
        long double x, y;
        cin >> x >> y;
        arr[i] = Point(x, y);
        if (y > mxy) {
            mxy = y;
            mxi = i;
        }
    }
    DCEL dcel = DCEL(arr);
    EventPoint ep;
    ep.index = mxi;
    ep.vertex = dcel.vertices[mxi];
    if (getVertexType(ep, dcel) == SPLIT) {
        reverse(arr.begin(), arr.end());
        dcel = DCEL(arr);
        ofstream rout("in1");
        rout << n << "\n";
        for (int i = 0; i < n; i++) {
            rout << arr[i].x << " " << arr[i].y << "\n";
        }
    }
    DCEL tans = makeMonotone(dcel);
    // fout << ans.edges.size() << "\n";
    // cout << ans.edges.size() << "\n";
    // for (auto it : ans.edges) {
    //     fout << it.v1->index << " " << it.v2->index << "\n";
    //     cout << it.v1->index << " " << it.v2->index << "\n";
    // }
    std::cout << "MakeMonotone Done!" << std::endl;
    tans = monotoneTriangulation(tans);
    std::cout << "Triangulation Done!" << std::endl;
    fout << tans.edges.size() << "\n";
    cout << tans.edges.size() << "\n";
    for (auto it : tans.edges) {
        fout << it.v1->index << " " << it.v2->index << "\n";
        cout << it.v1->index << " " << it.v2->index << "\n";
    }

    return 0;
}