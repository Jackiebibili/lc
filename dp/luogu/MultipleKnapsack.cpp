#include <iostream>
using namespace std;

int q1[40001], q2[40001];
int f[40001];

int main() {
   int n, W;
   cin >> n >> W;
   int ans = 0;
   for (int i = 0; i < n; i++) {
      int v, w, m;
      cin >> v >> w >> m;
      if (w == 0) {
         ans += v * m;
         continue;
      }
      int a = min(m, W / w);
      // enumerate remainder
      for (int b = 0; b < w; b++) {
         int k = (W - b) / w;
         int head = 1, tail = 0;
         for (int j = 0; j <= k; j++) {
            while (head <= tail && f[b + j * w] - j * v >= q2[tail]) {
               tail--;
            }
            tail++;
            q1[tail] = j;
            q2[tail] = f[b + j * w] - j * v;
            // maintain RMQ
            while (head <= tail && q1[head] < j - a) {
               head++;
            }
            f[b + j * w] = max(f[b + j * w], q2[head] + j * v);
         }
      }
   }

   cout << ans + f[W] << endl;
   return 0;
}