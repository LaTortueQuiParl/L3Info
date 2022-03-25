import networkx as nx
import matplotlib.pyplot as plt
import numpy as np


def genereGraphFromSnap():
    with open(f"graph.snap", "r") as graph_file:
        max = 0
        for line in graph_file.readlines():
            i,j = line.split(" ")
            j.strip("\n")
            if(int(i) > max):
                max = int(i)
            if(int(j) > max):
                max = int(j)

        graph = [i for i in range(max+1)]
        G2.add_nodes_from(graph)
        for k in range (max+1):
            G.add_node(graph[k], pos=(2*np.cos((k*np.pi)/((max+1)/2)), 2*np.sin((k*np.pi)/((max+1)/2))))

        graph_file.seek(0)
        for line in graph_file.readlines():
            i,j = line.split(" ")
            j.strip("\n")
            G.add_edge(int(i), int(j))
            G2.add_edge(int(i), int(j))

def dessinerGraphe():
    pos = nx.get_node_attributes(G,'pos')

    nx.draw(G, pos, with_labels=True, font_size=12,font_weight='bold')
    plt.axis("off")
    plt.show()
    #plt.savefig("path.png")

def degenerecence():
    degen = 1
    ok = False
    while(True):
        while(ok == False):
            index = []
            for i in G2.degree():
                if i[1] <= degen:
                    index.append(i[0])
            for i in index:
                G2.remove_node(i)

            if len(index) == 0:
                ok = True

        ok=False
        if len(G2.degree()) == 0:
            return degen
        else :
            degen+=1


G = nx.Graph()
G2 = nx.Graph()

genereGraphFromSnap()
print("degenerecence = ", degenerecence())
#dessinerGraphe()
print(G)
print(G.degree(0))
#nx.draw(G)


