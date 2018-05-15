
#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>//for data_vector
#include <algorithm>
#include <numeric>// for accumualate
#include <cmath>//for sqr and pow

namespace PDYSHA009{
	template <typename T, int numberOfChannels> class Sound {
	private:
		std::vector<T> data_vector;
		int sampleSize;
		int sampleRate;
		
	public:
	
		//main constructor
		Sound(std::string inFile, int sampleRate){
			this->sampleRate = sampleRate;
			this->sampleSize = (int)sizeof(T);
			
			//read in the file
			load(inFile);
		}
		 	
		//Copy Constructor
		Sound(const Sound & rhs){
			this->data_vector = rhs.data_vector;
			this->sampleSize = rhs.sampleSize;
			this->sampleRate = rhs.sampleRate;
			
		}
		
		//Move constructor
		Sound(Sound && rhs){
			this->data_vector = std::move(rhs.data_vector);
			this->sampleSize = rhs.sampleSize;
			this->sampleRate = rhs.sampleRate;
			
		}
		
		//Destructor (Default)
		~Sound() = default;
		
		//Operators
		//Copy Assignment Operator
		Sound &operator=(const Sound<T,1> & rhs){
			Sound<T,1>temp(rhs);			
			*this = std::move(rhs);			
			return *this;				
		}
		
		//Move Assignment Operator
		Sound  &operator=(Sound<T,1> && rhs){
			//copying
			this->data_vector = std::move(rhs.data_vector);
			this->sampleSize = rhs.sampleSize;
			this->sampleRate = rhs.sampleRate;
			
			
			//releasing
			rhs.sampleSize = 0;
			rhs.sampleRate = 0;
			
			
			return *this;
		}
		
		//concatination
		Sound &operator|(const Sound & rhs){
			data_vector.insert(data_vector.end(), rhs.data_vector.begin(), rhs.data_vector.end());
			return *this;
		}
		
		//* volume
		Sound & operator*(const std::pair<float, float> & volumeChange){
			for (int i = 0; i < data_vector.size(); i++){	//Step through of all audio data
				data_vector[i] *= volumeChange.first;	//this is mono....so only one of the two is needed
			}
			return *this;
		}
		
		//+ add
		Sound &operator+(const Sound & rhs){
			for (int i = 0; i < data_vector.size(); i++){	//Step through all the audio data
				data_vector[i] = clampSampleMax(data_vector[i] + rhs.data_vector[i]);
			}
			return *this;
		}
		
		//^ cut
		Sound &operator^(const std::pair<int,int> & cutBoundaries){
			std::vector<T> newVector;
			
			//if within boundaries add
			for (int i = 0; i < data_vector.size(); i++){
				if ((i >= cutBoundaries.first) && (i <= cutBoundaries.second)){
					newVector.push_back(data_vector[i]);
				}
			}
			
			
			data_vector = newVector;
			
			return *this;
		}
		
		
		
	
		//Read in file data from specified file mono version
		void load (std::string inFileName){
			std::ifstream infile(inFileName);
			
			
			if(!(infile.is_open())){
			
			    std::cout << "Unable to open file" << std::endl;
				
			}
			else//if file is open
			{
			
			    //get the file size
				infile.seekg (0, infile.end); 	
				long fileSize = infile.tellg();
				infile.seekg (0, infile.beg);
				
				//get the number of samples
				int numberOfSamples = (int) (fileSize / (sampleSize * numberOfChannels));
				
				
				data_vector.resize(numberOfSamples);
				
				for (int i = 0; i < data_vector.size(); i++){
					char charBuff[sampleSize];
					infile.read (charBuff, sampleSize);
					
					data_vector[i] = *(T *)charBuff;
				}
				
			}
			infile.close();
		}
		
		//Write to file	Mono version
		void save (std::string outputName){
			std::string fileName = outputName + "_" + std::to_string(sampleRate) + "_" + std::to_string(sampleSize * 8) + "_mono.raw";
			
			std::ofstream outfile(fileName, std::ios::binary | std::ios::out);
			
			if (!outfile.is_open()){
				std::cout << "Unable to save file" << std::endl;
			}else{
				outfile.write((char *)&data_vector[0], data_vector.size() * sampleSize);
			}
			outfile.close();
		}
		
		//Clamp sound
		T clampSampleMax(T audioSample){
			if (sampleSize == 1){
				return (audioSample > INT8_MAX) ? INT8_MAX : audioSample; 
			}else{
				return (audioSample > INT16_MAX) ? INT16_MAX : audioSample;
			}
		}
		
		//reverses the data_vector
		void reverse(){
			std::reverse(data_vector.begin(), data_vector.end());
		}
		
		//get a segment of data vec
		Sound & selectRange(int rangeStart, int rangeEnd){
			Sound * newSound = new Sound(*this);	
			
			newSound->data_vector.clear();		
			newSound->data_vector.resize((unsigned long)(rangeEnd-rangeStart));	
			
			
			
			std::copy(data_vector.begin() + rangeStart, data_vector.begin() + rangeEnd, newSound->data_vector.begin());
			
			return *newSound;
		}
		
		
		std::vector <T> & getAudioData(){
			return data_vector;
		}
		
		//get rms
		float calcRMS(){
			float audioDataSizeInverse = 1/((float)data_vector.size());
			return std::sqrt(audioDataSizeInverse * std::accumulate(data_vector.begin(),
			data_vector.end(), 0,[] (T accum, T x) {return (accum + pow(x, 2));}));	
		}
		
		//normalizes to rms input
		Sound & normalize(float rms){
			NormalFunction normalF (calcRMS(), rms);
			Sound * tempAudio = new Sound(*this);
			std::transform(data_vector.begin(), data_vector.end(), tempAudio->data_vector.begin(), normalF);
			return * tempAudio;
		}
		
		
		class NormalFunction{
		public:
			float currentRMS;
			float targetRMS;
			
			NormalFunction(float curRMS, float tarRMS):currentRMS(curRMS), targetRMS(tarRMS){}
			
			T operator()(T inputAmpl){
				return (T) (inputAmpl*(targetRMS/currentRMS));
			}
		};
	};
        
