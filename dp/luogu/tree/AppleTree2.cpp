// problem https://www.luogu.com.cn/problem/P3780
#include <iostream>
#include <vector>
using namespace std;

const int N = 4 * 1e4 + 10;
const int Q_LEN = 5 * 1e5 + 10;
const int MAXN = 6 * 1e7 + 10;

int dfn1[N];  // dfn[i] is the ith node's number in the post-order dfs
int dfn2[N];
int dfnloc1[N];  // dfnloc[i] is the order number of node i in the post-order dfs
int dfnloc2[N];
int dfnidx1 = 0, dfnidx2 = 0;

int pathv[N];  // pathv[i] is the total path value for the path from root to i (leaf)
int sz[N];     // sz[i] is the size of the subtree including the root at node i
int f1[MAXN];
int f2[MAXN];

int q1[Q_LEN];
int q2[Q_LEN];

int Q, n, m, idx;
vector<int> adj[N];
int pa[N];
int cnt[N];
int va[N];
int isnotleaf[N];

void dfs_left(int node) {
   sz[node] = 1;
   for (int i = 0; i < adj[node].size(); i++) {
      int next = adj[node][i];
      pathv[next] = pathv[node] + va[next];
      dfs_left(next);
      sz[node] += sz[next];
   }
   dfn1[++dfnidx1] = node;
   dfnloc1[node] = dfnidx1;
}

void dfs_right(int node) {
   for (int i = adj[node].size() - 1; i >= 0; i--) {
      dfs_right(adj[node][i]);
   }
   dfn2[++dfnidx2] = node;
   dfnloc2[node] = dfnidx2;
}

// dp in dfs post-order, using previous cousin and right most child
void dp(int* dfn, int* f) {
   // post order
   for (int i = 1; i <= idx; i++) {
      int node = dfn[i];
      int head = 1, tail = 1;

      int a = min(cnt[node], m);

      // must pick at least `one` item from the current node in order to collect from child nodes
      // q[head] + j * va[node] = j * va[node] so that q[head] = 0 for j = 1
      // monotonic queue stores the max val of current node for child knapsack size = 0 to j-1
      q1[tail] = q2[tail] = 0;

      for (int j = 1; j <= m; j++) {
         while (head <= tail && q1[head] < j - a) {
            head++;
         }
         int cur_val = f[(i - 1) * (m + 1) + j] - j * va[node];
         f[i * (m + 1) + j] = max(q2[head] + j * va[node], f[(i - sz[node]) * (m + 1) + j]);

         while (head <= tail && cur_val >= q2[tail]) {
            tail--;
         }
         tail++;
         q1[tail] = j;
         q2[tail] = cur_val;
      }
   }
}

int main() {
   cin >> Q;

   for (int i = 0; i < Q; i++) {
      cin >> n >> m;
      for (int j = 1; j <= n; j++) {
         cin >> pa[j] >> cnt[j] >> va[j];
         isnotleaf[pa[j]] = 1;
         // add edges to adj
         adj[pa[j]].push_back(j);
      }
      idx = n;
      // break a node into two nodes (cnt=1 and cnt=cnt-1)
      for (int j = 1; j <= n; j++) {
         if (cnt[j] > 1) {
            adj[j].push_back(++idx);
            cnt[idx] = cnt[j] - 1;
            cnt[j] = 1;
            va[idx] = va[j];
         }
      }

      // root path is itself value
      pathv[1] = va[1];

      // left of the path
      dfs_left(1);
      // right of path
      dfs_right(1);

      dp(dfn1, f1);
      dp(dfn2, f2);

      int ans = 0;
      for (int j = 1; j <= n; j++) {
         if (isnotleaf[j]) continue;

         for (int k = 0; k <= m; k++) {
            ans = max(ans, f1[(dfnloc1[j] - 1) * (m + 1) + k] + pathv[j] + f2[(dfnloc2[j] - sz[j]) * (m + 1) + (m - k)]);
         }
      }

      cout << ans << "\n";

      for (int j = 0; j <= idx; j++) {
         vector<int> emp;
         swap(emp, adj[j]);
         isnotleaf[j] = pathv[j] = sz[j] = 0;
      }

      for (int j = 0; j <= (idx + 1) * (m + 1); j++) {
         f1[j] = f2[j] = 0;
      }

      dfnidx1 = dfnidx2 = idx = 0;
   }
   return 0;
}