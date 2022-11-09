#include <bits/stdc++.h>

using namespace std;

#define N 100
#define INF INT_MAX

int cap[N][N];
vector<int> adj[N];
int pre[N];

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
int maxflow(int s, int t)
{
    int flow = 0;
    int flow2;

    while (flow2 = bfs(s, t))
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

    freopen("A.txt", "r", stdin);

    int persons, books;
    cin >> persons >> books;

    int n = persons + books;
    int t = persons + books + 1;

    vector<int> copies;

    for (int i = 0; i < books; i++)
    {
        int x;
        cin >> x;
        copies.push_back(x);
    }
    for (int i = 1; i <= persons; i++)
    {
        int b;
        cin >> b;
        while (b--)
        {
            int x;
            cin >> x;
            // cap[i][x + persons] = 1;
            cap[i][x + persons] = copies[x - 1];
            adj[i].push_back(x + persons);
            adj[x + persons].push_back(i);
        }
    }
    for (int i = 1; i <= persons; i++)
    {
        cap[0][i] = 1;
        adj[0].push_back(i);
        adj[i].push_back(0);
    }
    for (int i = persons + 1; i <= persons + books; i++)
    {
        cap[i][t] = 1;
        adj[i].push_back(t);
        adj[t].push_back(i);
    }

    cout << "NUmber of Matches: " << maxflow(0, t) << "\n";

    for (int i = 1; i <= persons; i++)
    {
        for (auto x : adj[i])
        {
            if (cap[i][x] == 0)
                cout << "Person #" << i << " --> Book #" << x - persons << endl;
        }
    }

    return 0;
}