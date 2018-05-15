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
	int optionIndex;
	
	string temp = argv[7];
	if(temp.compare("-o")==0)
	{
	 outputFileName = argv[8];
	 option = argv[9];
	 optionIndex=9;
	 //inputFileName = argv[10];
	 
	}
	else
	{
	 option = argv[7];
	 optionIndex=7;
	 //inputFileName = argv[8];
	}
	
	//deciding based on option

	if(option.compare("-add") == 0)//if the option is -add================
	{
	    cout<< option <<" function implemented"<<endl;
	    inputFileName = argv[optionIndex+1];
	        
	   if(sampleSize == 8)
	    {
	        if(numberOfChannels == 1)
	        {
	            Sound<int8_t,1> sound1 (inputFileName, sampleRate);
	            Sound<int8_t,1> sound2 (inputFileName2, sampleRate);
	            (sound1 + sound2).save(outputFileName);
	        }
	        else//2 channels
	        {
	            Sound<int8_t,2> sound1 (inputFileName, sampleRate);
	            Sound<int8_t,2> sound2 (inputFileName2, sampleRate);
	            (sound1 + sound2).save(outputFileName);
	        }
	    }
	    else// sample size = 16 bits
	    {
	        if(numberOfChannels == 1)
	        {
	            Sound<int16_t,1> sound1 (inputFileName, sampleRate);
	            Sound<int16_t,1> sound2 (inputFileName2, sampleRate);
	            (sound1 + sound2).save(outputFileName);
	        }
	        else//2 channels
	        {
	            Sound<int16_t,2> sound1 (inputFileName, sampleRate);
	            Sound<int16_t,2> sound2 (inputFileName2, sampleRate);
	            (sound1 + sound2).save(outputFileName);
	        }
	    }

	}//===================================================================
	else if(option.compare("-cut") == 0)
	{
	    cout<< option <<" function implemented"<<endl;
	    //cout<<argv[optionIndex+1]<<endl;
	    //cout<<argv[optionIndex+2]<<endl;
	    inputFileName = argv[optionIndex+3];
	    
	    int start = stoi(argv[optionIndex+1]);
	    int end = stoi(argv[optionIndex+2]);
	    pair<int, int> boundaries = make_pair(start, end);
	    
	    if(sampleSize == 8)
	    {
	        if(numberOfChannels == 1)
	        {
	            Sound<int8_t,1> sound1 (inputFileName, sampleRate);
	            (sound1^boundaries).save(outputFileName);
	        }
	        else//2 channels
	        {
	            Sound<int8_t,2> sound1 (inputFileName, sampleRate);
	            (sound1^boundaries).save(outputFileName);
	        }
	    }
	    else// sample size = 16 bits
	    {
	        if(numberOfChannels == 1)
	        {
	            Sound<int16_t,1> sound1 (inputFileName, sampleRate);
	            (sound1^boundaries).save(outputFileName);
	        }
	        else//2 channels
	        {
	            Sound<int16_t,2> sound1 (inputFileName, sampleRate);
	            (sound1^boundaries).save(outputFileName);
	        }
	    }
	}//==========end of cut===============================================
	
	else if(option.compare("-radd") == 0)
	{
	    cout<< option <<" function implemented"<<endl;
	    
	        /*int range1 = stoi (argv[optionIndex+1]);
			int range2 = stoi (argv[optionIndex+2]);
			int subRange1 = stoi (argv[optionIndex+3]);
            int subRange2 = stoi (argv[optionIndex+4]);  
            
            inputFileName = argv[optionIndex+5]; 
	    
	    Sound<int8_t,1> sound1 (inputFileName, sampleRate);
	    Sound<int8_t,1> sound2 (inputFileName2, sampleRate);
        (sound1.selectRange(range1 * sampleRate, range2 * sampleRate) + sound2.selectRange(subRange1, subRange2)).save(outputFileName);*/
	}
	else if(option.compare("-cat") == 0)
	{
	    cout<< option <<" function implemented"<<endl;
	    inputFileName = argv[optionIndex+1];
	        
	   if(sampleSize == 8)
	    {
	        if(numberOfChannels == 1)
	        {
	            Sound<int8_t,1> sound1 (inputFileName, sampleRate);
	            Sound<int8_t,1> sound2 (inputFileName2, sampleRate);
	            (sound1 | sound2).save(outputFileName);
	        }
	        else//2 channels
	        {
	            Sound<int8_t,2> sound1 (inputFileName, sampleRate);
	            Sound<int8_t,2> sound2 (inputFileName2, sampleRate);
	            (sound1 | sound2).save(outputFileName);
	        }
	    }
	    else// sample size = 16 bits
	    {
	        if(numberOfChannels == 1)
	        {
	            Sound<int16_t,1> sound1 (inputFileName, sampleRate);
	            Sound<int16_t,1> sound2 (inputFileName2, sampleRate);
	            (sound1 | sound2).save(outputFileName);
	        }
	        else//2 channels
	        {
	            Sound<int16_t,2> sound1 (inputFileName, sampleRate);
	            Sound<int16_t,2> sound2 (inputFileName2, sampleRate);
	            (sound1 | sound2).save(outputFileName);
	        }
	    }

	    
	}
	else if(option.compare("-v") == 0)
	{
	    cout<< option <<" function implemented"<<endl;
	    inputFileName = argv[optionIndex+3];
	    float lVol = stof(argv[optionIndex+1]);
	    float rVol = stof(argv[optionIndex+2]);
	    
	    
	    if(sampleSize == 8)
	    {
	        if(numberOfChannels == 1)
	        {
	            Sound<int8_t,1> sound1 (inputFileName, sampleRate);
	            (sound1 * make_pair(lVol, rVol)).save(outputFileName);
	        }
	        else//2 channels
	        {
	            Sound<int8_t,2> sound1 (inputFileName, sampleRate);
                (sound1 * make_pair(lVol, rVol)).save(outputFileName);
	        }
	    }
	    else// sample size = 16 bits
	    {
	        if(numberOfChannels == 1)
	        {
	            Sound<int16_t,1> sound1 (inputFileName, sampleRate);
	            (sound1 * make_pair(lVol, rVol)).save(outputFileName);
	        }
	        else//2 channels
	        {
	            Sound<int16_t,2> sound1 (inputFileName, sampleRate);
	            (sound1 * make_pair(lVol, rVol)).save(outputFileName);
	        }
	    }
	}
	else if(option.compare("-rev") == 0)
	{
	    cout<< option <<" function implemented"<<endl;
	    
	}
	else if(option.compare("-rms") == 0)
	{
	    cout<< option <<" function implemented"<<endl;
	}
	else if(option.compare("-norm") == 0)
	{
	    cout<< option <<" function implemented"<<endl;
	}
	
	//testing------------------------------------------------
	/*cout<<"input file name: "<<inputFileName<<endl;
	cout<<"input file name2: "<<inputFileName2<<endl;
	cout<<"sample rate: "<<sampleRate<<endl;
	cout<<"sample size: "<<sampleSize<<endl;
	cout<<"number of channels: "<<numberOfChannels<<endl;
	cout<<"output file name: "<<outputFileName<<endl;
	cout<<"option: "<<option<<endl;*/
	
	/*cout<<endl;
	for(int i =1;i<argc ; i++)
	{
	    cout<<i<<" "<<argv[i]<<endl;  
	}*/
	//--------------------------------------------------------
	
    
    /*string infile1 = "beez18sec_44100_signed_8bit_mono.raw";
    int sampleRate2 = 44100;
    //testing
    Sound<int8_t,1> sample1 (infile1, sampleRate2);//Create audio Sample #1,8bit
    //sample1.reverse();
    sample1.save("testsample");*/
    
    
    
	return 0;
}
