output: functions.o main.o
	g++ -g functions.o main.o -o main.exe

functions.o: functions.cpp
	g++ -c -g functions.cpp

main.o: main.cpp
	g++ -c -g main.cpp

target: dependencies
	action