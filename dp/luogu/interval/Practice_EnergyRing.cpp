// problem https://vijos.org/p/1312
#include <iostream>
using namespace std;

int f[201][201];
int s[201];

int main() {
   int L;
   cin >> L;

   for (int i = 1; i <= L; i++) {
      cin >> s[i];
      s[i + L] = s[i];
   }

   for (int len = 2; len <= L; len++) {
      for (int i = 1; i <= 2 * L - 1; i++) {
         int j = i + len - 1;
         for (int k = i; k < j && k <= 2 * L - 1; k++) {
            f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + s[i] * s[k + 1] * s[j + 1]);
         }
      }
   }

   int mx = 0;
   for (int i = 1; i <= L; i++) {
      mx = max(mx, f[i][i + L - 1]);
   }

   cout << mx << endl;

   return 0;
}