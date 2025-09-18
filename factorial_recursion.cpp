#include <bits/stdc++.h>
using namespace std;

int factorial(int n) {
    if (n == 0) {
        return 1;
    } 
    else {
        int result = n * factorial(n - 1);
        return result;
    }
}

int main() {
    int n = 5;
    int fact = factorial(n);
    cout << "Factorial of " << n << " is " << fact << endl;
    return 0;
}
