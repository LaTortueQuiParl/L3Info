class Graph:
    def __init__(self):
        self.nodes = []
        self.edges = []
        self.position = []
        self.couleur = []

    def add_nodes(self, n):
        if n not in self.nodes:
            self.nodes.append(n)
            self.position.append((n, [0,0]))
            self.couleur.append([n, 0])
            self.couleur.sort()
            self.position.sort()
            self.nodes.sort()

    def add_edge(self, n1, n2):
        if n1 in self.nodes and n2 in self.nodes:
            if (n1, n2) not in self.edges and (n2, n1) not in self.edges:
                self.edges.append((n1, n2))
                self.edges.append((n2, n1))
            self.edges.sort()
        else:
            print(n1, " ou/et ", n2, " n\'est pas un noeud.")

    def modif_position(self, n, pos):
        for i in self.position:
            if i[0] == n:
                i[1][0] = pos[0]
                i[1][1] = pos[1]

    def modif_couleur(self, n, coul):
        for i in self.couleur:
            if i[0] == n:
                i[1] = coul