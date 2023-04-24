// problem https://www.luogu.com.cn/problem/P1064
#include <iostream>
using namespace std;

int f[40001];
int iw[100001], iv[100001];

int main() {
   int idx = 0;

   int len, W;
   cin >> len >> W;

   // binary grouping
   for (int i = 1; i <= len; i++) {
      int v, w, m;
      cin >> v >> w >> m;

      // enough remaining items to be placed in a binary group
      for (int gs = 1; gs < m; m -= gs, gs <<= 1) {
         idx++;
         iw[idx] = gs * w;
         iv[idx] = gs * v;
      }
      // last group
      iw[++idx] = m * w;
      iv[idx] = m * v;
   }

   // 0-1 knapsack
   for (int i = 1; i <= idx; i++) {
      for (int j = W; j >= iw[i]; j--) {
         f[j] = max(f[j], f[j - iw[i]] + iv[i]);
      }
   }

   cout << f[W] << endl;

   return 0;
}