function [Af] = FFT1D(A)
    tmp = size(A);
    N = tmp(2);
    if (N == 1)
        Af(1) = A(1);
    else
        Af = zeros(1,N);
        for k = 0:N-1
            sE=0;
            sO=0;
            if (mod(N,2)==0)
                for j=0:(N/2-1)
                    expoE = exp(-(2*1i*pi*(2*j)*k)/N);
                    e = A(2*j+1);
                    sE = sE + e * expoE;
                end 
            else
                for j=0:(N/2)
                    expoE = exp(-(2*1i*pi*(2*j)*k)/N);
                    e = A(2*j+1);
                    sE = sE + e * expoE;
                end
            end
            for j=0:(N/2-1)
                expoO = exp(-(2*1i*pi*(2*j+1)*k)/N);
                o = A(2*j+2);
                sO = sO + o * expoO;
            end
            Af(k+1) = sO + sE;
        end
    end
end