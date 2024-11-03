#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

void Read(string file, vector<int> &price, int &budget) {
    ifstream f(file);
    int order, p;
    f >> order >> budget;
    while (f >> order >> p) {
        price.push_back(p);
    }
    f.close();
}

int dp(int budget, const vector<int> &price, vector<int> &item) {
    vector<int> bgt(budget + 1, 0); // Max money used for each budget
    vector<int> select(budget + 1, -1);

    for (int i = 0; i < price.size(); i++) {
        for (int j = budget; j >= price[i]; j--) {
            if (bgt[j] < bgt[j - price[i]] + price[i]) {
                bgt[j] = bgt[j - price[i]] + price[i];
                select[j] = i; // Track the index of the item
            }
        }
    }

    for (int m = budget; m > 0;) {
        int itemIndex = select[m];
        if (itemIndex != -1) {
            item.push_back(itemIndex);
            m -= price[itemIndex];
        } else {
            break;
        }
    }

    return bgt[budget];
}

int main() {
    string file_in = "D:\\LAB2\\data\\data2.dat";
    int all = 0;
    vector<int> price, item;
    int budget;
    Read(file_in, price, budget);
    auto start = chrono::high_resolution_clock::now();

    int money = dp(budget, price, item);
    cout << "数据集: data2" << endl;

    cout << "最大支出: " << money << endl;
    cout << "选中的物品索引及对应金额：" << endl;

    for (int index: item) {
        cout << "物品索引: " << index << ", 金额: " << price[index] << endl;
        all += price[index];
    }
    cout << "共计: " << all << endl;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "程序运行时间: " << duration.count() << " 毫秒" << endl;

    return 0;
}
