/*
	Writed by Lin Ming'An on 2016.03.14
	To read the HTK MFCC file.
*/


#include "HTKread.h"
#include <string.h>
#include<stdlib.h>
//#include "Platform.h"

union byte2 {
	char byte[2];
	short numint;
};

union byte4 {
	char byte[4];
	int numint;
	float numfloat;
};
short endianSwap2int(short a) {
	
	union byte2 un;
	char c1;
	un.numint = a;

	// swap
	c1 = un.byte[0];
	un.byte[0] = un.byte[1];
	un.byte[1] = c1;

	return un.numint;
}
int endianSwap4int(int a) {
	
	union byte4 un;
	char c1;
	un.numint = a;

	// swap
	c1= un.byte[0];
	un.byte[0] = un.byte[3];
	un.byte[3] = c1;
	c1 = un.byte[1];
	un.byte[1] = un.byte[2];
	un.byte[2] = c1;

	return un.numint;
}
float endianSwap4float(float a) {
	
	union byte4 un;
	char c1;
	un.numfloat = a;

	// swap
	c1 = un.byte[0];
	un.byte[0] = un.byte[3];
	un.byte[3] = c1;
	c1 = un.byte[1];
	un.byte[1] = un.byte[2];
	un.byte[2] = c1;

	return un.numfloat;
}

void endianSwap4(union byte4 *un) {
    // swap
    char c1 = (*un).byte[0];
    (*un).byte[0] = (*un).byte[3];
    (*un).byte[3] = c1;
    c1 = (*un).byte[1];
    (*un).byte[1] = (*un).byte[2];
    (*un).byte[2] = c1;
}
int findTokenInString(char *string, char *search_token) {
	
	int search_token_length;
	char token_buffer[256] = {'\0'};
	char search_buffer[256] = {'\0'};
	int byte_counter;
	int i;
	char input_char;
	
	search_token_length = strlen(search_token);

	if (search_token_length > 256)	{
		printf("findTokenInString(): search token length %ld bigger than size of token_buffer, terminating!\n", search_token_length);
		return 1;
	}

	(void) strcpy(token_buffer, search_token);    // copy the search token into a buffer of a fixed length (the search token can in general have a variable length); we want a fixed length

	byte_counter = 0;
	while (1) {
	// shift the search buffer by 1
		for (i = 0; i < search_token_length - 1; i++)	{
			search_buffer[i] = search_buffer[i + 1];
		}
		input_char = string[byte_counter];
		if (input_char == '\0') {
			break;
		}
		search_buffer[search_token_length - 1] = input_char;

		if (!strcmp(search_buffer, token_buffer)) {
			return byte_counter - search_token_length + 1;
		}
		byte_counter++;
	}
	return -1;              // -1 -> didn't find the token
}
void HTKHeader(FILE *inFile){
	/*------read the number_of_frames,sample_period,number_of_bytes_per_frame and parameter_kind----*/
	fread(&number_of_frames,4,1,inFile); 
	fread(&sample_period, 4, 1, inFile); 
	fread(&number_of_bytes_per_frame, 2, 1, inFile);
	fread(&parameter_kind, 2, 1, inFile);
	/*------------- big endian to little endian------------*/
	number_of_frames = endianSwap4int(number_of_frames);
	sample_period = endianSwap4int(sample_period);
	number_of_bytes_per_frame = endianSwap2int(number_of_bytes_per_frame);
	/*--------------get the frame length-------------------*/
	fea_vector_length = number_of_bytes_per_frame/4;                  // each sample is float32
	printf("number_of_frames=%d\nfea_vector_length=%d\n",number_of_frames,fea_vector_length);
}
float* Read_frame_feat(FILE *inFile){
	float temp_data=0.0;
	short feat_dim;
	frame_data = (float *)malloc(sizeof(float)*fea_vector_length);
	for(feat_dim=0;feat_dim<fea_vector_length;feat_dim++){
		if (fread(&temp_data,4,1,inFile)!=1){
			printf("Error reading features!");
			exit(0);
		}
		frame_data[feat_dim]=endianSwap4float(temp_data);
		//printf("%f ",frame_data[feat_dim]);
	}
	//printf("\n");
	return frame_data;
}
