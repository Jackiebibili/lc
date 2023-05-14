// problem https://vjudge.net/problem/ZOJ-3213
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int M = 8;
const int OFFSET = 3, MASK = (1 << OFFSET) - 1;
const int MAX = 16796, PRIME = 9973;
const int OCCU = 3;
int n, m;
int val, ans;

int ps[M + 1], psm[M + 1];
int mat[M + 1][M + 1];

void applyMax(int &a, int num) {
   if (a < num) {
      a = num;
   }
}

struct hashMap {
   int head[PRIME], next[MAX], sz;
   int keys[MAX];
   int values[MAX];

   void clear() {
      memset(head, -1, sizeof(head));
      sz = 0;
   }

   void push(int key) {
      int pos = key % PRIME;
      for (int i = head[pos]; ~i; i = next[i]) {
         if (keys[i] == key) {
            applyMax(values[i], val);
            return;
         }
      }

      keys[sz] = key, values[sz] = val;
      next[sz] = head[pos];  // old (prev) head
      head[pos] = sz++;      // new head
   }

   void roll() {
      for (int i = 0; i < sz; i++) {
         keys[i] <<= OFFSET;
      }
   }
} H[2][OCCU], *H1, *H2;

int encode() {
   memset(psm, -1, sizeof(psm));
   psm[0] = 0;

   int uniquegp = 1;
   int bin = 0;

   for (int i = m; i >= 0; i--) {
      int idx = ps[i];
      if (!~psm[idx]) {
         psm[idx] = uniquegp++;
      }
      bin <<= OFFSET;
      bin |= psm[idx];
   }

   return bin;
}

void decode(int bin) {
   for (int i = 0; i <= m; i++) {
      ps[i] = bin & MASK;
      bin >>= OFFSET;
   }
}

void push(int c, int col, int down, int right) {
   ps[col] = down;
   ps[col + 1] = right;

   H1[c].push(encode());
}

void clearAll(hashMap *h) {
   for (int i = 0; i < OCCU; i++) {
      h[i].clear();
   }
}

int solve() {
   ans = 0;
   val = 0;
   H1 = H[0], H2 = H[1];
   clearAll(H1);
   H1[0].push(0);

   for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
         // skip obstacles
         if (!mat[i][j]) continue;
         // single cell
         applyMax(ans, mat[i][j]);
         // rolling
         swap(H1, H2);
         clearAll(H1);

         for (int c = 0; c < OCCU; c++) {
            for (int k = 0; k < H2[c].sz; k++) {
               decode(H2[c].keys[k]);
               val = H2[c].values[k] + mat[i][j];

               int left = ps[j], top = ps[j + 1];
               bool down = mat[i + 1][j], right = mat[i][j + 1];

               if (left && top) {
                  if (left != top) {
                     for (int i = 0; i <= m; i++) {
                        if (ps[i] == left) {
                           ps[i] = top;
                        }
                     }
                     push(c, j, 0, 0);
                  }
               } else if (left || top) {
                  int plug = left | top;

                  if (down) {
                     push(c, j, plug, 0);
                  }
                  if (right) {
                     push(c, j, 0, plug);
                  }

                  // single plug disappears
                  if (c < 2) {
                     push(c + 1, j, 0, 0);
                  }
               } else {
                  val -= mat[i][j];
                  // no plug and skip the current cell
                  H1[c].push(H2[c].keys[k]);

                  val += mat[i][j];
                  if (down && right) {
                     push(c, j, m, m);
                  }

                  // single plug creation
                  if (c < 2) {
                     if (down) {
                        push(c + 1, j, m, 0);
                     }

                     if (right) {
                        push(c + 1, j, 0, m);
                     }
                  }
               }
            }
         }
      }
      for (int i = 0; i < OCCU; i++) {
         H1[i].roll();
      }
   }

   for (int i = 0; i < H1[2].sz; i++) {
      applyMax(ans, H1[2].values[i]);
   }

   return ans;
}

int main() {
   int T;
   scanf("%d", &T);

   while (T--) {
      memset(mat, 0, sizeof(mat));
      scanf("%d%d", &n, &m);

      for (int i = 0; i < n; i++) {
         for (int j = 0; j < m; j++) {
            scanf("%d", &mat[i][j]);
         }
      }
      int res = solve();

      printf("%d\n", res);
   }

   return 0;
}