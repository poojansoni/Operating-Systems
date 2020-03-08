//Non-preemptive Shortest Job First Algorithm
#include <stdio.h>

//Creating a structure for storing the process details
struct process {
  int process_no,at,bt,tat,flag;
};
void main() {
  int num;
  struct process list[10];
  printf("Enter the no. of processes\n");
  scanf("%d", &num);

  //Loop for getting values for processes from user
  for (int i = 0; i < num; i++) {
    list[i].process_no = i + 1;
    printf("Enter the available time for the process %d\n", i);
    scanf("%d", &list[i].at);
    printf("Enter the burst time for the process %d\n", i);
    scanf("%d", &list[i].bt);
    list[i].flag = 0;
    list[i].tat = 0;
  }

  //This loop will sort the process according to the arrival time of the processes and if the processes have the same arrival time, they will get sorted according to burst time.
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

  //Main part, as we know from the above loop that the first process will be the first to execute so we add its busting time to the global time, and then search for the next process whose arrival time is less than or equal to the global time and its burst time is minimum, and virtually execute it by setting its flag to 1, and increasing the global time according to its burst time.
  int time = 0, count = 0, min = 0;
  while (count < num) {
    time += list[min].bt;
    list[min].flag = 1;
    list[min].tat = time - list[min].at;
    min = -1;
    for (int i = 0; i < num; i++) {
      if (list[i].at <= time && list[i].flag == 0) {
        if (min == -1) {
          min = i;
        } else if (list[i].bt < list[min].bt) {
          min = i;
        }
      }
    }
    count++;
  }

  //Again sorting the process according to its number
  for (int i = 0; i < num - 1; i++) {
    for (int j = i + 1; j < num; j++) {
      if (list[i].process_no > list[j].process_no) {
        struct process temp = list[i];
        list[i] = list[j];
        list[j] = temp;
      }
    }
  }

  //For displaying the result
  printf("No.\tAT\tBT\tTAT\tWT\n");
  for (int i = 0; i < num; i++) {
    int temp = list[i].tat - list[i].bt;
    printf("%d\t%d\t%d\t%d\t%d", list[i].process_no, list[i].at, list[i].bt,
           list[i].tat,temp);
    printf("\n");
  }
}
