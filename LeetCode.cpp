// #include <gtest/gtest.h>
#include <Utility.h>
#include <Trie.h>

auto solve()
{
    vector<int> arr;
    read(arr);
    int res = 0;
    int n = arr.size();
    
    unordered_map<int,vector<int>> map;
    for (int i = 0; i < n; ++i)
        map[arr[i]].push_back(i);

    vector<char> visited(n);
    visited[0] = 1;
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        int levelSize = q.size();
        while (levelSize--)
        {
            int cur = q.front();
            if (cur == n-1) return res;
            if (cur == n-2) return res+1;
            q.pop();

            if (cur > 0 && visited[cur-1] == 0) {
                visited[cur-1]=1;
                q.push(cur-1);
            }
            if (cur < n-1 && visited[cur+1] == 0) {
                visited[cur+1]=1;
                q.push(cur+1);
            }
            for (int& next : map[arr[cur]]) {
                if (next == n-1) return res+1;
                if (visited[next] == 0) 
                {
                    q.push(next);
                    visited[next]=1;
                }
            }
            map[arr[cur]].clear();
        }
        ++res;
    }
    return res;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 3;
    FOR(t)
    {
        cout << "Case #" << i + 1 << ": " << endl;
        auto res = solve();
        print(res);
        print("Complete");
    }
    return 1;
}