void stud_select(int cfd,int id){
struct message msg;
write_msg(cfd,1,1,"\n Enter the course id : ");
read_msg(cfd,&msg);
int no = atoi(msg.body+3);
struct student student1;
struct courses course1;
int fd = open("./records/course_file",O_RDWR);
lseek(fd,no*sizeof(struct courses),SEEK_SET);
struct flock lock = {F_WRLCK, SEEK_SET, no*sizeof(struct courses), sizeof(struct courses), getpid()};
fcntl(fd,F_SETLKW,&lock);
read(fd,&course1,sizeof(course1));
lock.l_type = F_UNLCK;
fcntl(fd,F_SETLKW,&lock);
if(course1.blacklist[id]==1){
write_msg(cfd,0,1,"Sorry you are blocked");
}
else{
course1.enrolled_students[id] = id;
course1.total_Students+=1;
lseek(fd,-sizeof(struct courses),SEEK_CUR);
lock.l_type = F_WRLCK;
fcntl(fd,F_SETLKW,&lock);
write(fd,&course1,sizeof(course1));
lock.l_type = F_UNLCK;
fcntl(fd,F_SETLKW,&lock);
close(fd);
fd = open("./records/student_file",O_RDWR);
lseek(fd,id*sizeof(struct student),SEEK_SET);
struct flock lock = {F_WRLCK, SEEK_SET, id*sizeof(struct student), sizeof(struct student), getpid()};
fcntl(fd, F_SETLKW, &lock);
read(fd,&student1,sizeof(student1));
student1.courses[no] = no;
student1.n_courses+=1;
lseek(fd,-sizeof(struct student),SEEK_CUR);
write(fd,&student1,sizeof(student1));
lock.l_type = F_UNLCK;
fcntl(fd,F_SETLKW,&lock);
close(fd);

write_msg(cfd,0,1,"course selected successfully");
}
}

void fac_select(int cfd,int id){
struct message msg;
write_msg(cfd,1,1,"\n Enter the course id : ");
read_msg(cfd,&msg);
int no = atoi(msg.body+3);
struct faculty faculty1;
struct courses course1;
int fd = open("./records/course_file",O_RDWR);
lseek(fd,no*sizeof(struct courses),SEEK_SET);
struct flock lock = {F_WRLCK, SEEK_SET, no*sizeof(struct courses), sizeof(struct courses), getpid()};
fcntl(fd,F_SETLKW,&lock);
read(fd,&course1,sizeof(course1));
course1.faculties[id] = id;
course1.total_faculties+=1;
lseek(fd,-sizeof(struct courses),SEEK_CUR);
write(fd,&course1,sizeof(course1));
lock.l_type = F_UNLCK;
fcntl(fd,F_SETLKW,&lock);
close(fd);
fd = open("./records/faculty_file",O_RDWR);
lseek(fd,id*sizeof(struct faculty),SEEK_SET);
struct flock lock1 = {F_WRLCK, SEEK_SET, id*sizeof(struct faculty), sizeof(struct faculty), getpid()};
fcntl(fd, F_SETLKW, &lock1);
read(fd,&faculty1,sizeof(faculty1));
faculty1.courses[no] = no;
faculty1.total+=1;
lseek(fd,-sizeof(struct faculty),SEEK_CUR);
write(fd,&faculty1,sizeof(faculty1));
lock1.l_type = F_UNLCK;
fcntl(fd,F_SETLKW,&lock);
close(fd);

write_msg(cfd,0,1,"course selected successfully");

}

