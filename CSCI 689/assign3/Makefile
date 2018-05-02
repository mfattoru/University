CC = g++
CCFLAGS = -Wall -O

assign3 : assign3.o Athlete.o Country.o Sport.o Event.o
	$(CC) -o assign3 $(CCFLAGS) -Werror assign3.o Athlete.o Country.o Sport.o Event.o
assign3.o: assign3.cc
	$(CC) $(CCFLAGS) -c -Werror assign3.cc
Athlete.o: Athlete.cc
	$(CC) $(CCFLAGS) -c -Werror Athlete.cc
Country.o: Country.cc
	$(CC) $(CCFLAGS) -c -Werror Country.cc
Sport.o: Sport.cc
	$(CC) $(CCFLAGS) -c -Werror Sport.cc
Event.o: Event.cc
	$(CC) $(CCFLAGS) -c -Werror Event.cc
clean:
	-rm *.o assign3
