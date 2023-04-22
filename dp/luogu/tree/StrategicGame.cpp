// problem https://www.luogu.com.cn/problem/P2016
#include <iostream>
using namespace std;

const int MAXN = 1501;

struct edge {
   int u, next;
} edges[MAXN << 1];

int head[MAXN], f[MAXN][2];  // [node][0] for putting a soldier on the node, [node][1] otherwise
int n, idx = 0;

void add_edge(int u, int v) {
   edges[++idx] = (edge){v, head[u]};
   head[u] = idx;
}

void dfs(int node, int parent) {
   f[node][0] = 1;
   for (int ci = head[node]; ci; ci = edges[ci].next) {
      int cn = edges[ci].u;
      if (cn != parent) {
         dfs(cn, node);
         f[node][0] += min(f[cn][0], f[cn][1]);
         f[node][1] += f[cn][0];
      }
   }
}

int main() {
   scanf("%d", &n);

   for (int i = 1; i <= n; i++) {
      int sz, u, v;
      scanf("%d %d", &u, &sz);
      for (int j = 0; j < sz; j++) {
         scanf("%d", &v);
         add_edge(u, v);
         add_edge(v, u);
      }
   }

   // dfs
   dfs(0, -1);

   cout << min(f[0][0], f[0][1]) << endl;
   return 0;
}