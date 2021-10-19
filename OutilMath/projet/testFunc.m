function [result] = testFunc(func, N, V, dir)
    if (N == 0 || V == 0)
        "N = 0 || V = 0 is not valid"
        result=0;
    else
        rng(1)
        result = zeros([1,N]);
        ref = 10^-12;
        for i=1:N
            if(dir== 0)
                A = randi(V, [1,N]);
                res=func(A);
                LaFft=fft(A);
                R=res-LaFft;
            else 
                A = randi(V, [1,N]);
                ffA = FFT1D(A);
                res = func(ffA);
                %abs(ffA - res)
                iFft=ifft(fft(A));
                R=(1/N)*res-iFft;
            end
            for j=1:i
                if (real(R(j)) < ref)
                    result(j) = 1;
                end
            end
        end
    end
end