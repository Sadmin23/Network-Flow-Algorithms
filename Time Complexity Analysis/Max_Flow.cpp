#include <bits/stdc++.h>

using namespace std;

#define N 100
#define INF INT_MAX

int cap[N][N];
vector<int> adj[N];
int pre[N];

int cap2[N][N];
vector<int> adj2[N];
int pre2[N];
int visited[N];

bool reached = false;

void init()
{
    for (int i = 0; i < N; i++)
    {
        pre[i] = -1;
        pre2[i] = -1;

        for (int j = 0; j < N; j++)
        {
            cap[i][j] = 0;
            cap2[i][j] = 0;
        }
    }
}
int bfs(int s, int t)
{
    for (int i = 0; i < N; i++)
        pre[i] = -1;

    pre[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty())
    {
        int cur = q.front().first;
        int flo = q.front().second;
        q.pop();

        for (auto v : adj[cur])
        {
            if (pre[v] == -1 && cap[cur][v])
            {
                pre[v] = cur;

                int flo2 = min(flo, cap[cur][v]);

                if (v == t)
                    return flo2;
                q.push({v, flo2});
            }
        }
    }

    return 0;
}
int maxflow_EK(int s, int t)
{
    int flow = 0;
    int flow2;

    while (flow2 = bfs(s, t))
    {
        flow += flow2;
        int cur = t;

        while (cur != s)
        {
            int previous = pre[cur];
            cap[previous][cur] -= flow2;
            cap[cur][previous] += flow2;
            cur = previous;
        }
    }

    return flow;
}
int dfs_visit(int s, int t)
{
    visited[s] = 0;
    int flow = INF;

    for (auto i : adj2[s])
    {
        if (reached)
            return flow;
        if (visited[i] == -1 && cap2[s][i] > 0)
        {
            pre2[i] = s;
            flow = cap2[s][i];
            if (i == t)
            {
                reached = true;
                return flow;
            }
            flow = min(flow, dfs_visit(i, t));
        }
    }

    return flow;
}
int dfs(int s, int t)
{
    for (int i = 0; i < N; i++)
        pre2[i] = -1;

    pre2[s] = -2;

    reached = false;

    int cur_flow = INF;

    for (int i = 0; i < N; i++)
        visited[i] = -1;

    cur_flow = min(cur_flow, dfs_visit(s, t));

    if (reached)
        return cur_flow;

    return 0;
}
int maxflow_FF(int s, int t)
{
    int flow = 0;
    int flow2;

    while (flow2 = dfs(s, t))
    {
        // cout << flow2 << "\n";

        flow += flow2;
        int cur = t;

        while (cur != s)
        {
            int previous = pre2[cur];
            cap2[previous][cur] -= flow2;
            cap2[cur][previous] += flow2;
            cur = previous;
        }
    }

    return flow;
}
int main()
{
    init();

    freopen("B.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;

        adj[x].push_back(y);
        adj[y].push_back(x);
        cap[x][y] = z;

        adj2[x].push_back(y);
        adj2[y].push_back(x);
        cap2[x][y] = z;
    }

    auto st = chrono::high_resolution_clock::now();
    cout << "Edmonds Karp:\n\nMax Flow: " << maxflow_EK(0, n - 1) << "\n";
    auto ed = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(ed - st);
    cout << "Time: " << duration.count() << " microseconds\n\n\n";

    auto st1 = chrono::high_resolution_clock::now();
    cout << "Ford Fulkersion:\n\nMax Flow: " << maxflow_FF(0, n - 1) << "\n";
    auto ed1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(ed1 - st1);
    cout << "Time: " << duration1.count() << " microseconds\n\n";

    return 0;
}