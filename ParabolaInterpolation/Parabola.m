close all
P1 = [1 20 3]
P2 = [2.25 23 4.75]
P3 = [4 0 8]

x = [P1(1) P2(1) P3(1)]
y = [P1(2) P2(2) P3(2)]
z = [P1(3) P2(3) P3(3)]

a = norm(P2-P1)/(norm(P3-P2)+norm(P2-P1))

M = [ 0 0 1; a^2 a 1; 1 1 1 ]
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

h = get(gca,'DataAspectRatio') 
if h(3)==1
      set(gca,'DataAspectRatio',[1 1 1/max(h(1:2))])
else
      set(gca,'DataAspectRatio',[1 1 h(3)])
end

xs = zeros(1,10)
ys = zeros(1,10)
zs = zeros(1,10)

figure


for i=0:10
    xs(i+1) = x0(i/10)
    ys(i+1) = y0(i/10)
    zs(i+1) = z0(i/10)
end

plot3(xs,ys,zs, 'o');

h = get(gca,'DataAspectRatio') 
if h(3)==1
      set(gca,'DataAspectRatio',[1 1 1/max(h(1:2))])
else
      set(gca,'DataAspectRatio',[1 1 h(3)])
end
grid

f = pi/4
t = 33*pi/180

perspec = [ cos(f) sin(f)*sin(t) -sin(f)*cos(t) ;
            0 cos(t) sin(t) 
            sin(f) -cos(f)*sin(t) cos(f)*cos(t) ]
        
for i =1:11
    p = [xs(i) ys(i) zs(i)]
    pp = p*perspec
    xs(i) = pp(1)
    ys(i) = pp(2)
    zs(i) = pp(3)
end

figure
plot(xs,ys,'--b')
grid

figure
plot(ys,zs,'--g')
grid

figure
plot(xs, zs,'--r')
grid