CC = g++
CCFLAGS = -Wall -O

assign1 : assign1.o
	$(CC) $(CCFLAGS) -o assign1 assign1.o

# I had to comment the dependency on assign1.h.gch because the precompiled
# header file would exceed the allowed quota on the turing/hopper machine
# Commenting the line will let the program use the .h file instead of the
# precompiled one
assign1.o : #assign1.h.gch
	$(CC) -c $(CCFLAGS) -Werror assign1.cc

assign1.h.gch :
	$(CC) -c $(CCFLAGS) -Werror assign1.h

clean :
	-rm assign1 *.o *.gch
