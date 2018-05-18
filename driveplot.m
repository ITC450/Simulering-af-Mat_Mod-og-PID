clear;
coor = load('drive.txt', '-ascii');

x=coor(:,1);
y=coor(:,2);

figure
plot(x,y,'Color',[1,0,0])
axis equal

grid on
title('Drive')
xlabel('x')
ylabel('y')
