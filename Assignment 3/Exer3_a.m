a = 5;
f = 6;
t = 0:0.01:1;
m = 0:0.05:1;
j = 0:0.2:2;
x1 = a*sin(2*pi*f*m);
x2 = a*sin(2*pi*f*t);
x3 = a*sin(2*pi*f*j);


subplot(4,1,1)
plot(t,x2); 
title('Sine Wave');
xlabel('Time ');
ylabel('Amplitude ');

subplot(4,1,2)
stem(t,x2);
title('PAM Wave');
xlabel('Time');
ylabel('Amplitude');
hold on;
plot(t,x2); 

subplot(4,1,3)
stem(m,x1);
title('PAM Wave');
xlabel('Time');
ylabel('Amplitude');
hold on;
plot(m,x1); 

subplot(4,1,4)
stem(j,x3);
title('PAM Wave');
xlabel('Time');
ylabel('Amplitude');
hold on;
plot(j,x3); 


