#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <limits>

using namespace std;

void Merge_Sort(vector<int> &arr, int start, int end) {
    if (start >= end) return;
    int mid = start + (end - start) / 2;
    Merge_Sort(arr, start, mid);
    Merge_Sort(arr, mid + 1, end);
    vector<int> left(arr.begin() + start, arr.begin() + mid + 1),
            right(arr.begin() + mid + 1, arr.begin() + end + 1);
    left.push_back(numeric_limits<int>::max());
    right.push_back(numeric_limits<int>::max());
    int index_left = 0, index_right = 0;
    for (int i = start; i <= end; i++) {
        if (left[index_left] < right[index_right]) {
            arr[i] = left[index_left++];
        } else arr[i] = right[index_right++];
    }
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
    Merge_Sort(arr, 0, arr.size() - 1);
    cout << "中位数: " << arr[(arr.size() - 1) / 2] << endl;
    auto end = std::chrono::high_resolution_clock::now();

    chrono::duration<double, micro> duration = end - start;
    cout << "程序运行时间: " << duration.count() << " 微秒" << endl;

    return 0;
}
