f = 80; %Hz
tmin = -0.05;
tmax = 0.05;
t = linspace(tmin, tmax, 400);
x_c = cos(2*pi*f * t);

tiledlayout(5,1)
nexttile()
plot(t,x_c)
title("Original")
xlabel('t (seconds)')


%800 hz
f1=800;
T1=1/f1;
t1= linspace(tmin, tmax, 81);
nmin = ceil(tmin / T1);
nmax = floor(tmax / T1);
n = nmin:nmax;
x1 = cos(2*pi*f * n*T1);
nexttile
plot(t1,x1)
title("800")
xlabel('t (seconds)')

f2=125;
T2=1/f2;
t2= linspace(tmin, tmax, 13);
nmin = ceil(tmin / T2);
nmax = floor(tmax / T2);
n = nmin:nmax;
x2 = cos(2*pi*f * n*T2);
nexttile
plot(t2,x2)
title("125")
xlabel('t (seconds)')

f3=50;
T3=1/f3;
t3= linspace(tmin, tmax, 5);
nmin = ceil(tmin / T3);
nmax = floor(tmax / T3);
n = nmin:nmax;
x3 = cos(2*pi*f * n*T3);
nexttile
plot(t3,x3)
title("50")
xlabel('t (seconds)')

f4=10;
T4=1/f4;
t4= linspace(tmin, tmax, 1);
nmin = ceil(tmin / T4);
nmax = floor(tmax / T4);
n = nmin:nmax;
x4 = cos(2*pi*f * n*T4);
nexttile
plot(t4,x4)
title("10")
xlabel('t (seconds)')

