#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <windows.h>  // For high-resolution timer

typedef struct PCB {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int turnaround;
    int waiting;
} PCB;

// Create a new process
PCB* create_process(int pid, int arrival, int burst) {
    PCB* p = (PCB*)malloc(sizeof(PCB));
    p->pid = pid;
    p->arrival = arrival;
    p->burst = burst;
    p->remaining = burst;
    p->completion = 0;
    p->turnaround = 0;
    p->waiting = 0;
    return p;
}

// Generate n random processes
PCB** generate_random_processes(int n) {
    PCB** list = (PCB**)malloc(n * sizeof(PCB*));
    for (int i = 0; i < n; i++) {
        int at = rand() % 10;       // Arrival 0-9
        int bt = rand() % 10 + 1;   // Burst 1-10
        list[i] = create_process(i + 1, at, bt);
    }
    return list;
}

int main(int argc, char** argv) {
    srand((unsigned int)time(NULL));

    int n = atoi(argv[1]);
    PCB** p = generate_random_processes(n);

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    int completed = 0, current_time = 0;
    float total_tat = 0, total_wt = 0;

    while (completed != n) {
        int idx = -1, min_remaining = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i]->arrival <= current_time && p[i]->remaining > 0) {
                if (p[i]->remaining < min_remaining) {
                    min_remaining = p[i]->remaining;
                    idx = i;
                } else if (p[i]->remaining == min_remaining && p[i]->arrival < p[idx]->arrival) {
                    idx = i; // FCFS tie-breaker
                }
            }
        }

        if (idx != -1) {
            p[idx]->remaining--;
            current_time++;

            if (p[idx]->remaining == 0) {
                completed++;
                p[idx]->completion = current_time;
                p[idx]->turnaround = p[idx]->completion - p[idx]->arrival;
                p[idx]->waiting = p[idx]->turnaround - p[idx]->burst;

                total_tat += p[idx]->turnaround;
                total_wt += p[idx]->waiting;
            }
        } else {
            current_time++;
        }
    }

    QueryPerformanceCounter(&end);
    double elapsed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;

    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nExecution Time = %.6f seconds\n", elapsed);

    printf("\n");

    // Free memory
    for (int i = 0; i < n; i++) free(p[i]);
    free(p);

    return 0;
}
