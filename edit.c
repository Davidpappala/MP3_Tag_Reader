#include<stdio.h>
#include"edit.h"
#include<string.h>
#include"enum.h"

Status goto_edit_fun(EditInfo *eInfo,int argc,char *argv[])
{
    if(open_file(eInfo)==e_success)  //checking files opened or not
	printf("Files opening Done\n");
    else
	printf("Files opening fail\n");

    if(copying(eInfo,argc,argv)==e_success) //checking header copied or not
	printf("Copying Header Done\n");
    else
	printf("Copying Header fail\n");

    if(edit_title(eInfo,argc,argv)==e_success) //checking title copied or not
	printf("Title (TIT2) Done\n");
    else
	printf("Title (TIT2) fail\n");

    if(edit_artist(eInfo,argc,argv)==e_success) //checking artist name copied or not
	printf("Artist name (TPE1) Done\n");
    else
	printf("Artist name (TPE1) fail\n");

    if(edit_album(eInfo,argc,argv)==e_success) //checking album copied or not
	printf("Album (TALB) Done\n");
    else
	printf("Album (TALB) fail\n");

    if(edit_year(eInfo,argc,argv)==e_success) //checking year copied or not
	printf("Year (TYER) Done\n");
    else
	printf("Year (TYER) fail\n");

    if(edit_content(eInfo,argc,argv)==e_success) //checking content copied or not
	printf("Content (TCON) Done\n");
    else
	printf("Content (TCON) fail\n");

    if(edit_comment(eInfo,argc,argv)==e_success) //checking comment copied or not
	printf("Comment (COMM) Done\n");
    else
	printf("Comment (COMM) fail\n");

    if(copy_remaining(eInfo)==e_success) //checking remaining data copied or not
	printf("Remaining data Done\n");
    else
	printf("Remaining data fail\n");
}

Status open_file(EditInfo *eInfo) //for open files
{
    eInfo->fptr_source_file = fopen(eInfo->source_fname,"r"); //opening source file in read mode
    if(eInfo->fptr_source_file==NULL) //checking file opened or not
    {
	printf("Source file not opened\n");
	return e_failure;
    }

    eInfo->fptr_output_file = fopen(eInfo->output_fname,"w");  //opening dest file in write mode 
    if(eInfo->fptr_output_file==NULL) //checking file opened or not
    {
	printf("Destination file not opened\n");
	return e_failure;
    }
    return e_success; //returning success message

} 

Status copying(EditInfo *eInfo,int argc,char *argv[])  //copying header
{
    char str[11];
    fread(str,10,1,eInfo->fptr_source_file); //reading 10 bytes(header) from source file
    fwrite(str,10,1,eInfo->fptr_output_file); //writing those 10 bytes (header) into output file
    return e_success; //returning success messaga
}

Status Put_order(unsigned int len)
{
    //for convert big endian to little endian system or little to big endian system
    return ((len>>24) & 0x000000ff) | ((len>>8) & 0x0000ff00) | ((len<<8) & 0x00ff0000) | ((len<<24) & 0xff000000);    
}

Status editing(EditInfo *eInfo,char *argv[],int len) //for edit any (title/artist/album/year/content/comment)
{
    char str[3];
    int l=strlen(argv[3]); //finding length of new(title/artist/album/year/content/comment)
    unsigned int length = Put_order(l); //call the function to convert little endian to big endian system 
    fwrite(&length,4,1,eInfo->fptr_output_file); //insert the length into dest mp3 file
    fread(str,2,1,eInfo->fptr_source_file); //reading next two(flag) bytes
    fwrite(str,2,1,eInfo->fptr_output_file); //inserting flag bytes into dest mp3 file
    
    //so shifting the offset position in source file to skip original data beacause we edited the data in that place
    fseek(eInfo->fptr_source_file,len,SEEK_CUR); 
    fwrite(argv[3],l,1,eInfo->fptr_output_file); //writing new changed data into destination(output) file
}

Status as_it_is(EditInfo *eInfo,int len) //for copy data as it is
{
    char str[3];
    unsigned int length = Put_order(len); //converting little endian to big endian system
    fwrite(&length,4,1,eInfo->fptr_output_file); //writing the length into output file
    fread(str,2,1,eInfo->fptr_source_file);  //reading two(flag) bytes
    fwrite(str,2,1,eInfo->fptr_output_file); //writing the flag bytes into output file
    for(int i=0;i<len;i++) //run a loop upto original length times
    {
	char ch;
	fread(&ch,1,1,eInfo->fptr_source_file); //reading character by character from source file
	fputc(ch,eInfo->fptr_output_file); //writing each byte of character into output file
    } 
} 

Status edit_title(EditInfo *eInfo,int argc,char *argv[])
{
    char tag[5];
    fread(tag,4,1,eInfo->fptr_source_file);  //reading TIT2 tag (4 bytes) from source file
    if(strcmp(tag,"TIT2")!=0)  //checking recieved tag correct or not 
    {
	printf("Failed to read TIT2 tag\n");
	return e_failure;
    }
    fwrite(tag,4,1,eInfo->fptr_output_file);  //writing TIT2 tag (4 bytes) into output file
    unsigned int len;
    fread(&len,4,1,eInfo->fptr_source_file);  //reading length from source file
    len = Put_order(len);  //converting that length from big endian to little endian system
    if(strcmp(argv[2],"-t")==0)  //checking user selection(-t/-a/-A/-y/-m/-c)
    {
	editing(eInfo,argv,len);  //if its true call edit data function
    } 
    else
    {   //else call copy data as it is function
	as_it_is(eInfo,len);
    } 
    return e_success;
} 

