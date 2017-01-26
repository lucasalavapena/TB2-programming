#include <stdio.h>
#include <math.h>

int main () {
	//declare variables and set their according data types
	int no_streamlines, counter,counter2;
	double x_old,u_old,y_old,v_old,dt,x_new,y_new,x_initial,x_bar,y_bar,u_bar,v_bar;
	
	//open/create file and make it writeable
	FILE*fid1;
	fid1=fopen("stream.plt","w");
	//write 
	fprintf(fid1, "VARIABLES = \"x\" \"y\"");

	printf (" Please enter the number of streamlines wanted for plotting:");
	//add error message plz
	scanf ("%i" ,&no_streamlines);
	
	//set variables to the required or self select value
	x_old=-1;
	dt=0.01;
	counter=0;
	counter2=0;
	x_initial=-1;
	
	//loop for each different streamline
	while (counter<no_streamlines)
	{
	counter=counter+1;	
	fprintf(fid1, "\nZONE T=\%i ", counter);
	y_old=-0.75+(1.5/(no_streamlines-1))*(counter-1);
	fprintf(fid1, "\n%lf    %lf", x_initial, y_old);
	
		//loop for each different streamline point while checking for conditions given in the excercise
		while ((-1<=y_new<=1)&&-1<=x_new<=1)
			{
				/*u_old=1+(x_old)/(2*3.1415926*((x_old*x_old)+(y_old*y_old)));
				//add PI function thingy
				v_old=(y_old)/(2*3.1415926*((x_old*x_old)+(y_old*y_old)));
				x_new=x_old+u_old*dt;
				y_new=y_old+v_old*dt;
				fprintf(fid1, "\n%lf    %lf", x_new, y_new);
				y_old=y_new;
				x_old=x_new;
				counter2=counter2+1;
				if( counter2 > 1000) 
				{
				counter2=0;
				x_old=-1;
				break;
				}
			*/
				u_old=1+(x_old)/(2*3.1415926*((x_old*x_old)+(y_old*y_old)));
				//add PI function thingy
				v_old=(y_old)/(2*3.1415926*((x_old*x_old)+(y_old*y_old)));
				x_bar=x_old+0.5*u_old*dt;
				y_bar=y_old+0.5*v_old*dt;
				u_bar=1+(x_bar)/(2*3.1415926*((x_bar*x_bar)+(y_bar*y_bar)));
				//add PI function thingy
				v_bar=(y_old)/(2*3.1415926*((x_bar*x_bar)+(y_bar*y_bar)));
				x_new=x_old+0.5*(u_old+u_bar)*dt;
				y_new=y_old+0.5*(v_old+v_bar)*dt;
				fprintf(fid1, "\n%lf    %lf", x_new, y_new);
				y_old=y_new;
				x_old=x_new;
				counter2=counter2+1;
				if( counter2 > 1000) 
				{
				counter2=0;
				x_old=-1;
				break;
				}
				
			
			}
	}
	return(0);		
}
