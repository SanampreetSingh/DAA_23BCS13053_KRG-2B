#include <iostream>
using namespace std;


double power(double x, int y) {
    if (y == 0)
        return 1; 
    
    double temp = power(x, y / 2);
    
 
    if (y % 2 == 0) {
        return temp * temp;
    } 

    else {
        if (y > 0)
            return x * temp * temp; 
        else
            return (temp * temp) / x; 
    }
}

int main() {
    double base;
    int exponent;
    
    cout << "Enter base: ";
    cin >> base;
    cout << "Enter exponent: ";
    cin >> exponent;
    
    cout << base << "^" << exponent << " = " << power(base, exponent) << endl;
    return 0;
}
