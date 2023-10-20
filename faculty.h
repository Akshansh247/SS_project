#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>


struct faculty get_faculty_details(int fac_id){
int rBytes,wBytes, fd, offset;
struct faculty faculty1;
//check validity of customer-Id
//valid
fd = open("./records/faculty_file",O_RDONLY);

lseek(fd,fac_id*sizeof(struct faculty),SEEK_SET);
/*Setting Lock*/
struct flock lock = {F_RDLCK, SEEK_SET, fac_id*sizeof(struct faculty), sizeof(struct faculty), getpid()};
fcntl(fd, F_SETLKW, &lock);

/*...........*/
read(fd,&faculty1,sizeof(faculty1));
/*Unlocking....*/
lock.l_type = F_UNLCK;
fcntl(fd, F_SETLK, &lock);

close(fd);



//success...
return faculty1;
}

/* Setter Program */

bool set_faculty_details(int fac_id, struct faculty *facultyx){
int rBytes,wBytes, fd, offset;
facultyx->faculty_id=fac_id;
fd=open("./records/faculty_file",O_WRONLY);
lseek(fd,fac_id*sizeof(struct faculty),SEEK_SET);
struct flock lock = {F_WRLCK, SEEK_SET, fac_id*sizeof(struct faculty), sizeof(struct faculty), getpid()};
fcntl(fd, F_SETLKW, &lock);

/*...........*/
wBytes=write(fd,&(*facultyx),sizeof(*facultyx));
/*Unlocking....*/
lock.l_type = F_UNLCK;
fcntl(fd, F_SETLK, &lock);
/*...........*/

close(fd);
//success...
return 1;
}



