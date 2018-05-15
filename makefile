CC=g++
CCFLAGS=-std=c++11
LIBS=-lm

driver: main.o
		$(CC) $(CCFLAGS) main.o -o driver $(LIBS)

				
driver.o: main.cpp
		$(CC) $(CCFLAGS) main.cpp -c


		
clean: 
		@rm -f *.o
		@rm -f driver
		
test1: 
		./driver -r 44100 -b 8 -c 1 -o output -add file1.raw file2.raw
		
test2: 
		./driver -r 44100 -b 8 -c 1 -add file1.raw file2.raw
		
		
