// problem https://www.luogu.com.cn/problem/P2704
#include <iostream>
using namespace std;

const int MAXN = 101, MAXM = 10;
const int MAX = 1 << MAXM;

/**
 * @brief
 * f[i][j][k] is the max number of artillery units one can place until row i
 * with row i's jth artillery unit placement and row (i-1)'s kth artillery unit placement.
 *
 */
int f[3][MAX][MAX];

int N, M;
int m[MAXN];
char ro[MAXM + 1];
int num[MAX];

bool same_row_check(int row, int bin) {
   return !(m[row] & bin || bin & (bin << 1) || bin & (bin << 2));
}

bool nei_row_check(int bin1, int bin2) {
   return !(bin1 & bin2);
}

int main() {
   scanf("%d%d", &N, &M);

   for (int i = 1; i <= N; i++) {
      scanf("%s", ro);
      for (int j = 0; j < M; j++) {
         m[i] <<= 1;
         m[i] += ro[j] == 'H' ? 1 : 0;
      }
   }

   // init bin mapping
   for (int i = 0; i < (1 << M); i++) {
      int val = i;
      int cnt = 0;
      for (int val = i; val; val >>= 1) {
         if (val & 1) cnt++;
      }
      num[i] = cnt;
   }

   // init first row
   for (int i = 0; i < (1 << M); i++) {
      if (!same_row_check(1, i)) {
         continue;
      }
      f[1][i][0] = num[i];
   }

   // second row
   for (int i = 0; i < (1 << M); i++) {
      for (int j = 0; j < (1 << M); j++) {
         if (!same_row_check(1, i)) {
            continue;
         }
         if (!same_row_check(2, j)) {
            continue;
         }
         if (!nei_row_check(i, j)) {
            continue;
         }
         f[2][j][i] = num[i] + num[j];
      }
   }

   // rest of rows
   for (int r = 3; r <= N; r++) {
      for (int i = 0; i < (1 << M); i++) {
         if (!same_row_check(r, i)) {
            continue;
         }
         for (int j = 0; j < (1 << M); j++) {
            if (!same_row_check(r - 1, j)) {
               continue;
            }
            if (!nei_row_check(i, j)) {
               continue;
            }
            // previous i-2 row placement
            for (int k = 0; k < (1 << M); k++) {
               if (!same_row_check(r - 2, k)) {
                  continue;
               }
               if (!nei_row_check(i, k)) {
                  continue;
               }
               if (!nei_row_check(j, k)) {
                  continue;
               }
               f[r % 3][i][j] = max(f[r % 3][i][j], f[(r - 1) % 3][j][k] + num[i]);
            }
         }
      }
   }

   // find max
   int ans = 0;
   for (int i = 0; i < (1 << M); i++) {
      for (int j = 0; j < (1 << M); j++) {
         ans = max(ans, f[N % 3][i][j]);
      }
   }

   printf("%d\n", ans);

   return 0;
}