#include "schedule.h"
#include "schedule_line_list.h"
#include "schedule_station.h"

typedef struct schedule_s {
  ScheduleLineList line_list;
  ScheduleStationList stations;
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
  lineListCreate(&(new_schedule->line_list));
  return new_schedule;
}

void scheduleDestroy(Schedule schedule) { return; }

ScheduleResult scheduleAddLine(Schedule schedule, ScheduleLineType type,
                               int number, const char *description,
                               double price) {

  ScheduleLine new_line;
  char desc1[] = "Saburban";
  char desc2[] = "Intercity";
  char desc3[] = "Direct";

  if (schedule == NULL) {
    return SCHEDULE_NULL_ARG;
  }

  if (type < 0 || type > 2) {
    return SCHEDULE_INVALID_LINE_TYPE;
  }

  if (number < 0 || number > 9999) {
    return SCHEDULE_INVALID_LINE_NUMBER;
  }

  if (type > 0 && (!strcmp(description, desc1) && !strcmp(description, desc2) &&
                   !strcmp(description, desc3))) {
    return SCHEDULE_INVALID_TRAIN_TYPE;
  }

  if (!is_price_valid(price)) {
    return SCHEDULE_INVALID_PRICE;
  }

  if (lineListFind(schedule->line_list, number) == LINE_LIST_SUCCESS) {
    return SCHEDULE_LINE_ALREADY_EXISTS;
  }

  // good to go
  new_line = schedule_line_create(type, number, description, price);
  if (new_line == NULL) {
    return SCHEDULE_OUT_OF_MEMORY;
  }

  lineListGotoHead(schedule->line_list);
  lineListInsertFirst(schedule->line_list, new_line);

  return SCHEDULE_SUCCESS;
}

ScheduleResult scheduleRemoveLine(Schedule schedule, int number) { return 0; }

ScheduleResult scheduleAddStationToLine(Schedule schedule, int number,
                                        const char *station, int time) {

  StationListResult station_result;
  ScheduleLineResult line_result;
  ScheduleLine curr_line;
  ScheduleStation curr_station;
  ScheduleStationList list_of_stations;
  int length;

  if (schedule == NULL) {
    return SCHEDULE_NULL_ARG;
  }

  if (station == NULL) {
    return SCHEDULE_NULL_ARG;
  }

  if (number < 0 || number > 9999) {
    return SCHEDULE_INVALID_LINE_NUMBER;
  }

  if (time < 0) {
    return SCHEDULE_INVALID_TIME;
  }

  lineListFind(schedule->line_list, number);
  if (line_result == LINE_LIST_FAIL) {
    return SCHEDULE_LINE_DOESNT_EXIST;
  }

  lineListGetCurrent(schedule->line_list, &curr_line); // find and get the line
  if (line_result == LINE_LIST_FAIL) {
    return SCHEDULE_NO_LINES;
  }
    curr_station = schedule_station_create(station, time);
    if (curr_station == NULL) {
      return SCHEDULE_NULL_ARG;
    }
    schedule_line_get_stations(curr_line, &list_of_stations);
    length = stationListGetNumElements(list_of_stations);
    stationListGotoHead(list_of_stations);
  
  for(int i = 0 ; i < length ; i++){
    stationListGotoNext(list_of_stations);
  }

  station_result = stationListGetCurrent(
      schedule->stations, &curr_station); // find and get the station
  line_result = schedule_line_add_station(curr_line, curr_station);
  return SCHEDULE_SUCCESS;
}

ScheduleResult scheduleRemoveStationFromLine(Schedule schedule, int number,
                                             int index) {
  ScheduleLine line;
  ScheduleStationList station_list;
  LineListResult line_result;
  StationListResult station_result;

  if (schedule == NULL) {
    return SCHEDULE_NULL_ARG;
  }

  if (number < 0 || number > 9999) {
    return SCHEDULE_INVALID_LINE_NUMBER;
  }

  if (index < 0) {
    return SCHEDULE_STATION_DOESNT_EXIST;
  }

  line_result = lineListFind(schedule->line_list, number);
  if (line_result == LINE_LIST_FAIL) {
    return SCHEDULE_LINE_DOESNT_EXIST;
  }
  line_result = lineListGetCurrent(schedule->line_list, &line);
  schedule_line_get_stations(line, &station_list);
  stationListGotoHead(station_list);

  if (index == -1) {
    index = stationListGetNumElements(station_list);
  }

  for (int i = 0; i < index; i++) {
    stationListGotoNext(station_list);
  }
  stationListRemoveCurrent(station_list);
  return SCHEDULE_SUCCESS;
}

ScheduleResult scheduleReportStationsForLine(Schedule schedule, int number) {
  return 0;
}

ScheduleResult scheduleReportLines(Schedule schedule, ScheduleLineType type) {
  return 0;
}

ScheduleResult scheduleReportLinesBetweenStations(Schedule schedule,
                                                  const char *from,
                                                  const char *to) {
  return 0;
}
