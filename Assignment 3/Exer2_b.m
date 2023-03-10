freq=2;
freq2=0.5;
seq = [0 1 1 0 1 1 1 0];
amp=10;


for j=1:1:8

     time = j:0.001:j+1;
    if seq(1,j)==1
       inputSignal = amp+time-time;

       ask=amp * cos(2*pi*freq*time);

       fsk= amp * cos(2*pi*(freq+freq2)*time);
        psk=amp * cos(2*pi*freq*time);
    else
        inputSignal = 0+time-time;
        
        ask= 0 * cos(2*pi*freq*time);

         fsk=amp * cos(2*pi*(freq-freq2)*time);
         psk=amp * cos(2*pi*freq*time+pi);
    end

        %Input Signal
    subplot(5,1,1);
        plot(time-1, inputSignal);
    
    hold on;
    grid on;
    axis([0 8 -11 11]);
    title('Input Signal')
    
    %ASK
    subplot(5,1,2);
        plot(time-1,ask);
    
    hold on;
    grid on;
    axis([0 8 -11 11]);
    title('Amplitude Shift Key')
    

    
    %FSK
    subplot(5,1,3);
        plot(time-1,fsk);
    
    hold on;
    grid on;
    axis([0 8 -11 11]);
    title('Frequency Shift Key')

    %PSK
    subplot(5,1,4);
        plot(time-1,psk);
    
    hold on;
    grid on;
    axis([0 8 -11 11]);
    title('Phase Shift Key')
end

for i=1:2:8

    time = i:0.001:i+2;

    if seq(i)==1 && seq(i+1)==1
        qpsk = amp *cos(2* pi *freq *time+(pi/4));
    end

     if seq(i)==0 && seq(i+1)==1
        qpsk = amp *cos(2* pi *freq *time+(3*pi/4));
     end
     if seq(i)==0 && seq(i+1)==0
        qpsk = amp *cos(2* pi *freq *time-(3*pi/4));
     end
    if seq(i)==1 && seq(i+1)==0
        qpsk = amp *cos(2* pi *freq *time-(pi/4));
    end
   subplot(5,1,5);
   plot(time-1,qpsk); 

    hold on;
    grid on;
    axis([0 8 -11 11]);
    title('Quadra kill PSK')
end