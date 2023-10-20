void drop_stud (int cfd,int id){
struct message msg;
write_msg(cfd,1,0,"\nEnter Course-Id: ");
read_msg(cfd,&msg);
int no = atoi(msg.body+3);
struct courses course1 = get_course_details(no);
if(course1.enrolled_students[id] ==0){
       write_msg(cfd,0,1,"you aren't enrolled here\n");
       }
 else{
    course1.enrolled_students[id] =0;
    course1.blacklist[id] = 1;
    course1.total_Students = course1.total_Students-1;
    set_course_details(no,&course1);
    struct student student1 ;
    student1 = get_student_details(id);
    student1.courses[no] =0;
    student1.n_courses = student1.n_courses-1;
    set_student_details(id,&student1);
    char buff[100];
   
    sprintf(buff,"%s dropped , don't ever come again \n",course1.coursename);
    
    write_msg(cfd,0,1,buff);
    }}
    
 void drop_fac (int cfd,int id){
struct message msg;
write_msg(cfd,1,0,"\nEnter Course-Id: ");
read_msg(cfd,&msg);
int no = atoi(msg.body+3);
struct courses course1 = get_course_details(no);
if(course1.faculties[id] ==0){
       write_msg(cfd,0,1,"you aren't enrolled here\n");
       }
 else{
    course1.faculties[id] =0;
    course1.total_faculties = course1.total_faculties-1;
    set_course_details(no,&course1);
    struct faculty faculty1 ;
    faculty1 = get_faculty_details(id);
    faculty1.courses[no] =0;
    faculty1.total = faculty1.total-1;
    set_faculty_details(id,&faculty1);
    char buff[100];
   
    sprintf(buff,"%s dropped ,hope you find it good in future \n",course1.coursename);
    
    write_msg(cfd,0,1,buff);
    }}
    
    
    
