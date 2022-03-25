from asyncore import write
from nis import match
import numpy as np
from graphviz import Graph

def from_snap():
    with open(f"graph.snap", "r") as graph_file:
        max = 0
        dot_graph = Graph()
        for line in graph_file.readlines():
            i,j = line.split(" ")
            j.strip("\n")
            if (int(i) > max):
                max = int(i)
            if (int(j) > max):
                max = int(j)

        graph = [[] for i in range(max+1)]
        for i in range(max+1):
            dot_graph.node(f'{i}', f'{i}')

        graph_file.seek(0)
        for line in graph_file.readlines():
            i,j = line.split(" ")
            j.strip("\n")
            i,j = int(i), int(j)
            dot_graph.edge(f'{i}', f'{j}')
            if (j not in graph[i]):
                graph[i].append(j)
            if (i not in graph[j]):
                graph[j].append(i)

    with open("graph.dot", "w") as file:
        file.write(dot_graph.source)
    return graph

n = 10
def write_snap():
    with open("graph.snap", "w") as file:
        for i in range(n):
            file.write(f"{np.random.randint(n)} {np.random.randint(n)}\n")


def degen(G):
    degen = 1
    centre = [-1 for i in range(len(G))]
    while not all([len(v)==0 for v in G]):
        for i in range(len(G)):
            if len(G[i]) == degen:
                centre[i] = degen
                for deleting in G[i]:
                    G[i].remove(deleting)
                    G[deleting].remove(i)
                    print(f"{deleting=}")
                    print(f"{i=}")
        degen+=1
    return centre


def main(args = None) -> None:
    #np.random.seed(2)
    #write_snap()
    G = from_snap()
    print(f"{G=}")
    centre = degen(G)
    print(centre)




if __name__ == "__main__":
    main()