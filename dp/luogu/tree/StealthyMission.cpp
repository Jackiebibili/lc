// problem https://www.luogu.com.cn/problem/P4516
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 1e5 + 1;
const int MAXK = 101;
const int mod = 1e9 + 7;

/**
 * @brief
 * f[node][i][0/1][0/1] is the number of ways to apply i devices on the subtree
 * of node (as root) while node itself has 0/1 device and the node is tapped (1)
 * or not (0)
 */
int f[MAXN][MAXK][2][2];
int tmp[MAXK][2][2];
int head[MAXN], sz[MAXN];
int n, k, idx = 0;

struct edge {
   int u, next;
} edges[MAXN << 1];

void add_edge(int u, int v) {
   edges[++idx] = (edge){v, head[u]};
   head[u] = idx;
}

inline int solve(int a, long long b) {
   if (b >= mod) b %= mod;
   for (a += b; a >= mod; a -= mod)
      ;
   return a;
}

void dfs(int node, int parent) {
   int si = 1;  // how many child nodes so far
   // initial condition:
   // can place 0 or 1 on the current node
   // number of ways is 1
   f[node][0][0][0] = 1;
   f[node][1][1][0] = 1;

   for (int ci = head[node]; ci; ci = edges[ci].next) {
      int cn = edges[ci].u;

      if (cn == parent) continue;

      dfs(cn, node);

      // backtracking
      // copying states: make sure current state is not updated and
      // then use on the next state transition
      for (int i = 0; i <= min(si, k); i++) {
         memcpy(tmp[i], f[node][i], sizeof(f[node][i]));
         memset(f[node][i], 0, sizeof(f[node][i]));
         // tmp[i][0][0] = f[node][i][0][0];
         // f[node][i][0][0] = 0;
         // tmp[i][0][1] = f[node][i][0][1];
         // f[node][i][0][1] = 0;
         // tmp[i][1][0] = f[node][i][1][0];
         // f[node][i][1][0] = 0;
         // tmp[i][1][1] = f[node][i][1][1];
         // f[node][i][1][1] = 0;
      }

      for (int i = 0; i <= min(si, k); i++) {
         for (int j = 0; j <= min(sz[cn], k - i); j++) {
            // transitions
            f[node][i + j][0][0] = solve(f[node][i + j][0][0], 1ll * tmp[i][0][0] * f[cn][j][0][1]);

            f[node][i + j][0][1] = solve(f[node][i + j][0][1], 1ll * tmp[i][0][1] * (f[cn][j][0][1] + f[cn][j][1][1]));
            f[node][i + j][0][1] = solve(f[node][i + j][0][1], 1ll * tmp[i][0][0] * f[cn][j][1][1]);

            f[node][i + j][1][0] = solve(f[node][i + j][1][0], 1ll * tmp[i][1][0] * (f[cn][j][0][0] + f[cn][j][0][1]));

            f[node][i + j][1][1] = solve(f[node][i + j][1][1], 1ll * tmp[i][1][0] * (f[cn][j][1][0] + f[cn][j][1][1]));
            f[node][i + j][1][1] = solve(f[node][i + j][1][1], 1ll * tmp[i][1][1] * (1ll * f[cn][j][0][0] + 1ll * f[cn][j][0][1] + 1ll * f[cn][j][1][0] + 1ll * f[cn][j][1][1]));
         }
      }

      si += sz[cn];
   }

   sz[node] = si;
}

int main() {
   cin >> n >> k;

   for (int i = 1; i < n; i++) {
      int u, v;
      cin >> u >> v;

      add_edge(u, v);
      add_edge(v, u);
   }

   dfs(1, 0);

   cout << (f[1][k][0][1] + f[1][k][1][1]) % mod << endl;

   return 0;
}