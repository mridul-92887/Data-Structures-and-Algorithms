#include <bits/stdc++.h>
using namespace std;

int fibonacci(int n) {
    if (n == 0) {
        return 0;
    } 
    else if (n == 1) {
        return 1;
    } 
    else {
        int result = fibonacci(n - 1) + fibonacci(n - 2);
        return result;
    }
}

int main() {
    int n = 10;
    cout << "Fibonacci sequence up to " << n << " terms: ";
    for (int i = 0; i < n; i++) {
        cout << fibonacci(i) << " ";
    }
    cout << endl;
    return 0;
}
