// Priority based algorithm (Pre-emptive)
#include <stdio.h>

// Structure to store the process details
struct process {
  int process_no, at, bt, priority, tat, flag, remain_t;
};

void main() {
  int num;
  printf("Enter the number of processes\n");
  scanf("%d", &num);
  struct process list[num];

  // Loop will receive the process details from the user
  for (int i = 0; i < num; i++) {
    list[i].process_no = i;
    printf("Enter the available time for the process %d\n", i);
    scanf("%d", &list[i].at);
    printf("Enter the burst time for the process %d\n", i);
    scanf("%d", &list[i].bt);
    list[i].remain_t = list[i].bt;
    printf("Enter the priority of the process\n");
    scanf("%d", &list[i].priority);
    list[i].tat = 0;
    list[i].flag = 0;
  }

  // Loop will sort the processes according to their available time and if their
  // available time is same then the processes are sorted according to their
  // priority.
  for (int i = 0; i < num - 1; i++) {
    for (int j = i + 1; j < num; j++) {
      if (list[i].at > list[j].at) {
        struct process temp = list[j];
        list[j] = list[i];
        list[i] = temp;
      } else if (list[i].at == list[j].at) {
        if (list[i].priority > list[j].priority) {
          struct process temp = list[i];
          list[i] = list[j];
          list[j] = temp;
        }
      }
    }
  }

//Here the chosen process from the below loop is run in a sequence of 1-1 ms, the process executed is the process at the index 0 of the list array, (as it will be having highest priority) for 1 ms, and then the process chosen by the below loop will be given command and the process chosen by it will be executed and so on.
  int count = 0, current = 0, time = 0;
  for (int i = 0; count < num; i++) {
    printf("lol\t%d\n", list[current].process_no);
    time += 1;
    list[current].remain_t -= 1;
    if (list[current].remain_t == 0) {
      list[current].flag = 1;
      list[current].tat = time - list[current].at;
      count++;      
    }
    current = -1;

    //This loop selects a process whose arrival time is less than or equal to the current time and checks the priority, the process with the highest priority (i.e. smaller in numerical value) is chosen for execution
    for (int j = 0; j < num; j++) {
      if (list[j].flag == 0 && list[j].at <= time) {
        if (current == -1) {
          current = j;
          printf("%d\n", list[current].process_no);
        } else if (list[j].priority < list[current].priority) {
          current = j;
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
  printf("No.\tAT\tBT\tRT\tTAT\tWT\n");
  for (int i = 0; i < num; i++) {
    int temp = list[i].tat - list[i].bt;
    printf("%d\t%d\t%d\t%d\t%d\t%d", list[i].process_no, list[i].at, list[i].bt,
           list[i].remain_t, list[i].tat, temp);
    printf("\n");
  }
}
