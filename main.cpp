#include <stdio.h>
#include <vector>

using namespace std;

FILE *in = fopen("input.txt", "r");
FILE *out = fopen("output.txt", "w");
vector<int > cycle;

int connect[10000][10000], temp1, temp2, vertices, edges, stopdot;
bool visited[10000], addToCycle, conditionToWrite;

void init() {
    fscanf(in, "%i %i", &vertices, &edges);

    for (int i = 0 ; i < edges ; i++) {
        fscanf(in, "%i %i", &temp1, &temp2);
        temp1--; temp2--;
        connect[temp1][temp2] = 1;
        connect[temp2][temp1] = 1;
    }

    for (int i = 0 ; i < vertices ; i++){
        visited[i] = false;
    }
}

void print(bool can) {
    if (can) {
        for (int i = 0 ; i < cycle.size() ; i++){
            if (i != 0) fprintf(out, " ");
            fprintf(out, "%i", cycle[i]);
        }
        fprintf(out, "\n");
    }

    if (cycle.size() > 0)
            fprintf(out, "+\n");
        else
            fprintf(out, "-\n");
}

bool dfs(int v, int prev) {

    visited[v] = true;

    for (int i = 0 ; i < edges ; i++) {
        if (connect[v][i] == 1) {
            if (visited[i] && i != prev) {
                addToCycle = true;
                stopdot = i;
                cycle.push_back(stopdot + 1);
                cycle.push_back(v + 1);

                return true;
            }
            if (!visited[i])
                if (dfs(i, v)){
                    if (v == stopdot) addToCycle = false;
                    if (addToCycle) cycle.push_back(v + 1);

                    return true;
                }
        }
    }
    return false;
}

int main()
{
    init();
    print(dfs(0,0));
    return 0;
}
