#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 10000; // maximum number of vertices

// binary vectors of length n
vector<vector<int>> binary_vectors;

// adjacency matrix for the Hamming graph
bool adj[MAXN][MAXN];

// current clique
vector<int> clique;

// best clique found so far
vector<int> best_clique;


// check if v can be added to the current clique
bool can_add(int v) {
    // check if v is connected to all vertices in the clique
    for (int u : clique) {
        if (!adj[u][v]) return false; 
    }
    return true;
}

// recursive function for finding the maximal clique
void find_max_clique(int idx) {

    // check if the current clique is better than the best clique found so far
    if (clique.size() > best_clique.size()) {
        best_clique = clique;
    }

    // try adding each vertex to the clique
    for (int i = idx; i < binary_vectors.size(); i++) {
        int v = i;
        if (can_add(v)) {
            // add v to the clique and recursively search for larger cliques
            clique.push_back(v);
            find_max_clique(i+1);
            clique.pop_back();
        }
    }
}

int main() {
   
    int n, d; // length and minimum distance of vectors
    
    // read input
    cout << "n:";
    cin >> n;
    cout << "d:" ;
    cin >> d;

        // generate all binary vectors of length n
        for (int i = 0; i < (1 << n); i++) {
            vector<int> v;
            for (int j = 0; j < n; j++) {
                v.push_back((i >> j) & 1); 
            }                                                             
            binary_vectors.push_back(v);    
        }

        // construct the Hamming graph
        for (int i = 0; i < binary_vectors.size(); i++) {
            for (int j = i + 1; j < binary_vectors.size(); j++) {
                // calculate the Hamming distance between binary_vectors[i] and binary_vectors[j]
                int dist = 0;
                for (int k = 0; k < n; k++) {
                    if (binary_vectors[i][k] != binary_vectors[j][k]) dist++;
                }
                // if the distance is greater than or equal to d, add an edge between the two vertices
                if (dist >= d) {
                    adj[i][j] = adj[j][i] = true;
                }
            }
        }

        // find the maximal clique in the Hamming graph
        find_max_clique(0);

        // print the size of the maximal clique
        cout << "output:" << best_clique.size() << endl;
    
    return 0;
}