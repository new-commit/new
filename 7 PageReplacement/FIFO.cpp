#include <bits/stdc++.h>
using namespace std;

void fifoPage(const vector<int>& pg, int pn, int fn) {
    vector<int> fr;  // Frame
    queue<int> fifoQueue;
    int pageFaults = 0;

    vector<int> pageFaultsArray(pn, 0);
    vector<int> pageHitsArray(pn, 0);

    for (int i = 0; i < pn; i++) {
        int currentPage = pg[i];

        // Check if the page is already in the frame (page hit)
        if (find(fr.begin(), fr.end(), currentPage) == fr.end()) {
            // Page fault
            pageFaults++;
            pageFaultsArray[i] = 1;  // Mark as page fault

            if (fr.size() < fn) {
                fr.push_back(currentPage);
                fifoQueue.push(currentPage);
            } else {
                int replacedPage = fifoQueue.front();
                fifoQueue.pop();
                
                for(int j = 0; j < fr.size(); j++){
                    if(fr[j] == replacedPage){
                        fr[j] = currentPage;
                    }
                }
                fifoQueue.push(currentPage);
            }
        } else {
            pageHitsArray[i] = 1;  // Mark as page hit
        }

        cout << "Page " << currentPage << " is in the frame. Frame Contents: ";
        for (int page : fr) {
            cout << page << " ";
        }
        cout << endl;
    }

    cout << "\nPage Faults Array: ";
    for (int fault : pageFaultsArray) {
        cout << fault << " ";
    }
    cout << "\nPage Hits Array: ";
    for (int hit : pageHitsArray) {
        cout << hit << " ";
    }
    cout << endl;

}

int main() {
    int pn, fn;
    cout << "Enter the number of pages: ";
    cin >> pn;
    vector<int> pg(pn);

    cout << "Enter the page numbers:" << endl;
    for (int i = 0; i < pn; i++) {
        cin >> pg[i];
    }

    cout << "Enter the frame size: ";
    cin >> fn;

    fifoPage(pg, pn, fn);

    return 0;
}
