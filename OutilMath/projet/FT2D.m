function F = FT2D(I)
    tmp=size(I);
    N=tmp(1);
    M=tmp(2);
    F=zeros(N,M);
    for u = 1:N
        for v = 1:M
            S=0;
            for x=1:N
                for y=1:M
                    S = S + I(x,y)*exp(-2*1i*pi*(((u-1)*(x-1)/N) + ((y-1)*(v-1)/M)));
                end
            end
            F(u,v) = S;
        end
    end
end

