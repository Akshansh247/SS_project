bool admin_login(char* id,char* password){
	struct administrator my_admin;
	my_admin=get_admin_details(0);//default admin credentials
	if(my_admin.id==-1) return 0;
	if(strcmp(id,my_admin.login_id) == 0 && strcmp(password,my_admin.password) == 0)
	return 1;
return 0;
}
bool student_login(char* id,char* password){
	struct student student1;
	student1=get_student_details(atoi(id+5));
	if(student1.block ==0) return 0;
	if(student1.stud_id==-1)return 0;
	if(student1.stud_login_status==1) return 0;
	if(strcmp(student1.stud_login_id,id)==0 && strcmp(student1.stud_password,password)==0){
	student1.stud_login_status=1;                                                                     //making sure a blocked student can not access and also making sure multiple login not possible
	set_student_details(atoi(id+5),&student1);
	return 1;
	}
return 0;
}
bool faculty_login(char* id,char* password){
	struct faculty faculty1;
	faculty1=get_faculty_details(atoi(id+5));
	if(faculty1.faculty_id==-1)return 0;
	if(faculty1.login_status==1) return 0;
	if(strcmp(faculty1.fac_log_id,id)==0 && strcmp(faculty1.password,password)==0){
	faculty1.login_status=1;
	set_faculty_details(atoi(id+5),&faculty1);
	return 1;
	}
return 0;
}

void login_handle(int cfd,int type){
struct message msg;
char id[11];
char password[11];
int readBytes, writeBytes;
//Login Menu
//Getting Login_id
write_msg(cfd,1,0,"\nEnter Login-Id: ");
read_msg(cfd,&msg);

strcpy(id,msg.body);
write_msg(cfd,1,0,"\nEnter Password: ");
read_msg(cfd,&msg);
id[10] ='\0';

strcpy(password,msg.body);
password[10]='\0';

if(type==0 && admin_login(id,password)){
write_msg(cfd,0,1,"\nLogin Successful! ");

admin_menu(cfd);
}
else if(type==1 && student_login(id,password)){
write_msg(cfd,0,1,"\nLogin Successful! ");


student_menu(cfd,atoi(id+5));

}
else if(type ==2 && faculty_login(id,password)){
write_msg(cfd,0,1,"\nlogin Successful! ");

faculty_menu(cfd,atoi(id+5));
}
else{
write_msg(cfd,1,0,"\nLogin Failed:Invalid Details or Already Login...\nDo you want to Try again(Y/N): ");
read_msg(cfd,&msg);

if((msg.body[0]=='Y' && msg.body[1]=='\0') || (msg.body[0]=='y' && msg.body[1]=='\0'))
login_handle(cfd,type);
else{
write_msg(cfd,0,0,"");
}

}
}

