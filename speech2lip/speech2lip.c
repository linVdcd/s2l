/*
	Writed by Lin Ming'An on 2016.03.18
	speech to lip
*/
#include"speech2lip.h"
#include"stdlib.h"
#include<math.h>
float *vDMULv(float *v1,float *v2,int dim){
	int i=0;
	float *temp;
	temp = (float *)malloc(sizeof(float)*dim);
	if(temp==NULL){ printf("Cannot get memery!\n");exit(0);}
	for (i=0;i<dim;i++){
		temp[i] = 0.0;
		temp[i] = v1[i]*v2[i];
	}
	return temp;
}

float *vDDIVv(float *v1,float *v2,int dim){
	int i=0;
	float *temp;
	temp = (float *)malloc(sizeof(float)*dim);
	if(temp==NULL){ printf("Cannot get memery!\n");exit(0);}
	for (i=0;i<dim;i++){
		temp[i] = 0.0;
		temp[i] = v1[i]/v2[i];
	}
	return temp;
}
float *vDPLUSEv(float *v1,float *v2,int dim){
	int i=0;
	float *temp;
	temp = (float *)malloc(sizeof(float)*dim);
	if(temp==NULL){ printf("Cannot get memery!\n");exit(0);}
	for (i=0;i<dim;i++){
		temp[i] = 0.0;
		temp[i] = v1[i]+v2[i];
	}
	return temp;
}

float *vDMINUv(float *v1,float *v2,int dim){
	int i=0;
	float *temp;
	temp = (float *)malloc(sizeof(float)*dim);
	if(temp==NULL){ printf("Cannot get memery!\n");exit(0);}
	for (i=0;i<dim;i++){
		temp[i] = 0.0;
		temp[i] = v1[i]-v2[i];
	}
	return temp;
}

float *mMULv(float *v,float **m,int row,int col){
	int i,j;
	float *temp;
	temp = (float *)malloc(sizeof(float)*row);
	if(temp==NULL){ printf("Cannot get memery!\n");exit(0);}
	for(i=0;i<row;i++){
		temp[i] = 0.0;
		for(j=0;j<col;j++){
			temp[i]= temp[i]+v[j]*m[i][j];
		}
	}
	return temp;
}
float *vTanh(float *v,int dim){
	float *temp;
	int i;
	temp = (float *)malloc(sizeof(float)*dim);
	if(temp==NULL){ printf("Cannot get memery!\n");exit(0);}
	for (i=0;i<dim;i++){
		temp[i] = 0.0;
		temp[i] = tanh(v[i]);
	}
	return temp;
}

float *softmax(float *v,int dim){
	int i;
	float sum = 0.0;
	float *temp;
	temp = (float *)malloc(sizeof(float)*dim);
	if(temp==NULL){ printf("Cannot get memery!\n");exit(0);}
	for(i=0;i<dim;i++)
	{
		sum += exp(v[i]);
	}
	for(i = 0;i<dim;i++)
	{
		temp[i] = exp(v[i])/sum;
	}
	return temp;
}
void classes(float *v,int dim){
	int i;
	float max = 0;
	for(i=0;i<dim;i++){
		if (max<v[i]){
			max = v[i];
			lip_ID=i;
		}
	}
}
void s2l(char *wav_name,char *mfc_name,char *lip_name){
	int layers_size[] = {39,500,400,300,200,100,25};
	int layer_num = 7;
	int i=0,j,k;
	float *act,*t1,*t2,*t3,*t4,*t5,*t6,tempdata;
	float *input;
	FILE *file,*lip_file;
	char *hmfcc_argv[6]={"HMFCC","-A", "-C", "..//mfcc_64ms_step32ms.cfg", "..//temp.wav", "..//Out.mfc"};
	hmfcc_argv[4]=wav_name;
	hmfcc_argv[5]=mfc_name;
	CreatMFCC(6,hmfcc_argv);//computing the MFCC
	if((lip_file = fopen(lip_name,"wb"))==NULL){
		printf("Cannot open input HTK feature file %s\n", mfc_name);
		exit(0);
	}
	if((file = fopen(mfc_name,"rb"))==NULL){
		printf("Cannot open input HTK feature file %s\n", mfc_name);
		exit(0);
	}
	//read HTK header
	HTKHeader(file);
	ReadNetParams(layer_num,layers_size);
	//input = (float *)malloc(sizeof(float)*39);
	for(j=0;j<number_of_frames;j++){
		input = Read_frame_feat(file);
		if(input==NULL)
		{printf("Cannot readed %d frame feat\n",j);exit(0);}
		act = input;
		for(i = 1;i<LayerSize.size;i++)
		{
			if(i!=LayerSize.size-1)
			{
				t1 = mMULv(act,Layers_param[i-1].w,LayerSize.layer[i],LayerSize.layer[i-1]);
				t2 = vDPLUSEv(t1,Layers_param[i-1].b,LayerSize.layer[i]);
				t3 = vTanh(t2,LayerSize.layer[i]);
				t4 = vDMINUv(t3,Layers_param[i-1].mean,LayerSize.layer[i]);
				t5 = vDDIVv(t4,Layers_param[i-1].std,LayerSize.layer[i]);
				t6 = vDMULv(t5,Layers_param[i-1].gamma,LayerSize.layer[i]);
				act = vDPLUSEv(t6,Layers_param[i-1].beta,LayerSize.layer[i]);
				free(t1);free(t2);free(t3);free(t4);free(t5);free(t6);

			}
			else{
				t1 = mMULv(act,Layers_param[i-1].w,LayerSize.layer[i],LayerSize.layer[i-1]);
				t2 = vDPLUSEv(t1,Layers_param[i-1].b,LayerSize.layer[i]);
				act = softmax(t2,LayerSize.layer[i]);
				free(t1);free(t2);
				}
		}
		classes(act,25);
		fprintf(lip_file, "%d\n", lip_ID+1);
		free(act);
		//printf("%d ",lip_ID);
	}
	printf("\n");
	free(input);
	input=NULL;
	t1=NULL;t2=NULL;t3=NULL;t4=NULL;t5=NULL;t6=NULL;
	act = NULL;
	fclose(file);
	fclose(lip_file);
	Clean();
	
}