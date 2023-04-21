// problem https://www.luogu.com.cn/problem/P1122
#include <climits>
#include <iostream>
using namespace std;

const int MAXN = 16001;
int f[MAXN], head[MAXN];
int val[MAXN];

struct edge {
   int u, next;
} edges[MAXN << 1];

int n, idx = 0;

void add_edge(int u, int v) {
   edges[++idx] = (edge){v, head[u]};
   head[u] = idx;
}

void dfs(int node, int parent) {
   f[node] = val[node];
   for (int ci = head[node]; ci; ci = edges[ci].next) {
      int cn = edges[ci].u;
      if (cn != parent) {
         dfs(cn, node);
         f[node] += max(0, f[cn]);
      }
   }
}

int main() {
   cin >> n;

   for (int i = 1; i <= n; i++) {
      cin >> val[i];
   }

   for (int i = 1; i < n; i++) {
      int a, b;
      cin >> a >> b;
      add_edge(a, b);
      add_edge(b, a);
   }

   dfs(1, -1);

   int ans = INT_MIN;
   for (int i = 1; i <= n; i++) {
      ans = max(ans, f[i]);
   }

   cout << ans << endl;

   return 0;
}