 % HC-05 is bluetooth module
 b = Bluetooth('HC-05',1);
 x = [1:101];
 y = zeros(1,101);
 h = plot(x,y,'YDataSource','y');

for i = 1:101;
    fopen(b);
    
    while b.BytesAvailable == 0
    end
    % Store AVR response in variable 'response'
    response = fread(b, b.BytesAvailable, 'uint8');
      
        y(i) = response;
        xlim([i-9 i])
        refreshdata(h,'caller')
        drawnow
    
    fclose(b);
end