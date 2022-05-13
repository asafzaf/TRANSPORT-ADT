#include "schedule_station.h"
#include "schedule_station_list.h"

typedef struct schedule_station_s {
    char* station_name;
    int time;
    ScheduleStation next;
} ;

ScheduleStation schedule_station_create(const char *station, int time)
{
    ScheduleStationResult result;
    ScheduleStation new_station;
    new_station = (ScheduleStation*)malloc(sizeof(ScheduleStation*)); //list
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
    ScheduleStationList result_list;
    result_list = stationListRemoveCurrent(station); //list
    if ( result_list != SCHEDULE_STATION_SUCCESS ){
        return SCHEDULE_STATION_NULL_ARG;
    }
    return SCHEDULE_STATION_SUCCESS;
}

ScheduleStationResult schedule_station_get_name(ScheduleStation station, char **station_name)
{
    station->station_name = (char*)malloc(sizeof(*station_name)+1);
    if ( station->station_name == NULL ){
        return SCHEDULE_STATION_NULL_ARG;
    }
    strcpy(station->station_name, *station_name);
    if ( station->station_name == NULL ){
        return SCHEDULE_STATION_NULL_ARG;
    }
    return SCHEDULE_STATION_SUCCESS;
}

ScheduleStationResult schedule_station_get_time(ScheduleStation station, int *time)
{
    if ( *time < 0 ){
        return SCHEDULE_STATION_BAD_ARGUMENTS;
    }
    station->time = *time;
    return SCHEDULE_STATION_SUCCESS;
}
