#include <bits/stdc++.h>
using namespace std;

int main()
{
    int nums[] = {1, 12, -5, -6, 50, 3}; 
    int n = nums.lenght();
    int k;
    cin >> k;

    double max_prom = 0;
    for (int i = 0; i < k; i++) {
        max_prom += nums[i];
    }
    
    max_prom /= k;

    double current_prom = max_prom;
    int past, nuew;
    for (int i = 1; i <= n - k; i++) {
        past = nums[i-1];
        nuew = nums[i+k-1];
        current_prom = (current_prom - past + nuew) / (double) k;
        max_prom = max(max_prom, current_prom);
    }

    cout <<  max_prom << endl;
}
