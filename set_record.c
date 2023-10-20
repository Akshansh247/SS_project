
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>
#include "record_headers.h"
#include<stdbool.h>
#include "validity.h"


void main(){
struct record my_record;
int fd,writeBytes;
fd=open("./records/record_file",O_CREAT | O_RDWR,0777);
if(fd==-1){
perror("Cannot Open File");
exit(1);
}

my_record.students=0;
my_record.faculties=0;
my_record.admins=1;
my_record.courses=0;
writeBytes=write(fd,&my_record,sizeof(my_record));
if(writeBytes<=0){
perror("Cannot write into file");
exit(1);
}
close(fd);
}
/*A record file containing count of the ids created , it doesn't contain total number of the objects , it is to help when creating new ids ,as it helps the access of the file if id created is sequential*/
