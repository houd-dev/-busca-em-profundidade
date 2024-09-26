#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;

class Labirinto {
private:
    int largura, altura;
    vector<vector<int>> grid;

public:
    Labirinto(int largura, int altura) : largura(largura), altura(altura) {
        grid.resize(altura, vector<int>(largura, 1));
    }

    void gerarLabirintoRecursivo(int x, int y) {
        grid[y][x] = 0;
        vector<pair<int, int>> direcoes = {{2, 0}, {-2, 0}, {0, 2}, {0, -2}};
        std::shuffle(direcoes.begin(), direcoes.end(), std::default_random_engine(time(0)));

        for (auto& dir : direcoes) {
            int nx = x + dir.first, ny = y + dir.second;
            if (nx > 0 && ny > 0 && nx < largura && ny < altura && grid[ny][nx] == 1) {
                grid[y + dir.second / 2][x + dir.first / 2] = 0;
                gerarLabirintoRecursivo(nx, ny);
            }
        }
    }

    void gerarLabirintoNaoRecursivo(int x, int y) {
        stack<pair<int, int>> pilha;
        pilha.push({x, y});
        grid[y][x] = 0;

        while (!pilha.empty()) {
            auto [cx, cy] = pilha.top();
            pilha.pop();

            vector<pair<int, int>> direcoes = {{2, 0}, {-2, 0}, {0, 2}, {0, -2}};
            std::shuffle(direcoes.begin(), direcoes.end(), std::default_random_engine(time(0)));

            for (auto& dir : direcoes) {
                int nx = cx + dir.first, ny = cy + dir.second;
                if (nx > 0 && ny > 0 && nx < largura && ny < altura && grid[ny][nx] == 1) {
                    grid[cy + dir.second / 2][cx + dir.first / 2] = 0;
                    grid[ny][nx] = 0;
                    pilha.push({nx, ny});
                }
            }
        }
    }

    void salvarLabirinto(const string& nomeArquivo) {
        ofstream arquivo(nomeArquivo);
        for (const auto& linha : grid) {
            for (int cell : linha) {
                arquivo << (cell ? '#' : ' ');
            }
            arquivo << endl;
        }
        arquivo.close();
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));
    Labirinto labirinto(21, 21);
    labirinto.gerarLabirintoRecursivo(1, 1);
    labirinto.salvarLabirinto("labirinto_recursivo.ppm");

    Labirinto labirinto2(21, 21);
    labirinto2.gerarLabirintoNaoRecursivo(1, 1);
    labirinto2.salvarLabirinto("labirinto_nao_recursivo.ppm");

    return 0;
}
