#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;

/// 分区
int part(vector<int> &arr, int left, int right, int index) {
    int temp = arr[index];
    arr[index] = arr[right];
    arr[right] = temp;
    int local = left;
    for (int i = left; i < right; i++) {
        if (arr[i] < arr[right]) {
            temp = arr[i];
            arr[i] = arr[local];
            arr[local] = temp;
            local++;
        }
    }
    temp = arr[right];
    arr[right] = arr[local];
    arr[local] = temp;
    return local;
}

/// 小排序
int get_small_mid(vector<int> &arr, int left, int num) {
    sort(arr.begin() + left, arr.begin() + left + num);
    return arr[left + num / 2];
}

/// 主要功能函数
int Linear(vector<int> &arr, int left, int right, int k) {
    if (left == right) return arr[left];
    int num = right - left + 1;
    vector<int> mid;

    for (int i = 0; i < num / 5; i++) {
        mid.push_back(get_small_mid(arr, left + i * 5, 5));
    }
    if (num % 5) mid.push_back(get_small_mid(arr, left + (num / 5) * 5, num % 5));
    int middle = (mid.size() == 1) ? mid[0] : Linear(mid, 0, mid.size() - 1, (mid.size() - 1) / 2);

    int index = left;
    auto it = find(arr.begin() + left, arr.begin() + right + 1, middle);
    if (it != arr.end()) index = distance(arr.begin(), it);

    index = part(arr, left, right, index);

    if (index == k) return arr[index];
    else if (index < k) return Linear(arr, index + 1, right, k);
    else return Linear(arr, left, index - 1, k);
}


int main() {
    string outputdir = "..\\random_data\\size_";
    int size = 1000000;
    string out = outputdir + to_string(size);

    vector<int> arr;
    ifstream in(out);
    int temp;
    while (in >> temp) {
        arr.push_back(temp);
    }
    in.close();

    auto start = chrono::high_resolution_clock::now();
    int mid = Linear(arr, 0, arr.size() - 1, (arr.size() - 1) / 2);
    cout << "中位数: " << mid << endl;
    auto end = std::chrono::high_resolution_clock::now();

    chrono::duration<double, micro> duration = end - start;
    cout << "程序运行时间: " << duration.count() << " 微秒" << endl;

    return 0;
}
