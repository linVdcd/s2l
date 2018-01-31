#include"speech2lip.h"
#include <sys/timeb.h>
#include <stdlib.h>
#if defined(WIN32)
# define  TIMEB    _timeb
# define  ftime    _ftime
typedef __int64 TIME_T;
#else
#define TIMEB timeb
typedef long long TIME_T;
#endif
int time_interval()
{
	int ti;
    struct TIMEB ts1,ts2;
    TIME_T t1,t2;
    
    ftime(&ts1);//��ʼ��ʱ
	s2l("..\\temp.wav","..\\temp.mfc","..\\lip.txt");
    ftime(&ts2);//ֹͣ��ʱ
    t1=(TIME_T)ts1.time*1000+ts1.millitm;
    printf("t1=%lld\n",t1);
    t2=(TIME_T)ts2.time*1000+ts2.millitm;
    printf("t2=%lld\n",t2);
    ti=t2-t1;//��ȡʱ������msΪ��λ��

    return ti;
}
int main(){
	int ti=time_interval();
    printf("time interval=%d\n",ti);
	return 0;
}