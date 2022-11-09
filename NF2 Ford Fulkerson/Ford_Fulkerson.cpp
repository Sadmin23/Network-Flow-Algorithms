#include <bits/stdc++.h>

using namespace std;

#define N 100
#define INF INT_MAX

int cap[N][N];
vector<int> adj[N];
int pre[N];
int visited[N];

bool reached = false;

void init()
{
    for (int i = 0; i < N; i++)
    {
        pre[i] = -1;

        for (int j = 0; j < N; j++)
        {
            cap[i][j] = 0;
        }
    }
}
int dfs_visit(int s, int t)
{
    visited[s] = 0;
    int flow = INF;

    for (auto i : adj[s])
    {
        if (reached)
            return flow;
        if (visited[i] == -1 && cap[s][i] > 0)
        {
            pre[i] = s;
            flow = cap[s][i];
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
        pre[i] = -1;

    pre[s] = -2;

    reached = false;

    int cur_flow = INF;

    for (int i = 0; i < N; i++)
        visited[i] = -1;

    cur_flow = min(cur_flow, dfs_visit(s, t));

    if (reached)
        return cur_flow;

    return 0;
}
int maxflow(int s, int t)
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
            int previous = pre[cur];
            cap[previous][cur] -= flow2;
            cap[cur][previous] += flow2;
            cur = previous;
        }
    }

    return flow;
}
int main()
{
    init();

    freopen("input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;

        adj[x].push_back(y);
        adj[y].push_back(x);
        cap[x][y] = z;
    }

    cout << maxflow(0, n - 1) << "\n";

    return 0;
}