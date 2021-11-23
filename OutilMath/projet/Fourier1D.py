import time
import numpy as np
import cmath
import math
from matplotlib import pyplot as plt
from scipy.optimize import curve_fit

from numpy import RAISE, concatenate, dtype, fft

def DFT1D(A): #Transformer de fourier Discrete 1D
    N = A.shape[0] #Recupere la taille de A
    n = np.arange(N) #creer un tableau / matrice de taille N avec les valeurs allant de 0 à N-1
    k = n.reshape((N, 1)) #Transforme la matrice ligne n en matrice colonne
    M = np.exp(-2j * np.pi * k * n / N) #creer une matrice de taille 3*3 avec le calcul de l'exponentiel dont on a besoin
    return np.dot(M, A) # retourne le calcul matriciel de la matrice M avec la matrice A

def DIFT1D(A): #Transformer de fourier inverse discrete 1D
    N = A.shape[0] #Recupere la taille de A
    n = np.arange(N) #creer un tableau / matrice de taille N avec les valeurs allant de 0 à N-1
    k = n.reshape((N, 1)) #Transforme la matrice ligne n en matrice colonne
    M = np.exp(2j * np.pi * k * n / N) #creer une matrice de taille 3*3 avec le calcul de l'exponentiel dont on a besoin
    return (1/N)*np.dot(M, A) # retourne le calcul matriciel de la matrice M avec la matrice A

def FFT1D(A):
    N = np.shape(A)[0] #Recupere la taille de A
    if N%2 > 0:
        raise ValueError("Test")
    elif  N <= 2:
        return DFT1D(A)
    else:
        B = FFT1D(A[::2]) #execute la FFT sur un tableau de taille N/2 avec tout les éléments d'indice pair de A
        C = FFT1D(A[1::2]) #execute la FFT sur un tableau de taille N/2 avec tout les éléments d'indice impair de A
        exp = np.exp(-2j* np.pi * np.arange(N) / N) #cree un tableau de taille N avec le calcul de l'exponentiel dont on a besoin
        return np.concatenate([B + exp[:(int)(N/2)] * C, B + exp[(int)(N/2):] * C]) #retourne la concatenation de tout les tableaux pour obtenir la nouvelle matrice FFT(A)

def IFFT1D(A):
    N = np.shape(A)[0] #Recupere la taille de A
    if N%2 > 0:
        raise ValueError("Doit être une puissance de 2")
    elif N <= 2:
        return DIFT1D(A)
    else:
        B = IFFT1D(A[::2]) #execute la FFT sur un tableau de taille N/2 avec tout les éléments d'indice pair de A
        C = IFFT1D(A[1::2]) #execute la FFT sur un tableau de taille N/2 avec tout les éléments d'indice impair de A
        exp = np.exp(+2j* np.pi * np.arange(N) / N) #cree un tableau de taille N avec le calcul de l'exponentiel dont on a besoin
        return (1/N)*np.concatenate([B + exp[:N/2] * C, B + exp[N/2:] * C]) #retourne la concatenation de tout les tableaux pour obtenir la nouvelle matrice FFT(A)


# Methodes pour executer les tests
def TestSimple(n):
    A = np.random.random(n)
    print("Transformée de Fourier1D :")
    B = DFT1D(A)
    print(B)
    print()
    C = np.fft.fft(A)
    print(C)
    print()
    print(np.allclose(B, C))
    print("Transormée de Fourier inverse 1D :")
    D = DIFT1D(np.fft.fft(A))
    print(D)
    print()
    E = np.fft.ifft(np.fft.fft(A))
    print(E)
    print()
    print(np.allclose(D, E))

def TestRapide(n):
    A = np.random.random(n)
    print("Transformée de Fourier Rapide 1D :")
    B = FFT1D(A)
    print(B)
    print()
    C = np.fft.fft(A)
    print(C)
    print()
    print(np.allclose(B, C))
    '''
    print("Transormée de Fourier Rapide inverse 1D :")
    D = IFFT1D(np.fft.fft(A))
    print(D)
    print()
    E = np.fft.ifft(np.fft.fft(A))
    print(E)
    print()
    print(np.allclose(D, E))
    '''

def func(x, a, b,c):
    return a*np.log(b+x)+c

Lfast=[]
LfastP=[]
n=16
np.random.seed(0)
for i in range(1,n):
    M = np.random.randint(0, 100,2**i)
    start2 = time.time()
    FFT1D(M)
    end2 = time.time()
    LfastP.append(end2 - start2)

T = np.arange(0,n-1)
X=[2**i for i in T]

#A = np.array(Lfast)
#plt.plot(X, A, "b:o", label="Fourier")
#plt.scatter(X, A)
#y = np.poly1d(np.polyfit(X,A,2))
#t=np.linspace(min(X), max(X), 100)
#plt.plot(t, y(t),"--", color="red", label="x²")
#plt.title("Transformée de Fourier discrète 1D")
#plt.xlabel("Taille de la matrice")
#plt.ylabel("Temps d'exécution en secondes")
#plt.legend()

plt.scatter(X, LfastP)
plt.plot(X,LfastP, label="Fourier")
plt.title("Transformée de Fourier rapide discrète 1D")
plt.xlabel("Taille de la matrice")
plt.ylabel("Temps d'exécution en secondes")
plt.legend()

plt.show()

#TestRapide(64)