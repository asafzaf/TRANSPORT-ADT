#include "schedule_line.h"

typedef struct schedule_line_s {

  int number;
  double price;
  char *description;
  ScheduleLineType type;
  ScheduleStationList stations_list;

} schedule_line_s;

ScheduleLine schedule_line_create(ScheduleLineType type, int number,
                                  const char *description, double price) {

  ScheduleLine new_line;
  StationListResult station_result;  
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
  station_result = stationListCreate(&(new_line->stations_list));
  if(station_result == STATION_LIST_OUT_OF_MEMORY) {
    return NULL;
  }
  return new_line;
}

ScheduleLineResult schedule_line_destroy(ScheduleLine line){


  return 0;
}

ScheduleLineResult schedule_line_get_stations(ScheduleLine line, ScheduleStationList *stations){
  if(line == NULL || stations == NULL) {
    return SCHEDULE_LINE_BAD_ARGUMENTS;
  }
  *stations = line->stations_list;
   return SCHEDULE_LINE_SUCCESS;
}

ScheduleLineResult schedule_line_add_station(ScheduleLine line, ScheduleStation station){
  ScheduleLineResult line_result;
  StationListResult station_result;
  ScheduleStationList curr_station;
  char *station_name;
  int list_length;

  line_result = schedule_line_get_stations(line, &curr_station);
  if(line_result != SCHEDULE_LINE_SUCCESS) {
    return line_result;
  }
  list_length =  stationListGetNumElements(curr_station);
/*   if(list_length == 0) {
    lineListInsertFirst(curr_station,station);
    return SCHEDULE_LINE_SUCCESS;
  }
  for(int i = 0; i < list_length; i++) {
    lineListGotoNext(curr_station);
  } */
  

  station_result = stationListInsertLast(curr_station, station);
  if(station_result != SCHEDULE_LINE_SUCCESS) {
    return line_result;
  }
  
  return SCHEDULE_LINE_SUCCESS;

}


ScheduleLineResult schedule_line_get_details(ScheduleLine line,
                                             ScheduleLineType *type /* out */,
                                             int *number /* out */,
                                             char **description /* out */,
                                             double *price /* out */){

  if(type != NULL||number != NULL||description != NULL||price != NULL||line == NULL){
    return SCHEDULE_LINE_BAD_ARGUMENTS;
  }
  
  *type = line->type;
  *number = line->number;
  *description = line->description;
  *price = line->price;


  return 0;
                                             }

  int is_price_valid(float price) {
  price *= 1000;
  if ((int)price % 10) {
    return 0;
  }
  return 1;
}
