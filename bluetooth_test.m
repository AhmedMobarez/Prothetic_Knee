%%BAUD = 9600;
%%BITS = 8;        % Number of data bits
BT= Bluetooth('HC-05',1);
fopen(BT);
%%pause(2);
%%prompt = 'Required angle ';


while(1)
    
    
    response =fscanf(BT,'%c');
   %y = typecast(uint8(response), 'uint16');
    
  
    % Display received data on command line
    disp(str2num(response));
    %disp(char(response));
    pause(1);
   % disp(y);
end
fclose(BT);
delete(BT);
clear BT;