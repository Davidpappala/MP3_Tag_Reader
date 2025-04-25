#include<stdio.h>
#include"view.h"
#include<string.h>
#include"enum.h"
#include<stdlib.h>

Status goto_viewfun(ViewInfo *vInfo,int argc,char *argv[])  //function for doing all the task 
{
    skip_mp3_header(vInfo->fptr_src_file); //skiping the header(10 bytes)

    if(TIT2_tag(vInfo)==v_failure)  //checking operation done or not
    {
	printf("TIT2 TAG FAILED\n");
	exit(0);  //if it fail terminating the entire program
    } 
    if(TPE1_tag(vInfo)==v_failure)
    {
	printf("TPE1 TAG FAILED\n");
	exit(0);  //if it fail terminating the entire program
    } 
    if(TALB_tag(vInfo)==v_failure)
    {
	printf("TALB TAG FAILED\n");
	exit(0);  //if it fail terminating the entire program
    } 
    if(TYER_tag(vInfo)==v_failure)
    {
	printf("TYER TAG FAILED\n");
	exit(0);  //if it fail terminating the entire program
    } 
    if(TCON_tag(vInfo)==v_failure)
    {
	printf("TCON TAG FAILED\n");
	exit(0);  //if it fail terminating the entire program
    } 
    if(TCOM_tag(vInfo)==v_failure)
    {
	printf("TCOM TAG FAILED\n");
	exit(0);  //if it fail terminating the entire program
    } 

} 

 Status skip_mp3_header(FILE * fptr_src_file)
{
    fseek(fptr_src_file,10,SEEK_SET); //skip 10 bytes for header
    return v_success;  //returning succes message
}

Status put_order(unsigned int len) 
{
    //converting big endian to little endian 
    return ((len>>24) & 0x000000ff) | ((len>>8) & 0x0000ff00) | ((len<<8) & 0x00ff0000) | ((len<<24) & 0xff000000);    
}

Status do_task(ViewInfo *vInfo)
{
    unsigned int len;  
    fread(&len,4,1,vInfo->fptr_src_file); //reading length 
    unsigned int length = put_order(len); //calling function to convert big to little endian system 
    fseek(vInfo->fptr_src_file,2,SEEK_CUR); //skipping 2 bytes(flag bytes)
    char ch;
    for(int i=0;i<length;i++) //run a loop upto length times
    {
        fread(&ch,1,1,vInfo->fptr_src_file); //reading character by character from source file
	printf("%c",ch); //and printing
    } 
} 

Status TIT2_tag(ViewInfo *vInfo) //for title
{
    char str[5];
    fread(str,4,1,vInfo->fptr_src_file);  //reading tag and storing into string
    if(strcmp(str,"TIT2")!=0)  //checking recieved tag is correct or wrong
	return v_failure;
    printf("\nTITLE	:  ");
    do_task(vInfo);  //calling function to read size and print the result
    return v_success; //returning suuccess message
} 

Status TPE1_tag(ViewInfo *vInfo) //for artist name
{
    char str[5];
    fread(str,4,1,vInfo->fptr_src_file); //reading tag
    if(strcmp(str,"TPE1")!=0)  //checking tag is perfect or not
	return v_failure;
    printf("\n\nARTIST	:  ");
    do_task(vInfo);  //calling function to read size and print the result
    return v_success;
}

Status TALB_tag(ViewInfo *vInfo) //for album
{  
    char str[5];
    fread(str,4,1,vInfo->fptr_src_file); //raading first four bytes of tag
    if(strcmp(str,"TALB")!=0) //checking tag is correct or not
	return v_failure;
    printf("\n\nALBUM	:  ");
    do_task(vInfo);  //calling function to read size and print the result
    return v_success;
}

Status TYER_tag(ViewInfo *vInfo) //for year
{    
    char str[5];
    fread(str,4,1,vInfo->fptr_src_file); //read a tag
    if(strcmp(str,"TYER")!=0) //check tag is correct or wrong
	return v_failure;
    printf("\n\nYEAR	:  ");
    do_task(vInfo);  //calling function to read size and print the result
    return v_success;
}

Status TCON_tag(ViewInfo *vInfo)
{   
    char str[5];
    fread(str,4,1,vInfo->fptr_src_file); //reading 4 bytes(tag) from file
    if(strcmp(str,"TCON")!=0) //checking tag is correct or wrong
	return v_failure;
    printf("\n\nMUSIC	:  ");
    do_task(vInfo);  //calling function to read size and print the result
    return v_success;
}

Status TCOM_tag(ViewInfo *vInfo)
{
    char str[5];
    fread(str,4,1,vInfo->fptr_src_file); //reading tag from file 
    if(strcmp(str,"COMM")!=0) //checking is it correct or wrong
	return v_failure;
    printf("\n\nCOMMENT	:  ");
    do_task(vInfo);  //calling function to read size and print the result
    printf("\n");
    return v_success; 
}
