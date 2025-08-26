#include "./include/queue.h"
#include "./include/pcb.h"
#include <time.h>
#include <string.h>
#include <windows.h>

PCB** generate_random_processes(int n) {
  PCB** process_list = (PCB**)malloc(n * sizeof(PCB*));
  for (int i = 0; i < n; i++) {
    int arrival_time = rand() % 10;      // random 0-9
    int burst_time = rand() % 10 + 1;    // random 1-10
    process_list[i] = create_process(i + 1, arrival_time, burst_time);
  }
  return process_list;
}

void start_query(LARGE_INTEGER* freq, LARGE_INTEGER* start) {
  QueryPerformanceFrequency(freq);
  QueryPerformanceCounter(start);
}

double elapsed_time(LARGE_INTEGER* freq, LARGE_INTEGER* start, LARGE_INTEGER* end) {
  QueryPerformanceCounter(end);
  return (double)(end->QuadPart - start->QuadPart) / freq->QuadPart;
}

int main(int argc, char** argv) {
  LARGE_INTEGER start, end, freq;

  // seed random generator
  srand(time(NULL)); 

  int n = atoi(argv[1]);

  start_query(&freq, &start);
  PCB** process_list = generate_random_processes(n);
  printf("generator:\t%.10fs\n", elapsed_time(&freq, &start, &end));

  start_query(&freq, &start);
  quick_sort(process_list, 0, n -1, 0);
  printf("sorting:\t%.10fs\n", elapsed_time(&freq, &start, &end));

  // start_query(&freq, &start);
  // shortest_job_scheduling(process_list, n);
  // printf("shortest job scheduling: %.10fs\n", elapsed_time(&freq, &start, &end));

  return 0;
}