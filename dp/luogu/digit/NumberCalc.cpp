// problem https://www.luogu.com.cn/problem/P2602
#include <iostream>
#define ll long long
using namespace std;

const int N = 13;
const int M = 10;
const int BASE10 = 10;

/**
 * @brief
 * f[i] is the count of occurrence of a digit (whatever digit in 0-9)
 * from 0 to an upper bound, i digit-long number (e.g. 99 for 2-digit,
 * 999 for 3-digit).
 *
 * g[i] is the count of numbers from 1*10^i to (2*10^i) - 1, which is 10^i
 *
 *
 * Example:
 * count of 1s or (2s, 3s, ..., 9s) in [0, 9] is 10 * 0 + 10^0 = 1
 * count of 1s or (2s, 3s, ..., 9s) in [0, 99] is 10 * 1 + 10^1 = 20
 * count of 1s or (2s, 3s, ..., 9s) in [0, 999] is 10 * 20 + 10^2 = 300
 *
 * [0, 99] number grid
 * 00 01 02 ... 09
 * 10 11 12 ... 19
 * 20 21 22 ... 29
 * ...          .
 * ...          .
 * 90 91 92 ... 99
 */
ll f[N], g[N];
ll ans_upper[M], ans_lower[M];
int dig[N];

void solve(ll num, ll* ans) {
   int len = -1;
   ll remain = num;

   while (num > 0) {
      dig[++len] = num % BASE10;
      num /= BASE10;
   }

   for (int i = len; i >= 0; i--) {
      // previous i-1 digit combs
      for (int j = 0; j < BASE10; j++) {
         ans[j] += f[i] * dig[i];
      }

      // the ith (highest) digit combs
      for (int j = 0; j < dig[i]; j++) {
         ans[j] += g[i];
      }

      // the ith digit combining with remaining i-1 digits numbers to the right when the current ith digit is dig[i]
      remain -= g[i] * dig[i];
      ans[dig[i]] += remain + 1;  // starting from the least digit=0 to num

      // remove leading zero for combs when the ith digit is 0
      ans[0] -= g[i];
   }
}

int main() {
   ll low, high;

   scanf("%lld%lld", &low, &high);

   g[0] = 1;
   for (int i = 1; i < N; i++) {
      f[i] = BASE10 * f[i - 1] + g[i - 1];
      g[i] = BASE10 * g[i - 1];
   }

   solve(high, ans_upper);
   solve(low - 1, ans_lower);

   for (int i = 0; i < BASE10; i++) {
      printf("%lld ", (ans_upper[i] - ans_lower[i]));
   }

   return 0;
}