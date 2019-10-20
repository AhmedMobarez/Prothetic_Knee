
%% Real-Time Plotting Data from Arduino
%% Vincent Chow - 07/08/14
%
%  Configuration: 
%  - Place Arduino USB cable in correct port
%  - Match baud rate in Arduino IDE and this script
%  - Make sure data format from Arduino compatible with fscanf() in script
%  
%  Diagnostic tools:
%  - instrfind returns open serial ports
%  - Close serial port if interrupted. Use fclose(s) and
%  delete(s) in command window. 
%
%  References: 
%  Template provided by http://billwaa.wordpress.com/2013/07/10/matlab-real-time-serial-data-logger/


% setup
close all;
clear all;

%% Configuration
% set correct serial port address
%port = '/dev/tty.usbserial-A603UTCE';

% set these variables to desired values
baud_rate = 9600;  % baud rate - match with Arduino IDE
delay = 0.001;      % delay for plotting <-- is this necessary?
num_elem = 1;       % how many elements in data stream?

loop = 0;           % loop to plot every nth data point - reduces delay
n = 40;             % nth data point
time = 0;           % time vector
data = 0;           % data vector

index = 0;          % index for accessing time/data vectors
scroll_width = 10;  % size of moving window in sec

% initalize plots data
graph1 = plot(time, data, 'm-');
xlabel('Time [s]', 'fontsize', 14);
ylabel('Voltage [V]', 'fontsize', 14);
title('Realtime Plot of Potentiometer Signal', 'fontsize', 14);
min = 0;        % static y axis limits
max = 400;
max_bit = 1024; % max bits 2^10
max_v = 360;      % max voltage [V]

% setup serial port
s = Bluetooth('HC-05',1);
% since data is sent in a buffer of 10 bytes, our buffer is 2^10 in size
set(s, 'InputBufferSize', 255);
% microcontroller controls data flow
%set(s, 'FlowControl', 'hardware');
% chosen baudrate allows for realtime plotting without significant delay
%set(s, 'BaudRate', baud_rate);
% no parity bit checking (parity bit used to check for errors)
%set(s, 'Parity', 'none');
% set DataBits at 8 to allow transmission of binary data
%set(s, 'DataBits', 8);
% set number of bits indicating end of data transmission to 1
%set(s, 'StopBit', 1);
% set timeout to 10 seconds
set(s, 'Timeout', 10);

fopen(s); % open serial port as file for read access

fprintf('\n Close figure to terminate session.\n');

tic; % start time

%% Plotting
% plots data while graphs are open

% limit = 2000; % for loop limit for diagnostic purposes
% for I = 1:limit
while ishandle(graph1)
    
    % obtain data from serial port - change this to correct data format!
     
    stream = fscanf(s,2,'uint8');
    y = typecast(uint8(stream), 'uint16');
    
    disp(y);
   
    % loops to plot every nth data point - reduces delay
    % every 10th optimal w/ 28800 baud rate
    if (loop < n)
        loop = loop + 1;
        continue;
    elseif (loop == n)
        loop = 0;
    end

    % plot as long as data stream is not empty
    if (~isempty(stream) && numel(y) == num_elem)
        
        index = index + 1; % increment index

        time(index) = toc; % increment time
        
        % take data from stream into respective data arrays
        data(index) = y;
        
        % create scrolling window
        if(time(index) > scroll_width)
            set(graph1,'XData', time, 'YData', data);   % plots data after scroll_width has been reached
            axis([time(index) - scroll_width time(index) min max]);
            % axis([time(index) - scroll_width time(index) 0.992*data(index) 1.008*data(index)]);
        else
            % plot during first scroll_width seconds
            set(graph1, 'XData', time, 'YData', data);
            axis([0 scroll_width min max]);
        end
    
        pause(delay);
        
    end
end

% close serial port
fclose(s);

% delete serial port to allow plotting for subsequent sessions
delete(s);

fprintf('\n Session Terminated.\n');