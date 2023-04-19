#include <cstring>
#include <iostream>
using namespace std;

int f[30][3];
int x[30], y[30], z[30];

int helper(int n, int cur, int plmt) {
   // memo
   if (f[cur][plmt] != -1) {
      return f[cur][plmt];
   }

   int b1 = 0, b2 = 0;
   if (plmt == 0) {
      // use x and y for base
      b1 = x[cur];
      b2 = y[cur];
   } else if (plmt == 1) {
      // x and z
      b1 = x[cur];
      b2 = z[cur];
   } else {
      // y and z
      b1 = y[cur];
      b2 = z[cur];
   }

   int mx = 0;
   // add the next block onto the prev block
   for (int i = 0; i < n; i++) {
      // if can stack block
      // next block dim is x[i], y[i], z[i]
      if ((x[i] < b1 && y[i] < b2) || (x[i] < b2 && y[i] < b1)) {
         mx = max(mx, helper(n, i, 0) + z[i]);
      }
      if ((x[i] < b1 && z[i] < b2) || (x[i] < b2 && z[i] < b1)) {
         mx = max(mx, helper(n, i, 1) + y[i]);
      }
      if ((y[i] < b1 && z[i] < b2) || (y[i] < b2 && z[i] < b1)) {
         mx = max(mx, helper(n, i, 2) + x[i]);
      }
   }
   return f[cur][plmt] = mx;
}

int solution(int n) {
   // reset dp
   memset(f, -1, sizeof(f));

   for (int i = 0; i < n; i++) {
      cin >> x[i] >> y[i] >> z[i];
   }

   // choose the first block to place on the ground
   int mx = 0;
   for (int i = 0; i < n; i++) {
      mx = max(mx, helper(n, i, 0) + z[i]);
      mx = max(mx, helper(n, i, 1) + y[i]);
      mx = max(mx, helper(n, i, 2) + x[i]);
   }

   return mx;
}

int main() {
   int idx = 1;
   while (1) {
      int n;
      cin >> n;

      if (n == 0) break;
      int res = solution(n);

      cout << "Case " << idx++ << ": maximum height = " << res << endl;
   }
   return 0;
}