// problem https://vjudge.net/problem/HDU-2196
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN = 1e4 + 1;

/**
 * @brief
 * f[i][0] is the max length of path from i to a leaf node in the subtree of i (as root)
 * f[i][1] is the secondary max length of path from i to a leaf node in the subtree of i (as root)
 * f[i][2] is the max length of path from i `going up` to its parent and to a leaf node
 *
 */
int f[MAXN][3], head[MAXN];
int n, idx = 0;

struct edge {
   int u, w, next;
} edges[MAXN << 1];

void add_edge(int u, int v, int w) {
   // edges[++idx] = (edge){v, w, head[u]};
   edges[++idx].u = v;
   edges[idx].w = w;
   edges[idx].next = head[u];
   head[u] = idx;
}

/**
 * @brief
 * find f[i][0]
 *
 * @param node
 * @param parent
 */
void dfs(int node, int parent) {
   for (int ci = head[node]; ci; ci = edges[ci].next) {
      int cn = edges[ci].u, cw = edges[ci].w;
      if (cn != parent) {
         dfs(cn, node);
         if (f[cn][0] + cw > f[node][0]) {
            // max
            f[node][1] = f[node][0];
            f[node][0] = f[cn][0] + cw;
         } else {
            // secondary max
            f[node][1] = max(f[node][1], f[cn][0] + cw);
         }
      }
   }
}

/**
 * @brief
 * find f[i][2]
 * @param node
 * @param parent
 */
void dfs_dp(int node, int parent) {
   for (int ci = head[node]; ci; ci = edges[ci].next) {
      int cn = edges[ci].u, cw = edges[ci].w;
      if (cn != parent) {
         if (f[node][0] == f[cn][0] + cw) {
            // max path length is in the subtree of cn (as root)
            // need to use secondary max
            f[cn][2] = max(f[node][2] + cw, f[node][1] + cw);
         } else {
            // use max
            f[cn][2] = max(f[node][2] + cw, f[node][0] + cw);
         }
         dfs_dp(cn, node);
      }
   }
}

int main() {
   // EOF is -1
   while (~scanf("%d", &n)) {
      idx = 0;
      memset(f, 0, sizeof(f));
      memset(head, 0, sizeof(head));

      for (int i = 2; i <= n; i++) {
         int j, w;
         cin >> j >> w;
         add_edge(i, j, w);
         add_edge(j, i, w);
      }

      dfs(1, -1);

      dfs_dp(1, -1);

      for (int i = 1; i <= n; i++) {
         cout << max(f[i][0], f[i][2]) << "\n";
      }
   }

   return 0;
}