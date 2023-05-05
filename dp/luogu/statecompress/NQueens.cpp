#include <iostream>
using namespace std;

class Solution {
  public:
   /**
    * @brief
    *
    * @param row: current row number
    * @param y: binary representation of where cannot (1) place queen for vertical attack
    * @param rtl: binary representation of where cannot (1) place queen for right to left diagonal (/)
    * @param ltr: binary representation of where cannot (1) place queen for left to right diagonal (\)
    * @param n: total number of rows
    * @return int: the number of ways to place n queens in nxn grid
    */
   int dfs(int row, int y, int rtl, int ltr, int n) {
      int ans = 0;
      int queenplmtbin = ~(y | rtl | ltr) & (1 << n) - 1;

      while (queenplmtbin) {
         // find rightmost 1 bit
         int rowqueenplmtbin = queenplmtbin & -queenplmtbin;
         if (row == n) {
            ans++;
         } else {
            ans += dfs(row + 1, y | rowqueenplmtbin, (rtl | rowqueenplmtbin) << 1, (ltr | rowqueenplmtbin) >> 1, n);
         }
         // change the rightmost 1 bit to 0 bit
         queenplmtbin ^= rowqueenplmtbin;
      }

      return ans;
   }
   int totalNQueens(int n) {
      return dfs(1, 0, 0, 0, n);
   }
};

int main() {
   Solution sol;
   int n;
   scanf("%d", &n);
   cout << sol.totalNQueens(n) << endl;
   return 0;
}
