#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>


struct student get_student_details(int stud_id){
int rBytes,wBytes, fd, offset;
struct student student1;

fd = open("./records/student_file",O_RDONLY);

lseek(fd,stud_id*sizeof(struct student),SEEK_SET);
/*Setting Lock*/
struct flock lock = {F_RDLCK, SEEK_SET, stud_id*sizeof(struct student), sizeof(struct student), getpid()};
fcntl(fd, F_SETLKW, &lock);

/*...........*/
read(fd,&student1,sizeof(student1));
/*Unlocking....*/
lock.l_type = F_UNLCK;
fcntl(fd, F_SETLK, &lock);

close(fd);


//success...
return student1;
}

/* Setter Program */

bool set_student_details(int stud_id, struct student *studentx){
int rBytes,wBytes, fd, offset;
studentx->stud_id=stud_id;
fd=open("./records/student_file",O_WRONLY);
lseek(fd,stud_id*sizeof(struct student),SEEK_SET);
struct flock lock = {F_WRLCK, SEEK_SET, stud_id*sizeof(struct student), sizeof(struct student), getpid()};
fcntl(fd, F_SETLKW, &lock);

/*...........*/
wBytes=write(fd,&(*studentx),sizeof(*studentx));
/*Unlocking....*/
lock.l_type = F_UNLCK;
fcntl(fd, F_SETLK, &lock);
/*...........*/

close(fd);
//success...
return 1;
}



