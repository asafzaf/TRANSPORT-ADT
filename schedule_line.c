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

ScheduleStation curr_station;
  if(line == NULL) {
    return SCHEDULE_LINE_BAD_ARGUMENTS;
  }
if(line->stations_list != NULL){

do{
  stationListGotoHead(line->stations_list);
  stationListGetCurrent(line->stations_list, &curr_station);
  stationListRemoveCurrent(line->stations_list);
  schedule_station_destroy(curr_station);
}
while(stationListGotoNext(line->stations_list) == STATION_LIST_SUCCESS);
}

free(line->description);
free(line);

  return SCHEDULE_LINE_SUCCESS;
}

ScheduleLineResult schedule_line_get_stations(ScheduleLine line, ScheduleStationList *stations){
  if(line == NULL || stations == NULL) {
    return SCHEDULE_LINE_BAD_ARGUMENTS;
  }
  *stations = line->stations_list;
   return SCHEDULE_LINE_SUCCESS;
}

ScheduleLineResult schedule_line_add_station(ScheduleLine line, ScheduleStation station){
  ScheduleLineResult line_result = SCHEDULE_LINE_SUCCESS;
  StationListResult station_result = STATION_LIST_SUCCESS;
  ScheduleStationList curr_station;
  
  int list_length;
  curr_station = line->stations_list;
  if(line->stations_list == NULL) {
    stationListGotoHead(line->stations_list);
    stationListInsertFirst(line->stations_list, station);

  }
  list_length =  stationListGetNumElements(curr_station);
   if(list_length == 0) {
    stationListGotoNext(curr_station);
    return SCHEDULE_LINE_SUCCESS;
  }
  for(int i = 0; i < list_length; i++) {
    stationListGotoNext(curr_station);
  } 
  
  station_result = stationListInsertLast(curr_station, station);
  if(station_result != STATION_LIST_SUCCESS ) {
    return line_result;
  }
  
  return SCHEDULE_LINE_SUCCESS;

}


ScheduleLineResult schedule_line_get_details(ScheduleLine line,
                                             ScheduleLineType *type /* out */,
                                             int *number /* out */,
                                             char **description /* out */,
                                             double *price /* out */){

                                          
  if(line == NULL){
    return SCHEDULE_LINE_BAD_ARGUMENTS;
  }

  *type = line->type;
  *number = line->number;
  *description = line->description;
  *price = line->price;


  return 0;
}
ScheduleLineResult schedule_line_go_to_last_station(ScheduleStationList station_list, ScheduleStation *first_station,ScheduleStation *last_station){
  
  int list_length;

  if(station_list == NULL ){
    return SCHEDULE_LINE_NULL_ARG;
  }

  stationListGotoHead(station_list);
  stationListGetCurrent(station_list, first_station);
  list_length = stationListGetNumElements(station_list);
  for(int i = 0; i < list_length; i++) {
    stationListGotoNext(station_list);
  }
  stationListGetCurrent(station_list, last_station);
  
  return SCHEDULE_LINE_SUCCESS;
}

  int is_price_valid(float price) {
  price *= 1000;
  if ((int)price % 10) {
    return 0;
  }
  return 1;
}




