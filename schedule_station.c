#include "schedule_station.h"
#include "schedule_station_list.h"

typedef struct schedule_station_s {
    char* station_name;
    int time;
    ScheduleStation next;
}  ;

ScheduleStation schedule_station_create(const char *station, int time)
{
    ScheduleStationResult result;
    ScheduleStation new_station;
    new_station = stationListCreate; //list
    result = schedule_station_get_name(new_station , station);
    if ( result != 0 ){
        free(new_station);
    }
    result = schedule_station_get_time(new_station , &time);
    if ( result != 0){
        free(new_station);  
    }
    return new_station;
}

ScheduleStationResult schedule_station_destroy(ScheduleStation station)
{
    return stationListDestroy(station); //list
}
ScheduleStationResult schedule_station_get_name(ScheduleStation station, char **station_name)
{
    station->station_name = (char*)malloc(sizeof(*station_name)+1);
    if ( station->station_name == NULL ){
        return 4;
    }
    strcpy(station->station_name, *station_name);
    if ( station->station_name == NULL ){
        return 1;
    }
    return 0;
}
ScheduleStationResult schedule_station_get_time(ScheduleStation station, int *time)
{
    if ( *time < 0 ){
        return 2;
    }
    station->time = *time;
    return 0;
}
