#include "./pcb.h"
#include "./queue.h"
#include "./sort.h"

PCB* create_process(int process_id, int arrival_time, int burst_time) {
  PCB* process = (PCB*)malloc(sizeof(PCB));

  process->process_id = process_id;
  process->arrival_time = arrival_time;
  process->burst_time = burst_time;
  process->remaining_time = burst_time; 
  process->completion_time = 0;
  process->turnaround_time = 0;
  process->waiting_time = 0;

  return process;
}

void shortest_job_scheduling(PCB** process_list, int process_count) {
  int completed = 0;
  int time = 0;

  Queue* queue = create_queue();
  quick_sort(process_list, 0, process_count - 1, 0);

  int next_arrival = 0;

  while (completed < process_count) {
    while (next_arrival < process_count && process_list[next_arrival]->arrival_time <= time) {
      enqueue(queue, process_list[next_arrival]);
      next_arrival++;
    }

    if (!is_empty(queue)) {
      PCB* sb_process = get_shortest_burst_process(queue);

      sb_process->remaining_time--;
      time++;

      if (sb_process->remaining_time == 0) {
        sb_process->completion_time = time;
        sb_process->turnaround_time = sb_process->completion_time - sb_process->arrival_time;
        sb_process->waiting_time = sb_process->turnaround_time - sb_process->burst_time;

        dequeue(queue, sb_process->process_id);
        completed++;
      }
      
      // printf("P[%d]: [%d]\n", sb_process->process_id, time);
    }
    else {
      // printf("idle: [%d]\n", time);
      time++;
    }
  }
}