#include<iostream>
using namespace std;

int mainw[61];
int mainv[61];

int subw[61][3];
int subv[61][3];
int f[32001];

int main()
{
   int W,n;
   cin >> W >> n;
   for(int i = 1; i <= n; i++) {
      int w,p,q;
      cin >> w >> p >> q;
      if(q == 0) {
         // main
         mainw[i] = w;
         mainv[i] = w * p;
      } else {
         subw[q][0]++;
         subw[q][subw[q][0]] = w;
         subv[q][subw[q][0]] = w * p;
      }
   }

   for(int i = 1; i <= n; i++) {
      for (int j = W; mainw[i] != 0 && j >= mainw[i]; j--) {
         // main part only
         f[j] = max(f[j], f[j - mainw[i]] + mainv[i]);
         // main + part 1
         if(j >= mainw[i] + subw[i][1]) {
            f[j] = max(f[j], f[j - mainw[i] - subw[i][1]] + mainv[i] + subv[i][1]);
         }
         // main + part 2
         if(j >= mainw[i] + subw[i][2]) {
            f[j] = max(f[j], f[j - mainw[i] - subw[i][2]] + mainv[i] + subv[i][2]);
         }
         // main + part 1 & 2
         if (j >= mainw[i] + subw[i][1] + subw[i][2]) {
            f[j] = max(f[j], f[j - mainw[i] - subw[i][1] - subw[i][2]] + mainv[i] + subv[i][1] + subv[i][2]);
         }
      }
   }

   cout << f[W] << endl;
   return 0;
}