import matplotlib.pyplot as plt
import numpy as np
import sys
import copy
from classGraph import Graph

def genereGraphFromSnap():
    #Création d'un graphe vide à l'aide de la classGraph
    G = Graph()
    #on ouvre le fichier snap
    with open(sys.argv[1], "r") as graph_file:
        max = 0 #Plus grand noeud présent dans le graphe (ex : si max=3 alors les noeuds sont : {0,1,2,3})
        for line in graph_file.readlines():

            i,j = line.split(" ")
            j.strip("\n")

            #Mise à jour du noeud Maximal
            if(int(i) > max):
                max = int(i)
            if(int(j) > max):
                max = int(j)

        #Création du graphe en ajoutant tout les noeuds de 0 à max
        graph = [i for i in range(max+1)]
        for i in graph:
            G.add_node(i)
        
        #On reparcours le fichier pour ajouter les arêtes
        graph_file.seek(0)
        for line in graph_file.readlines():
            i,j = line.split(" ")
            j.strip("\n")
            G.add_edge(int(i), int(j))
    
    return G

def dessinerGraphe(G, centres):
    X, Y, size = [G.position[i][1][0] for i in G.nodes], [G.position[i][1][1] for i in G.nodes], [100 for i in G.nodes]

    if max(centres) <= 8:
        color_cycle= ["red","green","blue","brown","orange","grey","yellow","pink"]

        for i in G.nodes:
            plt.scatter(G.position[i][1][0], G.position[i][1][1], c=color_cycle[centres[i]])
    else:
        plt.scatter(X,Y)

    for i in G.nodes:
        plt.text(X[i],Y[i],str(i))

    for i in G.edges:
        plt.plot([X[i[0]], X[i[1]]], [Y[i[0]], Y[i[1]]], color='blue')

    ax = plt.gca()

    for i in range(max(centres)):
        circle = plt.Circle((0, 0), i+1, fill=False, color = 'red')
        ax.add_patch(circle)


    plt.axis("equal")

    #Enregistrement du graphe au format PDF
    print("Voulez-vous enregistrer au format PDF ? [Y/N]")
    rep = input()
    if rep == 'Y':
        plt.savefig("graph.pdf")
    #Affichage direct du graphe
    plt.show()
    

def degenerecence(G2):
    degen = 1 #Initialisation de la dégénérescence à 1 (la dégénéréscence minimal)
    degSupDegen = False #Savoir quand sortir d'une boucle
    
    centres = [-1 for i in G2.nodes] #Initialisation du tableau de centres à -1
    while(True):
        while(degSupDegen == False):
            index = []
            for i in G2.degree:
                if i[1] <= degen:
                    index.append(i[0]) #Mise en mémoire du noeuds de degré inférieur ou égal à degen
                    centres[i[0]] = degen #Mise à jour du tableau de centres du graphe G
            for i in index:
                G2.remove_node(i) #Suppression du noeud i qui met à jour le degré des autres noeuds

            if len(index) == 0:
                degSupDegen = True #Si tout les degrés du graphe sont supérieur à la dégénéréscence, on passe à true

        degSupDegen=False
        if len(G2.degree) == 0:
            return degen, centres #Retourne le tableau de centres ainsi que la dégénéréscence du graphe lorsque tout les noeuds ont étés supprimés de G2
        else :
            degen+=1

def modifPos(G, degenGraph, centres):
    nbnoeuds = max(G.nodes)
    for i in G.nodes:
        rayon = (degenGraph-centres[i]+1)
        alpha1 = (i*np.pi)/((centres.count(max(centres))+1)/2)
        alpha2 = (i*np.pi)/((nbnoeuds+1)/2)
        #On fait un cercle avec les noeuds qui ont le plus grand centre
        if centres[i] == max(centres):
            G.modif_position(i, [rayon*np.cos(alpha1), rayon*np.sin(alpha1)])
        # on fait un autre cercle avec tout les autres noeuds et de leurs centre
        else:
            G.modif_position(i, [rayon*np.cos(alpha2), rayon*np.sin(alpha2)])

def sortNodes(centres):
    #Création d'une liste intermédiaire qui va contenir des listes contenant le sommet qui ont ce centre
    # ex : inter[1] contient tous les sommets qui sont de centre 2
    inter = [[] for i in range(0, max(centres))]
    i = 0
    for k in centres:
        # On met dans la liste des centres k (indexée à k-1), le sommet i
        inter[k-1].append(i)
        i += 1
    return reversed([item for sublist in inter for item in reversed(sublist)])

def colorGlouton(G, centres):

    color = [-1 for i in G.nodes]

    #On parcourt tous les noeuds de notre graphe suivant le numéro de centre décroissant
    for i in sortNodes(centres):
        #initialisation de la couleur à "0"
        couleur = 0
        #récupération des couleurs des noeuds voisins
        couleurvoisins = []
        for edge in G.get_edges(i):
            k = 1 if edge[0]==i else 0
            couleurvoisins.append(color[edge[k]])
        couleurvoisins.sort() #tri dans l'ordre croissant
        for j in range(len(couleurvoisins)):
            if couleurvoisins[j] == couleur:
                couleur += 1

        #affectation de la couleur "minimale" dans le tableau de couleur
        color[i] = couleur
    return color

def TestGraphe():
    G = genereGraphFromSnap()

    print(f"{G.nodes = }")

    #Calcul de la dégénérécence du graphe G
    degenGraph, centres = degenerecence(copy.deepcopy(G))
    
    #Calcul de la coloration du graphe G
    color = colorGlouton(G, centres)
    
    print(f"{centres = }")
    print(f"{color = }")
    print("degenerecence = ", degenGraph)
    print("nb Couleur utilisés : ", max(color)+1)
    

    modifPos(G, degenGraph, centres)

    dessinerGraphe(G, centres)
    

TestGraphe()