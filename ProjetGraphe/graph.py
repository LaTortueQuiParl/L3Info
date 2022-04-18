import networkx as nx
import matplotlib.pyplot as plt
import numpy as np
import sys

def genereGraphFromSnap():
    #Création d'un graphe vide grace à networkx
    G = nx.Graph()
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
        G.add_nodes_from(graph)
        
        #On reparcours le fichier pour ajouter les arêtes
        graph_file.seek(0)
        for line in graph_file.readlines():
            i,j = line.split(" ")
            j.strip("\n")
            G.add_edge(int(i), int(j))
    
    return G

def dessinerGraphe(G, centres):
    pos = nx.get_node_attributes(G,'pos')

    nx.draw(G, pos, with_labels=True, font_size=12,font_weight='bold')

    ax = plt.gca()

    for i in range(max(centres)):
        circle = plt.Circle((0, 0), i+1, fill=False, color = 'red')
        ax.add_patch(circle)


    plt.axis("equal")

    #Affichage direct du graphe
    #plt.show()
    #Enregistrement du graphe au format PDF
    #plt.savefig("path.pdf")

def degenerecence(G):
    degen = 1 #Initialisation de la dégénérescence à 1 (la dégénéréscence minimal)
    degSupDegen = False #Savoir quand sortir d'une boucle
    G2 = nx.Graph(G) #Copie du graphe pour travailler plus simplement dessus
    centres = [-1 for i in G.nodes()] #Initialisation du tableau de centres à -1
    while(True):
        while(degSupDegen == False):
            index = []
            for i in G2.degree():
                if i[1] <= degen:
                    index.append(i[0]) #Mise en mémoire du noeuds de degré inférieur ou égal à degen
                    centres[i[0]] = degen #Mise à jour du tableau de centres du graphe G
            for i in index:
                G2.remove_node(i) #Suppression du noeud i qui met à jour le degré des autres noeuds

            if len(index) == 0:
                degSupDegen = True #Si tout les degrés du graphe sont supérieur à la dégénéréscence, on passe à true

        degSupDegen=False
        if len(G2.degree()) == 0:
            return degen, centres #Retourne le tableau de centres ainsi que la dégénéréscence du graphe lorsque tout les noeuds ont étés supprimés de G2
        else :
            degen+=1

def modifPos(G, degenGraph, centres):
    #NetworkX propose déjà une méthode pour afficher en cercle le graphe, mais on le refais ici

    nbnoeuds = max(G.nodes())
    for i in G.nodes():
        rayon = (degenGraph-centres[i]+1)
        alpha1 = (i*np.pi)/((centres.count(max(centres))+1)/2)
        alpha2 = (i*np.pi)/((nbnoeuds+1)/2)
        #On fait un cercle avec les noeuds qui ont le plus grand centre
        if centres[i] == max(centres):
            G.nodes[i]['pos'] = (rayon*np.cos(alpha1), rayon*np.sin(alpha1))
        # on fait un autre cercle avec tout les autres noeuds et de leurs centre
        else:
            G.nodes[i]['pos'] = (rayon*np.cos(alpha2), rayon*np.sin(alpha2))

def sortNodes(centres):
    #Création d'une liste intermédiaire qui va contenir des listes contenant le sommet qui ont ce centre
    # ex : inter[1] contient tous les sommets qui sont de centre 2
    inter = [[] for i in range(0, max(centres))]
    k = 0
    for i in centres:
        # On met dans la liste des centres i (indexée à i-1), le sommet k
        inter[i-1].append(k)
        k += 1
    return sorted([item for sublist in inter for item in sublist], reverse=True)

def colorGlouton(G, centres):

    color = [-1 for i in G.nodes()]

    #On parcourt tous les noeuds de notre graphe suivant le numéro de centre décroissant
    for i in sortNodes(centres):
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
        G.nodes[i]['color'] = 'r'
    return color

def TestGraphe():
    G = genereGraphFromSnap()

    print(G)

    #Calcul de la dégénérécence du graphe G
    degenGraph, centres = degenerecence(G)
    print("degenerecence = ", degenGraph)

    #Calcul de la coloration du graphe G
    color = colorGlouton(G, centres)
    print("nb Couleur utilisés : ", max(color)+1)

    print("Graph =", G.nodes())
    print(f"{centres = }")
    print(f"{color = }")

    modifPos(G, degenGraph, centres)

    dessinerGraphe(G, centres)


TestGraphe()