Status edit_artist(EditInfo *eInfo,int argc,char *argv[])
{
    char tag[5];
    fread(tag,4,1,eInfo->fptr_source_file);  //reading TPE1 tag (4 bytes) from source file
    if(strcmp(tag,"TPE1")!=0)  //checking recieved tag correct or not 
    {
	printf("Failed to read TIT2 tag\n");
	return e_failure;
    }
    fwrite(tag,4,1,eInfo->fptr_output_file);  //writing TPE1 tag (4 bytes) into output file
    int len;
    fread(&len,4,1,eInfo->fptr_source_file);  //reading length from source file
    len = Put_order(len);  //converting that length from big endian to little endian system
    if(strcmp(argv[2],"-a")==0)  //checking user selection(-t/-a/-A/-y/-m/-c)
    {
	editing(eInfo,argv,len);  //if its true call edit data function
    } 
    else
    {  //else call copy data as it is function
	as_it_is(eInfo,len);
    } 
    return e_success;
}

Status edit_album(EditInfo *eInfo,int argc,char *argv[])
{
    char tag[5];
    fread(tag,4,1,eInfo->fptr_source_file);  //reading TALB tag (4 bytes) from source file
    if(strcmp(tag,"TALB")!=0)  //checking recieved tag correct or not 
    {
	printf("Failed to read TIT2 tag\n");
	return e_failure;
    }
    fwrite(tag,4,1,eInfo->fptr_output_file);  //writing TALB tag (4 bytes) into output file
    int len;
    fread(&len,4,1,eInfo->fptr_source_file);  //reading length from source file
    len = Put_order(len);  //converting that length from big endian to little endian system
    if(strcmp(argv[2],"-A")==0)  //checking user selection(-t/-a/-A/-y/-m/-c)
    {
	editing(eInfo,argv,len);  //if its true call edit data function
    } 
    else
    {  //else call copy data as it is function
	as_it_is(eInfo,len);
    } 
    return e_success;
}

Status edit_year(EditInfo *eInfo,int argc,char *argv[])
{
    char tag[5];
    fread(tag,4,1,eInfo->fptr_source_file);  //reading TYER tag (4 bytes) from source file
    if(strcmp(tag,"TYER")!=0)  //checking recieved tag correct or not 
    {
	printf("Failed to read TIT2 tag\n");
	return e_failure;
    }
    fwrite(tag,4,1,eInfo->fptr_output_file);  //writing TYER tag (4 bytes) into output file
    int len;
    fread(&len,4,1,eInfo->fptr_source_file);  //reading length from source file
    len = Put_order(len);  //converting that length from big endian to little endian system
    if(strcmp(argv[2],"-y")==0)  //checking user selection(-t/-a/-A/-y/-m/-c)
    {
	editing(eInfo,argv,len);  //if its true call edit data function
    } 
    else
    {  //else call copy data as it is function
	as_it_is(eInfo,len);
    } 
    return e_success;
}
Status edit_content(EditInfo *eInfo,int argc,char *argv[])
{
    char tag[5];
    fread(tag,4,1,eInfo->fptr_source_file);  //reading TCON tag (4 bytes) from source file
    if(strcmp(tag,"TCON")!=0)  //checking recieved tag correct or not 
    {
	printf("Failed to read TIT2 tag\n");
	return e_failure;
    }
    fwrite(tag,4,1,eInfo->fptr_output_file);  //writing TCON tag (4 bytes) into output file
    int len;
    fread(&len,4,1,eInfo->fptr_source_file);  //reading length from source file
    len = Put_order(len);  //converting that length from big endian to little endian system
    if(strcmp(argv[2],"-m")==0)  //checking user selection(-t/-a/-A/-y/-m/-c)
    {
	editing(eInfo,argv,len);  //if its true call edit data function
    } 
    else
    {    //else call copy data as it is function
	as_it_is(eInfo,len);
    } 
    return e_success;
}
Status edit_comment(EditInfo *eInfo,int argc,char *argv[])
{
    char tag[5];
    fread(tag,4,1,eInfo->fptr_source_file);  //reading COMM tag (4 bytes) from source file
    if(strcmp(tag,"COMM")!=0)  //checking recieved tag correct or not 
    {
	printf("Failed to read TIT2 tag\n");
	return e_failure;
    }
    fwrite(tag,4,1,eInfo->fptr_output_file);  //writing COMM tag (4 bytes) into output file
    int len;
    fread(&len,4,1,eInfo->fptr_source_file);  //reading length from source file
    len = Put_order(len);   //converting that length from big endian to little endian system
    if(strcmp(argv[2],"-c")==0)   //checking user selection(-t/-a/-A/-y/-m/-c)
    {
	editing(eInfo,argv,len);   //if its true call edit data function
    } 
    else
    {   //else call copy data as it is function
	as_it_is(eInfo,len);
    }	  
    return e_success;
}

Status copy_remaining(EditInfo *eInfo)  //copy remaining data
{
    char ch;
    while(fread(&ch,1,1,eInfo->fptr_source_file)>0)  //copying remaining all data upto EOF
    {
	fputc(ch,eInfo->fptr_output_file); //writing each character in to output file
    } 
    return e_success;
    fclose(eInfo->fptr_source_file);  //closing source file
    fclose(eInfo->fptr_output_file); //closing output file
   /* 
    eInfo->fptr_output_file = fopen(eInfo->output_fname,"r");
      eInfo->fptr_source_file = fopen(eInfo->source_fname,"w");
      char c;
      while(fread(&c,1,1,eInfo->fptr_output_file)>1)
      {
      fputc(c,eInfo->fptr_source_file);
      } */
}    


