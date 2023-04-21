// problem https://www.luogu.com.cn/problem/P1352
#include <iostream>
using namespace std;

int f[6001][2];

// children[i] is the last child on the level of parent i
// last child (null) on the level is 0
int children[6001], isnonroot[6001];
int n, idx = 0;

struct edge {
   int u, next;
} edges[6001];

void dfs(int node) {
   // for each node, dfs its children
   for (int c = children[node]; c; c = edges[c].next) {
      int cnode = edges[c].u;
      dfs(cnode);
      // parent not attending
      f[node][0] += max(f[cnode][1], f[cnode][0]);
      // parent attending
      f[node][1] += f[cnode][0];
   }
}

int main() {
   // total number of nodes
   cin >> n;
   // read in the happiness value
   for (int i = 1; i <= n; i++) {
      cin >> f[i][1];
   }

   // generate the tree
   for (int i = 1; i < n; i++) {
      // v is the child of u
      int v, u;
      cin >> v >> u;

      isnonroot[v] = 1;
      edges[++idx].u = v;
      edges[idx].next = children[u];
      children[u] = idx;
   }

   for (int i = 1; i <= n; i++) {
      if (!isnonroot[i]) {
         // is root
         dfs(i);
         cout << max(f[i][0], f[i][1]) << endl;
         break;
      }
   }

   return 0;
}