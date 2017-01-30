#include <stdio.h>
#include <math.h>
//declare global variables and set their according data types
int no_streamlines, counter,counter2, inputed_method;
double x_old,u_old,y_old,v_old,dt,x_new,y_new,x_initial,x_bar,y_bar,u_bar,v_bar;
double u_old_calc(double x_old, double y_old) {
	u_old=1+(x_old)/(2*3.1415926*((x_old*x_old)+(y_old*y_old)));
   return u_old; 
}
double v_old_calc(double x_old, double y_old) {
	v_old=(y_old)/(2*3.1415926*((x_old*x_old)+(y_old*y_old)));
   return v_old; 
}
double method1 (){
//open/create file and make it writeable
FILE*fid1;
fid1=fopen("stream.plt","w");
fprintf(fid1, "VARIABLES = \"x\" \"y\""); //prints variable names for tecplot into stream.plt file
while (counter<no_streamlines)
	{
	counter=counter+1;	
	fprintf(fid1, "\nZONE T=\"%i\"", counter);
	y_old=-0.75+(1.5/(no_streamlines-1))*(counter-1); // calculates first y value, which ensure equally spaced distances for the streamlines
	x_old=-1;
		while (-1<=y_old && y_old<=1 &&-1<=x_old && x_old<=1) // while loop to ensure
			{
			fprintf(fid1, "\n%lf    %lf", x_old, y_old);
			x_new=x_old+u_old_calc(x_old,y_old)*dt;
			y_new=y_old+v_old_calc(x_old,y_old)*dt;
			y_old=y_new;
			x_old=x_new;
			counter2=counter2+1;
			if( counter2 > 1000) 
			{
				counter2=0;
				break;
			}
			}
	}
return (0);
}
double method2 (){
//open/create file and make it writeable
FILE*fid1;
fid1=fopen("stream.plt","w");
fprintf(fid1, "VARIABLES = \"x\" \"y\""); //prints variable names for tecplot into stream.plt file
while (counter<no_streamlines)
	{
	counter=counter+1;	
	fprintf(fid1, "\nZONE T=\"%i\"", counter);
	y_old=-0.75+(1.5/(no_streamlines-1))*(counter-1);
	x_old=-1;
		while (-1<=y_old && y_old<=1 &&-1<=x_old && x_old<=1)
		{
			fprintf(fid1, "\n%lf    %lf", x_old, y_old);	
			x_bar=x_old+0.5*u_old_calc(x_old,y_old)*dt;
			y_bar=y_old+0.5*v_old_calc(x_old,y_old)*dt;
			u_bar=1+(x_bar)/(2*3.1415926*((x_bar*x_bar)+(y_bar*y_bar)));
			//add PI function thingy
			v_bar=(y_old)/(2*3.1415926*((x_bar*x_bar)+(y_bar*y_bar)));
			x_new=x_old+0.5*(u_old+u_bar)*dt;
			y_new=y_old+0.5*(v_old+v_bar)*dt;
			y_old=y_new;
			x_old=x_new;
			counter2=counter2+1;
			if( counter2 > 1000) 
			{
				counter2=0;
				break;
			}
		}
	}
return (0);
}
int main () {
	input: //input for number of streamlines
	printf (" Please enter the number of streamlines wanted for plotting:");
	scanf ("%i" ,&no_streamlines);
	while (no_streamlines<=0)
	{
		goto input;
	}
	dt=0.01; // change for other one
	counter=0; // counter for each streamline
	counter2=0; //counter for each streamline data point	
	methodinput: // with checks to ensure only 1 or 2 are inputted otherwise they are brought back to input data again
	printf (" Please enter the Method wanted (1) for Euler method and (2) for Runge-Kutta method: ");
	scanf ("%i" ,&inputed_method);
	if (inputed_method==1)
	{
		method1();
	}
	else if (inputed_method==2)
	{
		method2();
	}
	else 
	{
		goto methodinput; // brings back to methodinput
	}
	return(0);		
}
