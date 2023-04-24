#include <iostream>
using namespace std;

int f[201][201];

int main() {
   int n, M, T;
   cin >> n >> M >> T;

   for (int i = 0; i < n; i++) {
      int m, t;
      cin >> m >> t;

      for (int j = M; j >= m; j--) {
         for (int k = T; k >= t; k--) {
            f[j][k] = max(f[j][k], f[j - m][k - t] + 1);
         }
      }
   }

   cout << f[M][T] << endl;

   return 0;
}