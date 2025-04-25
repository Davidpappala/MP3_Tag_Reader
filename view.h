#ifndef VIEW_H
#define VIEW_H
#include "enum.h"

typedef struct _ViewInfo //structure data type
{
    char *src_fname;   //for store file name
    FILE *fptr_src_file;  //file pointer for open file

} ViewInfo; 

Status goto_viewfun(ViewInfo *vInfo,int argc,char *argv[]);  //for goto view funtion

Status skip_mp3_header(FILE * fptr_src_file); //for skip the header

Status TIT2_tag(ViewInfo *vInfo);  //function for read song title

Status TPE1_tag(ViewInfo *vInfo);  //function for artist name

Status TALB_tag(ViewInfo *vInfo); //function for read album

Status TYER_tag(ViewInfo *vInfo); //function for read year

Status TCON_tag(ViewInfo *vInfo);  //function for read contest

Status TCOM_tag(ViewInfo *vInfo); //function for read comment

Status put_order(unsigned int len);  //function for converting big endian to little endian system


#endif

