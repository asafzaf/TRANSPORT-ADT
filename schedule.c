#include "schedule.h"
#include "schedule_line_list.h"

typedef struct schedule_s {
  ScheduleLineList line_list;
} schedule;

Schedule scheduleCreate() {

  Schedule new_schedule;
   // creating a new transport system
  new_schedule = (Schedule)malloc(sizeof(schedule));
  if (new_schedule == NULL) {
    printf("ERROR\n");
    return NULL;
  }
  // creating the linked list with error as return value
  lineListCreate(&new_schedule->line_list); 
  return new_schedule;
}

ScheduleResult scheduleAddLine(Schedule schedule, ScheduleLineType type,
                               int number, const char *description,
                               double price) {
  ScheduleResult result;
  ScheduleLine new_line;

  new_line = schedule_line_create(type,number,description,price);
  
  lineListInsertFirst(schedule->line_list,new_line);
  return result;
}