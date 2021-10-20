import numpy as np
import cmath
import math

from numpy import fft

def FFT1D(A):
    N = np.size(A)
    I = np.zeros(N, dtype=complex)
    for k in range(N):
        s=0.0+0.0j
        for x in range(N):
            s = s + A[x]*cmath.exp(-2j*math.pi*k*x/N)
        I[k] = s
    return I

def IFFT1D(A):
    N = np.size(A)
    I = np.zeros(N, dtype=complex)
    for k in range(N):
        s=0.0+0.0j
        for x in range(N):
            s = s + A[x]*cmath.exp(+2j*math.pi*k*x/N)
        I[k] = (1/N) * s
    return I

def Verif1D(A,B):
    dim = A.shape
    x = dim[0]
    for i in range(x):
        a = A[i]
        b = B[i]
        c = a-b
        if(c>(10**-14)):
            return "La différence est trop grande !!"
    return "La différence est négligeable car <10^-15"

A=np.array([1,4,2])
B = FFT1D(A)
D = np.fft.fft(A)
C = IFFT1D(D)
E = np.fft.ifft(D)
print(B)
print(D)
print(Verif1D(B,D))
print(C)
print(E)
print(Verif1D(C,E))