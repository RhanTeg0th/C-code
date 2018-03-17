#include <stdio.h>



/* Project Euler problem #1. Written by Anton L Feichtmeir using Emacs24/GCC. 
   Date: 3/17/18   */

int main(void)
{



  unsigned long s3 = 0;

 

  for(unsigned int i = 1; i < 334; i++){

     s3 = s3 + (3*i);

    
  }


  unsigned long s5 = 0;

  for(unsigned int j = 1; j < 1000; j++){

    if(j%5==0 && j%3!=0){

      s5 = s5 + j;

    }else{

      s5 = s5 + 0;

    }

    
  }



  printf("Project Euler problem 1 solution = ");
  printf("%lu \n", s3+s5);
 

  return 0;
}
