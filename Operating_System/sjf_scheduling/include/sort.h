#pragma once
#include "pcb.h"

void swap(PCB **a, PCB **b) {
    PCB* temp = *a;
    *a = *b;
    *b = temp;
}

// 0 - arrival time
// 1 - burst time
// 2 - completion time
int partition(PCB* arr[], int low, int high, int flag) {
  int pivot = (flag == 0) ? arr[high]->arrival_time : (flag == 1) ? arr[high]->burst_time : arr[high]->completion_time; 
  int i = low - 1;

  for (int j = low; j < high; j++) {
    int current = (flag == 0) ? arr[j]->arrival_time : (flag == 1) ? arr[j]->burst_time : arr[j]->completion_time;
 
    if (current <= pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return i + 1;
}

void quick_sort(PCB* arr[], int low, int high, int flag) {
  if (low < high) {
    int pi = partition(arr, low, high, flag);
    quick_sort(arr, low, pi - 1, flag);
    quick_sort(arr, pi + 1, high, flag);
  }
}

void print_process_table(PCB** process_list, int n) {
    printf("+-----------+-------------+-----------+----------------+----------------+----------------+\n");
    printf("| ProcessID | ArrivalTime | BurstTime | CompletionTime | TurnaroundTime | WaitingTime    |\n");
    printf("+-----------+-------------+-----------+----------------+----------------+----------------+\n");
    for (int i = 0; i < n; i++) {
        PCB* p = process_list[i];
        printf("| %-9d | %-11d | %-9d | %-14d | %-14d | %-14d |\n",
               p->process_id,
               p->arrival_time,
               p->burst_time,
               p->completion_time,
               p->turnaround_time,
               p->waiting_time);
    }
    printf("+-----------+-------------+-----------+----------------+----------------+----------------+\n");
}

