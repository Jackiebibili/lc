// Problem F in https://codeforces.com/gym/100220/attachments/download/1766/20052006-zimniye-pyetrozavodskiye-sbory-andrew-stankevich-contest-16-en.pdf
#include <algorithm>
#include <iostream>
#define ll long long
using namespace std;

const int M = 10;
/**
 * @brief
 * Plugs appears in pairs, so the minimum number of plugs in the same group is 2.
 * Maximum min(n, m) is 10, so it will not have more than 5 (101(b), 3 bits) plug groups.
 */
const int OFFSET = 3, MASK = (1 << OFFSET) - 1;
/**
 * @brief
 * Hash table uses separate chaining technique.
 * Maximum slots # is `PRIME`
 * Maximum capacity is `MAX`
 */
const int MAX = 16796, PRIME = 9973;
int n, m;
ll val;

/**
 * @brief
 * Plugs states (on the contour line)
 * and plug state mappings (least number starting with 1)
 * There are m+1 plugs on the contour line: m's plugs and a left plug.
 */
int ps[M + 1], psm[M + 1];

/**
 * @brief
 * Stores the valid contour line plug states
 */
struct hashMap {
   int head[PRIME], next[MAX], sz;
   int keys[MAX];
   ll values[MAX];

   void clear() {
      sz = 0;
      memset(head, -1, sizeof(head));
   }

   void push(int key, ll value = val) {
      int loc = key % PRIME;

      // find an entry in the map
      for (int i = head[loc]; ~i; i = next[i]) {
         if (keys[i] == key) {
            // increment the mapped value (+=)
            values[i] += value;
            return;
         }
      }

      // new key
      keys[sz] = key, values[sz] = value;
      next[sz] = head[loc];
      head[loc] = sz++;
   }

   void roll() {
      for (int i = 0; i < sz; i++) {
         keys[i] <<= OFFSET;
      }
   }
} H[2], *H1, *H2;

int encode() {
   int v = 0;

   int unique = 1;
   memset(psm, -1, sizeof(psm));
   psm[0] = 0;  // 0 for no plugs

   for (int i = m; i >= 0; i--) {
      int idx = ps[i];
      // if the least unique group number is not assigned - assign
      if (!~psm[idx]) psm[idx] = unique++;
      v <<= OFFSET;
      v |= psm[idx];
   }

   return v;
}

void decode(int v) {
   for (int i = 0; i <= m; i++) {
      ps[i] = v & MASK;
      v >>= OFFSET;
   }
}

void push(int col, int down, int right) {
   ps[col] = down, ps[col + 1] = right;
   H1->push(encode());
}

ll solve() {
   H1 = &H[0], H2 = &H[1];
   H1->clear();
   H1->push(0, 1);

   for (int i = 1; i <= n; i++) {
      for (int j = 0; j < m; j++) {
         // rolling array
         swap(H1, H2);
         H1->clear();

         // iterate over all valid contour line plug states
         for (int k = 0; k < H2->sz; k++) {
            int bin = H2->keys[k];
            decode(bin);
            val = H2->values[k];

            int left = ps[j], top = ps[j + 1];
            bool down = i < n, right = j < m - 1;

            if (left && top) {
               if (left == top) {
                  if (!down && !right) {
                     // can close up the cycle
                     // no more down/right plugs
                     push(j, 0, 0);
                  }
               } else {
                  // left and top has plugs but plug
                  // but plug group numbers differ
                  // join them together as a path
                  for (int i = 0; i <= m; i++) {
                     if (ps[i] == top) {
                        ps[i] = left;
                     }
                  }
                  // no more down/right plugs
                  push(j, 0, 0);
               }
            } else if (left || top) {
               // either left/top has plug
               int pg = left | top;
               // extends the plug in down/right directions
               if (down) {
                  push(j, pg, 0);
               }
               if (right) {
                  push(j, 0, pg);
               }
            } else {
               // no plugs
               // form two down/right plugs in the same plug group
               if (down && right) {
                  push(j, m, m);
               }
            }
         }
      }
      // left roll for initializing the left plug state (3 bits) to 000
      H1->roll();
   }

   // valid state count must be 1 to have the value
   return H1->sz == 1 ? H1->values[0] : 0;
}

int main() {
   scanf("%d%d", &n, &m);

   // make sure m is the smaller number in {n, m}
   if (n < m) {
      swap(n, m);
   }

   ll ans = solve();

   printf("%lld\n", ans);

   return 0;
}