#include<iostream>
using namespace std;

const int len = 1000;
int dp[len];

int main()
{  
    for(int i = 0; i < len; i++) {
      cout << dp[i] << " ";
    }
    return 0;
}