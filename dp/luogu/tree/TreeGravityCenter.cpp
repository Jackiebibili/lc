#include <iostream>
using namespace std;

const int MAXN = 1e5 + 1;

struct edge {
   int u, w, next;
} edges[MAXN << 1];

int n, idx = 0, head[MAXN];
int sz[MAXN];

/**
 * @brief
 * Gravity center is one/two nodes in the tree when regarding the node as the root,
 * the max subtree size is the minimum among choosing other nodes as root
 */
int ans_val = -1, ans_node = 0;

void add_edge(int u, int v, int w) {
   edges[++idx] = (edge){v, w, head[u]};
   head[u] = idx;
}

void dfs(int u, int fa) {
   sz[u] = 1;
   int maxSubtreeNodeCnt = 0;
   for (int i = head[u]; i; i = edges[i].next) {
      int v = edges[i].u, w = edges[i].w;
      if (v == fa) continue;

      dfs(v, u);
      sz[u] += sz[v];
      maxSubtreeNodeCnt = max(maxSubtreeNodeCnt, sz[v]);
   }

   // backtracking after finishing the subtree
   int nodeCntUpward = n - sz[u];
   maxSubtreeNodeCnt = max(maxSubtreeNodeCnt, nodeCntUpward);
   if (ans_val == -1 || ans_val > maxSubtreeNodeCnt) {
      ans_val = maxSubtreeNodeCnt;
      ans_node = u;
   }
}
