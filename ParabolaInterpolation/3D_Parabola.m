P1 = [1 2 3]
P2 = [2.25 4 4.75]
P3 = [4 7 8]

x = [P1(1) P2(1) P3(1)]
y = [P1(2) P2(2) P3(2)]
z = [P1(3) P2(3) P3(3)]

M = [ 0 0 1; 0.25 0.5 1;1 1 1 ]
Mi = inv(M)

P = transpose([x;y;z])

Mp = Mi*P


x0 = @(t) 1*t^2+2*t+1
y0 = @(t) 2*t^2+3*t+2
z0 = @(t) 3*t^2+2*t+3

x0 = @(t) Mp(1,1)*t^2+Mp(2,1)*t+Mp(3,1)
y0 = @(t) Mp(1,2)*t^2+Mp(2,2)*t+Mp(3,2)
z0 = @(t) Mp(1,3)*t^2+Mp(2,3)*t+Mp(3,3)

figure
hold on
ezplot3(x0,y0,z0,[0 1])
plot3(x,y,z,'o')
camlight
h = get(gca,'DataAspectRatio') 
if h(3)==1
      set(gca,'DataAspectRatio',[1 1 1/max(h(1:2))])
else
      set(gca,'DataAspectRatio',[1 1 h(3)])
end

for i=0:10
    ii = i/10
    p = [ x0(i/10),y0(i/10),z0(i/10)]
end