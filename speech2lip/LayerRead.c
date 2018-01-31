/*
	Writed by Lin Ming'An on 2016.03.16
	To read one layer nerual networks's params
*/

#include"LayerRead.h"

char temp[1];
void InitLayersize(int size,int *layer){
	int i;
	if(size==0||layer==NULL){printf("layersize cannot be NULL!\n"); exit(0);}
	LayerSize.size=size;
	LayerSize.layer = (int *)malloc(sizeof(int)*size);
	if(LayerSize.layer==NULL){printf("Cannot get memery for LayerSize.layer\n"); exit(0);}
	for(i = 0;i<size;i++)
		LayerSize.layer[i] = layer[i];
}

void ReadNetParams(int size,int *layer){
	int l;
	//char temp[1];
	char b_name[] = "..\\paramsbin\\001b.bin";
	char w_name[] = "..\\paramsbin\\001w.bin";
	char BN_name[] ="..\\paramsbin\\001bn.bin";

	InitLayersize(size,layer);
	Layers_param = (struct layerparam *)malloc(sizeof(struct layerparam)*(LayerSize.size-1));
	if(Layers_param==NULL) {printf("Cannot get memery for Layer_param!\n"); exit(0);}

	for(l=1;l<LayerSize.size;l++){
		itoa(l,temp,10);
		if(l!=LayerSize.size-1){
			b_name[15]=temp[0];
			w_name[15]=temp[0];
			BN_name[15]=temp[0];
			OpenFile_Param(b_name,w_name,BN_name);
			Read_LayerParams(LayerSize.layer[l],LayerSize.layer[l-1]);
			Layers_param[l-1].b = b_param;
			Layers_param[l-1].w = w_param;
			Layers_param[l-1].gamma = gamma_param;
			Layers_param[l-1].beta = beta_param;
			Layers_param[l-1].mean = mean_param;
			Layers_param[l-1].std = std_param;
		}
		else{
			b_name[15]=temp[0];
			w_name[15]=temp[0];
			OpenFile_Param(b_name,w_name,NULL);
			Read_LayerParams(LayerSize.layer[l],LayerSize.layer[l-1]);
			Layers_param[l-1].b = b_param;
			Layers_param[l-1].w = w_param;
		}
	}
}

void Writetxt(int l,int row,int col,char *b,char *w,char *bn){
	
	int i,j;
	FILE *b_file,*w_file,*bn_file;
	b_file = fopen(b,"wt");
	w_file = fopen(w,"wt");
	bn_file = fopen(bn,"wt");
	for(i=0;i<col;i++)
	{
		fprintf(b_file, "%f\n", Layers_param[l-1].b[i]);
		fprintf(bn_file,"%f %f %f %f\n",Layers_param[l-1].gamma[i],Layers_param[l-1].beta[i],Layers_param[l-1].mean[i],Layers_param[l-1].std[i]);
	}
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
			fprintf(w_file, "%f ", Layers_param[l-1].w[i][j]);
		fprintf(w_file, "\n");
	}
	
	fclose(b_file);
	fclose(w_file);
}