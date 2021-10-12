%频域分析稳定性，计算幅值和相角裕度
%PITCH内环参数
% ks=0.0446;
% kp=1500;
% kd=28;
% num=[0 kd*ks kp*ks];
% den=[0.05 1 0];
%PITCH外环
% kp=10;
% num=[0 kp*1.249 kp*66.9];
% den=[0.05 2.249 66.9 0];
% s1=tf(num,den);%开环传函
% margin(s1)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%roll-IN-LOOP
% ks=0.08;
% kp=600;
% kd=25;
% num=[0 kd*ks kp*ks];
% den=[0.05 1 0];
%ROLL-OUT-LOOP
% kp=13;
% num=[0 kp*1.6 kp*44];
% den=[0.05 2.6 44 0];
% s2=tf(num,den);%开环传函
% margin(s2)
%%%%%%%%%%%%%%%%%%%%%%
%height_control
% ks=0.00864;
% kp=300;
% kd=1800;
% num=[0 0 kd*ks kp*ks];
% den=[0.05 1 0 0];
% s3=tf(num,den);%开环传函
% margin(s3)
%%%%%%%%%%%%%%%%%%%%%%%%%
%YAW内环参数
% ks=0.0259;
% kp=2800;
% kd=55;
% num=[0 kd*ks kp*ks];
% den=[0.045 1 0];
% %YAW外环
% kp=12;
% num=[0 kp*1.425 kp*72.52];
% den=[0.045 2.425 72.52 0];
% s4=tf(num,den);%开环传函
% margin(s4)
%%%%%%%%%%%%%%%%%%%%%%%%
%HEIGHT内环参数
% ks=0.00864;
% kp=1000;
% kd=1000;
% ki=700;
% num=[0 kd*ks kp*ks ki*ks];
% den=[0.05 1 0 0 0]; 
%%%%%%%%%%%%%%%%%%%%%%%%
% num=[0 0.0039 0.00236];
% den=[0.045 1.09 2.163 3.847];
% s5=tf(num,den);%开环传函
% rlocus(s5)
% [k,poles]=rlocfind(s5)
% kp=6500;
% kd=1000;
% num=[0 0 0.0039*kd 0.0039*kp+0.00236*kd 0.00236*kp];
% den=[0.045 1.09 3.138 4.437 0];
kp=6000;
kd=1500;
ki=100;
num=[0 0 0.0039*kd 0.0039*kp+0.00236*kd 0.00236*kp+0.0039*ki 0.0023*ki];
den=[0.045 1.09 3.138 4.437 0 0];
s6=tf(num,den);%开环传函
margin(s6)