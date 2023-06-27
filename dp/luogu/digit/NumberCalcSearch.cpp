// problem https://www.luogu.com.cn/problem/P2602
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;

const int N = 14;
const int BASE10 = 10;

/**
 * @brief
 * f[i] eventually contains result for occurrence of digits in [1, 9]
 */
ll tens[N], f[N], re[N];
int digs[BASE10];

ll dfs(int len, int dig, bool isLeading0, bool isCeiling) {
   // a number of zero digits have no count
   if (len == 0) {
      return 0;
   }

   // memorize only full digit numbers (e.g. 99, 999)
   if (!isLeading0 && !isCeiling && ~f[len]) {
      return f[len];
   }

   ll cnt = 0;
   int upper = isCeiling ? digs[len] : BASE10 - 1;

   for (int i = 0; i <= upper; i++) {
      if (isLeading0 && i == 0) {
         // calculate separately for number without leading 0s
         cnt += dfs(len - 1, dig, 1, isCeiling && i == upper);
      } else if (i == dig && isCeiling && i == upper) {
         // reach upper limit, add only the remainder + 1
         cnt += re[len - 1] + 1 + dfs(len - 1, dig, 0, 1);
      } else if (i == dig) {
         // one row for numbers of `len` digits, leading digit is i
         cnt += tens[len - 1] + dfs(len - 1, dig, 0, 0);
      } else {
         // normal flow
         cnt += dfs(len - 1, dig, 0, isCeiling && i == upper);
      }
   }

   // memorize only full digit numbers (e.g. 99, 999)
   if (!isLeading0 && !isCeiling) {
      f[len] = cnt;
   }

   return cnt;
}

ll solve(int dig, ll num) {
   int len = 0;
   memset(f, -1, sizeof(f));

   while (num > 0) {
      digs[++len] = num % BASE10;
      num /= BASE10;

      re[len] = re[len - 1] + digs[len] * tens[len - 1];  // e.g. num=999: re = [9, 99, 999]
   }

   return dfs(len, dig, 1, 1);
}

int main() {
   ll low, high;
   scanf("%lld%lld", &low, &high);

   tens[0] = 1;
   for (int i = 1; i < N; i++) {
      tens[i] = tens[i - 1] * BASE10;
   }

   for (int i = 0; i < BASE10; i++) {
      ll ans = solve(i, high) - solve(i, low - 1);
      printf("%lld ", ans);
   }

   return 0;
}