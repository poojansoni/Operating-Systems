// Here the multi-level scheduling algorithm has three queues first runs on
// P-SJF, second on round robin of predefined time constant of 2ms, and // third
// on P-FCFS basis. So let's begin to code.

#include <stdio.h>
#include <stdlib.h>
// structure for storing the process details
struct process {
  int process_no, at, bt, tat, flag, remain_t, priority, queue_no;
};

void main() {
  int num, queue_1_size = 0, queue_2_size = 0, queue_3_size = 0, size = 0;
  printf("Enter the no. of processes\n");
  scanf("%d", &num);
  struct process list[num];

  // This loop will take the details of the processes from the user
  for (int i = 0; i < num; i++) {
    list[i].process_no = i;
    printf("Enter the at for process %d\n", i);
    scanf("%d", &list[i].at);
    printf("Enter the burst time of the process %d\n", i);
    scanf("%d", &list[i].bt);
    list[i].remain_t = list[i].bt;
    printf("Enter the priority of the process %d\n", i);
    scanf("%d", &list[i].priority);
    printf("Enter the queue no of the process %d\n", i);
    scanf("%d", &list[i].queue_no);
    if (list[i].queue_no == 1)
      queue_1_size++;
    else if (list[i].queue_no == 2)
      queue_2_size++;
    else if (list[i].queue_no == 3)
      queue_3_size++;
    else {
      printf("Wrong queue no. inserted\n");
    }
    list[i].flag = 0;
  }
  int queue1[queue_1_size], queue2[queue_2_size], queue3[queue_3_size];
  int x = 0, y = 0, z = 0;  // x,y,z are indexes for queue 1,2,3 respectively

  // This loop is used to distribute the processes to their respective queues
  for (int i = 0; i < num; i++) {
    if (list[i].queue_no == 1) {
      queue1[x++] = i;
    } else if (list[i].queue_no == 2) {
      queue2[y++] = i;
      size += list[i].bt;
    } else {
      queue3[z++] = i;
    }
  }

  // This loop arranges the process of the first queue first according to the
  // available time and if the available time is same then according to the
  // burst time
  for (int i = 0; i < queue_1_size - 1; i++) {
    for (int j = i + 1; j < queue_1_size; j++) {
      if (list[queue1[i]].at > list[queue1[j]].at) {
        int temp = queue1[j];
        queue1[j] = queue1[i];
        queue1[i] = temp;
      } else if (list[queue1[i]].at == list[queue1[j]].at) {
        if (list[queue1[i]].bt > list[queue1[j]].bt) {
          int temp = queue1[j];
          queue1[j] = queue1[i];
          queue1[i] = temp;
        }
      }
    }
  }
  printf("%d\n", list[queue1[0]].bt);

  // This loop is used to sort the processes in the queue2 according to the
  // available time
  for (int i = 0; i < queue_2_size - 1; i++) {
    for (int j = i + 1; j < queue_2_size; j++) {
      if (list[queue2[i]].at > list[queue2[j]].at) {
        int temp = queue2[i];
        queue2[i] = queue2[j];
        queue2[j] = temp;
      }
    }
  }

  // This loop is used to sort the processes in the queue3 accoeding to the
  // available time
  for (int i = 0; i < queue_3_size - 1; i++) {
    for (int j = i + 1; j < queue_3_size; j++) {
      if (list[queue3[i]].at > list[queue3[j]].at) {
        int temp = queue3[i];
        queue3[i] = queue3[j];
        queue3[j] = temp;
      }
    }
  }

  int count = 0, current = 0, time = 0, tq = 2, old_time = -1, index = 0,
      index2 = 0, running = 0;
  size = (int)size / tq + 1;
  int process_queue[size];
  for (int i = 0; count < num; i++) {
    current = -1;
    //Picking up process from first queue
    for (int i = 0; i < num; i++) {
      if (list[i].flag == 0 && list[i].at <= time) {
        if (current == -1) {
          current = i;
        } else if (list[i].remain_t < list[current].remain_t) {
          current = i;
        }
      }
    }
    
    //Checking for process in 2nd queue if process is not available in 1st
    if (current == -1) {
      for (int j = 1; j < num; j++) {
        if (list[j].at <= time && list[j].flag == 0 && list[j].at > old_time) {
          process_queue[index++] = j;
        }
      }
      if (list[current].flag == 0) {
        process_queue[index++] = current;
      }
      current = process_queue[running++];
    }

    //Checking for process in third queue if a process is not available in 2nd
    if (current == -1) {
      current = queue3[index2++];
    }
    old_time = time;

    //Execution of selected process for 1 time stamp
    if (list[current].queue_no == 2) {
      time += tq;
      list[current].remain_t -= tq;
    } else {
      time++;
      list[current].remain_t -= 1;
    }
    if (list[current].remain_t <= 0) {
      time += list[current].remain_t;
      list[current].flag = 1;
      list[current].tat = time - list[current].at;
      count++;
    }
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