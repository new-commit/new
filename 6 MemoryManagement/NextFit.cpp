#include <iostream>
#include <vector>
using namespace std;

void nextFit(vector<int>& blockSize, int m, const vector<int>& processSize, int n) {
    vector<int> allocation(n, -1); // Initialize allocation array with -1 (no allocation)
    int j = 0; 

    for (int i = 0; i < n; i++) {
        
        int count = 0;
        while (count < m) { 
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j + 1;
                blockSize[j] -= processSize[i]; 
                break; 
            }
            j = (j + 1) % m; 
            count++;
        }
    }

    cout << "Process no.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t\t" << processSize[i] << "\t\t" << allocation[i] << endl;
    }
}

int main() {
    int m, n;
    cout << "Enter the number of blocks and processes: ";
    cin >> m >> n;
    vector<int> blockSize(m), processSize(n);
    cout << "Enter the sizes of each block:\n";
    for (int i = 0; i < m; i++) {
        cin >> blockSize[i];
    }
    cout << "Enter the sizes of each process:\n";
    for (int i = 0; i < n; i++) {
        cin >> processSize[i];
    }
    nextFit(blockSize, m, processSize, n);
    return 0;
}
