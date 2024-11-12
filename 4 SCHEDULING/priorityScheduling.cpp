#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;          // Process ID
    int arrivalTime; // Arrival Time
    int burstTime;   // Burst Time
    int priority;    // Priority
    int startTime;   // Start Time
    int completionTime;  // Completion Time
    int waitingTime;    // Waiting Time
    int turnAroundTime; // Turnaround Time
    int remainingTime;  // Remaining Burst Time for Preemption
    bool isCompleted;   // To check if the process is completed
};

bool compareArrivalTime(Process p1, Process p2) {
    return p1.arrivalTime < p2.arrivalTime;  // Sort by arrival time
}

bool comparePriority(Process p1, Process p2) {
    return p1.priority > p2.priority;  // Sort by priority (higher priority first)
}

void findAvgTime(vector<Process>& p, int n) {
    vector<int> ProcessOrder;
    deque<int> readyQueue;
    int time = 0, completed = 0;
    int totalWaitTime = 0, totalTurnAroundTime = 0;
    
    int i = 0; // Index to track unprocessed processes

    while (completed < n) {
        // Add all processes that have arrived by current time
        while (i < n && p[i].arrivalTime <= time) {
            readyQueue.push_back(i);
            i++;
        }

        // Sort the ready queue by priority
        sort(readyQueue.begin(), readyQueue.end(), [&](int a, int b) {
            return comparePriority(p[a], p[b]);
        });

        if (!readyQueue.empty()) {
            int current = readyQueue.front();
            readyQueue.pop_front();

            ProcessOrder.push_back(current);

            if (p[current].startTime == -1) {
                p[current].startTime = time;  // Set start time for the first execution
            }

            // Process one unit of time
            p[current].remainingTime -= 1;
            time++;

            // If the process finishes
            if (p[current].remainingTime == 0) {
                p[current].completionTime = time;
                p[current].turnAroundTime = p[current].completionTime - p[current].arrivalTime;
                p[current].waitingTime = p[current].turnAroundTime - p[current].burstTime;

                totalWaitTime += p[current].waitingTime;
                totalTurnAroundTime += p[current].turnAroundTime;

                p[current].isCompleted = true;
                completed++;
            }

            // If the process is not completed, push it back to the ready queue
            if (!p[current].isCompleted && p[current].remainingTime > 0) {
                readyQueue.push_back(current);
            }
        } else {
            // If no process is ready, advance time to the next arrival
            if (i < n) time = p[i].arrivalTime;
        }
    }

    // Output process details and average times
    cout << "\nProcess\tArrival Time\tBurst Time\tPriority\tStart Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int j = 0; j < n; j++) {
        cout << "P" << (p[j].id) << "\t\t" << p[j].arrivalTime << "\t\t" << p[j].burstTime << "\t\t" << p[j].priority
             << "\t\t" << p[j].startTime << "\t\t" << p[j].completionTime << "\t\t" << p[j].turnAroundTime << "\t\t" << p[j].waitingTime << endl;
    }
    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << (float)totalWaitTime / n << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << (float)totalTurnAroundTime / n << endl;
    cout << "Process Order : ";
    for (auto process : ProcessOrder) cout << "P" << p[process].id << " ";
    cout << endl; 
}

int main() {
    int n;
    cout << "Enter the total number of processes: ";
    cin >> n;

    vector<Process> p(n);  // Reserve space for `n` processes
    
    for (int i = 0; i < n; i++) {
        cout << "Enter the Arrival time, Burst time, and Priority respectively for Process " << (i + 1) << ": ";
        cin >> p[i].arrivalTime >> p[i].burstTime >> p[i].priority;
        p[i].id = i + 1;  // Process ID (1-based index)
        p[i].remainingTime = p[i].burstTime;  // Initially remaining time is equal to burst time
        p[i].startTime = -1;  // No process has started yet
        p[i].isCompleted = false;  // Initially no process is completed
    }

    // Sort processes by arrival time
    sort(p.begin(), p.end(), compareArrivalTime);

    findAvgTime(p, n);

    return 0;
}
