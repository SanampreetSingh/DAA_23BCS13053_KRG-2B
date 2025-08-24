#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> arr(n);
    map<int, int> freq;
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        freq[arr[i]]++;
    }
    cout << "Element : Frequency" << endl;
    for (auto c : freq) {
        cout << c.first << " : " << c.second << endl;
    }
    return 0;
}