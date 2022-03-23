from asyncore import write
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

n = 100
def write_snap():
    with open("graph.snap", "w") as file:
        for i in range(100):
            file.write(f"{np.random.randint(100)} {np.random.randint(100)}\n")


def degen(G):
    degen = 0
    for i in range(len(G)):
        if len(G[i]) == degen:
            for deleting in G[i]:
                G[i].remove(deleting)
                deleting.remove(i)


def main(args = None) -> None:
    np.random.seed(1)
    write_snap()
    G = from_snap()
    degen(G)




if __name__ == "__main__":
    main()