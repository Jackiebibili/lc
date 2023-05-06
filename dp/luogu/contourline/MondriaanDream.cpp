// problem https://vjudge.net/problem/HDU-1400
#include <algorithm>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;

const int MAXN = 11;
const int MAX = 1 << MAXN;

/**
 * @brief
 * Where is the contour line?
 * Mirrored left and right parts: the low bit represent the first column's config
 *
 * For row i and while we are visiting the column j, the contour line goes along
 * the row i and continue until column j, then going up to row i-1 and going
 * horizontally to the last column.
 * ------------------------
 * | f[] has been decided |
 * |         _____________|
 * |________|<-           |
 * |  f[] has not         |
 * |        been decided  |
 * ------------------------
 * state transitions: insert the next head into where the arrow is pointed
 */

/**
 * @brief
 * f[i][j] means the number of ways to fill the grid entirely using 1x2 or 2x1 blocks
 * when the current ith row's binary representation is j (1 bit for occupied, 0 bit otherwise).
 * 
 */
ll f[2][MAX];
ll *f1, *f2;
int n, m;

int main() {
   while (~scanf("%d%d", &n, &m) && n) {
      f1 = f[0];
      f2 = f[1];
      memset(f1, 0, sizeof(ll) * (1 << m));
      // init state
      // filling the previous all (invisible) rows entirely before the first row is `one` way
      // and current row placement is none (all 0 bits)
      f1[0] = 1;
      for (int i = 1; i <= n; i++) {
         for (int j = 0; j < m; j++) {
            swap(f1, f2);
            // f2 is current values
            memset(f1, 0, sizeof(ll) * (1 << m));
            // f1 is `next` values
            for (int k = 0; k < (1 << m); k++) {
               if (f2[k]) {
                  // can place a 1x2 on the same row
                  if (j < m - 1 && !(k >> j & 3)) {
                     f1[k ^ 1 << j + 1] += f2[k];
                  }
                  // can place a 2x1 or place nothing
                  f1[k ^ 1 << j] += f2[k];
               }
            }
         }
      }
      printf("%lld\n", f1[0]);
   }
   return 0;
}