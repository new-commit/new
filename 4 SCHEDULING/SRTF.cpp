#include <bits/stdc++.h>
using namespace std;

// Function to find the shortest remaining time first schedule
void calculateSRTF(int n, int at[], int bt[], int start[], int completion[], int tat[], int wt[]) {
    int remainingTime[n];
    int currentTime = 0;
    int completed = 0;
    int prev = -1;

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++) {
        remainingTime[i] = bt[i];
    }

    while (completed < n) {
        int idx = -1;
        int minRemainingTime = INT_MAX;

        // Find process with the shortest remaining time among the arrived processes
        for (int i = 0; i < n; i++) {
            if (at[i] <= currentTime && remainingTime[i] > 0) {
                if (remainingTime[i] < minRemainingTime) {
                    minRemainingTime = remainingTime[i];
                    idx = i;
                }
                // If remaining times are the same, choose process with earlier arrival time
                if (remainingTime[i] == minRemainingTime && at[i] < at[idx]) {
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            // Set start time of the process if it's the first time being executed
            if (remainingTime[idx] == bt[idx]) {
                start[idx] = currentTime;
            }

            remainingTime[idx]--; // Execute process for one unit of time
            currentTime++;

            // If process is completed
            if (remainingTime[idx] == 0) {
                completion[idx] = currentTime;
                tat[idx] = completion[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                completed++;
            }
        } else {
            // If no process is ready, increment the current time
            currentTime++;
        }
    }
}

// Function to print results and calculate averages
void printResults(int n, int at[], int bt[], int start[], int completion[], int tat[], int wt[]) {
    float totalTAT = 0, totalWT = 0;

    cout << "\nProcess\tArrival Time\tBurst Time\tStart Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        totalTAT += tat[i];
        totalWT += wt[i];
        cout << "P" << (i + 1) << "\t" << at[i] << "\t\t" << bt[i] << "\t\t" << start[i] << "\t\t"
             << completion[i] << "\t\t" << tat[i] << "\t\t" << wt[i] << endl;
    }

    cout << "\nAverage Turnaround Time: " << (totalTAT / n) << endl;
    cout << "Average Waiting Time: " << (totalWT / n) << endl;

}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    int at[n], bt[n], start[n], completion[n], tat[n], wt[n];

    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time and Burst Time for Process " << (i + 1) << ": ";
        cin >> at[i] >> bt[i];
    }

    // Calculate SRTF
    calculateSRTF(n, at, bt, start, completion, tat, wt);

    // Print results
    printResults(n, at, bt, start, completion, tat, wt);

    return 0;
}
