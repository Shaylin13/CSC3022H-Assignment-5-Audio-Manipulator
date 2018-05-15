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
		
add: 
		./driver -r 44100 -b 8 -c 1 -add file1.raw file2.raw
		
cut: 
		./driver -r 44100 -b 8 -c 1 -cut 0 100000 file1.raw
		
radd: 
		./driver -r 44100 -b 8 -c 1 -radd 0 100000 0 100000 file1.raw file2.raw
		
cat: 
		./driver -r 44100 -b 8 -c 1 -cat file1.raw file2.raw
		
v: 
		./driver -r 44100 -b 8 -c 1 -v 10 10 file1.raw
		
