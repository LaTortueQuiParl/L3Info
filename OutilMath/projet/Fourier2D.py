import numpy as np
import cmath
import math

from numpy import fft

def FFT2D(A):
    dim = A.shape
    M = dim[0]  #nombre de colonnes dans la matrice A
    N = dim[1]  #nombre de ligne dans la matrice A
    I = np.zeros((M,N), dtype=complex)
    for u in range(M):
        for v in range(N):
            s=0.0+0.0j
            for x in range(M):
                for y in range(N):
                    s = s + A[x][y]*cmath.exp(-2j*math.pi*((u*x/M)+(v*y/N)))
            I[u][v] = s
    return I

def IFFT2D(A):
    dim = A.shape
    M = dim[0]  #nombre de ligne dans la matrice A
    N = dim[1]  #nombre de colonne dans la matrice A
    I = np.zeros((M,N), dtype=complex)
    for u in range(M):
        for v in range(N):
            s=0.0+0.0j
            for x in range(M):
                for y in range(N):
                    s = s + A[x][y]*cmath.exp(+2j*math.pi*((u*x/M)+(v*y/N)))
            I[u][v] = (1/(M*N)) * s
    return I

def Verif2D(A,B):
    dim = A.shape
    x = dim[0]
    y = dim[1]
    for i in range(x):
        for j in range(y):
            a = A[i][j]
            b = B[i][j]
            c = a-b
            if(c>(10**-14)):
                return "La différence est trop grande !!"
    return "La différence est négligeable car <10^-15"

A=np.array([[1,4,2],[4,9,3]])
B = FFT2D(A)
D = np.fft.fft2(A)
C = IFFT2D(D)
E = np.fft.ifft2(D)
print(B)
print(D)
print(Verif2D(B,D))
print(C)
print(E)
print(Verif2D(C,E))