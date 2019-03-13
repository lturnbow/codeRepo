% Lauren Turnbow
% MAT363
% Project 2
clear all
clc
a=2.1;         
b=5.1; 
c=0.02;      
t=0:.5:300;      
time=600;
x=.1:(2/19):a;
p=length(x);
y=linspace(.1,b,p);
q=length(y);
deltax=0.1;
deltay=0.1;
deltat=.3;
r=c*deltat/deltax;

for i=1:p %time = 0
    for j=1:q
        u(i,j,1)=3*(1-abs(sin(i*deltax)))*(1-abs(sin(2*j*deltay)))+2*(1-abs(sin(5*i*deltax)))*(1-abs(sin(7*j*deltay)));
    end
end

for i=1:p %first time iteration
    for j=1:q
        u(i,j,2) = 3*(1-abs(sin(i*deltax)))*(1-abs(sin(2*j*deltay)))+2*(1-abs(sin(5*i*deltax)))*(1-abs(sin(7*j*deltay)))+deltat*sin((i*deltax+j*deltay)^2);
    end
end

for k=2:time 
     for i=2:p 
         for j=2:q 
            if (i == p || j == q) %to not go out of bounds
                break;
            end
            u(i,j,k+1)=r^2*(u(i+1,j,k)+u(i,j+1,k)+u(i-1,j,k)+u(i,j-1,k)-4*u(i,j,k))+2*u(i,j,k)-u(i,j,k-1)+(deltat^2)*(sin((i*deltax*j*deltay)^2+k));    
         end
    end
    disp(k)
end

[X,Y]=meshgrid(x,y);
fig=figure;
for i=1:time
    surf(X,Y,u(:,:,i));
    title('2D Wave Equation Simulation');
    axis([0 a 0 b -30 30])
    xlabel('X Axis');
    ylabel('Y Axis');
    zlabel('Z Axis');
    F(i)=getframe(fig);
end

