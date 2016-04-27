function plot_truck_movement (c)

figure1 = figure;

[row,column] = size (c);

M1 = 2;
L1 = 8;
L2 = 3;
L3 = 12;

for i= 1:column
    
    x = c(1);
    y = c(2);
    t1 = c(3);
    p1 = c(4);
    p2 = c(5);
    
    t2 = t1-p1;
    t3 = t2-p2;
    
    x1 = x + L3*cosd(t3);           y1 = 500 - y - L3*sind(t3);
    x2 = x1 + L2*cosd(t2);          y2 = 500 - y1 - L2*sind(t2);
    x3 = x2 + (M1+L1)*cosd(t1);     y3 = 500 - y2 - (M1+L1)*sind(t1);
    
    x = x/500;  x1 = x1/500;    x2 = x2/500;    x3 = x3/500;
    y = y/500;  y1 = y1/500;    y2 = y2/500;    y3 = y3/500;
    
    annotation (figure1,'line',[x y],[x1 y1]);
    annotation (figure1,'line',[x1 y1],[x2 y2]);
    annotation (figure1,'line',[x2 y2],[x3 y3]);
    
end
