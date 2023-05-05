#include<iostream>
using namespace std;

const int len = 100;
int dp[len], dp2[len];

int main()
{  
    // memset(dp, 0x3f3f, sizeof(dp));
    // memcpy(dp2, dp, sizeof(dp2));
    
    // memset(dp, 0, sizeof(dp));

    // for(int i = 0; i < len; i++) {
    //   cout << dp[i] << " ";
    // }
    // cout << endl;
    // for(int i = 0; i < len; i++) {
    //   cout << dp2[i] << " ";
    // }
    for(int i = 0, j = 0, z = i; i < 5; i++) {
      cout << i << " " << z << endl;
      j++;
    }
    // 0110 -> 0100
    int i = 6, j = 4;

    // i -= i & -i;
    // i &= i-1;
    i |= (1 << j-1);

    cout << i << endl;
    return 0;
}