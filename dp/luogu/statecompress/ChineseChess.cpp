// problem https://www.luogu.com.cn/problem/P2051
#include <iostream>
#define ll long long
using namespace std;

const int MAX = 101;
const int MOD = 9999973;

/**
 * @brief
 * f[i][j][k] means the number of ways to place cannons until row i
 * when there are j cols have one cannon and k cols have two cannons
 */
ll f[MAX][MAX][MAX];
int n, m;

int comb_select2(int n) {
   return ((n * (n - 1)) / 2) % MOD;
}

int main() {
   scanf("%d%d", &n, &m);

   // place no cannons initially
   f[0][0][0] = 1;

   for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
         for (int k = 0; k <= m - j; k++) {
            // place no cannons
            f[i][j][k] = (f[i][j][k] + f[i - 1][j][k]) % MOD;

            // place one cannon
            // one on cols with no cannons
            if (j >= 1) f[i][j][k] = (f[i][j][k] + f[i - 1][j - 1][k] * (m - j + 1 - k)) % MOD;
            // one on cols with one cannon
            if (k >= 1) f[i][j][k] = (f[i][j][k] + f[i - 1][j + 1][k - 1] * (j + 1)) % MOD;

            // place two cannons
            // one on cols with no cannons; one on cols with one cannon
            if (k >= 1) f[i][j][k] = (f[i][j][k] + f[i - 1][j][k - 1] * (m - j - k + 1) * j) % MOD;
            // two on cols with one cannon
            if (k >= 2) f[i][j][k] = (f[i][j][k] + f[i - 1][j + 2][k - 2] * comb_select2(j + 2)) % MOD;
            // two on cols with no cannons
            if (j >= 2) f[i][j][k] = (f[i][j][k] + f[i - 1][j - 2][k] * comb_select2(m - k - j + 2)) % MOD;
         }
      }
   }

   ll ans = 0;
   for (int i = 0; i <= m; i++) {
      for (int j = 0; j <= m - i; j++) {
         ans = (ans + f[n][i][j]) % MOD;
      }
   }

   printf("%d\n", (int)ans);

   return 0;
}