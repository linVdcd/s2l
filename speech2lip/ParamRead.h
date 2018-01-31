/*
	Writed by Lin Ming'An on 2016.03.16
	To read the nerual networks's params from bin file
*/


#include "stdio.h"
#include <stdlib.h>
#ifndef _PARAMREAD_H_
#define _PARAMREAD_H_

#define bool char
#define true 1
#define false 0

#ifdef __cplusplus
extern "C"{
#endif


float** w_param;
float* gamma_param;
float* beta_param;
float* mean_param;
float* std_param;
float* b_param;
FILE *b_file,*w_file,*BN_file;

void OpenFile_Param(char *b_name,char *w_name,char *BN_name);
void CloseFile();
void Create_params();
void Del_params();

void Read_b(FILE* in_file);// read the b param.
void Read_w(FILE* in_file);// read the w params.
void Read_BN(FILE* in_file);//read the BN params

void Read_LayerParams(int x,int y);
void Clean();
#ifdef __cplusplus
}
#endif

#endif
