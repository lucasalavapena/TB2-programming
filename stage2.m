close all
clear all

% Stores, t, x, y in array for each point tracked
massA=dlmread('massA_data.csv',',',2,0);
massB=dlmread('massB_data.csv',',',2,0);

%plotting 
plot (massA(:,2),massA(:,3),'rx')
hold on
plot (massB(:,2),massB(:,3),'bx')
ylim([-0.1 0.1])
ylabel('y position (m)')
xlabel('x position (m)')
legend('Center (mass A)','Cornor (mass B)' )

% calculating velocity of Mass A and B, both the horizontal and the
% vertical are stored in one array/matrix.
for i=(2:(size(massA, 1)))
    velocity_A(i-1,1)=(massA(i,2)-massA(i-1,2))/(massA(i,1)-massA(i-1,1));
    velocity_A(i-1,2) =(massA(i,3)-massA(i-1,3))/(massA(i,1)-massA(i-1,1));
    velocity_B(i-1,1)=(massB(i,2)-massB(i-1,2))/(massB(i,1)-massB(i-1,1));
    velocity_B(i-1,2)=(massB(i,3)-massB(i-1,3))/(massB(i,1)-massB(i-1,1));
end    

start=40;
time=massA(start:161,1,1);
horizontal_velocity_fit = polyfit(time,velocity_A(start:161,1),1)

figure;
subplot(4,1,1)
plot ((massA(start:161)),velocity_A(start:161,1),'r')
hold on
plot (time,horizontal_velocity_fit(1)*time+horizontal_velocity_fit(2),'b')
hold on
text(0.36,1.5,strcat('a = ',num2str(horizontal_velocity_fit(1))))
ylabel('horizontal velocity (m/s)')
xlabel('Time(s)')

%plotting vertical velocity of Mass A
subplot(4,1,2)
plot ((massA(start:161)),velocity_A(start:161,2),'b')
hold on
ylabel('vertical velocity (m/s)')
xlabel('Time(s)')

R_AB_xy=massA(1:161,:,:)-massB(1:161,:,:); 
R_AB_xy(:,1) = [];
R_AB=sqrt((R_AB_xy(:,1)).^2+(R_AB_xy(:,2)).^2);
% position relative to B,
V_AB=sqrt((velocity_A(:,1)-velocity_B(:,1)).^2+(velocity_A(:,2)-velocity_B(:,2)).^2); 
W_AB=V_AB./R_AB;


W_AB_fit = polyfit(time,W_AB(start:161),1)% linear fit for angular velocity graph, 

subplot(4,1,3)
plot (time,W_AB(start:161),'b')
hold on
plot (time,W_AB_fit(1)*time+W_AB_fit(2),'r')
hold on
text(0.36,30,strcat('\alpha = ',num2str(W_AB_fit(1))))
ylabel('angular velocity rad^-1')
xlabel('Time(s)')

t_1=0.238857323200000;% found using frame by frame video 

mu_calculated_with_a=-(horizontal_velocity_fit(1)/(9.80665));

R=0.0286;


mu_calculated_with_w=((0.4*R*W_AB_fit(1))/(9.80665));
%analytical solution
t_analytical=horizontal_velocity_fit(2)/(mu_calculated_with_w*9.80665*(3.5));

%graphical solution, using the equations of the lines rather than data
%points.
t_graphically=(horizontal_velocity_fit(1).*time+horizontal_velocity_fit(2))-(W_AB_fit(1).*time+W_AB_fit(2)).*R;
t_graphically_fit = polyfit(time,t_graphically,1)
t_graphically_solution=(W_AB_fit(2).*R-horizontal_velocity_fit(2))/(horizontal_velocity_fit(1)-W_AB_fit(1).*R)

subplot(4,1,4)
plot (time,t_graphically,'bx')
hold on 
plot (time,t_graphically_fit(1)*time+t_graphically_fit(2),'r')
hold on
ylabel('v-wr')
xlabel('Time(s)')


