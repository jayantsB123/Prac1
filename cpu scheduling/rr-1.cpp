#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

struct Process {
    int id;         // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
};

bool compareArrival(const Process &a, const Process &b) {
    return a.arrival < b.arrival;
}

void roundRobinScheduling(Process processes[], int n, int timeQuantum) {
    queue<Process> readyQueue;

    int currentTime = 0;
    int remainingBurstTime[n];

    sort(processes, processes + n, compareArrival);

    for (int i = 0; i < n; i++) {
        readyQueue.push(processes[i]);
        remainingBurstTime[i] = processes[i].burst;
    }

    while (!readyQueue.empty()) {
        Process currentProcess = readyQueue.front();
        readyQueue.pop();

        int executionTime = min(timeQuantum, remainingBurstTime[currentProcess.id - 1]);
        currentTime += executionTime;
        remainingBurstTime[currentProcess.id - 1] -= executionTime;

        cout << "Executing Process " << currentProcess.id << " for " << executionTime << " units. Current Time: " << currentTime << endl;

        // Display the ready queue
        cout << "Ready Queue: ";
        queue<Process> tempQueue = readyQueue;
        while (!tempQueue.empty()) {
            cout << "P" << tempQueue.front().id << " ";
            tempQueue.pop();
        }
        cout << endl;

        // Add processes to the ready queue that have arrived by the current time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && remainingBurstTime[i] > 0) {
                readyQueue.push(processes[i]);
            }
        }
    }
}

int main() {
    int n = 4; // Set the number of processes
    Process processes[n];

    // Initialize processes with predefined values
    // You can modify these values as needed
    int arrivalTimes[] = {0, 1, 2, 4};
    int burstTimes[] = {5,4,2,1};

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        processes[i].arrival = arrivalTimes[i];
        processes[i].burst = burstTimes[i];
    }

    int timeQuantum;
    cout << "Enter the time quantum for Round Robin: ";
    cin >> timeQuantum;

    roundRobinScheduling(processes, n, timeQuantum);

    return 0;
}
