% Sequence 1101111011
for i=1:1:6
T = (5*10^-3);
b0 = 2;
ft= (b0/2) + 1.6 + 3  ;
t= 0:.000001:0.01;

for n=1:1:1000000

    An= (7/(pi*n))*(1 - cos((2*pi*n/5)) + cos(3*pi*n/5) -cos((7*pi*n/5)) + cos(8*pi*n/5) - cos((10*pi*n/5)));

    Bn= (7/(pi*n))*(sin((2*pi*n/5)) - sin(3*pi*n/5) +sin((7*pi*n/5)) - sin(8*pi*n/5) + sin((10*pi*n/5)));
% 
%      An=(1/(pi*n))*(1-cos((2*pi*n)/2.5)+cos((3*pi*n)/2.5)-cos((4*pi*n)/2.5));
%      Bn=(1/(pi*n))*(sin((2*pi*n)/2.5)+sin((4*pi*n)/2.5)-sin((3*pi*n)/2.5));

    ft = ft + An*sin(2*pi*n*t/T) + Bn*cos(2*pi*n*t/T) ;
    
        if i == 1 %300Hz
            frequency = 300;
            if n/T > frequency
                break;
            end  
        end
         if i == 2 %500Hz
            frequency = 500;
            if n/T > frequency
                break;
            end  
         end
         if i == 3 %1000Hz
            frequency = 1000;
            if n/T > frequency
                break;
            end  
         end
         if i == 4 %5000Hz
            frequency = 5000;
            if n/T > frequency
                break;
            end  
         end
         if i == 5 %10000Hz
            frequency = 10000;
            if n/T > frequency
                break;
            end  
         end
         if i == 6 %1000000Hz
            frequency = 1000000;
            if n/T > frequency
                break;
            end
         end
        
end
subplot(6,1,i);
plot(t,ft);
grid on; %to show grid
title(['Frequency : ',num2str(frequency),'Hz']);
xlabel('T(s)'),ylabel('Volt'); %Label message
axis auto; 
end

