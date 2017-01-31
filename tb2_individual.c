/*
C Programming Indivudal Assemnet: Group 1
Program written by: Lucas Alava Pena
Program's Purpose:
Plot streamlines using Euler (1) or Runge Method (2), as described in excercise sheet
*/
#include <stdio.h>

//declare global variables and set their according data types
int no_streamlines, counter_streamlines,counter_loop, inputed_method;
double x_old,u_old,y_old,v_old,dt,x_new,y_new,x_bar,y_bar,u_bar,v_bar;
/*
no_streamlines are the number of streamlines inputted
counter_streamlines is the counter to ensure that all streamlines are calculated and no more
counter_loop is the counter to ensure that the program does not gone on forever when y =0
inputed_method is the variable where the method wanted is stored in.

doubles:
x_old is the intial or previous value of x, note that it will be used to print the current value,
 this is done to ensure that it only prints the values into the file if is within the boundary which was given
u_old is the previous value of x velocity
y_old is the intial or previous value of y, note that it will be used to print the current value,
 this is done to ensure that it only prints the values into the file if is within the boundary which was given
v_old is the previous value of y velocity
x_new is the current value of x
y_new is the current value of y
x_bar is the intermidate x position which is calculate between two points
y_bar is the intermidate y position which is calculate between two points
u_bar is the intermidate x velocity which is calculate between two points
v_bar is the intermidate y velocity which is calculate between two points
*/

double u_old_calc(double x_old, double y_old) { // u_old_calc function which calculates u_old using function given in sheet with inputs x_old and y_old
	u_old=1+(x_old)/(2*3.1415926*((x_old*x_old)+(y_old*y_old))); //Calculates u_old using function given in sheet
	return u_old; //returns value to be used in calulation
}
double v_old_calc(double x_old, double y_old) { // v_old_calc function which calculates v_old using function given in sheet with inputs x_old and y_old
	v_old=(y_old)/(2*3.1415926*((x_old*x_old)+(y_old*y_old))); //Calculates v_old using function given in sheet
	return v_old; //returns value to be used in calulation
}
double euler_method (){
//open/create file and make it writeable
	FILE*fid1;
	fid1=fopen("stream.plt","w");
	fprintf(fid1, "VARIABLES = \"x\" \"y\""); //prints variable names for tecplot into stream.plt file
	while (counter_streamlines<no_streamlines){
		counter_streamlines=counter_streamlines+1;	
		fprintf(fid1, "\nZONE T=\"Streamline no. %i\"", counter_streamlines); // Prints Zone information for each streamline
		y_old=-0.75+(1.5/(no_streamlines-1))*(counter_streamlines-1); // calculates first y value for each streamline and ensure equally spaced distances for the streamlines
		x_old=-1; // assigns first x value
		while (-1<=y_old && y_old<=1 &&-1<=x_old && x_old<=1){ // while loop to ensure				
			fprintf(fid1, "\n%lf    %lf", x_old, y_old);//prints x and y value into file
			x_new=x_old+u_old_calc(x_old,y_old)*dt; // calculates new y value
			y_new=y_old+v_old_calc(x_old,y_old)*dt;// calculates new y value
			y_old=y_new;
			x_old=x_new;
			/* stores new calculated value in old value so that the new value can be printed next time the while loop runs, 
			this is done to ensure that it only prints the values into the file if is within the boundary which was given. This boundary 
			being -1<=y<=1 and -1<=x<=1
			*/
			counter_loop=counter_loop+1;//increase count for number of loops
			if(counter_loop > 1000){ //checks if count for number of loops is more than 1000
				counter_loop=0; //if it is more than 1000 the variable is reset to 0  
				break; //it breaks out of the while loop
			}
		}
	}
	return (0);
}
double RK_method (){
//open/create file and make it writeable
	FILE*fid1;
	dt=0.05; // higher as it is more accurate, not needed to be changed if wanted
	fid1=fopen("stream.plt","w");
	fprintf(fid1, "VARIABLES = \"x\" \"y\""); //prints variable names for tecplot into stream.plt file
	while (counter_streamlines<no_streamlines){
		counter_streamlines=counter_streamlines+1;	
		fprintf(fid1, "\nZONE T=\"Streamline no. %i\"", counter_streamlines); // Prints Zone information for each streamline
		y_old=-0.75+(1.5/(no_streamlines-1))*(counter_streamlines-1); // calculates first y value for each streamline and ensure equally spaced distances for the streamlines
		x_old=-1; // assigns first x value
		while (-1<=y_old && y_old<=1 &&-1<=x_old && x_old<=1){
			fprintf(fid1, "\n%lf    %lf", x_old, y_old);	//prints x and y value into file
			x_bar=x_old+0.5*u_old_calc(x_old,y_old)*dt;//calculates  x_bar value
			y_bar=y_old+0.5*v_old_calc(x_old,y_old)*dt;//calculates y_bar value
			u_bar=1+(x_bar)/(2*3.1415926*((x_bar*x_bar)+(y_bar*y_bar)));//calculates u_bar value
			v_bar=(y_bar)/(2*3.1415926*((x_bar*x_bar)+(y_bar*y_bar)));//calculates v_bar value
			x_new=x_old+0.5*(u_old+u_bar)*dt; //calculates new x value
			y_new=y_old+0.5*(v_old+v_bar)*dt;//calculates new y value
			y_old=y_new;
			x_old=x_new;
			/* stores new calculated value in old value so that the new value can be printed next time the while loop runs, 
			this is done to ensure that it only prints the values into the file if is within the boundary which was given. This boundary 
			being -1<=y<=1 and -1<=x<=1
			*/
			counter_loop=counter_loop+1;//increase count for number of loops
			if(counter_loop > 1000){ //checks if count for number of loops is more than 1000
				counter_loop=0; //if it is more than 1000 the variable is reset to 0  
				break; //it breaks out of the while loop
			}
		}
	}
	return (0);
}
int main () {
	input: //input for number of streamlines
	printf (" Please enter the number of streamlines wanted for plotting:");//prints request for number of streamlines
	scanf ("%i" ,&no_streamlines);//stored inputted number of streamlines in no_streamlines
	while (no_streamlines<=0){
		goto input;
	}
	dt=0.01; // change for other one
	counter_streamlines=0; // counter_streamlines for each streamline
	counter_loop=0; //counter_streamlines for each streamline data point	
	methodinput: // with checks to ensure only 1 or 2 are inputted otherwise they are brought back to input data again
	printf (" Please enter the Method wanted (1) for Euler method and (2) for Runge-Kutta method: "); //asks for input
	scanf ("%i" ,&inputed_method);//stores input into inputed_method
	if (inputed_method==1){ //checks if input_method is equal to 2 so that it can call the request function, in this case the RK_method
		euler_method(); //calls euler_method function
	}
	else if (inputed_method==2){ //checks if input_method is equal to 2 so that it can call the request function, in this case the RK_method
		RK_method(); //calls RK_method function
	}
	else {
		goto methodinput; // brings back to methodinput to ensure only or 1 or inputted
	}
	return(0);		
}
