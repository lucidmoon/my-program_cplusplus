#include <iostream>
#include <vector>
using namespace std;

void bubbleSort(vector<int>& arr){
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = 0; j + 1 < arr.size() - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(){
    vector<int> arr = { 70, 20, 40, 10, 120, 340, 5, 1 };
    cout << "-= Bubble Sorting =-" << endl;
    
    cout << "Before sort: ";
    for (int value : arr) {
        cout << value << " ";
    }
    cout << endl;

    bubbleSort(arr);
    cout << "After sort : ";
    for (int value : arr) {
        cout << value << " ";
    }
    cout << endl;

    return 0;
}