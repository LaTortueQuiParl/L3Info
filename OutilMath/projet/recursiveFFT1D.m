function Y = recursiveFFT1D(X, N, s)
    if (N==1)
        Y(1) = x(1);
    else
        Yd = recursiveFFT1D(X, N/2, 2*s);
        Yg = recursiveFFT1D(X+s, N/2, 2*s);           
        for k=0:N/2-1
           p = Y(k+1);
           q = exp((-2*1i*k*pi)/N) * Y(1+k+N/2);
           Y(k+1) = p + q;
           Y(1 + k + N/2) = p - q;
        end
    end
end

%function Y = recursiveFFT1D(A, N, x)
%    if (x==0)
%        Y(x+1) = Y(x+1) + A(1);
%    end
%    if (mod(x,2) == 0)
%        Y(x) = A(x) * exp(-2*1i*pi*x/(N/2)) + recursiveFFT1D(A, N, x-1);
%    end
%end

   