	//stereo----------------------------------------------------------------------------------------------------------
	template <typename T> class Sound<T, 2> {
        private:
		std::vector<std::pair<T, T>> data_vector;
		int sampleSize;
		int sampleRate;
		
	public:
		
		//Constructor
		Sound(std::string fileName, int sampleRate) {
			load(fileName);
			this->sampleRate = sampleRate;
			this->sampleSize = (int)sizeof(T);
		}
		
		~Sound() = default;
		
		//Copy Constructor
		Sound(const Sound & rhs){
			this->data_vector = rhs.data_vector;
			this->sampleSize = rhs.sampleSize;
			this->sampleRate = rhs.sampleRate;
			
		}
		
		//Move Constructor
		Sound (Sound && rhs){
			this->data_vector = std::move(rhs.data_vector);
			this->sampleRate = rhs.sampleRate;
			this->sampleSize = rhs.sampleSize;
			
		}
		
		
		//Operators
		//Copy assign operator
		Sound &operator=(const Sound & rhs){
			Sound<T, 2> tempSound(rhs);
			*this = std::move(tempSound);
			return *this;
		}
		
		//Move assign operator
		Sound &operator=(Sound && rhs){
			this->data_vector = std::move(rhs.data_vector);
			this->sampleSize = rhs.sampleSize;
			this->sampleRate = rhs.sampleRate;
			
			rhs.sampleSize = 0;
			rhs.sampleRate = 0;
			
			
			return *this;
		}
		
		//concatination
		Sound &operator|(const Sound & rhs){
			data_vector.insert(data_vector.end(), rhs.data_vector.begin(), rhs.data_vector.end());
			return *this;
		}
		
		//* multiply volume
		Sound &operator*(const std::pair <float, float> & volumeChange){
			for (int i = 0; i < data_vector.size(); i++){	//Step through of all audio data
				data_vector[i] = std::make_pair(data_vector[i].first * volumeChange.first, data_vector[i].second * volumeChange.second);
			}
			return *this;
		}
		
		//add
		Sound &operator+(const Sound & rhs){
			for (int i = 0; i < data_vector.size(); i++){	//Step through all the audio data
				T leftClamp = clampSampleMax(data_vector[i].first + rhs.data_vector[i].first);
				T rightClamp = clampSampleMax(data_vector[i].second + rhs.data_vector[i].second);

				data_vector[i] = std::make_pair(leftClamp, rightClamp);
			}
			return*this;
		}
		
		//cut
		Sound &operator^(const std::pair<int,int> & cutBoundaries){
			std::vector<std::pair<T, T>> newVector;
			
			
			for (int i = 0; i < data_vector.size(); i++){
				if ((i >= cutBoundaries.first) && (i <= cutBoundaries.second)){
					newVector.push_back(data_vector[i]);
				}
			}
			
			data_vector = newVector;
			
			return *this;
		}
		
		void load(std::string inFileName){
			std::ifstream infile(inFileName);
			
			
			if(!(infile.is_open())){
				
				std::cout << "Unable to open file." << std::endl;
				
			}else{
			
			    //get file size
			    infile.seekg (0, infile.end); 	
				long fileSize = infile.tellg();	
				infile.seekg (0, infile.beg);
				
				//get the number of samples
				int numberOfSamples = (int) (fileSize / (sampleSize * 2));
				
				data_vector.resize((unsigned long)(numberOfSamples));	
				
				//store data
				for (int i = 0; i < numberOfSamples; i++){
					char charBuffLeft[sampleSize];
					infile.read (charBuffLeft, sampleSize);
					char charBuffRight[sampleSize];
					infile.read (charBuffRight,sampleSize);
					
					data_vector[i] = std::make_pair(*(T *)charBuffLeft, *(T *)charBuffRight);
				}
				
			}
			infile.close();
		}
		
		//Write to file	Stereo version
		void save(std::string outputName){
			
			std::string fileName = outputName + "_" + std::to_string(sampleRate) + "_" + std::to_string(sampleSize * 8) + "_stereo.raw";
			
			std::ofstream outfile(fileName, std::ios::binary | std::ios::out);
			
			if (!outfile.is_open()){
				std::cout << "Unable to save file" << std::endl;
			}
			else
			{
			    for (auto data : data_vector) {
					outfile.write((char *)&data.first, sampleSize);
					outfile.write((char *)&data.second, sampleSize);
				}
				
			}
			outfile.close();
		}
		
		//clamp sound
		T clampSampleMax(T audioSample){
			if (sampleSize == 1){
				return (audioSample > INT8_MAX) ? INT8_MAX : audioSample; 
			}else{
				return (audioSample > INT16_MAX) ? INT16_MAX : audioSample;
			}
		}
		
		
		void reverse(){
			std::reverse(data_vector.begin(), data_vector.end());
		}
		
		
	    	Sound & selectRange(int rangeStart, int rangeEnd){
			Sound<T,2> * newSound = new Sound(*this);	
			
			newSound->data_vector.clear();		
			newSound->data_vector.resize((unsigned long)(rangeEnd-rangeStart));	
			
			std::copy(data_vector.begin() + rangeStart, data_vector.begin() + rangeEnd, newSound->data_vector.begin());
			
			return *newSound;
		}
		
		
		std::vector <T> & getAudioData(){
			return data_vector;
		}
		
		//get the RMS of the audio file 
		std::pair<float,float> calcRMS(){
			std::pair<float, float> rms;
			float audioDataSizeInverse = 1 / (float) data_vector.size();

			rms = std::accumulate(data_vector.begin(), data_vector.end(), std::pair<float, float>(0, 0),[] (std::pair<float, float> accum, std::pair<T, T> x) {
				accum = std::make_pair(accum.first + (std::pow(x.first, 2)), accum.second + (std::pow(x.second, 2)));
				return accum;
			});		
			rms = std::make_pair(std::sqrt(rms.first * audioDataSizeInverse), std::sqrt(rms.second * audioDataSizeInverse));
			return rms;		
		}
		
		//rms value
		Sound & normalize(float leftRMS, float rightRMS){
			NormalFunction normalF (calcRMS(), std::make_pair(leftRMS, rightRMS));
			Sound<T,2> * tempAudio = new Sound(*this);
			std::transform(data_vector.begin(), data_vector.end(), tempAudio->data_vector.begin(), normalF);
			return * tempAudio;
		}
		
		// calculate the normal values. 
		class NormalFunction{
		public:
			std::pair<float, float> currentRMS;
			std::pair<float, float> targetRMS;
			
			NormalFunction(std::pair<float, float> curRMS, std::pair<float, float> tarRMS):currentRMS(curRMS), targetRMS(tarRMS){}
			
			std::pair<T, T> operator()(std::pair<float, float> inputAmpl){
				return std::make_pair((T) (inputAmpl.first * (targetRMS.first / currentRMS.first)), (T) (inputAmpl.second * (targetRMS.second / currentRMS.second)));
			}
		};
		
	};
}
#endif
