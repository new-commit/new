#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, tq, time = 0, totalTurnaroundTime = 0, totalWaitingTime = 0;
    cout << "Enter the time quantum: ";
    cin >> tq;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> arrivalTime(n), burstTime(n), remainingTime(n);
    vector<int> startTime(n, -1), completionTime(n), turnaroundTime(n), waitingTime(n);
    deque<int> readyQueue;

    // Input process details
    cout << "Enter the arrival time and burst time of the processes:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ": ";
        cin >> arrivalTime[i] >> burstTime[i];
        remainingTime[i] = burstTime[i];
    }

    int remain = n;

    // Populate the ready queue initially with all processes that arrive at time 0
    for (int i = 0; i < n; i++) {
        if (arrivalTime[i] == 0) {
            readyQueue.push_back(i);
        }
    }

    while (remain > 0) {
        // If the ready queue is empty, increment time until a process arrives
        if (readyQueue.empty()) {
            time++;
            // Check if any new processes have arrived at this time
            for (int i = 0; i < n; i++) {
                if (arrivalTime[i] == time && remainingTime[i] > 0) {
                    readyQueue.push_back(i);
                }
            }
            continue;
        }

        // Get the front process in the ready queue
        int i = readyQueue.front();
        readyQueue.pop_front();

        // Record the start time if the process has never started
        if (startTime[i] == -1) {
            startTime[i] = time;
        }

        // Execute the process for the time quantum or until completion
        if (remainingTime[i] <= tq) {
            time += remainingTime[i];
            remainingTime[i] = 0;
            completionTime[i] = time;

            // Calculate turnaround time and waiting time
            turnaroundTime[i] = completionTime[i] - arrivalTime[i];
            waitingTime[i] = turnaroundTime[i] - burstTime[i];

            totalTurnaroundTime += turnaroundTime[i];
            totalWaitingTime += waitingTime[i];
            remain--;  // Process is completed
        } else {
            time += tq;
            remainingTime[i] -= tq;
        }

        // Add any newly arrived processes to the ready queue
        for (int j = 0; j < n; j++) {
            if (arrivalTime[j] <= time && remainingTime[j] > 0 &&
                find(readyQueue.begin(), readyQueue.end(), j) == readyQueue.end() && j != i) {
                readyQueue.push_back(j);
            }
        }

        // If the current process is not yet complete, add it back to the queue
        if (remainingTime[i] > 0) {
            readyQueue.push_back(i);
        }
    }

    // Output process information
    cout << "\nProcess\tArrival Time\tBurst Time\tStart Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << (i + 1) << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" 
             << startTime[i] << "\t\t" << completionTime[i] << "\t\t" 
             << turnaroundTime[i] << "\t\t" << waitingTime[i] << endl;
    }

    // Calculate and print average waiting time and turnaround time
    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << (float)totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << (float)totalTurnaroundTime / n << endl;

    return 0;
}
