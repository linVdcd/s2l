/*
	Writed by Lin Ming'An on 2016.03.16
	To read the nerual networks's params from bin file
*/

#include "ParamRead.h"


int dim;
int row;
int col;
bool BN=false;

void OpenFile_Param(char *b_name,char *w_name,char *BN_name)
{
	BN = false;
	if((b_file = fopen(b_name,"rb")) == NULL){
		printf("cannot open %s\n",b_name);
		exit(0);}
	if((w_file = fopen(w_name,"rb")) == NULL){
		printf("cannot open %s\n",w_name);
		exit(0);}
	if(BN_name!=NULL){
		BN = true;
		if((BN_file = fopen(BN_name,"rb")) == NULL){
			printf("cannot open %s\n",BN_name);
			exit(0);
		}
	}
}
void CloseFile(){
	fclose(b_file);
	fclose(w_file);
	if(BN==true)
		fclose(BN_file);
}

void Create_params(){
	int i;
	b_param = (float *)malloc(sizeof(float)*dim);
	if (b_param==NULL){printf("Cannot get memery for b_param!\n"); exit(0);}
	w_param = (float **)malloc(sizeof(float)*row);
    for (i = 0; i < row; i ++) { // 按行分配每一列
      w_param[i] = (float *)malloc(sizeof(float) * col);	
    }
	if (w_param==NULL){printf("Cannot get memery for w_param!\n"); exit(0);}
	if(BN==1){
		gamma_param = (float *)malloc(sizeof(float)*dim);
		if (gamma_param==NULL){printf("Cannot get memery for gamma_param!\n"); exit(0);}
		beta_param = (float *)malloc(sizeof(float)*dim);
		if (beta_param==NULL){printf("Cannot get memery for beta_param!\n"); exit(0);}
		mean_param = (float *)malloc(sizeof(float)*dim);
		if (mean_param==NULL){printf("Cannot get memery for mean_param!\n"); exit(0);}
		std_param = (float *)malloc(sizeof(float)*dim);
		if (std_param==NULL){printf("Cannot get memery for std_param!\n"); exit(0);}
	}
}
void Del_params(){
	int i;
	if(BN==1){
		if(gamma_param!=NULL)
		{free(gamma_param); gamma_param=NULL;}
		if(beta_param!=NULL)
		{free(beta_param); beta_param=NULL;}
		if(mean_param!=NULL)
		{free(mean_param); mean_param=NULL;}
		if(std_param!=NULL)
		{free(std_param); std_param=NULL;}
	}
	if(b_param!=NULL)
	{free(b_param); b_param=NULL;}

	if(w_param!=NULL){
		for(i=0;i<row;i++)
			free(w_param[i]);
		free(w_param);
		w_param=NULL;
	}
}



void Read_b(FILE *in_file){
	float temp_data=0.0;
	int i;
	for(i=0;i<dim;i++){
		if (fread(&temp_data,4,1,in_file)!=1)
		{
			printf("Cannot read %dth b param\n",i);
			exit(0);
		}
		b_param[i]=temp_data;
	}
}
void Read_BN(FILE* in_file){
	float temp_data;
	int i=0;
	
	for(i=0;i<dim;i++){
		if (fread(&temp_data,4,1,in_file)!=1)
		{
			printf("Cannot read %dth gamma param\n",i);
			exit(0);
		}
		gamma_param[i]=temp_data;
		if (fread(&temp_data,4,1,in_file)!=1)
		{
			printf("Cannot read %dth beta param\n",i);
			exit(0);
		}
		beta_param[i]=temp_data;
		if (fread(&temp_data,4,1,in_file)!=1)
		{
			printf("Cannot read %dth mean param\n",i);
			exit(0);
		}
		mean_param[i]=temp_data;
		if (fread(&temp_data,4,1,in_file)!=1)
		{
			printf("Cannot read %dth std param\n",i);
			exit(0);
		}
		std_param[i]=temp_data;
	}
}
void Read_w(FILE* in_file){
	int i=0,j=0;
	float temp_data=0;
	
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			if (fread(&temp_data,4,1,in_file)!=1)
			{
				printf("Cannot read %d row %d col w param\n",i);
				exit(0);
			}
			w_param[i][j]=temp_data;
		}
	}
}
void Read_LayerParams(int x,int y){
	row = x;
	col = y;
	dim = x;
	Create_params();
	Read_b(b_file);
	Read_w(w_file);
	if(BN==1)
		Read_BN(BN_file);
}
void Clean(){//call this function at the end of the program.
	CloseFile();
	Del_params();
}