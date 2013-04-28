#!/usr/bin/env python
# encoding: utf-8
"""
Voight Kampff python implementation
http://olimpiada-informatica.org/?cmd=problema&pbm=voightkampff

Olimpiada Matemática Española, Graphs section
"""
import sys

subjects = None
graph = None


class Graph(object):
    nodes = {}  # Dict with node id (name) and dict with neighbours
    human = {}  # Init node values to none by default
    edge_values = {}
    is_consistent = True

    def add_node(self, id):
        self.nodes[id] = {}
        self.human[id] = None
        self.edge_values[id] = {}

    def add_edge(self, source, dest, isHuman):
        # Special case:
        # subject statement inconsistent with previous statement of the same subject.
        if dest in self.edge_values[source]:
            if self.edge_values[source][dest] is not isHuman:
                self.is_consistent = False
        # Special case:
        # subject statement inconsistent with another subject statement (if they accuse each other,
        # they must report the same).
        if source in self.edge_values[dest]:
            if not isHuman is self.edge_values[dest][source]:
                self.is_consistent = False

        self.edge_values[source][dest] = isHuman

        def says():
            if self.human[source]:  # If source is human, destination is whatever source says
                return isHuman
            else:  # Otherwise, destination is the contrary to what source says it is
                return not isHuman

        def is_said():
            return self.human[dest] is isHuman  # If source has not lied, source is human

        self.nodes[source][dest] = says
        self.nodes[dest][source] = is_said

    def del_edge(self, source, dest):
        del self.nodes[source][dest]
        del self.nodes[dest][source]


def parse():
    global subjects
    global graph
    line = sys.stdin.readline()
    data = line.split()
    numSubjects = int(data[0])
    numStatements = int(data[numSubjects + 1])
    subjects = data[1:numSubjects + 1]
    graph = Graph()
    for subject in subjects:
        graph.add_node(subject)
    for x in xrange(numStatements):
        line = sys.stdin.readline()
        data = line.split()
        is_human = None
        if data[-1] == "human":
            is_human = True
        else:
            is_human = False
        graph.add_edge(data[0], data[2], is_human)
    sys.stdin.readline()  # Blank line, ignore


def dfs(node):
    """Return a list of traversed nodes or False if Graph not satisfiable"""
    global graph
    graph.human[node] = True
    traversed_nodes = set()
    stack = []
    stack.append(node)
    while stack:
        node = stack.pop()
        traversed_nodes.add(node)
        neighbours = graph.nodes[node].keys()
        for neighbour in neighbours:
            if graph.human[neighbour] is None:
                graph.human[neighbour] = graph.nodes[node][neighbour]()
            else:
                inconsistency = graph.human[neighbour] is not graph.nodes[node][neighbour]()
                if inconsistency:
                    return False
            graph.del_edge(node, neighbour)
            stack.append(neighbour)
    return traversed_nodes


def voight_kampff():
    global subjects
    global graph
    if not graph.is_consistent:
        return 0
    nodes = set(subjects)
    connected_components = 0
    while nodes:
        node = iter(nodes).next()
        traversed_nodes = dfs(node)
        if not traversed_nodes:
            return 0
        else:
            connected_components += 1
            nodes -= traversed_nodes
    return 2**connected_components


if __name__ == '__main__':
    counter = 1
    while True:
        try:
            parse()
            print "Case {0}: {1}".format(counter, voight_kampff())
            counter += 1
        except:
            break
