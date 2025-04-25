#ifndef EDIT_H
#define EDIT_H
#include "enum.h"

typedef struct _EditInfo //strcture data type
{
    char * source_fname;  //name for source mp3 file
    FILE * fptr_source_file;  //to open source mp3 file

    char * output_fname;  //name for dest mp3 file
    FILE * fptr_output_file;  //to open dest mp3 file

} EditInfo; 

Status goto_edit_fun(EditInfo *eInfo,int argc,char *argv[]); //function for call all functions 

Status open_file(EditInfo *eInfo); //for opening files

Status copying(EditInfo *eInfo,int argc,char *argv[]); //for copying first header 

Status edit_title(EditInfo *eInfo,int argc,char *argv[]);  //for edit title

Status edit_artist(EditInfo *eInfo,int argc,char *argv[]); //for edit artist name

Status edit_album(EditInfo *eInfo,int argc,char *argv[]); //for edit album

Status edit_year(EditInfo *eInfo,int argc,char *argv[]); //for edit year

Status edit_content(EditInfo *eInfo,int argc,char *argv[]); //for edit content

Status edit_comment(EditInfo *eInfo,int argc,char *argv[]); //for edit comment

Status copy_remaining(EditInfo *eInfo);  //for copying remaining data

Status Put_order(unsigned int len); //for changing big endian to little endian system or little to big endian system

Status editing(EditInfo *eInfo,char *argv[],int len); //for edit any data

Status as_it_is(EditInfo *eInfo,int len); //for copy data as it is

#endif

