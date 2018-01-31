/*
	Writed by Lin Ming'An on 2016.03.18
	speech to lip
*/
#include<stdlib.h>
#include <stdio.h>
#include"HTKread.h"
#include "LayerRead.h"
#include ".\HMFCC\HMFCC.h"
#ifndef _SPEECH2LIP_H_
#define _SPEECH2LIP_H_

#ifdef __cplusplus
extern "C"{
#endif
short lip_ID;
float *vDMULv(float *v1,float *v2,int dim);// vector dot multi
float *vDDIVv(float *v1,float *v2,int dim);// vector dot div
float *vDMINUv(float *v1,float *v2,int dim);//vector dot minus
float *vDPLUSEv(float *v1,float *v2,int dim); // vector dot add
float *mMULv(float *v,float **m,int row,int col);// matrix multi vector
float *vTanh(float *v,int dim);
float *softmax(float *v,int dim);
void classes(float *v,int dim);
void s2l(char *wav_name,char *mfc_name,char *lip_name);// speech 2 lip interface
#ifdef __cplusplus
}
#endif

#endif
