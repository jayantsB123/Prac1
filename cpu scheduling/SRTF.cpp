#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Process {
    int id;         // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int remaining;  // Remaining burst time
    int completion; // Completion time
    int turnaround;
    int waiting;
};

bool compareArrivalTimes(const Process &a, const Process &b) {
    return a.arrival < b.arrival;
}

struct CompareRemainingTime {
    bool operator()(const Process &a, const Process &b) {
        return a.remaining > b.remaining;
    }
};

void findCompletionTimes(Process pr[], int n) {
    priority_queue<Process, vector<Process>, CompareRemainingTime> pq;
    int currentTime = 0;

    // Vector to store Gantt Chart
    vector<pair<int, int>> ganttChart;

    for (int i = 0; i < n; i++) {
        while (!pq.empty() && pq.top().arrival <= currentTime) {
            Process currentProcess = pq.top();
            pq.pop();

            int executeTime = min(currentProcess.remaining, pr[i].arrival - currentTime);

            // Update Gantt Chart
            ganttChart.push_back({currentProcess.id, executeTime});

            currentProcess.remaining -= executeTime;
            currentTime += executeTime;

            if (currentProcess.remaining > 0) {
                pq.push(currentProcess);
            } else {
                currentProcess.completion = currentTime;
            }
        }

        if (pr[i].arrival > currentTime) {
            currentTime = pr[i].arrival;
        }

        pr[i].remaining = pr[i].burst;
        pq.push(pr[i]);
    }

    // Process any remaining processes in the priority queue
    while (!pq.empty()) {
        Process currentProcess = pq.top();
        pq.pop();

        currentProcess.completion = currentTime + currentProcess.remaining;

        // Update Gantt Chart
        ganttChart.push_back({currentProcess.id, currentProcess.remaining});

        currentTime = currentProcess.completion;
    }

    // Display Gantt Chart
    cout << "Gantt Chart:\n";
    cout << "| ";
    for (const auto &pair : ganttChart) {
        cout << "P" << pair.first << " | ";
    }
    cout << endl;
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

int main() {
    int n = 4;
    Process processes[n];

    int arrivalTimes[] = {0, 1, 2, 3};
    int burstTimes[] = {6, 8, 7, 3};

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        processes[i].arrival = arrivalTimes[i];
        processes[i].burst = burstTimes[i];
        processes[i].remaining = burstTimes[i];
    }

    sort(processes, processes + n, compareArrivalTimes);

    findCompletionTimes(processes, n);
    findTurnaroundTimes(processes, n);
    findWaitingTimes(processes, n);

    // Display detailed results
    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t" << processes[i].arrival << "\t" << processes[i].burst << "\t"
             << processes[i].completion << "\t\t" << processes[i].turnaround << "\t\t" << processes[i].waiting << endl;
    }

    return 0;
}
