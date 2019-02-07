CC = g++
CCFLAGS = -g -Wall -Werror

assign7: assign7.o Amenity.o utils.o AmenityFunctor.o
	$(CC) $(CCFLAGS) -o assign7 assign7.o Amenity.o utils.o AmenityFunctor.o

assign7.o : assign7.cc
	$(CC) $(CCFLAGS) -c -o assign7.o assign7.cc

Amenity.o : Amenity.cc Amenity.h
	$(CC) $(CCFLAGS) -c -o Amenity.o Amenity.cc

utils.o : utils.cc utils.h
	$(CC) $(CCFLAGS) -c -o utils.o utils.cc

AmenityFunctor.o: AmenityFunctor.cc AmenityFunctor.h
	$(CC) $(CCFLAGS) -c -o AmenityFunctor.o AmenityFunctor.cc

clean:
	-rm *.o assign7
