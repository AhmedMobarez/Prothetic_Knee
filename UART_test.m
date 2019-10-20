PORT = 'COM3';  % Change as necessary
BAUD = 9600;
BITS = 8;        % Number of data bits
AVR = serial(PORT, 'BaudRate', BAUD, 'DataBits', BITS);
fopen(AVR);
pause(2);
prompt = 'Required angle ';
x = input(prompt)
fwrite(AVR, x, 'async');
while AVR.BytesAvailable == 0
end
% Store AVR response in variable 'response'
response = fread(AVR, AVR.BytesAvailable, 'uint8');
% Display received data on command line
disp('AVR:');
disp(response);
fclose(AVR);
delete(AVR);
clear AVR;