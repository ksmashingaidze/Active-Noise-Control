clear all
N = 20;                   %Filter length

myRecObj = audiorecorder(44100, 16, 2);    %sample 44.1kHz, 32-bit sound and 2 channels   
disp('Commence Recording')                  
recordblocking(myRecObj, 5);               %Record sound for 20s
disp('Finished Recording.');
mysound = getaudiodata(myRecObj);                %Assign recorded stereo signal to 'y'
                                           %Left channel is ref mic, right is error mic

[Ns, width] = size(mysound);                 %Get dimensions of sound array

x = zeros(Ns, 1);               %Initialise mono channels as column vectors
err_right = zeros(Ns, 1);
y = zeros(Ns,1);        %Ns samples of x taken, so Ns values of y at the end 
x_rev = zeros(N,1);
w = zeros(1,N);         %Initialisation of filter coefficients. Note w and x_rev have the same length

mu = 0.005;                  %LMS step-size initialisation


for n = 1:Ns                           %Populate mono channels

err_right(n) = mysound(n,2);

for k = N:-1:1               %Shift values right, such that most recent sample is x(0)

if (k==1)

x(n) = 100*mysound(n,1);     %Amplify original signal
x_rev(k) = x(n);

else

x_rev(k) = x_rev(k-1);

end

end

%x(1) is the most recent sample at time n

y(n) = mtimes(w,x_rev);                  %Perform convolution of y and adaptive filter w
e(n) = x(n) - y(n);                      %Calculate error
w = w + 2*mu*e(n).*transpose(x_rev);         %Update filter coefficients

end

n = 1:Ns;                                %n takes values of 1 to the total number of samples taken
figure;
subplot(3,1,1);
plot(n,x);
title('Graph showing x[n] reference signal');
xlabel('n');
ylabel('Magn. x[n]');
legend('x[n]');

subplot(3,1,2);
plot(n,y);
title('Graph showing LMS output signal y[n]');
xlabel('n');
ylabel('Magn. y[n]');
legend('y[n]');

subplot(3,1,3);
plot(n,e);
title('Graph showing error e[n]');
xlabel('n');
ylabel('Magn. e[n]');
legend('e[n]');






