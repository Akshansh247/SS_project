
void semOp(int semid, int semnum, int op) {
    struct sembuf semaphore;
    semaphore.sem_num = semnum;
    semaphore.sem_op = op;
    semaphore.sem_flg = 0;
    if (semop(semid, &semaphore, 1) == -1) {
        perror("semop");
        exit(EXIT_FAILURE);
    }
}//semaphore operations

void add_student_handle(int cfd){                               //adds new student
int stud_id;
int fd = open("./records/record_file",O_RDWR);
struct record record1;
struct message msg;
key_t key ;
int semid;
key = ftok(".",'1');
semid = semget(key,1,0644);                   //getting the semaphore
semOp(semid,0,-1);
read(fd,&record1,sizeof(record1));
stud_id = record1.students+1;
record1.students = stud_id;
lseek(fd, 0, SEEK_SET);
write(fd,&record1,sizeof(record1));
semOp(semid,0,1);
close(fd);
struct student student1;                     //to make sure new student created have next id 
student1.stud_id = stud_id;                    
write_msg(cfd,1,1,"\nEnter Name: ");
read_msg(cfd,&msg);
strcpy(student1.stud_name,msg.body);
write_msg(cfd,1,0,"\nEnter Age: ");
read_msg(cfd,&msg);
student1.stud_age = atoi(msg.body);
write_msg(cfd,1,0,"\nEnter gender: ");
read_msg(cfd,&msg);
student1.stud_gender = msg.body[0];
write_msg(cfd,1,2,"\nEnter Password:  ");
read_msg(cfd,&msg);
strcpy(student1.stud_password ,msg.body);
strcpy(student1.stud_login_id,"");
student1.n_courses=0;
for(int i=0;i<10;i++){
student1.courses[i] = 0;
}
student1.block = 0;
student1.stud_login_status = 0;
int fd1 = open("./records/student_file",O_CREAT|O_RDWR,0777);
lseek(fd1,stud_id*sizeof(struct student),SEEK_SET);
struct flock lock = {F_WRLCK, SEEK_SET, stud_id*sizeof(struct student), sizeof(struct student), getpid()};
fcntl(fd1, F_SETLKW, &lock);                                                                                   //writing into the file , applied lock before writing so that no other can access
write(fd1,&student1,sizeof(student1));
lock.l_type = F_UNLCK;
fcntl(fd1,F_SETLKW,&lock);
write_msg2(cfd,0,1,"\n Student Created Successfully!\nStud-Id. Generated is ",stud_id);
char buff [30];
sprintf(buff,"MT23-%d",stud_id);
strcpy(student1.stud_login_id,buff);
bool status=set_student_details(stud_id,&student1);
if(status==0){
write_msg(cfd,0,1,"\nLogin-Id Setting Failed...");
}
else{
write_msg2(cfd,0,1,"\nLogin-Id Settings Completed Successfully... Login-Id: MT23-",stud_id);
}
close(fd1);
}

void add_faculty_handle(int cfd){
int fac_id;
int fd = open("./records/record_file",O_RDWR);
struct record record1;
struct message msg;
key_t key ;
int semid;
key = ftok(".",'2');
semid = semget(key,1,0644);
semOp(semid,0,-1);
read(fd,&record1,sizeof(record1));                                                 //doing same what did in students function ,just changing it to faculty
fac_id = record1.faculties+1;
record1.faculties = fac_id;
lseek(fd, 0, SEEK_SET);
write(fd,&record1,sizeof(record1));
semOp(semid,0,1);
close(fd);
struct faculty faculty1;
faculty1.faculty_id = fac_id;
write_msg(cfd,1,1,"\nEnter Name: ");
read_msg(cfd,&msg);
strcpy(faculty1.fac_name,msg.body);

write_msg(cfd,1,2,"\nEnter Password: # ");
read_msg(cfd,&msg);
strcpy(faculty1.password ,msg.body);
strcpy(faculty1.fac_log_id,"");
faculty1.total=0;
for(int i=0;i<10;i++){
faculty1.courses[i]=0;
}
faculty1.login_status = 0;

int fd1= open("./records/faculty_file",O_CREAT|O_RDWR,0777);
lseek(fd1,fac_id*sizeof(struct faculty),SEEK_SET);
struct flock lock = {F_WRLCK, SEEK_SET,fac_id*sizeof(struct faculty), sizeof(struct faculty), getpid()};
fcntl(fd1, F_SETLKW, &lock);
write(fd1,&faculty1,sizeof(faculty1));
lock.l_type = F_UNLCK;
fcntl(fd1,F_SETLKW,&lock);
write_msg2(cfd,0,1,"\n Faculty Created Successfully!\n faculty Id. Generated is ",fac_id);
char buff [30];
sprintf(buff,"IITB-%d",fac_id);
strcpy(faculty1.fac_log_id,buff);
bool status=set_faculty_details(fac_id,&faculty1);
if(status==0){
write_msg(cfd,0,1,"\nLogin-Id Setting Failed...");
}
else{
write_msg2(cfd,0,1,"\nLogin-Id Settings Completed Successfully... Login-Id: IITB-",fac_id);
}
close(fd1);

}
void add_course_handle(int cfd){
int course_id;
int fd = open("./records/record_file",O_RDWR);
struct record record1;
struct message msg;
key_t key ;
int semid;
key = ftok(".",'2');
semid = semget(key,1,0644);
semOp(semid,0,-1);
read(fd,&record1,sizeof(record1));
course_id = record1.courses+1;
record1.courses = course_id;
lseek(fd, 0, SEEK_SET);
write(fd,&record1,sizeof(record1));
semOp(semid,0,1);
close(fd);
struct courses course1;
course1.course_no = course_id;
write_msg(cfd,1,1,"\nEnter Name: ");
read_msg(cfd,&msg);
strcpy(course1.coursename,msg.body);
for(int i=0;i<10;i++){
course1.faculties[i]=0;
}
course1.del = 0;
course1.total_Students = 0;
course1.total_faculties = 0;

int fd1= open("./records/course_file",O_CREAT|O_RDWR,0777);
lseek(fd1,course_id*sizeof(struct courses),SEEK_SET);
struct flock lock = {F_WRLCK, SEEK_SET,course_id*sizeof(struct courses), sizeof(struct courses), getpid()};
fcntl(fd1, F_SETLKW, &lock);
write(fd1,&course1,sizeof(course1));
lock.l_type = F_UNLCK;
fcntl(fd1,F_SETLKW,&lock);
write_msg2(cfd,0,1,"\n Course Created Successfully!\nCourse-no. Generated is ",course_id);                      //doing same for courses
char buff [30];
sprintf(buff,"CS-%d",course_id);
strcpy(course1.course_id,buff);
bool status=set_course_details(course_id,&course1);
if(status==0){
write_msg(cfd,0,1,"\nCourse creation Failed...");
}
else{
write_msg2(cfd,0,1,"\nCourse Settings Completed Successfully... Course-Id: CS:-",course_id);
}
close(fd1);

}




