PDYSHA009

to compile open the terminal in the folder PDYSHA009
and type make

to run type ./driver and commands in the format asked in the assignment document

For the convinience of the tutors ive add commands to test each function in the make file

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
		
		========================================================================================================
		
		these have preset values to test on the files file1 & file2 which are two 8bit mono files
		I however encountered a problem, my template works for 16 bit and stereo (2 channels), however when
		called in the main if statements i get a floating point exception, I added a 2-channel test that runs 
		at the end of the main class to show that it does infact work despite the issue
		
		If you would like to further test it please edit end section:
		
		Sound<int8_t,2> soundx ("file3.raw", sampleRate);
        Sound<int8_t,2> soundy ("file4.raw", sampleRate);
        (soundx + soundy).save("soundx");
        
        the output is correct and I cant understand why when I run the exact same lines it doesnt work above
        sorry for the inconvinience.
        
        ========================================================================================================
        
        
        references
        https://codereview.stackexchange.com/questions/93176/ring-buffer-for-audio-processing-follow-up
        https://www.geeksforgeeks.org/templates-cpp/
        http://www.cplusplus.com/doc/oldtutorial/templates/
        https://stackoverflow.com/questions/49161854/reading-raw-audio-file
        https://www.quora.com/What-might-be-the-possible-causes-for-floating-point-exception-error-in-C++
        https://github.com/Shmosh001/CSC3022H-Assignment-5/blob/master/Audio.h
        https://github.com/jb155/CSC3022H_Assignment5
		

