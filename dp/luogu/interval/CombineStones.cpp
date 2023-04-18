// problem https://www.luogu.com.cn/problem/P1880
#include <iostream>
using namespace std;

int f[201][201];  // for max
int g[201][201];  // for min
int s[201];
int pre[200];

int main() {
   int L;
   cin >> L;

   for (int i = 1; i <= L; i++) {
      int num;
      cin >> num;
      s[i] = s[L + i] = num;
   }
   for (int i = 1; i <= 2 * L - 1; i++) {
      pre[i] = pre[i - 1] + s[i];
   }

   for (int l = 2; l <= L; l++) {
      for (int i = 1; i <= 2 * L - 1; i++) {
         int j = i + l - 1;
         int mn = 1e+9, mx = 0;
         for (int k = i; k < j && k <= 2 * L - 1; k++) {
            mx = max(mx, f[i][k] + f[k + 1][j] + pre[j] - pre[i - 1]);
            mn = min(mn, g[i][k] + g[k + 1][j] + pre[j] - pre[i - 1]);
         }
         f[i][j] = mx;
         g[i][j] = mn;
      }
   }

   int mn = 1e+9, mx = 0;
   for (int i = 1; i <= L; i++) {
      mn = min(mn, g[i][i + L - 1]);
      mx = max(mx, f[i][i + L - 1]);
   }

   cout << mn << endl
        << mx << endl;

   return 0;
}