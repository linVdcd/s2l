
#ifndef _HMFCC_H_
#define _HMFCC_H_

#include "HShell.h"
#include "HMem.h"
#include "HMath.h"
#include "HSigP.h"
#include "HWave.h"
#include "HVQ.h"
#include "HAudio.h"
#include "HParm.h"
#include "HLabel.h"
#include "HModel.h"
#define T_TOP     001           /* basic progress reporting */
#define T_KINDS   002           /* report file formats and parm kinds */
#define T_SEGMENT 004           /* output segment label calculations */
#define T_MEM     010           /* debug memory usage */

static int  trace  = 0;         /* Trace level */
typedef struct _TrList *TrPtr;  /* simple linked list for trace info */
typedef struct _TrList {      
   char *str;                   /* output string */
   TrPtr next;                  /* pointer to next in list */
} TrL;
static TrL trList;              /* 1st element in trace linked list */
static TrPtr trStr = &trList;   /* ptr to it */

static int traceWidth = 70;     /* print this many chars before wrapping ln */

static ConfParam *cParm[MAXGLOBS];
static int nParm = 0;            /* total num params */

/* ---------------------- Global Variables ----------------------- */




static HTime st=0.0;            /* start of samples to copy */
static HTime en=0.0;            /* end of samples to copy */
static HTime xMargin=0.0;       /* margin to include around extracted labs */
static Boolean stenSet=FALSE;   /* set if either st or en set */
static int labstidx=0;          /* label start index (if set) */
static int labenidx=0;          /* label end index (if set) */
static int curstidx=0;          /* label start index (if set) */
static int curenidx=0;          /* label end index (if set) */
static int labRep=1;            /* repetition of named label */
static int auxLab = 0;          /* auxiliary label to use (0==primary) */
static Boolean chopF = FALSE;   /* set if we should truncate files/trans */

static LabId labName = NULL;    /* name of label to extract (if set) */
static Boolean useMLF=FALSE;    /* set if we are saving to an mlf */
static Boolean labF=FALSE;      /* set if we should  process label files too */
static char *labDir = NULL;     /* label file directory */
static char *outLabDir = NULL;  /* output label dir */
static char *labExt = "lab";    /* label file extension */

static Wave wv;                 /* main waveform; cat all input to this */
static ParmBuf pb;              /* main parmBuf; cat input, xform wv to this */
static Transcription *trans=NULL;/* main labels; cat all input to this */
static Transcription *tr;       /* current transcription */
static char labFile[255];       /* current source of trans */
static HTime off = 0.0;         /* length of files appended so far */

/* ---------------- Memory Management ------------------------- */

#define STACKSIZE 100000        /* assume ~100K wave files */
static MemHeap iStack;          /* input stack */
static MemHeap oStack;          /* output stack */
static MemHeap cStack;          /* chop stack */
static MemHeap lStack;          /* label i/o  stack */
static MemHeap tStack;          /* trace list  stack */

#ifdef __cplusplus
extern "C" {
#endif
/* -------------------------- Trace Flags & Vars ------------------------ */



/* ---------------- Process Command Line ------------------------- */

#define MAXTIME 1E13            /* maximum HTime (1E6 secs) for GetChkdFlt */

void ReportUsage(void);

/* SetConfParms: set conf parms relevant to this tool */
void SetConfParms(void);

/* FixOptions: Check and set config options */
void FixOptions(void);


void CreatMFCC(int argc1, char *argv1[]);



/* ----------------- Trace linked list handling ------------------------ */

/* AppendTrace: insert a string to trStr for basic tracing */
void AppendTrace(char *str);

/* PrintTrace: Print trace linked list */
void PrintTrace(void);

/* ------------------- Utility Routines ------------------------ */

/* ClampStEn: set/clamp  st/en times */
void ClampStEn(HTime length, HTime *st, HTime *en);

/* ----------------- Label Manipulation ------------------------ */

/* FixLabIdxs: -ve idxs count from end, so set +ve and check */
void FixLabIdxs(int nlabs);

/* SetLabSeg: Set st and en for label (sequence) */
void SetLabSeg(Transcription *tr);

/* LoadTransLabs: Load transcription from file */
Transcription *LoadTransLabs(char *src);
/* SaveLabs: save trans t to label file corresponding to tgt */
void SaveLabs(char *tgt, Transcription *t);

/* AppendLabs: append label file corresponding to src to trans,
   len is time length of this file; accumulate to find offset for
   concatenated files */
void AppendLabs(Transcription *t, HTime len);

/* ChopLabs: Chop trans around stime to etime. end = 0 means to end of file */
void ChopLabs(Transcription *t, HTime start, HTime end);

/* ----------------------- Wave File Handling ------------------------ */

/* ChopWave: return wave chopped to st and end. end = 0 means all */
Wave ChopWave(Wave srcW, HTime start, HTime end, HTime sampRate);

/* IsWave: check config parms to see if target is a waveform */
Boolean IsWave(char *srcFile);

/* OpenWaveFile: open source wave file and extract portion if indicated */
HTime OpenWaveFile(char *src);

/* AppendWave: append the src file to global wave wv */
HTime AppendWave(char *src);

/* ----------------------- Parm File Handling ------------------------ */

/* ChopParm: return parm chopped to st and end. end = 0 means all */
ParmBuf ChopParm(ParmBuf b, HTime start, HTime end, HTime sampRate);
/* AppendParm: append the src file to current Buffer pb. Return appended len */
HTime AppendParm(char *src);
/* OpenParmFile: open source parm file and return length */
HTime OpenParmFile(char *src);
/* --------------------- Speech File Handling ---------------------- */

/* OpenSpeechFile: open waveform or parm file */
void OpenSpeechFile(char *s);

/* AppendSpeechFile: open waveform or parm file */
void AppendSpeechFile(char *s);

/* PutTargetFile: close and store waveform or parm file */
void PutTargetFile(char *s);
//int main(int argc, char*argv[]){
//	Hmain(6,argv);//computing the MFCC

//	return 0;
//}
/* ----------------------------------------------------------- */
/*                      END:  HCopy.c                          */
/* ----------------------------------------------------------- */
#ifdef __cplusplus
}
#endif
#endif