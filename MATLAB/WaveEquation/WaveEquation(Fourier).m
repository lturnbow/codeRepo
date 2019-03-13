% Lauren Turnbow
% MAT363
% Project 1
clear all
clc
a=2;         
b=5;         
c=0.02;      
t=0:.5:300;      
time=600;
x=0:(2/19):a;
p=length(x);
y=linspace(0,b,p);
q=length(y);
deltax=(b-a)/p;
deltay=(b-a)/q;
AMatrix=zeros(20,20);

for m=1:20
    for n=1:20
        amnIntegral=0;
        for i=1:p
            for j=1:q
                % f(x,y) = xy(cos(xy)+sin(xy))
                amnIntegral=amnIntegral+(x(i)*y(j)*(cos(x(i)*y(j))+sin(x(i)*y(j))))*sin(m*pi*x(i)/a)*sin(n*pi*y(j)/b)*deltax*deltay;
            end
        end
        AMatrix(m,n)=(4/(a*b))*amnIntegral;
        disp(m);
    end
end

for k=1:time 
     for i=1:p 
         for j=1:q 
            sum=0;
            for m=1:20
                for n=1:20
                    kmn=pi*sqrt((m/a)^2+(n/b)^2);
                    sum=sum+AMatrix(m,n)*cos(kmn*t(k)*c)*sin(m*pi*x(i)/a)*sin(n*pi*y(j)/b);
                end
            end
            u(i,j,k)=sum;
        end
    end
    disp(k)
end

[X,Y]=meshgrid(x,y);
fig=figure;
for i=1:time
    surf(X,Y,u(:,:,i));
    title('2D Wave Equation Simulation');
    axis([0 a 0 b -10 10])
    xlabel('X Axis');
    ylabel('Y Axis');
    zlabel('Z Axis');
    F(i)=getframe(fig);
end

