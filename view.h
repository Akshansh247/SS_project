#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<string.h>
#include<errno.h>
#include<stdbool.h>
#include<time.h>

void view_courses_handle(int cfd){
struct courses course1;
struct message msg;
int id;
int readBytes, writeBytes;                                                                 //accessing the file and reading it to view
int fd = open("./records/course_file",O_RDONLY);
read(fd,&course1,sizeof(course1));
while(read(fd,&course1,sizeof(course1))){
if(course1.del == 0){
char buff[50];
sprintf(buff,"course name --> %s\n",course1.coursename);
write_msg(cfd,0,1,buff);

sprintf(buff,"course id  ---> %s\n",course1.course_id);
write_msg(cfd,0,1,buff);

sprintf(buff,"total students ---> %d\n",course1.total_Students);
write_msg(cfd,0,1,buff);

sprintf(buff,"total faculties ---> %d\n",course1.total_faculties);
write_msg(cfd,0,1,buff);
struct faculty faculty1;

for(int i=0 ;i<10;i++){
if(course1.faculties[i]!=0){
faculty1 = get_faculty_details(i);
sprintf(buff, "Teched by --> %s \n",faculty1.fac_name);
write_msg(cfd,0,1,buff);}
}

write_msg(cfd,0,1,"------------X----------------\n\n");
}
}
}


void view_students_handle(int cfd){
write_msg(cfd,1,0,"what do you want to do?\n 1. Vaiw all students?. \n 2. View a particular student \n");
struct student student1;
struct message msg;
read_msg(cfd,&msg);
if(atoi(msg.body) ==1){
int id;
int readBytes, writeBytes;
int fd = open("./records/student_file",O_RDONLY);
read(fd,&student1,sizeof(student1));
while(read(fd,&student1,sizeof(student1))){
char buff[50];
sprintf(buff,"Student name --> %s\n",student1.stud_name);
write_msg(cfd,0,1,buff);

sprintf(buff,"student id  ---> %s\n",student1.stud_login_id);
write_msg(cfd,0,1,buff);

write_msg(cfd,0,1,"------------X----------------\n\n");

}
}
else if (atoi(msg.body) ==2){
char buff[50];
write_msg(cfd,0,1,"\nenter his id -->  ");
read_msg(cfd,&msg);
student1 = get_student_details(atoi(msg.body));
sprintf(buff,"Student name --> %s\n",student1.stud_name);
write_msg(cfd,0,1,buff);

sprintf(buff,"student id  ---> %s\n",student1.stud_login_id);
write_msg(cfd,0,1,buff);
}
}
void view_faculties_handle(int cfd){
struct faculty student1;
struct message msg;
int id;
int readBytes, writeBytes;
int fd = open("./records/faculty_file",O_RDONLY);
read(fd,&student1,sizeof(student1));
while(read(fd,&student1,sizeof(student1))){
char buff[50];
sprintf(buff,"faculty name --> %s\n",student1.fac_name);
write_msg(cfd,0,1,buff);

sprintf(buff,"faculty id  ---> %s\n",student1.fac_log_id);
write_msg(cfd,0,1,buff);

write_msg(cfd,0,1,"------------X----------------\n\n");

}
}

void view_stud_enrolled(int cfd,int id){

struct student student1 ;
student1 = get_student_details(id);
for(int i=0;i<10;i++){
if(student1.courses[i] ==i){
struct courses course1 = get_course_details(i);
char buff[50];
sprintf(buff,"\n %s \n",course1.coursename);
write_msg(cfd,0,1,buff);
}
}}
void view_faculty_enrolled(int cfd,int id){

struct faculty faculty1 ;
faculty1 = get_faculty_details(id);
for(int i=0;i<10;i++){
if(faculty1.courses[i] ==i){
struct courses course1 = get_course_details(i);
char buff[50];
sprintf(buff,"\n %s \n",course1.coursename);
write_msg(cfd,0,1,buff);
}
}}

void view_faculty(int cfd,int id){
struct faculty faculty1;
faculty1 = get_faculty_details(id);
char buff [50];
sprintf(buff,"password -> %s\n",faculty1.password);
write_msg(cfd,0,1,buff);
}
void view_stud(int cfd , int id){
struct student student1;
student1 = get_student_details(id);
char buff[50];
sprintf(buff,"password -> %s\n",student1.stud_password);
write_msg(cfd,0,1,buff);
}


