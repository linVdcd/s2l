/*
	Writed by Lin Ming'An on 2016.03.16
	To read one layer nerual networks's params
*/

#include<stdlib.h>
#include <stdio.h>
#include "ParamRead.h"
#include <string.h>
#ifndef _LAYERREAD_H_
#define _LAYERREAD_H_

#ifdef __cplusplus
extern "C"{
#endif


typedef struct layerparam{
	float **w;
	float *b;
	float *gamma;
	float *beta;
	float *mean;
	float *std; 
};

typedef struct layersize{
	int size;
	int *layer;// include the input and output layer.
};

struct layersize LayerSize;
struct layerparam *Layers_param;


void InitLayersize(int size,int *layer);
void ReadNetParams(int size,int *layer);
void Writetxt(int l,int row,int col,char *b,char *w,char *bn);
#ifdef __cplusplus
}
#endif

#endif
