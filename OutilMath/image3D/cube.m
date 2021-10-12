J = rgb2gray(imread("Image151.jpg"));
K = rgb2gray(imread("Image153.jpg"));

cubeD = double(J)/double(max(max(J)));
cubeG = double(K)/double(max(max(K)));

tmp = size(cubeD);
N = tmp(1);
M = tmp(2);

A = zeros(N,M);

qmin = zeros(N-1,2);

for i = 2:N-1
   for j = 2:M-1
       s = 1000;
       B = [cubeG(i-1,j-1), cubeG(i-1,j), cubeG(i-1, j+1);
           cubeG(i, j-1), cubeG(i,j), cubeG(i,j+1);
           cubeG(i+1, j-1), cubeG(i+1,j), cubeG(i+1, j+1)];
       for k = 2:M-1
           C = [cubeD(i-1,k-1), cubeD(i-1,k), cubeD(i-1, k+1);
           cubeD(i, k-1), cubeD(i,k), cubeD(i,k+1);
           cubeD(i+1, k-1), cubeD(i+1,k), cubeD(i+1, k+1)];
           q = (B(1,1) - C(1,1))^2 + (B(1,2) - C(1,2))^2 + (B(1,3) - C(1,3))^2 + (B(2,1) - C(2,1))^2 + (B(2,2) - C(2,2))^2 + (B(2,3) - C(2,3))^2 + (B(3,1) - C(3,1))^2 + (B(3,2) - C(3,2))^2 + (B(3,3) - C(3,3))^2;
           if (s > q)
               s = q;
               A(i,j) = i-k;
           end
       end
   end
end
mesh(A)
