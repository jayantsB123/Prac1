#include<bits/stdc++.h>
using namespace std;

struct Process {
    int id;         // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int completion; // Completion time
    int turnaround; int waiting;
};

void calculateCompletionTime(Process processes[], int n) {
    processes[0].completion = processes[0].arrival + processes[0].burst;

    for (int i = 1; i < n; i++) {
        processes[i].completion = max(processes[i].arrival, processes[i - 1].completion) + processes[i].burst;
    }
}

void calculateTurnaroundTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround = processes[i].completion - processes[i].arrival;
    }
}

void calculateWaitingTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].waiting = processes[i].turnaround - processes[i].burst;
    }
}

void displayResults(Process processes[], int n) {
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";

    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t" << processes[i].arrival << "\t\t"
             << processes[i].burst << "\t\t" << processes[i].completion << "\t\t"
             << processes[i].turnaround << "\t\t" << processes[i].waiting << endl;
    }
}

void displayGanttChart(Process processes[], int n) {
    cout << "\nGantt Chart:\n";

    for (int i = 0; i < n; i++) {
        cout << "| P" << processes[i].id << " ";
    }
    cout << "|\n";

    for (int i = 0; i < n; i++) {
        cout << processes[i].completion << "\t";
    }
    cout << "\n";
}

int main() {
    int n = 6; // Set the number of processes
    Process processes[n];

    // Initialize processes with predefined values
    // You can modify these values as needed
    int arrivalTimes[] = {0,1,1,1,2,3};
    int burstTimes[] = {9,3,2,4,3,2};

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        processes[i].arrival = arrivalTimes[i];
        processes[i].burst = burstTimes[i];
    }

    // Sort the processes based on arrival time (assuming all arrival times are distinct)
    sort(processes, processes + n, [](const Process &a, const Process &b) {
        return a.arrival < b.arrival;
    });

    calculateCompletionTime(processes, n);
    calculateTurnaroundTime(processes, n);
    calculateWaitingTime(processes, n);

    displayResults(processes, n);
    displayGanttChart(processes, n);

    return 0;
}
