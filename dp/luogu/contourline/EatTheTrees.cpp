// problem https://www.luogu.com.cn/problem/P5074
#include <algorithm>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;

const int MAXN = 12;
const int MAX = 1 << (MAXN + 1);

/**
 * @brief
 * f[.][k] means the number of ways to fill the grid entirely with Hamiltonian paths
 * when k is the current contour line config in binary when the low bit is the leftmost
 * column and f[i] rolls for each column j.
 *
 * State transitions:
 * When we iterate row by row, column (j) by column, k >> j bit is whether the current
 * cell's left cell has a horizon line and k >> (j+1) bit is whether the current cell's
 * top cell has a vertical line.
 * After the transition, the k >> j bit is whether the current cell has a vertical line
 * and k >> (j+1) bit is whether the current cell has a horizontal line, which can be used
 * as the left plug by the next column on the same row.
 */
ll f[2][MAX], *f1, *f2;
int len, n, m, tree;

ll solve() {
   f1 = f[0];
   f2 = f[1];
   memset(f1, 0, sizeof(ll) * (1 << m + 1));
   f1[0] = 1;

   for (int i = 1; i <= n; i++) {
      for (int j = 0; j < m; j++) {
         // rolling array
         swap(f1, f2);
         memset(f1, 0, sizeof(ll) * (1 << m + 1));

         scanf("%d", &tree);
         for (int k = 0; k < (1 << m + 1); k++) {
            // if no value in dp, then skip
            if (!f2[k]) continue;
            bool left = k >> j & 1, up = k >> j + 1 & 1;
            if (tree) {
               // has tree
               /**
                * left     up    next state     next bin
                *  1       1                       00
                *  0       0        Γ              11
                *  1       0        -              01
                *  0       1        |              10
                */
               f1[k ^ 3 << j] += f2[k];
               /**
                * left     up    next state     next bin
                *  1       0        |              10
                *  0       1        -              01
                */
               if (left != up) f1[k] += f2[k];
            } else {
               // no tree
               if (!left && !up) f1[k] += f2[k];
            }
         }
      }
      /**
       * left roll for initializing the left plug bit to 0
       * because first column in a row cannot have left plug and the
       * next state in binary representation of k starts with up plug bit
       * and the high bit (when = 1) of k is illegal because we cannot
       * plug another left head to the right of the boundary of the grid.
       */
      // rolling array
      swap(f1, f2);
      memset(f1, 0, sizeof(ll) * (1 << m + 1));
      for (int k = 0; k < (1 << m); k++) {
         f1[k << 1] = f2[k];
      }
   }

   return f1[0];
}

int main() {
   scanf("%d", &len);

   while (len-- > 0) {
      scanf("%d%d", &n, &m);
      ll ans = solve();
      printf("%lld\n", ans);
   }

   return 0;
}