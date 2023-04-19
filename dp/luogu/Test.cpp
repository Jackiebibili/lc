#include<iostream>
using namespace std;

const int len = 100;
int dp[len];

int main()
{  
    memset(dp, -1, sizeof(dp));
    for(int i = 0; i < len; i++) {
      cout << dp[i] << " ";
    }
    return 0;
}