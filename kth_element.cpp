#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

/// index = k
int kth(vector<int> arr, int k) {
    nth_element(arr.begin(), arr.begin() + k, arr.end());
    return arr[k];
}

int main() {
    string outputdir = "..\\random_data\\size_";
    int size = 100000;
    string out = outputdir + to_string(size);

    vector<int> arr;
    ifstream in(out);
    int temp;
    while (in >> temp) {
        arr.push_back(temp);
    }
    in.close();

    auto start = chrono::high_resolution_clock::now();
    int mid = kth(arr, (arr.size() - 1) / 2);
    cout << "中位数: " << mid << endl;
    auto end = std::chrono::high_resolution_clock::now();

    chrono::duration<double, micro> duration = end - start;
    cout << "程序运行时间: " << duration.count() << " 微秒" << endl;

    return 0;
}
