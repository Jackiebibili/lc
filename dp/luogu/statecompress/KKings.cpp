// problem https://www.luogu.com.cn/problem/P1896
#include <iostream>
#define ll long long
using namespace std;

const int MAXN = 10;
const int MAXM = (1 << MAXN) + 1;
/**
 * @brief
 * f[i][j][l] means the number of ways we can place l kings on row i
 * with kings' jth placement on that row.
 */
ll f[MAXN][MAXM][MAXN * MAXN + 1];
ll kcnt[MAXM], state[MAXM];
int n, k, idx = 0;

void dfs(int curidx, int bin, int kingscnt) {
   if (curidx >= n) {
      state[++idx] = bin;
      kcnt[idx] = kingscnt;
      return;
   }

   // do not place a king
   dfs(curidx + 1, bin, kingscnt);

   // place a king
   dfs(curidx + 2, bin + (1 << curidx), kingscnt + 1);
}

bool isOk(int placeidxA, int placeidxB) {
   // orthogonal direction
   if (state[placeidxA] & state[placeidxB]) return false;
   // diagonal directions
   if (state[placeidxA] & (state[placeidxB] << 1)) return false;
   if (state[placeidxB] & (state[placeidxA] << 1)) return false;
   return true;
}

void dp() {
   // first row
   dfs(0, 0, 0);
   for (int j = 1; j <= idx; j++) {
      // count as one way for the first row
      f[1][j][kcnt[j]] = 1;
   }

   // rest of rows
   for (int i = 2; i <= n; i++) {
      for (int j = 1; j <= idx; j++) {
         // for each xth placement
         for (int x = 1; x <= idx; x++) {
            if (!isOk(j, x)) continue;
            for (int l = kcnt[j]; l <= k; l++) {
               f[i][j][l] += f[i - 1][x][l - kcnt[j]];
            }
         }
      }
   }
}

int main() {
   scanf("%d%d", &n, &k);

   dp();

   ll ans = 0;

   for (int j = 1; j <= idx; j++) {
      ans += f[n][j][k];
   }

   printf("%lld\n", ans);

   return 0;
}