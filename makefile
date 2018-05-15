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
		
rev: 
		./driver -r 44100 -b 8 -c 1 -rev file1.raw
		
rms: 
		./driver -r 44100 -b 8 -c 1 -rms file1.raw
		
norm: 
		./driver -r 44100 -b 8 -c 1 -norm 0.56 0.33 file1.raw
		
#the above are for mono sounds below are stereo sounds

test2: 
		./driver -r 44100 -b 8 -c 2 -o output -add file3.raw file4.raw
		
add2: 
		./driver -r 44100 -b 8 -c 2 -add file3.raw file4.raw
		
cut2: 
		./driver -r 44100 -b 8 -c 2 -cut 0 100000 file3.raw
		
radd2: 
		./driver -r 44100 -b 8 -c 2 -radd 0 100000 0 100000 file3.raw file4.raw
		
cat2: 
		./driver -r 44100 -b 8 -c 2 -cat file3.raw file4.raw
		
v2: 
		./driver -r 44100 -b 8 -c 2 -v 10 10 file3.raw
		
rev2: 
		./driver -r 44100 -b 8 -c 2 -rev file3.raw
		
rms2: 
		./driver -r 44100 -b 8 -c 2 -rms file3.raw
		
norm2: 
		./driver -r 44100 -b 8 -c 2 -norm 0.56 0.33 file3.raw
		
		
		
