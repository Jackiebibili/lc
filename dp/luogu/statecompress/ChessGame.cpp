// problem https://www.luogu.com.cn/problem/P4363
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 10;
const int MAX = 1 << (MAXN << 1);
const int INF = 0x7fffffff;

int A[MAXN + 1][MAXN + 1], B[MAXN + 1][MAXN + 1];

/**
 * @brief
 * f[i] means the final score that Faye exceeds Niu when both players
 * play their best strategies `starting` from the board configuration
 * represented by the `contour line` from the bottom left corner to
 * the top right corner of the chess board when scanning the i in
 * binary form from its lower bits to higher bits, given 1 for going
 * up and 0 for going right.
 */
int f[MAX];
int n, m;

// min-max
int dfs(int cline, int turn) {
   if (~f[cline]) {
      return f[cline];
   }
   int row = n + 1, col = 1;
   int res = turn ? -INF : INF;
   /**
    * find corners:
    * corner is the shape below
    *  ______
    * |corner
    * |
    * |
    * going up and then right
    * bin representation: 01
    */

   for (int i = 0; i < m + n - 1; i++) {
      if ((cline >> i) & 1) {
         row--;
      } else {
         col++;
      }

      // 01 & 11 = 01
      if (((cline >> i) & 3) != 1) {
         continue;
      }

      if (turn) {
         res = max(res, dfs(cline ^ (3 << i), turn ^ 1) + A[row][col]);
      } else {
         res = min(res, dfs(cline ^ (3 << i), turn ^ 1) - B[row][col]);
      }
   }

   return f[cline] = res;
}

int main() {
   scanf("%d%d", &n, &m);
   for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
         scanf("%d", &A[i][j]);
      }
   }
   for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
         scanf("%d", &B[i][j]);
      }
   }
   memset(f, -1, sizeof(f));

   // start at the last game config: 0 score
   f[((1 << n) - 1) << m] = 0;
   int ans = dfs((1 << n) - 1, 1);

   printf("%d\n", ans);
   return 0;
}