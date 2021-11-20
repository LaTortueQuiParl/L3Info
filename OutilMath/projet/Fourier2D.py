import numpy as np
import cmath
import math

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

def DFT1D(A): #Transformer de fourier Discrete 1D
    N = A.shape[0] #Recupere la taille de A
    n = np.arange(N) #creer un tableau / matrice de taille N avec les valeurs allant de 0 à N-1
    k = n.reshape((N, 1)) #Transforme la matrice ligne n en matrice colonne
    M = np.exp(-2j * np.pi * k * n / N) #creer une matrice de taille 3*3 avec le calcul de l'exponentiel dont on a besoin
    return np.dot(M, A) # retourne le calcul matriciel de la matrice M avec la matrice A

def FFT1D(A):
    N = np.shape(A)[0] #Recupere la taille de A
    if N%2 > 0:
        raise ValueError("Test")
    elif  N <= 32:
        return DFT1D(A)
    else:
        B = FFT1D(A[::2]) #execute la FFT sur un tableau de taille N/2 avec tout les éléments d'indice pair de A
        C = FFT1D(A[1::2]) #execute la FFT sur un tableau de taille N/2 avec tout les éléments d'indice impair de A
        exp = np.exp(-2j* np.pi * np.arange(N) / N) #cree un tableau de taille N avec le calcul de l'exponentiel dont on a besoin
        return np.concatenate([B + exp[:(int)(N/2)] * C, B + exp[(int)(N/2):] * C]) #retourne la concatenation de tout les tableaux pour obtenir la nouvelle matrice FFT(A)

def FFT2D(A):
    N = np.shape(A)[0] # On récupère la taille de A qui est de taille NxN
    I = np.zeros((N,N), dtype=complex) # Matrice intermédiaire qui contient les transformées de Fourrier de toutes les lignes de A
    R = np.zeros((N,N), dtype=complex) # La transformée de fourrier de A
    for i in range(N): # On calcule les transformée des colonnes plus lignes, l'ordre est interchangeable
        #I[i] = np.fft.fft(A[i]) # On applique FFT1D sur chaque ligne de la matrice A
        I[:, i] = np.fft.fft(A[:, i]) # On applique FFT1D sur chaque colonne de la matrice A
    for j in range(N):
        #R[:, j] = np.fft.fft(I[:, j]) # On applique FFT1D sur chaque colonne de la matrice intermédiaire I
        R[j] = np.fft.fft(I[j]) # On applique FFT1D sur chaque ligne de la matrice intermédiaire I
    return R

#A=np.array([[1,4,2],[4,9,3]])
np.random.seed(0)
n=4
A=np.random.randint(5, size=(n,n))

#B = FT2D(A)
D = np.fft.fft2(A)
#print(np.allclose(B,D))

#C = IFT2D(D)
#E = np.fft.ifft2(D)
#print(np.allclose(C,E))

F = FFT2D(A)
print(np.allclose(F, D))
