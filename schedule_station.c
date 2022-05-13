#include "schedule_station.h"

typedef struct schedule_station_s{
    int number;
    int time;
    char *name;
}station;

ScheduleStation schedule_station_create(const char *station, int time){
    return NULL;
}

ScheduleStationResult schedule_station_destroy(ScheduleStation station){
    return 0;
}

ScheduleStationResult schedule_station_get_name(ScheduleStation station, char **station_name){
    return 0;
}

ScheduleStationResult schedule_station_get_time(ScheduleStation station, int *time){
    return 0;
}

