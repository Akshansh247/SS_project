void admin_menu(int cfd){

struct message msg;
int readBytes, writeBytes;
begin2:
write_msg(cfd,1,0,"\n....... Welcome to Admin Menu .......\n1. Add Student\n2. View Student\n3. Add Faculty\n4. View Faculty\n5. Activate Student\n6. De-activate Student\n7. Unbann a student\n8. add a new curse \n 9. delete a course \n 10/ any key to Exit\nEnter Your Choice: ");
read_msg(cfd,&msg);
int choice=atoi(msg.body);
switch(choice){
case 1: add_student_handle(cfd); 	
	goto begin2;
	break;
case 2: view_students_handle(cfd); 	
	goto begin2; 
	break;
case 3: add_faculty_handle(cfd); 	
	goto begin2; 
	break;
case 4: view_faculties_handle(cfd); 	
	goto begin2; 
	break;
case 5: activate(cfd);
	goto begin2; 
	break;
case 6: block(cfd);
	goto begin2; 
	break;
case 7: unbann(cfd);
        goto begin2;
        break;
case 8: add_course_handle(cfd);
	goto begin2; 
	break;
case 9: deletecourse(cfd);
        goto begin2;
        break;
default:
	write_msg(cfd,0,0,"");
	break;
}

}

void student_menu(int cfd, int id){

struct message msg;
int readBytes, writeBytes;
begin3:
write_msg(cfd,1,0,"\n....... Welcome to Student Menu .......\n1. View Courses\n2. Add course\n3. Drop Course \n 4. View Enrolled courses\n 5.change password \n 6. any other to exit \n Enter Your Choice: ");
read_msg(cfd,&msg);

int choice=atoi(msg.body);
switch(choice){
case 1: view_courses_handle(cfd); 	
goto begin3; 
break;
case 2: stud_select(cfd,id); 		
goto begin3; 
break;
case 3: drop_stud(cfd,id);
goto begin3;
break;
case 4: view_stud_enrolled(cfd,id);
goto begin3;
break;
case 5:changepassword(cfd);
goto begin3;
break; 
default:
	struct student student1;
	student1=get_student_details(id);
	student1.stud_login_status=0;
	set_student_details(id,&student1);
	write_msg(cfd,0,0,"");
	break;
}

}
void faculty_menu(int cfd, int id){

struct message msg;
int readBytes, writeBytes;
begin4:
write_msg(cfd,1,0,"\n....... Welcome to Faculty Menu .......\n1. View Courses\n2. Add course\n3. Drop Course  \n 4. View Enrolled courses\n 5.change password \n 6.bann a student \n7. any other to exit \n Enter Your Choice: ");
read_msg(cfd,&msg);

int choice=atoi(msg.body);
switch(choice){
case 1: view_courses_handle(cfd); 	
goto begin4; 
break;
case 2: fac_select(cfd,id); 		
goto begin4; 
break;
case 3: drop_fac(cfd,id);
goto begin4;
break;
case 4:view_faculty_enrolled(cfd,id);
goto begin4;
case 5:changefac(cfd);
goto begin4;
break;
case 6:bann(cfd);
goto begin4;
break;
default:
	struct faculty faculty1;
	faculty1=get_faculty_details(id);
	faculty1.login_status=0;
	set_faculty_details(id,&faculty1);
	write_msg(cfd,0,0,"");
	break;
}

}


