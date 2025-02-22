#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please input numbers to find average." << endl;
        return 1;
    }

    vector<double> numbers;
    double sum = 0;
    
    for (int i = 1; i < argc; ++i) {
        double num = atof(argv[i]);
        numbers.push_back(num);
        sum += num;
    }
    
    if (numbers.empty()) {
        cout << "No numbers entered. Exiting..." << endl;
        return 1;
    }
    
    double average = sum / numbers.size();
    
    cout << "---------------------------------" << endl;
    cout << "Average of " << numbers.size() << " numbers = " << average << endl;
    cout << "---------------------------------" << endl;
    
    return 0;
}