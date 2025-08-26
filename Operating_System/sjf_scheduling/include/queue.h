#pragma once
#include <stdlib.h>
#include "./pcb.h"

struct PCB;

typedef struct Node {
  PCB* process;
  struct Node* next;
} Node;

typedef struct {
  PCB* process;

  Node* front;
  Node* rear;
} Queue;

Node* create_node(PCB* process);

Queue* create_queue();
int is_empty(Queue* queue);
void enqueue(Queue* queue, struct PCB* process);
void dequeue(Queue* queue, int process_id);
struct PCB* get_shortest_burst_process(Queue* queue);