#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>


struct courses get_course_details(int course_no){
int rBytes,wBytes, fd, offset;
struct courses course1;
//check validity of customer-Id
//valid
fd = open("./records/course_file",O_RDONLY);

lseek(fd,course_no*sizeof(struct courses),SEEK_SET);
/*Setting Lock*/
struct flock lock = {F_RDLCK, SEEK_SET, course_no*sizeof(struct courses), sizeof(struct courses), getpid()};
fcntl(fd, F_SETLKW, &lock);

/*...........*/
read(fd,&course1,sizeof(course1));
/*Unlocking....*/
lock.l_type = F_UNLCK;
fcntl(fd, F_SETLK, &lock);

close(fd);



return course1;
}

/* Setter Program */

bool set_course_details(int course_no, struct courses *coursex){
int rBytes,wBytes, fd, offset;
coursex->course_no=course_no;
fd=open("./records/course_file",O_WRONLY);
lseek(fd,course_no*sizeof(struct courses),SEEK_SET);
struct flock lock = {F_WRLCK, SEEK_SET, course_no*sizeof(struct courses), sizeof(struct courses), getpid()};
fcntl(fd, F_SETLKW, &lock);

/*...........*/
wBytes=write(fd,&(*coursex),sizeof(*coursex));
/*Unlocking....*/
lock.l_type = F_UNLCK;
fcntl(fd, F_SETLK, &lock);
/*...........*/

close(fd);
//success...
return 1;
}



