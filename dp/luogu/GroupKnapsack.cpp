#include <iostream>
using namespace std;

int gs[101], g[101][1001];  // gs[i] for group size for the ith group, g[i][j] for the jth item in the ith group
int wa[1001], va[1001];     // wa is weight, va is value
int f[1001];                // dp

int main() {
   int n, W;
   int maxg = 0;
   cin >> W >> n;

   for (int i = 1; i <= n; i++) {
      int a, b, c;
      cin >> a >> b >> c;

      gs[c]++;
      g[c][gs[c]] = i;
      wa[i] = a;
      va[i] = b;
      maxg = max(maxg, c);
   }

   for (int i = 1; i <= maxg; i++) {
      for (int j = W; j >= 0; j--) {
         for (int k = 1; k <= gs[i]; k++) {
            if (j >= wa[g[i][k]]) {
               f[j] = max(f[j], f[j - wa[g[i][k]]] + va[g[i][k]]);
            }
         }
      }
   }

   cout << f[W] << endl;

   return 0;
}