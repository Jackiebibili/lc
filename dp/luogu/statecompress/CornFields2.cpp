// problem https://www.luogu.com.cn/problem/P1879
#include <cstring>
#include <iostream>
using namespace std;

const int MAX = 13;
const int LEN = 1 << MAX;
const int MOD = 1e8;

/**
 * @brief
 * f[i][j] means the number of ways to plant until row i
 * with planting config j
 */
int f[2][LEN];
int m[MAX];
int M, N;

bool check_same_row(int row, int bin) {
   return !(m[row] & bin || bin & (bin << 1));
}

bool check_nei_row(int bin1, int bin2) {
   return !(bin1 & bin2);
}

void dfs(int num, int bin) {
   if (num >= N) {
      f[1][bin] = 1;
      return;
   }

   // do not plant
   dfs(num + 1, bin);

   if (!(m[1] >> num & 1)) {
      // plant
      dfs(num + 2, bin + (1 << num));
   }
}

int main() {
   scanf("%d%d", &M, &N);

   for (int i = 1; i <= M; i++) {
      int x;
      int val = 0;
      for (int j = 1; j <= N; j++) {
         val <<= 1;
         scanf("%d", &x);
         val += x ^ 1;
      }
      m[i] = val;
   }

   // first row
   // for (int i = 0; i < (1 << N); i++) {
   //    if (!check_same_row(1, i)) {
   //       continue;
   //    }
   //    f[1][i] = 1;
   // }
   dfs(0, 0);

   // rest of row
   for (int i = 2; i <= M; i++) {
      // clear the rolling array
      memset(f[i % 2], 0, sizeof(f[i % 2]));
      for (int j = 0; j < (1 << N); j++) {
         if (!check_same_row(i, j)) continue;
         for (int k = 0; k < (1 << N); k++) {
            if (!check_same_row(i - 1, k)) continue;
            if (!check_nei_row(j, k)) continue;
            f[i % 2][j] = (f[i % 2][j] + f[(i - 1) % 2][k]) % MOD;
         }
      }
   }

   int ans = 0;
   for (int i = 0; i < (1 << N); i++) {
      ans = (ans + f[M % 2][i]) % MOD;
   }

   printf("%d\n", ans);

   return 0;
}
