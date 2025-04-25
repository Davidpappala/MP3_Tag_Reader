/*
 * NAME : DAVID PAPPALA
 * DATE : 20/09/2024
 * DESCRIPTION :To Implement a MP3 Tag Reader and Editor using File Handling.READING THE TAGS FROM MP3 AUDIO FILE PRINT		ING THE DETAILS AND EDITING THE DETIALS (ID3 VESRION ONLY)
 * */

#include<stdio.h>
#include"view.h"
#include<string.h>
#include"edit.h"
int main(int argc,char *argv[])
{
    ViewInfo vInfo;  //structure variable for view option
    EditInfo eInfo;  //structure variable for edit option
    if(argc==1)      //checking all CLA available or not
    {
	printf("---------------------------------------\nERROR: ./a.out : INVALID ARGUMENTS");
	 printf("USAGE: \n");
	printf("To view please pass like : ./a.out -v .mp3_filename\n");
	printf("To Edit please pass like : ./a.out -e [-t -a -A -y -m -c] .mp3\n");
	 printf("---------------------------------------\n");
	return 0;  //if not available terminating the main funtion
    } 

    if(strcmp(argv[1],"-v")==0)  //for view option
    {
	if(argc!=3) //checking all CLA is passed or not for view option
	{
	    printf("./a.out -v .mp3\n");
	    return 0;
	} 
	vInfo.src_fname = argv[2];  //taking file name
	
	if(strchr(argv[2],'.')==NULL) //checking in source file extension present or not
	{
	    printf("ERROR : Audio file should be .mp3 file\n");
	    return 0;
	} 
	
	char * dup = strchr(argv[2],'.');  //storing the extension into one string

	if(strcmp(dup,".mp3")!=0)  //checking extension(for mp3 file)
	{
	    printf("ERROR : Audio file should be .mp3 file\n");
	    return 0;
	}

	vInfo.fptr_src_file = fopen(vInfo.src_fname,"r");  //opening that into readmode
	
	if(vInfo.fptr_src_file==NULL)  //checking file is opened or not
	{
	    printf("Source file not opened\n");
	    return 0;
	} 
	char str[4];
	fread(str,3,1,vInfo.fptr_src_file);
	
	if(strcmp(str,"ID3")!=0)  //checking first 3 bytes ID3 is available or not
	{
	    printf("ERROR : ID3 MISSED CHECK MP3 FILE\n");
	    return 0;
	}
	rewind(vInfo.fptr_src_file);  //moving the offset to starting index

	printf("\n-------------------------------------------------------------\n");
	printf("\tMP3 TAG READER AND EDITOR FOR ID3V2\n");
	printf("-------------------------------------------------------------\n");
        
	goto_viewfun(&vInfo,argc,argv);  //calling the function to view details
	
	printf("\n-------------------------------------------------------------\n");
	printf("\tDETAILS DISPLAYED SUCCESSFULLY\n");
	printf("-------------------------------------------------------------\n\n");

    }

    else if(strcmp(argv[1],"-e")==0)  //to edit details
    {
	if(argc!=5)  //checking all CLA is passed or not for edit option
	{
	    printf("./a.out -e [-t -a -A -y -m -c] .mp3\n");
	    return 0;
	} 
	int decide=0;
	if(strcmp(argv[2],"-t")==0)   //for checking user entered valid edit option or not
	    decide++;
	else if(strcmp(argv[2],"-a")==0)   //for checking user entered valid edit option or not
	    decide++;
	else if(strcmp(argv[2],"-A")==0)   //for checking user entered valid edit option or not
	    decide++;
	else if(strcmp(argv[2],"-y")==0)   //for checking user entered valid edit option or not
	    decide++;
	else if(strcmp(argv[2],"-m")==0)   //for checking user entered valid edit option or not
	    decide++;
	else if(strcmp(argv[2],"-c")==0)   //for checking user entered valid edit option or not
	    decide++;
	if(decide==0)
	{   //if user entered invalid edit option
	    printf("choose valid option to edit : \n-t  ->  title\n-a  ->  artist\n-A  ->  album\n-y  ->  year\n-m  ->  content\n-c  ->  comment\n");
	    return 0;
	} 
	eInfo.source_fname = argv[4];   //storing file name into string

	eInfo.output_fname = "output.mp3";  //taking the another file to store edited details

	if(strchr(argv[4],'.')==NULL) //checking in source file extension present or not
	{
	    printf("ERROR : Audio file should be .mp3 file\n");
	    return 0;
	} 
	char * dup = strchr(argv[4],'.');  //storing the extension into one string
	
	if(strcmp(dup,".mp3")!=0)  //checking extension(for mp3 file)
	{
	    printf("ERROR : Audio file should be .mp3 file\n");
	    return 0;
	}

	eInfo.fptr_source_file = fopen(eInfo.source_fname,"r"); //opening source file into read mode
	char str[4];
	fread(str,3,1,eInfo.fptr_source_file); //reading first 3 bytes from mp3 file

	if(strcmp(str,"ID3")!=0)  //checking first 3 bytes ID3 is available or not
	{
	    printf("ERROR : ID3 MISSED CHECK MP3 FILE\n");
	    return 0;
	}

	rewind(eInfo.fptr_source_file);  //moving the curser position to beginning
	goto_edit_fun(&eInfo,argc,argv);  //calling the function to edit details

    }
    else if(strcmp(argv[1],"--help")==0)  //for help menu
    {
	printf("\n------------------HELP MENU-----------------------\n");
	printf("\n1.  -v  ->  to view mp3 file contents\n");
	printf("\n2.  -e  ->  to edit mp3 file contents\n");
	printf("\n	    2.1  -t  -> to edit song title\n");
	printf("\n	    2.2  -a  -> to edit artist name\n");
	printf("\n	    2.3  -A  -> to edit album name\n");
	printf("\n	    2.4  -y  -> to edit year\n");
	printf("\n	    2.5  -m  -> to edit content\n");
	printf("\n	    2.6  -c  -> to edit comment\n");
	printf("\n--------------------------------------------------\n");
	return 0;
    } 
    else  //if user enter unsupported input
    {
	printf("./a.out -v .mp3\n");
	printf("./a.out -e [-t -a -A -y -m -c] .mp3\n");
	return 0;
    } 
}
