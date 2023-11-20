#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;         // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int completion; // Completion time
    int turnaround;
    int waiting;
};

bool compareArrivalTimes(const Process &a, const Process &b) {
    return a.arrival < b.arrival;
}

bool compareBurstTimes(const Process &a, const Process &b) {
    return a.burst < b.burst;
}

void findCompletionTimes(Process pr[], int n) {
    pr[0].completion = pr[0].arrival + pr[0].burst;

    for (int i = 1; i < n; i++) {
        pr[i].completion = max(pr[i].arrival, pr[i - 1].completion) + pr[i].burst;
    }
}

void findTurnaroundTimes(Process pr[], int n) {
    for (int i = 0; i < n; i++) {
        pr[i].turnaround = pr[i].completion - pr[i].arrival;
    }
}

void findWaitingTimes(Process pr[], int n) {
    for (int i = 0; i < n; i++) {
        pr[i].waiting = pr[i].turnaround - pr[i].burst;
    }
}

void displayGanttChart(Process pr[], int n) {
    // Print Gantt chart header
    cout << "Gantt Chart:\n";
    for (int i = 0; i < n; i++) {
        cout << "+-----";
    }
    cout << "+\n";

    // Print process IDs in the timeline
    for (int i = 0; i < n; i++) {
        cout << "|  P" << pr[i].id << " ";
    }
    cout << "|\n";

    // Print Gantt chart footer
    for (int i = 0; i < n; i++) {
        cout << "+-----";
    }
    cout << "+\n";
}

int main() {
    int n = 4;
    Process processes[n];

    int arrivalTimes[] = {0, 1, 2, 3};
    int burstTimes[] = {6, 8, 7, 3};

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        processes[i].arrival = arrivalTimes[i];
        processes[i].burst = burstTimes[i];
    }

    sort(processes, processes + n, compareBurstTimes);

    findCompletionTimes(processes, n);
    findTurnaroundTimes(processes, n);
    findWaitingTimes(processes, n);

    // Display Gantt chart
    displayGanttChart(processes, n);

    // Display results
    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t" << processes[i].arrival << "\t" << processes[i].burst << "\t"
             << processes[i].completion << "\t\t" << processes[i].turnaround << "\t\t" << processes[i].waiting << endl;
    }

    return 0;
}
