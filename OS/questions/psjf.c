//Pre-emptive shortest job first algorithm

#include <stdio.h>

// Struct for storing the process information
struct process {
  int process_no, at, bt, tat, flag, remain_t;
};
void main() {
  int num;
  printf("Enter the number of the processes\n");
  scanf("%d", &num);
  struct process list[num];

  //This loop will take input from the user for the processes
  for (int i = 0; i < num; i++) {
    list[i].process_no = i;
    printf("Enter the available time of process %d\n", i);
    scanf("%d", &list[i].at);
    printf("Enter the burst time for the process %d\n", i);
    scanf("%d", &list[i].bt);
    list[i].remain_t = list[i].bt;
    list[i].flag = 0;
    list[i].tat = 0;
  }

  //This loop will sort the processes according to their available time and if their at is same then according to their burst time
  for (int i = 0; i < num - 1; i++) {
    for (int j = i + 1; j < num; j++) {
      if (list[i].at > list[j].at) {
        struct process temp = list[i];
        list[i] = list[j];
        list[j] = temp;
      } else if (list[i].at == list[j].at) {
        if (list[i].bt > list[j].bt) {
          struct process temp = list[i];
          list[i] = list[j];
          list[j] = temp;
        }
      }
    }
  }
  //Main part, here we divide the overall execution in a time quantum of 1, i.e. every process will run for 1 time quantum and then check for the process with min burst time remaining and execute that process.
  int time = 0, count = 0, current = 0;
  for (int j = 0; count < num; j++) {
    time++;
    list[current].remain_t -= 1;
    if (list[current].remain_t == 0) {
      count++;
      list[current].flag = 1;
      list[current].tat = time - list[current].at;
    }
    current = -1;

    //This loop selects the process with the minimum burst remaining from the process pool
    for (int i = 0; i < num; i++) {
      if (list[i].flag == 0 && list[i].at <= time) {
        if (current == -1) {
          current = i;
        } else if (list[i].remain_t < list[current].remain_t) {
          current = i;
        }
      }
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
