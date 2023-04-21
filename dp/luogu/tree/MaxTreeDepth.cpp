#include <iostream>
using namespace std;

const int MAXN = 1e6 + 1;
const int MAX = MAXN << 1;
long long f[MAXN];
long long cnt[MAXN], dep[MAXN], head[MAXN];
long long n;
int idx = 0;

struct edge {
   int u, next;
} edges[MAX];

void addEdge(int u, int v) {
   edges[++idx].u = v;
   edges[idx].next = head[u];
   head[u] = idx;
}

void dfs(int node, int parent) {
   cnt[node] = 1;  // root itself in the subtree
   dep[node] = dep[parent] + 1;
   for (int ci = head[node]; ci; ci = edges[ci].next) {
      int cn = edges[ci].u;
      if (cn != parent) {
         dfs(cn, node);
         cnt[node] += cnt[cn];
      }
   }
}

void dfsSwapRoot(int node, int parent) {
   for (int ci = head[node]; ci; ci = edges[ci].next) {
      int cn = edges[ci].u;
      if (cn != parent) {
         f[cn] = f[node] + n - 2 * cnt[cn];
         dfsSwapRoot(cn, node);
      }
   }
}

int main() {
   cin >> n;

   for (int i = 1; i < n; i++) {
      int u, v;
      cin >> u >> v;
      addEdge(u, v);
      addEdge(v, u);
   }

   dfs(1, -1);
   for (int i = 1; i <= n; i++) {
      f[1] += dep[i];
   }

   dfsSwapRoot(1, -1);

   long long max = -1;
   int node = -1;
   for (int i = 1; i <= n; i++) {
      if (max < f[i]) {
         max = f[i];
         node = i;
      }
   }

   cout << node << endl;

   return 0;
}