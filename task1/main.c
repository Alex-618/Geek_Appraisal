#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
 double y,i,a;
 double h=0.001;
 scanf("%lf",&a);
 y=a;
 printf("(x=%lf,y=%lf)\n",0,y);
 for(i=0.001;;i=i+0.001)
 {
 	if(y-(2-h)/(2+h)*y<=0.00001)
 	{
 		printf("(x=%lf,y=%lf)\n",i,(2-h)/(2+h)*y);
 		break;
	 }
 	y=(2-h)/(2+h)*y;
    printf("(x=%lf,y=%lf)\n",i,y);
 }
	
	return 0; 
}

