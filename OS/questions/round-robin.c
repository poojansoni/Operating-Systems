// round-robin algorithm
#include <math.h>
#include <stdio.h>

// structure to store the process details
struct process {
  int process_no, at, bt, flag, tat, remain_t;
};

void main() {
  int num, tq, size = 0;
  printf("Enter the number of processes\n");
  scanf("%d", &num);
  printf("Enter the time quantum\n");
  scanf("%d", &tq);
  struct process list[num];

  // Loop will receive details for all the processes
  for (int i = 0; i < num; i++) {
    list[i].process_no = i;
    printf("Enter the available time for the process %d\n", i);
    scanf("%d", &list[i].at);
    printf("Enter the burst tie for the proces %d\n", i);
    scanf("%d", &list[i].bt);
    size += list[i].bt;
    list[i].remain_t = list[i].bt;
    list[i].flag = 0;
    list[i].tat = 0;
  }

  // This loop will sort the processes according to their available time
  for (int i = 0; i < num - 1; i++) {
    for (int j = i + 1; j < num; j++) {
      if (list[i].at > list[j].at) {
        struct process temp = list[i];
        list[i] = list[j];
        list[j] = temp;
      }
    }
  }
  // Here size is the computed size of the queue for the processes in
  // process_queue
  size = size / tq + 1;
  int process_queue[size];
  // printf("%d", size);
  int count = 0, time = 0, current = 0, old_time = -1, index = 0, running = 0;

  // Here we execute the first process and see if its burst time completed or
  // not, if completed then its flag is set to one and its tat is calculated and
  // if not it is added to the process queue. Also, before inserting the current
  // running process to the queue, we first insert the newly available process
  // into the queue, which got available between the the current time quantum
  // period i.e current time - old time. The next execution process for execution
  // is chosen from this queue.
  for (int i = 0; count < num; i++) {
    time += tq;
    list[current].remain_t -= tq;
    if (list[current].remain_t <= 0) {
      time += list[current].remain_t;
      count++;
      list[current].flag = 1;
      list[current].tat = time - list[current].at;
    }
    for (int j = 1; j < num; j++) {
      if (list[j].at <= time && list[j].flag == 0 && list[j].at > old_time) {
        process_queue[index++] = j;
      }
    }
    if (list[current].flag == 0) {
      process_queue[index++] = current;
    }
    current = process_queue[running++];
    old_time = time;
  }

  // Again sorting the process according to its number
  for (int i = 0; i < num - 1; i++) {
    for (int j = i + 1; j < num; j++) {
      if (list[i].process_no > list[j].process_no) {
        struct process temp = list[i];
        list[i] = list[j];
        list[j] = temp;
      }
    }
  }

  // For displaying the result
  printf("No.\tAT\tBT\tTAT\tWT\n");
  for (int i = 0; i < num; i++) {
    int temp = list[i].tat - list[i].bt;
    printf("%d\t%d\t%d\t%d\t%d", list[i].process_no, list[i].at, list[i].bt,
           list[i].tat, temp);
    printf("\n");
  }
}