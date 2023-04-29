// problem https:  // www.luogu.com.cn/problem/P2986
#include <iostream>
using namespace std;

const int MAXN = 1e5 + 1;

struct edge {
   int u, w, next;
} edges[MAXN << 1];

int n, idx = 0, cnt[MAXN], head[MAXN];

// g[i] is the total distance cost going down the tree for all nodes in the subtree of node i (as root) to i
// f[i] is the total distance from all other nodes to node i
long long totalnodes, g[MAXN], f[MAXN], sz[MAXN];

void add_edge(int u, int v, int w) {
   edges[++idx] = (edge){v, w, head[u]};
   head[u] = idx;
}

void dfs(int u, int fa) {
   sz[u] = cnt[u];
   for (int i = head[u]; i; i = edges[i].next) {
      int v = edges[i].u, w = edges[i].w;
      if (v == fa) continue;

      dfs(v, u);
      sz[u] += sz[v];

      g[u] += g[v] + sz[v] * w;
   }
}

void dp(int u, int fa) {
   for (int i = head[u]; i; i = edges[i].next) {
      int v = edges[i].u, w = edges[i].w;
      if (v == fa) continue;

      f[v] = f[u] + (totalnodes - sz[v]) * w - (w * sz[v]);

      dp(v, u);
   }
}

int main() {
   scanf("%d", &n);

   for (int i = 1; i <= n; i++) {
      scanf("%d", &cnt[i]);
   }

   for (int i = 1; i < n; i++) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      add_edge(u, v, w);
      add_edge(v, u, w);
   }

   dfs(1, 0);

   // root
   f[1] = g[1];
   totalnodes = sz[1];

   dp(1, 0);

   // find min node
   long long ans = -1;
   for (int i = 1; i <= n; i++) {
      if (ans == -1) {
         ans = f[i];
      } else {
         ans = min(ans, f[i]);
      }
   }

   printf("%lld\n", ans);

   return 0;
}