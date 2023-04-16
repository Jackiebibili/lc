#include <iostream>

using namespace std;

int wa[3402], da[3402];
int f[12881];

int main() {
   int n = 0, m = 0;
   cin >> n >> m;

   for (int i = 0; i < n; i++) {
      cin >> wa[i] >> da[i];
   }

   for (int i = 0; i < n; i++) {
      for (int j = m; j >= wa[i]; j--) {
         f[j] = max(f[j], f[j - wa[i]] + da[i]);
      }
   }

   cout << f[m] << endl;

   return 0;
}