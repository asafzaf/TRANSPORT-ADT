prog: schedule_line.o schedule_station.o schedule.o main.o 
	gcc -std=c99 -Wall -pedantic-errors *.c -L. -lprog2 -o scheduler.exe
	del *.o 
	./scheduler.exe
schedule_line.o: schedule_line.c schedule_line.h
	gcc -c schedule_line.c
schedule_station.o: schedule_station.c schedule_station.h
	gcc -c schedule_station.c
schedule.o: schedule.c schedule.h
	gcc -c schedule.c
main.o: main.c
	gcc -c main.c



clean:
	del schedule_line.o schedule_station.o schedule.o
	