import numpy as np
import cmath
import time
import math
from matplotlib import pyplot as plt

from numpy import fft

def FT2D(A):
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

def IFT2D(A):
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

def FFT2D(A):
    N = np.shape(A)[0] # On récupère la taille de A qui est de taille NxN
    I = np.zeros((N,N), dtype=complex) # Matrice intermédiaire qui contient les transformées de Fourrier de toutes les lignes de A
    R = np.zeros((N,N), dtype=complex) # La transformée de fourrier de A
    for i in range(N): # On calcule les transformées des colonnes plus lignes, l'ordre est interchangeable
        #I[i] = np.fft.fft(A[i]) # On applique FFT1D sur chaque ligne de la matrice A
        I[:, i] = np.fft.fft(A[:, i]) # On applique FFT1D sur chaque colonne de la matrice A
    for j in range(N):
        #R[:, j] = np.fft.fft(I[:, j]) # On applique FFT1D sur chaque colonne de la matrice intermédiaire I
        R[j] = np.fft.fft(I[j]) # On applique FFT1D sur chaque ligne de la matrice intermédiaire I
    return R

def IFFT2D(A):
    N = np.shape(A)[0] # On récupère la taille de A qui est de taille NxN
    I = np.zeros((N,N), dtype=complex) # Matrice intermédiaire qui contient les transformées de Fourrier inverses de toutes les lignes de A
    R = np.zeros((N,N), dtype=complex) # La transformée de fourrier inverse de A
    for i in range(N): # On calcule les transformées inverses des colonnes plus lignes, l'ordre est interchangeable
        #I[i] = np.fft.ifft(A[i]) # On applique np.fft.ifft sur chaque ligne de la matrice A
        I[:, i] = np.fft.ifft(A[:, i]) # On applique np.fft.ifft sur chaque colonne de la matrice A
    for j in range(N):
        #R[:, j] = np.fft.ifft(I[:, j]) # On applique np.fft.ifft sur chaque colonne de la matrice intermédiaire I
        R[j] = np.fft.ifft(I[j]) # On applique np.fft.ifft sur chaque ligne de la matrice intermédiaire I
    return R

#A=np.array([[1,4,2],[4,9,3]])
#np.random.seed(0)
#a = True
#n = 100
#for i in range(2, n):
#    A=np.random.randint(100, size=(i,i))
#    F = FFT2D(A)
#    IF = IFFT2D(F)
#    if (np.allclose(F, np.fft.fft2(A)) == False or np.allclose(IF, A) == False):
#        a = False

#print(a)

Lfast=[]
LfastP=[]
n=13
np.random.seed(1)
for i in range(1,n):
    M = np.random.randint(0, 100,size=(2**i, 2**i))
    start2 = time.time()
    FFT2D(M)
    end2 = time.time()
    LfastP.append(end2 - start2)

T = np.arange(0,n-1)
X=[2**i for i in T]

#plt.subplot(121)
#A = np.array(Lfast)
#plt.plot(X, A, "b:o", label="Fourier")
#plt.scatter(X, A)
#y = np.poly1d(np.polyfit(X,A,2))
#t=np.linspace(min(X), max(X), 100)
#plt.plot(t, y(t),"--", color="red", label="x^4")
#plt.title("Transformée de Fourier discrète 2D")
#plt.xlabel("Taille de la matrice")
#plt.ylabel("Temps d'exécution en secondes")
#plt.legend()

plt.scatter(X, LfastP)
plt.plot(X,LfastP, label="Fourier")
plt.title("Transformée de Fourier rapide discrète 2D")
plt.xlabel("Taille de la matrice")
plt.ylabel("Temps d'exécution en secondes")
plt.legend()


plt.show()
#B = FT2D(A)
#print(np.allclose(B,D))

#C = IFT2D(D)
#E = np.fft.ifft2(D)
#print(np.allclose(C,E))
