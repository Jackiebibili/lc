#include <iostream>
using namespace std;

long long f[10000001];
int w[10000];
int v[10000];

int main() {
   int W, n;
   cin >> W >> n;

   for (int i = 0; i < n; i++) {
      cin >> w[i] >> v[i];
   }

   for (int i = 0; i < n; i++) {
      for (int j = 0; j <= W - w[i]; j++) {
         f[j + w[i]] = max(f[j + w[i]], f[j] + v[i]);
      }
   }

   cout << f[W] << endl;

   return 0;
}