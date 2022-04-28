class Graph:
    def __init__(self):
        self.nodes = []
        self.edges = []
        self.position = []
        self.couleur = []
        self.degree = []

    def add_node(self, n):
        if n not in self.nodes:
            self.nodes.append(n)
            self.position.append([n, [0,0]])
            self.couleur.append([n, 0])
            self.degree.append([n, 0])
            self.degree.sort()
            self.couleur.sort()
            self.position.sort()
            self.nodes.sort()

    def add_edge(self, n1, n2):
        if n1 in self.nodes and n2 in self.nodes:
            if (n1, n2) not in self.edges and (n2, n1) not in self.edges:
                if n1 <= n2:
                    self.edges.append((n1, n2))
                else:
                    self.edges.append((n2, n1))
                #Augmetation des degrés des noeud n1 et n2
                for i in self.degree:
                    if i[0] == n1:
                        i[1] += 1
                    if i[0] == n2:
                        i[1] += 1
            self.edges.sort()
        else:
            print(n1, " ou/et ", n2, " n\'est pas un noeud.")

    def get_edges(self, n):
        
        res = [i for i in self.edges if i[0] == n or i[1] == n]
        return res

    def get_position(self, n):

        pos = []
        for i in self.position:
            if i[0] == n:
                pos.append(i[1][0])
                pos.append(i[1][1])
        return pos

    def modif_position(self, n, pos):
        for i in self.position:
            if i[0] == n:
                i[1][0] = pos[0]
                i[1][1] = pos[1]

    def modif_couleur(self, n, coul):
        for i in self.couleur:
            if i[0] == n:
                i[1] = coul

    def remove_node(self, n):

        self.nodes.remove(n) #Suppression du noeud dans la liste de noeud

        #Suppression de toutes les arêtes en lien avec le noeud
        for i in self.edges:
            if i[0] == n:
                del self.edges[self.edges.index(i)]
                for j in self.degree:
                    if j[0] == i[1]:
                        j[1] -= 1
            elif i[1] == n:
                del self.edges[self.edges.index(i)]
                for j in self.degree:
                    if j[0] == i[0]:
                        j[1] -= 1

        #Suppression de la position du noeud
        for i in self.position:
            if i[0] == n:
                del self.position[self.position.index(i)]

        #Suppression du degré du noeud
        for i in self.degree:
            if i[0] == n:
                del self.degree[self.degree.index(i)]

        #Suppression de la couleur du noeud
        for i in self.couleur:
            if i[0] == n:
                del self.couleur[self.couleur.index(i)]