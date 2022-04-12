import networkx as nx
import matplotlib.pyplot as plt
import numpy as np
import sys

def genereGraphFromSnap():
    #on ouvre le fichier snap
    with open(sys.argv[1], "r") as graph_file:
        max = 0
        for line in graph_file.readlines():
            i,j = line.split(" ")
            j.strip("\n")
            if(int(i) > max):
                max = int(i)
            if(int(j) > max):
                max = int(j)

        graph = [i for i in range(max+1)]
        G.add_nodes_from(graph)
        
        graph_file.seek(0)
        for line in graph_file.readlines():
            i,j = line.split(" ")
            j.strip("\n")
            G.add_edge(int(i), int(j))

def dessinerGraphe():
    pos = nx.get_node_attributes(G,'pos')
    #pos = nx.circular_layout(G, 2)
    nx.draw(G, pos, with_labels=True, font_size=12,font_weight='bold')

    ax = plt.gca()

    for i in range(max(centres)):
        circle = plt.Circle((0, 0), i+1, fill=False, color = 'red')
        ax.add_patch(circle)


    plt.axis("equal")
    plt.show()
    #plt.savefig("path.pdf")

def degenerecence(G):
    degen = 1
    ok = False
    G2 = nx.Graph(G)
    centres = [-1 for i in G.nodes()]
    while(True):
        while(ok == False):
            index = []
            for i in G2.degree():
                if i[1] <= degen:
                    index.append(i[0])
                    centres[i[0]] = degen
            for i in index:
                G2.remove_node(i)

            if len(index) == 0:
                ok = True
        ok=False
        if len(G2.degree()) == 0:
            return degen, centres
        else :
            degen+=1

def modifPos():

    nbnoeuds = max(G.nodes())
    for i in G.nodes():
        rayon = (degenGraph-centres[i]+1)
        alpha1 = (i*np.pi)/((centres.count(max(centres))+1)/2)
        alpha2 = (i*np.pi)/((nbnoeuds+1)/2)
        #On fait un cercle avec les noeuds qui ont le plus grand sommet
        if centres[i] == max(centres):
            G.nodes[i]['pos'] = (rayon*np.cos(alpha1), rayon*np.sin(alpha1))
        # on fait un autre cercle avec tout les autres noeuds
        else:
            G.nodes[i]['pos'] = (rayon*np.cos(alpha2), (degenGraph-centres[i]+1)*np.sin(alpha2))

def colorGlouton():

    color = [-1 for i in G.nodes()]

    #On parcourt tous les noeuds de notre graphe
    for i in G.nodes():

        #initialisation de la couleur à "0"
        couleur = 0
        #récupération des couleurs des noeuds voisins
        couleurvoisins = [color[edge[1]] for edge in G.edges(i)]
        couleurvoisins.sort() #tri dans l'ordre croissant
        for j in range(len(couleurvoisins)):
            if couleurvoisins[j] == couleur:
                couleur += 1

        #affectation de la couleur "minimale" dans le tableau de couleur
        color[i] = couleur
    return color


#Création d'un graphe vide
G = nx.Graph()

genereGraphFromSnap()

print(G)

#Calcul de la dégénérécence du graphe G
degenGraph, centres = degenerecence(G)
print("degenerecence = ", degenGraph)

#Calcul de la coloration du graphe G
color = colorGlouton()
print("nb Couleur utilisés : ", max(color)+1)

print(G.nodes())
print(centres)
print(color)

modifPos()

dessinerGraphe()
