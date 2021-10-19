N=10; % On testera pour tous les tableaux de taille 1 à N
V=10; % Les tableaux auront des valeurs comprises entre 1 et V
direct=0; % Transformée direct lorsque direct=0
indirect=1; %  Transformée indirect lorsque indirect=1
%resultatFFT1D = testFunc(@FFT1D, N, V, direct);
%resultatiFFT1D = testFunc(@iFFT1D, N, V, indirect)
%resultatFT2D = testFunc(@FT2D, N, V, direct, 2);
rng(1)
A=randi(V, [1, N]);
x = 1;
resultatrecFFT1D = recursiveFFT1D(A, N, x)