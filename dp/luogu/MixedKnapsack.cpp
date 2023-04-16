#include <iostream>
using namespace std;

int f[1001];
int q1[1001], q2[1001];

int main() {
   int hs, ms, he, me, n;
   int ans = 0;
   scanf("%d:%d %d:%d %d", &hs, &ms, &he, &me, &n);
   int W = (he * 60 + me) - (hs * 60 + ms);
   for (int i = 1; i <= n; i++) {
      int w, v, p;
      cin >> w >> v >> p;

      if (w == 0) {
         ans += v * p;
      } else if (p == 1) {
         // 0-1
         for (int j = W; j >= w; j--) {
            f[j] = max(f[j], f[j - w] + v);
         }
      } else if (p == 0) {
         // complete
         for (int j = w; j <= W; j++) {
            f[j] = max(f[j], f[j - w] + v);
         }
      } else {
         // multiple
         // RMQ
         p = min(p, W / w);
         // enumerate remainder
         for (int d = 0; d < w; d++) {
            int k = (W - d) / w;
            int head = 1, tail = 0;
            for (int j = 0; j <= k; j++) {
               while (head <= tail && f[d + j * w] - j * v >= q2[tail]) {
                  tail--;
               }
               tail++;
               q1[tail] = j;
               q2[tail] = f[d + j * w] - j * v;

               while (head <= tail && q1[head] < j - p) {
                  head++;
               }
               f[d + j * w] = max(f[d + j * w], q2[head] + j * v);
            }
         }
      }
   }

   cout << f[W] + ans << endl;

   return 0;
}