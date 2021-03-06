%中国石油天然气集团公司在东海有一个油气田（节点vs），该公司要将开采的天然气
%通过管道运送到上海的一个配送中心（节点vt），天然气在运送途中要经过两次管道换接
%点（节点B和C），换接前后管道长短不一，而且不同的管道对应不同的单位流量运费。
%如图，天然气运送的管道网络图，弧线表示管道，弧旁的数字为（bij,cij）,
%其中bij表示管道上的单位流量费用，cij表示管道上的容量。
%公司希望选择一个经济实惠的管道路线运送天然气，既运送最多的天然气又使总的运输费用最少。
clear
f=-[1,1,0,0,0,0,0,0,0]; 
aeq=[1,0,-1,-1,1,0,0,0,0; 0,1,1,0,0,-1,0,0,0; 0,0,0,1,0,0,1,-1,0; 0,0,0,0,-1,1,-1,0,-1];
beq=zeros(4,1);
lb=zeros(9,1);
ub=[4;5;1;3;1;2;3;5;2];
[x,fval]=linprog(f,[],[],aeq,beq,lb,ub); %求出最大流
f1=[1,3,1,3,2,4,1,2,4];
aeq1=[ 1,1,0,0,0,0,0,0,0; 1,0,-1,-1,1,0,0,0,0; 0,1,1,0,0,-1,0,0,0; 0,0,0,1,0,0,1,-1,0; 0,0,0,0,-1,1,-1,0,-1]; 
beq1=[-fval;beq];
[z,fvall]=linprog(f1,[],[],aeq1,beq1,lb,ub);