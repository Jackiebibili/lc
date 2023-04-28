// problem https://vjudge.net/problem/POJ-3585
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 2e5 + 1;

int T, n, idx = 0;
int head[MAXN], deg[MAXN];
// g[node] is the max flow from node down the tree
int g[MAXN];
// f[node] is the accumulation degree of node
int f[MAXN];

struct edge {
   int u, w, next;
} edges[MAXN << 1];

void add_edge(int u, int v, int w) {
   // edges[++idx] = (edge){v, w, head[u]};
   edges[++idx].u = v;
   edges[idx].w = w;
   edges[idx].next = head[u];
   head[u] = idx;
   deg[u]++;
}

void dfs(int u, int fa) {
   g[u] = 0;
   for (int i = head[u]; ~i; i = edges[i].next) {
      int w = edges[i].w, v = edges[i].u;

      if (v == fa) continue;

      dfs(v, u);

      if (deg[v] == 1) {
         g[u] += w;
      } else {
         g[u] += min(w, g[v]);
      }
   }
}

void dfs_dp(int u, int fa) {
   for (int i = head[u]; ~i; i = edges[i].next) {
      int w = edges[i].w, v = edges[i].u;

      if (v == fa) continue;

      if (deg[u] == 1) {
         // deg(u) is 1 => u is root and v is the only child
         f[v] = g[v] + w;
      } else {
         f[v] = g[v] + min(w, f[u] - min(w, g[v]));
      }

      dfs_dp(v, u);
   }
}

void solve() {
   // reset data
   idx = 0;
   memset(head, -1, sizeof(head));
   memset(deg, 0, sizeof(deg));
   memset(f, 0, sizeof(f));
   memset(g, 0, sizeof(g));

   scanf("%d", &n);
   for (int i = 1; i < n; i++) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      add_edge(u, v, w);
      add_edge(v, u, w);
   }

   dfs(1, 0);

   // A(root)
   f[1] = g[1];

   dfs_dp(1, 0);

   // sum up
   int ans = 0;
   for (int i = 1; i <= n; i++) {
      ans = max(ans, f[i]);
   }

   printf("%d\n", ans);
}

int main() {
   scanf("%d", &T);

   for (int k = 1; k <= T; k++) {
      solve();
   }

   return 0;
}
