/*
	Writed by Lin Ming'An on 2016.03.14
	To read the HTK MFCC file
*/


#include "stdio.h"
#ifndef _HTKREAD_H_
#define _HTKREAD_H

#ifdef __cplusplus
extern "C"{
#endif
//--------------HTK Header Parameters-------------
int number_of_frames;
int fea_vector_length;
int sample_period;
short number_of_bytes_per_frame;
short parameter_kind;
float * frame_data;

//-------- New -------------
void endianSwap4(union byte4 *un);
short endianSwap2int(short a);// big endian to little endian for short int type (16byte)
int endianSwap4int(int a);// big endian to little endian for int type (32byte)
float endianSwap4float(float a);// big endian to little endian for float type (32byte)
int findTokenInString(char *string, char *search_token);
void HTKHeader(FILE *inFile);// read the HTK header
float* Read_frame_feat(FILE *inFile);// read one frame MFCC feature 
#ifdef __cplusplus
}
#endif

#endif