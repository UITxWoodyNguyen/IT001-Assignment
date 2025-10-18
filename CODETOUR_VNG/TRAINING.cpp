#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    long long c, k;
    cin >> n >> c >> k;
    
    vector<long long> a(n), b(n);
    int cnt = 0;
    map<long long, long long> mp;
    
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        if (a[i] >= k) {
            cnt++;
        } else if (b[i] > 0) {
            long long x = (k - a[i] + b[i] - 1) / b[i];
            mp[x]++;
        }
    }
    
    vector<pair<long long, long long>> v;
    for (auto& p : mp) {
        v.push_back(p);
    }
    
    sort(v.begin(), v.end());
    
    long long l = 0, r = 0;
    for (auto& p : v) {
        r += p.second;
    }
    
    long long ans = 0;
    
    auto check = [&](long long m) -> bool {
        long long s = 0;
        long long rem = m;
        for (auto& p : v) {
            if (rem == 0) break;
            long long take = min(p.second, rem);
            s += p.first * take;
            rem -= take;
            if (s > c) return false;
        }
        return s <= c;
    };
    
    while (l <= r) {
        long long mid = l + (r - l) / 2;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    
    cout << cnt + ans << endl;
    
    return 0;
}
