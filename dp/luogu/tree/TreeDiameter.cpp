#include <iostream>
using namespace std;

const int MAXN = 1e5 + 1;

struct edge {
   int u, w, next;
} edges[MAXN << 1];

int n, idx = 0, head[MAXN];

/**
 * @brief
 * Diameter of a tree is the max path length between any two leaf nodes.
 * f1[i] is the maximum path length going down to leaf node in the subtree of i (as root).
 * f2[i] is the second maximum path length going down to leaf node in the subtree of i (as root).
 */
int f1[MAXN], f2[MAXN];
int ans = 0;

void add_edge(int u, int v, int w) {
   edges[++idx] = (edge){v, w, head[u]};
   head[u] = idx;
}

void dfs(int u, int fa) {
   for (int i = head[u]; i; i = edges[i].next) {
      int v = edges[i].u, w = edges[i].w;
      if (v == fa) continue;

      dfs(v, u);

      if (f1[u] < f1[v] + 1) {
         f2[u] = f1[u];
         f1[u] = f1[v] + 1;
      } else {
         f2[u] = max(f2[u], f1[v] + 1);
      }

      ans = max(ans, f1[u] + f2[u]);
   }
}
