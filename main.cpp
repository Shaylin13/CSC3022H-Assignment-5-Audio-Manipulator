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
	
	//knowing that the format of the first 5 values must be the same we can assign them as below:
	
	int sampleRate = stoi(argv[2]);
	int sampleSize = stoi(argv[4]);
	int numberOfChannels = stoi(argv[6]);
	string outputFileName = "out";
	
	string inputFileName;
	string inputFileName2 = argv[argc-1];
	
	string option;
	
	string temp = argv[7];
	if(temp.compare("-o")==0)
	{
	 outputFileName = argv[8];
	 option = argv[9];
	 inputFileName = argv[10];
	 
	}
	else
	{
	 option = argv[7];
	 inputFileName = argv[8];
	}
	
	//deciding based on option
	
	
	
	
	//testing------------------------------------------------
	cout<<"input file name: "<<inputFileName<<endl;
	cout<<"input file name2: "<<inputFileName2<<endl;
	cout<<"sample rate: "<<sampleRate<<endl;
	cout<<"sample size: "<<sampleSize<<endl;
	cout<<"number of channels: "<<numberOfChannels<<endl;
	cout<<"output file name: "<<outputFileName<<endl;
	cout<<"option: "<<option<<endl;
	
	/*cout<<endl;
	for(int i =1;i<argc ; i++)
	{
	    cout<<i<<" "<<argv[i]<<endl;  
	}*/
	//--------------------------------------------------------
	
    
    string infile1 = "beez18sec_44100_signed_8bit_mono.raw";
    int sampleRate2 = 44100;
    //testing
    Sound<int8_t,1> sample1 (infile1, sampleRate2);//Create audio Sample #1,8bit
    //sample1.reverse();
    sample1.save("testsample");
    
    
    
	return 0;
}
