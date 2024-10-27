#include <iostream>
#include <fstream>
#include <ctime>
#include <random>

using namespace std;

void GenerateData(const string &filename, int size) {
    ofstream outFile(filename);

    mt19937 generator(static_cast<unsigned>(time(0)));
    uniform_int_distribution<int> distribution(1, size * 10);

    for (int i = 0; i < size; ++i) {
        int randomValue = distribution(generator);
        outFile << randomValue << endl;
        cout << randomValue << endl;
    }

    outFile.close();
}

int main() {
    string outputdir = "..\\random_data\\size_";
    int size = 10000000;
    string out = outputdir + to_string(size);
    GenerateData(out, size);
    return 0;
}
