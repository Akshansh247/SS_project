#include <stdbool.h>
struct record{
int courses;
int students;
int admins;
int faculties;

};

struct message{
int id;
bool type;
int action;
char body[1000];
};
struct faculty{
int faculty_id;
char fac_name[30];;
int courses[10];
int total;
char fac_log_id[25];
char password[30];
bool login_status;
};

struct student{
int stud_id;
char stud_name[25];
int stud_age;
char stud_gender;
//Login Credentials
char stud_login_id[11]; 
char stud_password[11];
int courses[10]; 
int n_courses;
bool stud_login_status;
int block;
};

struct courses{
int course_no;
char course_id[10];
int enrolled_students[100];
int faculties[10];
int total_Students;
int total_faculties;
char coursename[30];
int blacklist[100];
int del;
};

struct administrator{
int id;
char name[25];
char login_id[10];
char password[10];
};


