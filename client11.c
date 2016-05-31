#include <stdio.h>  
 #include <stdlib.h>        
 #include <string.h>          //for string operations  
 #include <unistd.h>          //NULL constant defined here  
 #include <sys/types.h>            
 #include <sys/socket.h>          //for sockets  
 #include <netinet/in.h>          //Internet Protocol family sockaddr_in defined here   
 #include <pthread.h>          // for the cosy POSIX threads  
 #include <signal.h>          //for ctrl+c signal  
 #define MYPORT 4444     /* default port number */  
 #define MAXDATALEN 256  
 int      sockfd;  
 int      n,x;                         /*variables for socket*/  
 struct sockaddr_in addr,cl_addr;          /* structure to hold server's address */  
 char      buffer[MAXDATALEN];  
 char      buf[10];            
 void *quitproc();  
 void* chat_write(int);  
 void* chat_read(int);  
 void *zzz();  
 

/***************main starts************/  

int main(int argc, char *argv[]){  
	char * serveraddr;
	pthread_t thr1,thr2;          /* variable to hold thread ID */  
     

	if( argc != 2 ){       
		       printf("help:u need to put server ip\n");  
		       exit(0);  
		       }  
	


      /*=============socket creating==============*/  
      sockfd = socket(AF_INET, SOCK_STREAM, 0);  

      if (sockfd == -1)  
        printf ("client socket error\n");  
      else       
        printf("socket\t\tcreated\n");  


      /*===============set info===================*/  
       serveraddr = argv[1];   
      bzero((char *) &cl_addr, sizeof(cl_addr));  
      cl_addr.sin_family = AF_INET;  
      cl_addr.sin_port = MYPORT;  
      cl_addr.sin_addr.s_addr = inet_addr(serveraddr);  


      /*=========for username=====================*/  
      bzero(buf,10);  
      printf("\nENTER YOUR NAME::");  
      fgets(buf,10,stdin);  
      __fpurge(stdin);       
      buf[strlen(buf)-1]=':';  


      /*=============client connect to server============*/  
      if(connect(sockfd, (struct sockaddr *) &cl_addr, sizeof(cl_addr))==-1)  
      {  
        printf("client connect error\n");  
        //exit(0);  
      }  
      else  
        printf("%s connected to server\n",buf); 
	printf("ji"); 


      printf("\rYOU JOINED AS- %s",buffer-1);  
      send(sockfd,buf,strlen(buf),0);  
      pthread_create(&thr2,NULL,(void *)chat_write,(void *)sockfd);     //thread creation for writing  
      pthread_create(&thr1,NULL,(void *)chat_read,(void *)sockfd);     //thread creation for reading  
      pthread_join(thr2,NULL);  
      pthread_join(thr1,NULL);  
      return 0;  
 } /*main ends*/  


 /*======================================================================*/  

 /*======reading continously from socket=============*/  


 void* chat_read(int sockfd)  
 {  
      if (signal(SIGINT,(void *)quitproc)==0)  
      if(signal(SIGTSTP, (void *)zzz)==0)  
      while(1)  
      {  
        n=recv(sockfd,buffer,MAXDATALEN-1,0);  
         if(n==0){   
            printf("\nDUE TO SOME UNEXPECTED REASONS SERVER HAS BEEN SHUTDOWN\n\n");  
             exit(0);  
             }  
         if(n>0){  
              printf("\n%s ",buffer);  
            bzero(buffer,MAXDATALEN);  
             }  
      }//while ends  
 }  


 /*======writing continously to socket=============*/  

 void* chat_write(int sockfd)  
 {  
      while(1)  
      {  
        printf("%s",buf);  
          fgets(buffer,MAXDATALEN-1,stdin);  
         if(strlen(buffer)-1>sizeof(buffer)){  
             printf("buffer size full\t enter within %d characters\n",sizeof(buffer));  
             bzero(buffer,MAXDATALEN);  
             __fpurge(stdin);  
             }  
        n=send(sockfd,buffer,strlen(buffer),0);  
         if(strncmp(buffer,"quit",4)==0)  
             exit(0);  
         bzero(buffer,MAXDATALEN);  
      }//while ends  
 }  
 

/*======handling signals==========*/  
 void *quitproc(){            //handling ctrl+d  
    printf("\rPLEASE TYPE 'quit' TO EXIT\n");  
 }  
 void *zzz(){               //handling ctrl+z  
    printf("\rPLEASE TYPE 'quit' TO EXIT\n");  
 }  
