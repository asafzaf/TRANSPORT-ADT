#include "schedule_line.h"

typedef struct schedule_line_s {

  int number;
  double price;
  char *description;
  ScheduleLineType type;
  ScheduleLine next;

} schedule_line_s;

ScheduleLine schedule_line_create(ScheduleLineType type, int number,
                                  const char *description, int price) {

  ScheduleLine new_line;
    
  new_line = (ScheduleLine)malloc(sizeof(schedule_line_s));
  if (new_line == NULL) {
    printf("NULL\n");
    return NULL;
  }
  new_line->description = (char *)malloc(strlen(description) + 1);
  if (new_line->description == NULL) {
    printf("NULL\n");
    return NULL;
  }
  strcpy(new_line->description, description);
  new_line->price = price;
  new_line->type = type;
  new_line->number = number;

  return new_line;
}