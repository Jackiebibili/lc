// problem https://www.luogu.com.cn/problem/P2014
#include <iostream>
using namespace std;

int f[301][302];
int head[301];
int n, m, idx = 0;

struct edge {
   int u, pre;
} edges[301];

void dfs(int node) {
   // dfs to leaf
   for (int c = head[node]; c; c = edges[c].pre) {
      dfs(edges[c].u);
   }
   // for each child node (subtree or group in group dp)
   for (int c = head[node]; c; c = edges[c].pre) {
      int cnode = edges[c].u;
      for (int j = m; j > 0; j--) {
         // pick one from each subtree: for each items in the group
         for (int k = 1; k < j; k++) {
            f[node][j] = max(f[node][j], f[node][j - k] + f[cnode][k]);
         }
      }
   }
}

int main() {
   cin >> n >> m;

   m++;

   for (int i = 1; i <= n; i++) {
      int k, s;
      cin >> k >> s;
      f[i][1] = s;
      edges[++idx].u = i;
      edges[idx].pre = head[k];
      head[k] = idx;
   }

   dfs(0);

   cout << f[0][m] << endl;

   return 0;
}