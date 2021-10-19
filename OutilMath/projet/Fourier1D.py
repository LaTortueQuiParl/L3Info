import numpy as np
import cmath
import math

def FFT1D(A):
    N = np.size(A)
    I = np.zeros(N, dtype=complex)
    for k in range(N):
        s=0.0+0.0j
        for x in range(N):
            s = s + A[x]*cmath.exp(-2j*math.pi*k*x/N)
        I[k] = s
    return I

def FFT1DInv(A):
    N = np.size(A)
    I = np.zeros(N, dtype=complex)
    for k in range(N):
        s=0.0+0.0j
        for x in range(N):
            s = s + A[x]*cmath.exp(+2j*math.pi*k*x/N)
        I[k] = (1/N) * s
    return I


A=np.array([1,4,2])
B = FFT1D(A)
C = FFT1DInv(B)
print(B)
print(C)