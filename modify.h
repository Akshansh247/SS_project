void activate (int cfd ){
write_msg(cfd,1,0,"\nEnter Student-Id: ");
struct message msg;
read_msg(cfd,&msg);
int id = atoi(msg.body+5);
struct student student1;
student1 = get_student_details(id);
student1.block = 1;                                           /*to modify the details , using already made functions , can use semaphores  around getting and setting to protect them but now removed*/
set_student_details(id,&student1);
write_msg(cfd,0,1,"Activated successfully\n");
}
void block (int cfd){
write_msg(cfd,1,0,"\nEnter Student-Id: ");
struct message msg;
read_msg(cfd,&msg);
int id = atoi(msg.body+5);
struct student student1;
student1 = get_student_details(id);
student1.block = 0;
set_student_details(id,&student1);
write_msg(cfd,0,1,"Deactivated successfully\n");
}

void unbann (int cfd ){

write_msg(cfd,1,0,"\nEnter Course-Id: ");
struct message msg;
read_msg(cfd,&msg);
int id = atoi(msg.body+2);

write_msg(cfd,1,0,"\nEnter Student you want to unbann : ");
read_msg(cfd,&msg);
int id2 = atoi(msg.body+5);
struct courses course1;
course1 = get_course_details(id);
course1.blacklist[id2] = 0;
set_course_details(id,&course1);
write_msg(cfd,0,1,"Unbanned successfully\n");
}

void bann (int cfd){
write_msg(cfd,1,0,"\nEnter Course-Id: ");
struct message msg;
read_msg(cfd,&msg);
int id = atoi(msg.body+2);

write_msg(cfd,1,0,"\nEnter Student you want to bann : ");
read_msg(cfd,&msg);
int id2 = atoi(msg.body+5);
struct courses course1;
struct student student1;
course1 = get_course_details(id);
student1 = get_student_details(id2);
course1.blacklist[id2] = 1;
course1.enrolled_students[id] = 0;
course1.total_Students = course1.total_Students-1;
set_course_details(id,&course1);
student1.courses[id] = 0;
student1.n_courses = student1.n_courses-1;
set_student_details(id2,&student1);
write_msg(cfd,0,1,"banned successfully\n");
}

void changepassword (int cfd){
write_msg(cfd,1,0,"\nEnter Student-Id: ");
struct message msg;
read_msg(cfd,&msg);
int id = atoi(msg.body+5);
struct student student1;
student1 = get_student_details(id);
write_msg(cfd,1,0,"\nEnter new Password ");
read_msg(cfd,&msg);
bzero(student1.stud_password,sizeof(student1.stud_password));
strcpy(student1.stud_password,msg.body);
set_student_details(id,&student1);
char buff[1050];
sprintf(buff,"\n New password is %s ",msg.body);
write_msg(cfd,0,1,buff);
}
void changefac (int cfd){
write_msg(cfd,1,0,"\nEnter faculty-Id: ");
struct message msg;
read_msg(cfd,&msg);
int id = atoi(msg.body+5);
struct faculty faculty1;
faculty1 = get_faculty_details(id);
write_msg(cfd,1,0,"\nEnter new Password ");
read_msg(cfd,&msg);
bzero(faculty1.password,sizeof(faculty1.password));
strcpy(faculty1.password,msg.body);
set_faculty_details(id,&faculty1);
char buff[1050];
sprintf(buff,"\n New password is %s ",msg.body);
write_msg(cfd,0,1,buff);
}

void deletecourse (int cfd){
write_msg(cfd,1,0,"\nEnter Course-Id you want to delete:- ");
struct message msg;
read_msg(cfd,&msg);
int id = atoi(msg.body+2);
struct courses course1;
course1 = get_course_details(id);
course1.del = 1;
set_course_details(id,&course1);
write_msg(cfd,0,1,"\nCourse deleted successfully");
}

