clear;
coor = load('drive.txt', '-ascii');

x=coor(:,1);
y=coor(:,2);
x2=coor(:,3);
y2=coor(:,4);

figure
plot(x,y,x2,y2,'r')
axis equal

grid on
title('Drive')
xlabel('x')
ylabel('y')

ylims = get(gca,'YLim');
hold on
plot([0 0], ylims, '-black')
