#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<string.h>
#include<errno.h>
#include<stdbool.h>

struct message{
int id;
bool type;
int action;
char body[1000];
};

void client_access(int sfd);
void main()
{
struct sockaddr_in saddr;
int sfd, status;

sfd=socket(AF_INET,SOCK_STREAM,0);

if(sfd==-1){
perror("Error while creating socket: ");
exit(1);
}

printf("client side  socket created successfully \n");

printf("enter the socket_no. \n");
int d;
scanf("%d",&d);
saddr.sin_addr.s_addr=htonl(INADDR_ANY);
saddr.sin_family=AF_INET;
saddr.sin_port=htons(d);

status=connect(sfd,(struct sockaddr *)&saddr,sizeof(saddr));

if(status==-1){ 
perror("Error while connecting to server: ");
exit(1);
}

printf("client to server connection successfully established\n");


client_access(sfd);
close(sfd);
}


void client_access(int sfd){
char *exit_msg="";
int readBytes, writeBytes;
struct message msg;
msg.id=0;
int itr=1;
while(itr){
readBytes=read(sfd,&msg,sizeof(msg));


if(msg.type==0){

if(msg.action==0){
exit_msg="\nExit Signal Received from Server\nExiting...\n";
write(1,exit_msg,strlen(exit_msg));
return;
}
else if(msg.action==1){
write(1,msg.body,strlen(msg.body));
}
else return;
}
else if(msg.type==1){
if(msg.action==0){
write(1,msg.body,strlen(msg.body));
msg.id=itr;
char temp[1000];
read(0,temp,sizeof(temp));
bzero(msg.body,sizeof(msg.body));
int i=0;
while(temp[i]!=' ' && temp[i]!='\n' && temp[i]!='\0')
{
msg.body[i]=temp[i];
i++;
}
msg.body[i]='\0';
writeBytes=write(sfd,&msg,sizeof(msg));

}

else if(msg.action==1){
write(1,msg.body,strlen(msg.body));
msg.id=itr;
char temp[1000];
read(0,temp,sizeof(temp));
bzero(msg.body,sizeof(msg.body));
int i=0;
while(temp[i]!='\n' && temp[i]!='\0')
{
msg.body[i]=temp[i];
i++;
}
msg.body[i]='\0';

writeBytes=write(sfd,&msg,sizeof(msg));
}
else{
char temp[1000];
strcpy(temp, getpass(msg.body));
msg.id=itr;
msg.type=1;
msg.action=1;
bzero(msg.body,sizeof(msg.body));
strcpy(msg.body,temp);
msg.body[strlen(temp)]=='\0';
writeBytes=write(sfd,&msg,sizeof(msg));
}

}
else{
exit_msg="Invalid Message Structure sent by Server\nExiting...\n";
write(1,exit_msg,strlen(exit_msg));
return;
}
itr++;
}
}

