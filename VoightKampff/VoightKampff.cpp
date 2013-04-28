// Voight Kampff C++ implementation
// Octavi Font
// http://olimpiada-informatica.org/?cmd=problema&pbm=voightkampff

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <utility>
#include <string>

using namespace std;

typedef std::map<string, bool> BMAP;
typedef std::map<string, pair<bool, bool> > BBMAP;
typedef std::map<string, short int> IMAP;
typedef std::map<string, BMAP > DMAP;
typedef std::map<string, BBMAP > DDMAP;


class Graph
{
public:
    DDMAP nodes;
    DMAP edgeValues;
    IMAP human;
    bool isConsistent;

    Graph() :
        isConsistent(true)
    {
    }

    void addNode(const string &id) {
        nodes[id] = BBMAP();
        edgeValues[id] = BMAP();
        human[id] = -1;
    };

    void addEdge(const string &source, const string &dest, bool isHuman) {
        if (edgeValues[source].find(dest) != edgeValues[source].end())
        {
            if (edgeValues[source][dest] != isHuman)
                isConsistent = false;
        }
        if (edgeValues[dest].find(source) != edgeValues[dest].end())
        {
            if (edgeValues[dest][source] != isHuman)
                isConsistent = false;
        }
        edgeValues[source][dest] = isHuman;
        nodes[source][dest] = make_pair(isHuman, true);
        nodes[dest][source] = make_pair(isHuman, false);
    }

    void delEdge(const string &source, const string &dest) {
        nodes[source].erase(dest);
        nodes[dest].erase(source);
    }

};

short int nodeValue(const short int node, const pair<bool, bool> pair) {
    if (pair.second)
    {
        if (node == 1) // source is human, therefore, dest is what source says
            return pair.first * 1;
        else // source is replicant, therefore dest is what source does NOT say
            return !pair.first * 1;
    }
    else { // If it is said
        if (node == pair.first) // What was said is true, source is human
            return 1;
        else // What was said is false, source is replicant
            return 0;
    }
}


vector<string> dfs(Graph &g, string &nodeStart) {
    vector<string> traversedNodes;
    vector<string> stack;
    stack.push_back(nodeStart);
    g.human[nodeStart] = 1;
    while(!stack.empty()) {
        string node = stack.back();
        short int nodeIsHuman = g.human[node];
        stack.pop_back();
        traversedNodes.push_back(node);
        vector<string> neighbours;
        vector<pair<string, string> > deletions;
        for(BBMAP::iterator it = g.nodes[node].begin(); it != g.nodes[node].end(); it++) {
            string neighbour = it->first;
            if (g.human[neighbour] == -1)
                g.human[neighbour] = nodeValue(nodeIsHuman, it->second);
            else {
                bool inconsistency;
                inconsistency = g.human[neighbour] != nodeValue(nodeIsHuman, it->second);
                if (inconsistency)
                    throw false;
            }
            deletions.push_back(make_pair(node, neighbour));
            stack.push_back(neighbour);
        }
        for (vector<pair<string, string> >::iterator it = deletions.begin(); it != deletions.end(); ++it)
            g.delEdge(it->first, it->second);
    }
    return traversedNodes;
}

int voightKampff(Graph &g) {
    if (!g.isConsistent)
        return 0;
    set<string> nodeIds;
    int combinations = 1;
    for (DDMAP::iterator it = g.nodes.begin(); it != g.nodes.end(); it++) {
        nodeIds.insert(it->first);
    }
    while (!nodeIds.empty()) {
        vector<string> results;
        string node = *nodeIds.begin();
        try {
            results = dfs(g, node);
        }
        catch (bool b) {
                return 0;
        }
        combinations *= 2;
        for (vector<string>::iterator it = results.begin(); it != results.end(); ++it)
            nodeIds.erase(*it);
    }
    return combinations;
}

int main() {
    typedef map<string, short int> Subjects;
    typedef std::map<string, std::vector<pair<string, bool> > > Statements;
    typedef std::map<string, bool> Checked;

    short int numSubjects;
    short int caseNum = 1;
    while(cin >> numSubjects) {
        Graph g;
        Subjects isHuman;
        Statements statements;
        Checked isChecked;
        // -1: not initialized; 0: replicant, 1: human
        for (int i = 0; i < numSubjects; ++i) {
            string subject;
            cin >> subject;
            g.addNode(subject);
        }
        int numStatetements;
        cin >> numStatetements;
        for (int i = 0; i < numStatetements; ++i)
        {
            string subject, s, referee, thing;
            cin >> subject >> s >> referee >> s >> thing;
            if (thing == "a") {// This is a replicant
                cin >> s;
                g.addEdge(subject, referee, false);
            }
            else // This is a human
                g.addEdge(subject, referee, true);
        }
        int combinations = voightKampff(g);
        cout << "Case " << caseNum << ": " << combinations << endl;
        caseNum++;
    }
}