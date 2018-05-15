//PDYSHA009 main.cpp
#include "Sound.h"
#include <iostream>
#include <string>

using namespace std;
using namespace PDYSHA009;

int main(int argc, char* argv[])
{

	cout << "Sound processing initiated"<<endl;
	cout<<"\n";
	
	int pos =1;
	string inputFileName;
	string outputFileName;
	int sampleSize;
	int sampleRate;
	int numberOfChannels;
	
    
    string infile1 = "beez18sec_44100_signed_8bit_mono.raw";
    int sampleRate = 44100;
    //testing
    Sound<int8_t,1> sample1 (infile1, sampleRate);//Create audio Sample #1,8bit
    //sample1.reverse();
    sample1.save("testsample");
    
    
    
	return 0;
}
