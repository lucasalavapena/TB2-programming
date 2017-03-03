
%{
Program written by: Lucas Alava Pena, la16600@my.bristol.ac.uk
Aeronautics and Mechanics AENG11301: MATLAB Coursework
Program's Purpose: Complete all parts of the assignment dealing with an
analysis of the motion of a ball.
%}
close all
clear all

%Stores t, x, y in array for each point tracked, 
%Note mass A is the center mark and mass B is the bottom right corner one
massA=dlmread('massA_data.csv',',',2,0);
massB=dlmread('massB_data.csv',',',2,0);

%Note that while these varaibles were created for the excercise (as a 
%required output), the original arrays above were used for the rest of the 
%excercise.
massA_B_times=massA(:,1)
massA_position=massA(:,2:3)
massB_position=massB(:,2:3)

%plotting y and x location of mass A and mass B
plot (massA(:,2),massA(:,3),'rx')
hold on
plot (massB(:,2),massB(:,3),'bx')
ylim([-0.1 0.1])
ylabel('y position (m)')
xlabel('x position (m)')
legend('Center (mass A)','Corner (mass B)' )

% calculating velocity of mass A and B, both the horizontal and the
% vertical are stored in one array/matrix.
for i=(2:(size(massA, 1)))
    velocity_A(i-1,1)=(massA(i,2)-massA(i-1,2))/(massA(i,1)-massA(i-1,1));
    velocity_A(i-1,2) =(massA(i,3)-massA(i-1,3))/(massA(i,1)-massA(i-1,1));
    velocity_B(i-1,1)=(massB(i,2)-massB(i-1,2))/(massB(i,1)-massB(i-1,1));
    velocity_B(i-1,2)=(massB(i,3)-massB(i-1,3))/(massB(i,1)-massB(i-1,1));
end    
%
start=40;%row number when the impact has occured, so that the data before 
%can ignored
time=massA(start:161,1,1)-0.083080808080000;% subtracting its time so that
% the graph start from point of impact.
%creating a fit for the horizontal velocity line
horizontal_velocity_fit = polyfit(time,velocity_A(start:161,1),1);


figure;
%plotting horizontal velocity of Mass A
subplot(3,1,1)
plot (time,velocity_A(start:161,1),'b')
hold on
plot (time,horizontal_velocity_fit(1)*time+horizontal_velocity_fit(2),'r')
hold on
text(0.31,1.5,strcat('a = ',num2str(horizontal_velocity_fit(1))))
ylabel('horizontal velocity (m/s)')
xlabel('Time(s)')
legend('Horizontal velocity','Horizontal velocity fit')

%plotting vertical velocity of Mass A (both with its data and a linear fit)
%vs time
subplot(3,1,2)
plot (time,velocity_A(start:161,2),'b')
hold on
ylabel('vertical velocity (m/s)')
xlabel('Time(s)')
ylim([-1 1]) 
legend('Vertical velocity')

%velocities from impact note that the first column is in the x direction 
%and the second in the y direction
velocitiesA_from_impact =velocity_A(start:161,:)
velocitiesB_from_impact =velocity_B(start:161,:)

%position from impact note that the first column is in the x direction 
%and the second in the y direction
positionA_from_impact =massA(start:161,2:3)
positionB_from_impact =massB(start:161,2:3)

%Calculating relative position of A to B and relative velocity, in order to
%get angular velocity in rad^-1
R_AB_xy=massA(1:161,:,:)-massB(1:161,:,:); 
R_AB_xy(:,1) = [];%removes the first column from before which has the 
%differences in time which are all 0.
R_AB=sqrt((R_AB_xy(:,1)).^2+(R_AB_xy(:,2)).^2);
V_AB=sqrt((velocity_A(:,1)-velocity_B(:,1)).^2+(velocity_A(:,2)-velocity_B(:,2)).^2); 
W_AB=V_AB./R_AB;

% linear (hence ,1) fit for angular velocity vs time graph 
W_AB_fit = polyfit(time,W_AB(start:161),1);

%{
By using curve fitting rather than calulating the acceleration from
velocity points we gain better results. This can be seen clearly from the 
graph/s, at least for the one with angular velocity, it has large 
variations, which would cause a large range of values for the
acceleration, by using plot fitting we are able to have a constant a, which 
generally follows the trend seems to be. Plot fitting  essentially averages
out the points to be able to create a smooth line which fits the points as 
much as possible, thus minimsing the effect of the variations and achieving
and overall better result.
%}

%plotting angular velocity of A relative to B (both with its data and a 
%linear fit) vs time
subplot(3,1,3)
plot (time,W_AB(start:161),'b')
hold on
plot (time,W_AB_fit(1)*time+W_AB_fit(2),'r')
hold on
text(0.31,30,strcat('\alpha = ',num2str(W_AB_fit(1))))
ylabel('angular velocity (rad^-1)')
xlabel('Time(s)')
legend('Angular velocity','Angular velocity fit')

%calculating dynamic friction using a and w
mu_calculated_with_a=-(horizontal_velocity_fit(1)/(9.80665))

R=0.0286; %is shown in video +-0.01 mm

mu_calculated_with_w=((0.4*R*W_AB_fit(1))/(9.80665))
%{
Both of the magnitudes are in the form 0.098x (0.0986 (calculated with a) 
and 0.0982 (calculated with w)), they were very close to each other just 
0.0004 off each other.Already looking at this number we can see that the 
number could be correct as it is not very large, signficantly bigger than 1
and it is not negative. Furthermore ~0.1 sounds reasonable for the given
materials/situation.
%}

%Finding time when the ball will stop slipping and simply roll over the 
%surface using different methods:
%1. analytical solution
t_analytical=horizontal_velocity_fit(2)/(mu_calculated_with_w*9.80665*(3.5))

%2. graphical solution, using the equations of the lines rather than data
%points.
t_graphically=(horizontal_velocity_fit(1).*time+horizontal_velocity_fit(2))-(W_AB_fit(1).*time+W_AB_fit(2)).*R;
t_graphically_solution=(W_AB_fit(2).*R-horizontal_velocity_fit(2))/(horizontal_velocity_fit(1)-W_AB_fit(1).*R)



