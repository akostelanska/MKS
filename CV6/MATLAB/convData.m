clear all;
close all;

data = csvread('ntc.csv');

t = data(1:end, 1);

r_ntc = data(1:end, 2);

for i = 1:length(r_ntc)
    ad(i,1) = (r_ntc(i,1)/(r_ntc(i,1)+10))*1024;
end

p = polyfit(ad, t, 10);

ad2 = 0:1023;
t2 = round(polyval(p, ad2), 1);

plot(ad, t);
hold on,
plot(ad2, t2, 'r');
hold off

dlmwrite('data.dlm', t2*10, ',');

