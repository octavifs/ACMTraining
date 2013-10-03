#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Tree {
public:
    int x, y;
    bool seen;
    Tree() {
        this->x = 0;
        this->y = 0;
        this->seen = false;
    }
};

bool sort_byX(Tree *lhs, Tree *rhs) {
    return lhs->x < rhs->x;
}

bool sort_byY(Tree *lhs, Tree *rhs) {
    return lhs->y < rhs->y;
}


int main() {
    int N, M;
    while(true) {
        cin >> N >> M;
        if(!N && !M)
            break;
        vector<Tree> tree_pool(N);
        map<int, vector<Tree*> > mapX;
        map<int, vector<Tree*> > mapY;
        for (int i = 0; i < N; ++i)
        {
            int x, y;
            cin >> x >> y;
            Tree &t = tree_pool[i];
            t.x = x;
            t.y = y;
            mapX[x].push_back(&t);
            mapY[y].push_back(&t);
        }
        // Sort Trees
        for (map<int, vector<Tree*> >::iterator it= mapX.begin(); it != mapX.end(); it++)
        {
            vector<Tree*> &entries = it->second;
            sort(entries.begin(),entries.end(), sort_byY);
        }
        for (map<int, vector<Tree*> >::iterator it= mapY.begin(); it != mapY.end(); it++)
        {
            vector<Tree*> &entries = it->second;
            sort(entries.begin(),entries.end(), sort_byX);
        }
        // Read paths & get seen trees per path
        int seen_trees = 0;
        for (int i = 0; i < M; ++i)
        {
            char axis, equal;
            int val;
            cin >> axis >> equal >> val;
            if (axis == 'x')
            {
                // Traverse all rows
                for (map<int, vector<Tree*> >::iterator it= mapY.begin(); it != mapY.end(); it++)
                {
                    vector<Tree*> &entries = it->second;
                    vector<Tree*>::iterator entry;
                    Tree t;
                    t.y = val;
                    // get the iterator where the horizontal line cuts the row
                    entry = upper_bound(entries.begin(), entries.end(), &t, sort_byX);
                    // get tree on either side, if possible. If not seen, add it to the list
                    if (entry != entries.end() && !(*entry)->seen) {
                        seen_trees++;
                        (*entry)->seen = true;
                    }
                    else if (entry != entries.begin() && !(*(--entry))->seen) {
                        seen_trees++;
                        (*entry)->seen = true;   
                    }
                }
            }
            else if (axis == 'y')
            {
                // traverse all columns
                for (map<int, vector<Tree*> >::iterator it= mapX.begin(); it != mapX.end(); it++)
                {
                    vector<Tree*> &entries = it->second;
                    vector<Tree*>::iterator entry;
                    Tree t;
                    t.y = val;
                    // get the iterator where the horizontal line cuts the column
                    entry = upper_bound(entries.begin(), entries.end(), &t, sort_byY);
                    // get tree on either side, if possible. If not seen, add it to the list
                    if (entry != entries.end() && !(*entry)->seen) {
                        seen_trees++;
                        (*entry)->seen = true;
                    }
                    else if (entry != entries.begin() && !(*(--entry))->seen) {
                        seen_trees++;
                        (*entry)->seen = true;   
                    }
                }
            }
        }
        cout << seen_trees << endl;

    }
}