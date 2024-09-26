#include <iostream>
#include <vector>
#include <stack>
#include <chrono>
#include <cstdlib>
#include <fstream>

using namespace std;

class Grafo {
private:
    int numVertices;
    vector<vector<int>> adjacencias;
    vector<bool> visitado;

public:
    Grafo(int numVertices) {
        this->numVertices = numVertices;
        adjacencias.resize(numVertices);
        visitado.resize(numVertices, false);
    }

    void adicionarAresta(int v1, int v2) {
        adjacencias[v1].push_back(v2);
        adjacencias[v2].push_back(v1);
    }

    void dfsRecursivo(int source) {
        visitado[source] = true;
        for (int adj : adjacencias[source]) {
            if (!visitado[adj]) {
                dfsRecursivo(adj);
            }
        }
    }

    void dfsNaoRecursivo(int source) {
        fill(visitado.begin(), visitado.end(), false);
        stack<int> pilha;
        pilha.push(source);

        while (!pilha.empty()) {
            int vertice = pilha.top();
            pilha.pop();

            if (!visitado[vertice]) {
                visitado[vertice] = true;
            }

            for (int adj : adjacencias[vertice]) {
                if (!visitado[adj]) {
                    pilha.push(adj);
                }
            }
        }
    }

    void gerarGrafoAleatorio(int edges) {
        while (edges--) {
            int v1 = rand() % numVertices;
            int v2 = rand() % numVertices;
            if (v1 != v2) {
                adicionarAresta(v1, v2);
            }
        }
    }
};

int main() {
    int sizes[] = {100, 200, 500, 1000, 100000};
    ofstream resultados("resultados.txt");

    if (!resultados.is_open()) {
        cerr << "Erro ao abrir o arquivo para escrita!" << endl;
        return 1;
    }

    for (int n : sizes) {
        Grafo grafo(n);
        grafo.gerarGrafoAleatorio(n * 2);

        auto start = chrono::high_resolution_clock::now();
        grafo.dfsRecursivo(0);
        auto end = chrono::high_resolution_clock::now();
        long long recursivoTempo = chrono::duration_cast<chrono::microseconds>(end - start).count();
        resultados << "DFS Recursivo para " << n << " nós: " << recursivoTempo << " microsegundos" << endl;

        start = chrono::high_resolution_clock::now();
        grafo.dfsNaoRecursivo(0);
        end = chrono::high_resolution_clock::now();
        long long naoRecursivoTempo = chrono::duration_cast<chrono::microseconds>(end - start).count();
        resultados << "DFS Não-Recursivo para " << n << " nós: " << naoRecursivoTempo << " microsegundos" << endl;
    }

    resultados.close();
    cout << "Resultados gravados em resultados.txt" << endl;

    return 0;
}
