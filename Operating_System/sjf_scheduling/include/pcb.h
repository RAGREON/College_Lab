#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct PCB {
  int process_id;
  int arrival_time;
  int burst_time;
  int remaining_time;
  int completion_time;
  int turnaround_time;
  int waiting_time;
} PCB;

PCB* create_process(int process_id, int arrival_time, int burst_time);
void shortest_job_scheduling(PCB** process_list, int process_count);
