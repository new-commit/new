#include <bits/stdc++.h>
using namespace std;

void findCompletionTime(int n, int at[], int bt[], int completion[], int start[]) {
    vector<pair<int, int>> processes;
    
    // Store arrival time and process index
    for (int i = 0; i < n; i++) {
        processes.push_back({at[i], i});
    }
    
    // Sort processes based on arrival time
    sort(processes.begin(), processes.end());

    // Set the start and completion time for the first process
    start[processes[0].second] = at[processes[0].second];
    completion[processes[0].second] = start[processes[0].second] + bt[processes[0].second];

    // Calculate start and completion times for the rest of the processes
    for (int i = 1; i < n; i++) {
        start[processes[i].second] = max(completion[processes[i - 1].second], at[processes[i].second]);
        completion[processes[i].second] = start[processes[i].second] + bt[processes[i].second];
    }
}

void findTurnAroundTime(int n, int at[], int completion[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = completion[i] - at[i]; // TAT = Completion Time - Arrival Time
    }
}

void findWaitingTime(int n, int bt[], int tat[], int wt[]) {
    for (int i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i]; // WT = Turnaround Time - Burst Time
    }
}

void printGanttChart(int n, int start[], int bt[], int completion[]) {
    cout << "\nGantt Chart:\n";
    cout << "-------------------------------------------------\n";
    
    // Top row with process numbers
    vector<pair<int,int>>GT;
    for(int i = 0; i < n; i++){
        GT.push_back({start[i], i});
    }
    sort(GT.begin(),GT.end());
    for (int i = 0; i < n; i++) {
        cout << "|  P" << (GT[i].second + 1) << "  ";
    }
    cout << "|\n";

    cout << "-------------------------------------------------\n";

    // Bottom row with start and end times
    for (int i = 0; i < n; i++) {
        cout << start[i] << " ";
    }
    cout << completion[n - 1] << "\n"; // Last completion time
}

void findAvgTime(int n, int at[], int bt[]) {
    int completion[n], wt[n], tat[n], start[n];
    
    findCompletionTime(n, at, bt, completion, start);
    findTurnAroundTime(n, at, completion, tat);
    findWaitingTime(n, bt, tat, wt);

    int tavg = 0, wavg = 0;

    cout << "\nProcess No. Arrival Time Burst Time Start Time Completion Time Wait Time Turnaround Time\n";
    for (int i = 0; i < n; i++) {
        wavg += wt[i];
        tavg += tat[i];
        
        cout << "P" << (i + 1) << "\t\t" << at[i] << "\t\t" << bt[i] << "\t\t" << start[i] << "\t\t" 
             << completion[i] << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }

    cout << "Average Waiting Time: " << ((float)wavg / (float)n) << endl;
    cout << "Average Turnaround Time: " << ((float)tavg / (float)n) << endl;

    // Print Gantt Chart
    printGanttChart(n, start, bt, completion);
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    int at[n], bt[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter the Arrival Time and Burst Time of process " << (i + 1) << ": ";
        cin >> at[i] >> bt[i];
    }

    findAvgTime(n, at, bt);
    return 0;
}
