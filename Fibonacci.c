#include <stdio.h>
#include "apue.h"



int  Fibonacci(unsigned int n);
int main()
{

  
  char   cmd[256];
  char   str[40][256];
  char*  name = tempnam(NULL,NULL);
  char*  line  = "\n";
  FILE*  log;
  

  mkfifo(name, 0777);
  log  = fopen(name,"w+");
  
  if (log == NULL){
        printf("can't open file\n");
	return EXIT_FAILURE;
  }else{
        goto DO;
  }

  DO:  

    for(unsigned int i = 0; i < 20;i++){
      
        sprintf(str[(2*i)],"%s",line);
        fputs(str[(2*i)],log);
        sprintf(str[(2*i)+1],"%u\n",Fibonacci(i));
        fputs(str[(2*i)+1],log);
        fflush(NULL);
        
    }
   
    if(fork()==0){         
        sprintf(cmd, "gnome-terminal -e \"cat %s\"", name);
        system(cmd);       
        for(unsigned int j = 0; j < 40 ; j++){    
               fgets(str[j],sizeof(cmd),log);            
        }
        exit(0);
    }else if(fork()<0) {
        perror("fork () error");    
    }  

}

int Fibonacci(unsigned int n)
{


  if(n==0){
           
    return 0;

  }else if(n==1){

    return 1;

  }else if(n>1){


    return Fibonacci(n-2)+Fibonacci(n-1);


  }

}

