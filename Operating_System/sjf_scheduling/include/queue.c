#include "./queue.h"
#include "./pcb.h"

Node* create_node(PCB* process) {
  Node* node = (Node*)malloc(sizeof(Node));
  node->process = process;
  node->next = NULL;
  return node;
}

Queue* create_queue() {
  Queue* queue = (Queue*)malloc(sizeof(Queue));
  queue->front = queue->rear = NULL;
  return queue;
}

int is_empty(Queue* queue) {
  return (queue->front == NULL);
}

void enqueue(Queue* queue, PCB* process) {
  Node* newNode = create_node(process);
  if (queue->front == NULL) {
    queue->front = queue->rear = newNode;
    return;
  }
  queue->rear->next = newNode;
  queue->rear = newNode;
}

void dequeue(Queue* queue, int process_id) {
  if (is_empty(queue)) return; 

  Node* temp = queue->front;
  Node* prev = NULL;

  if (temp != NULL && temp->process->process_id == process_id) {
    queue->front = queue->front->next;
    if (queue->front == NULL) {
      queue->rear = NULL;
    }
    free(temp);
    return;
  }

  while (temp != NULL && temp->process->process_id != process_id) {
    prev = temp;
    temp = temp->next;
  }

  if (temp == NULL) {
    return;
  }

  prev->next = temp->next;
  if (temp == queue->rear) {
    queue->rear = prev;
  }

  free(temp);
}

PCB* get_shortest_burst_process(Queue* queue) {
  Node* current = queue->front;
  Node* shortest = current;

  while (current != NULL) {
    if (current->process->remaining_time < shortest->process->remaining_time) {
      shortest = current;
    }
    current = current->next;
  }
  
  return shortest->process;
}