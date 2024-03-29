function plot_truck_movement (c)

    figure1 = figure;
    [row,column] = size (c);
    
    % Draw boundary area
    annotation(figure1,'rectangle',[50/600 50/600 500/600 500/600],'LineWidth',1,...
        'FaceColor',[0.9412 0.9412 0.9412],...
        'Color',[0 0.498 0]);
    
    % Draw dock point
    annotation(figure1,'rectangle',[(49/600) (299/600) (2/600) (2/600)],...
        'FaceColor',[0 0 1],...
        'Color',[1 0 0]);
    
    % Create textbox
    annotation(figure1,'textbox',[0 0.4663 0.08114 0.0753],...
        'String',{'DOCK'},...
        'HorizontalAlignment','right',...
        'FontName','High Tower Text',...
        'FitBoxToText','off',...
        'LineStyle','none');
    
    M1 = 2;
    L1 = 8;
    L2 = 3;
    L3 = 12;
    
    for m = 1:5:column
    
        x = c(1,m);
        y = c(2,m);
        t1 = c(3,m);
        p1 = c(4,m);
        p2 = c(5,m);
    
        t2 = t1-p1;
        t3 = t2-p2;
    
        x0 = x + 50;                    y0 = y + 50;
        x1 = x0 + L3*cosd(t3);          y1 = y0 + L3*sind(t3);
        x2 = x1 + L2*cosd(t2);          y2 = y1 + L2*sind(t2);
        x3 = x2 + (M1+L1)*cosd(t1);     y3 = y2 + (M1+L1)*sind(t1);
    
        %x_y = [ x0 y0; x1 y1; x2 y2; x3 y3]
    
        if x0<0
            x0 = 0;
        end
        if y0<0
            y0 = 0;
        end
        if x1<0;
            x1 = 0;
        end
        if y1<0
            y1 = 0;
        end
        if x2<0
            x2 = 0;
        end
        if y2<0
            y2 = 0;
        end
        if x3<0
            x3 = 0;
        end
        if y3<0
            y3 = 0;
        end
        
        if x0>600
            x0 = 600;
        end
        if y0>600
            y0 = 600;
        end
        if x1>600
            x1 = 600;
        end
        if y1>600
            y1 = 600;
        end
        if x2>600
            x2 = 600;
        end
        if y2>600
            y2 = 600;
        end
        if x3>600
            x3 = 600;
        end
        if y3>600
            y3 = 600;
        end
    
        x0 = x0/600;
        x1 = x1/600;
        x2 = x2/600;
        x3 = x3/600;
        y0 = y0/600;
        y1 = y1/600;
        y2 = y2/600;
        y3 = y3/600;
    
        %x_y = [x0 y0 x1 y1; x1 y1 x2 y2; x2 y2 x3 y3]
    
        if (m==1)
            
            % Draw starting point in red colour
            annotation(figure1,'line',[x0 x1],[y0 y1],'LineWidth',1,...
            'Color',[1 0 0]);
            annotation(figure1,'line',[x1 x2],[y1 y2],'LineWidth',1,...
            'Color',[1 0 0]);
            annotation(figure1,'line',[x2 x3],[y2 y3],'LineWidth',1,...
            'Color',[1 0 0]);
        
        else        
            annotation (figure1,'line',[x0 x1],[y0 y1]);
            annotation (figure1,'line',[x1 x2],[y1 y2]);
            annotation (figure1,'line',[x2 x3],[y2 y3]);  
        end
    
    end        
    
    
    