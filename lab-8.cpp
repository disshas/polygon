#include <iostream>
#include <vector>
#include <cassert> // Подключение заголовочного файла для assert

using namespace std;

void countConnections(const vector<vector<int>>& adjacencyMatrix, vector<int>& connections) { // + N*24 + N^2*4 + 24+N*4
    int n = adjacencyMatrix.size(); // Количество элементов // + 4 // O(1)
    connections.resize(n, 0); // Обнуление массива для хранения связей // O(N)
    if (n == 0){
        cout << "пустой граф" << endl; 
    } // O(1)
    for (int i = 0; i < n; ++i) { // + 4
        for (int j = 0; j < n; ++j) { // + 4
            if (adjacencyMatrix[i][j] == 1) {
                connections[i]++;
            } 
        } 
        cout << "элемент " << i << " содержит " << connections[i] << " связей" << endl; // O(N)
    } // O(N^2)
} // N*24 + N^2*4 + 24+N*4 + 4*3 = N*28 + N^2*4 + 36 // O(1)*2 + O(N)*2 + O(N^2) = O(N^2)

 void runTests() {
    // Тест 1: Пустой граф
    {   cout << "тест 1" << endl;
        vector<vector<int>> adjacencyMatrix = {};
        vector<int> connections;
        countConnections(adjacencyMatrix, connections);
        assert(connections == vector<int>{}); // Проверяем, что connections пуст
    }

    // Тест 2: Граф из одного элемента без связей
    {   cout << "тест 2" << endl;
        vector<vector<int>> adjacencyMatrix = {{0}};
        vector<int> connections;
        countConnections(adjacencyMatrix, connections);
        assert(connections.size() == 1 && connections[0] == 0);
    }

    // Тест 3: Граф из двух элементов с одной связью
    {   cout << "тест 3" << endl;
        vector<vector<int>> adjacencyMatrix = {
            {0, 1},
            {1, 0}
        };
        vector<int> connections;
        countConnections(adjacencyMatrix, connections);
        assert((connections.size() == 2 && connections[0] == 1 && connections[1] == 1));
    }

    // Тест 4: Полный граф на трёх вершинах
    {   cout << "тест 4" << endl;
        vector<vector<int>> adjacencyMatrix = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0}
        };
        vector<int> connections;
        countConnections(adjacencyMatrix, connections);
        assert((connections.size() == 3 && connections[0] == 2 && connections[1] == 2 && connections[2] == 2));
    }

    // Тест 5: Разреженный граф на 4 вершинах
    {   cout << "тест 5" << endl;
        vector<vector<int>> adjacencyMatrix = {
            {0, 1, 0, 0},
            {1, 0, 1, 0},
            {0, 1, 0, 1},
            {0, 0, 1, 0}
        };
        vector<int> connections;
        countConnections(adjacencyMatrix, connections);
        assert((connections.size() == 4 && connections[0] == 1 && connections[1] == 2 &&
                connections[2] == 2 && connections[3] == 1));
    } 

    // Тест 6: Матрица смежности с изолированной вершиной
    {   cout << "тест 6" << endl;
        vector<vector<int>> adjacencyMatrix = {
            {0, 1, 0},
            {1, 0, 0},
            {0, 0, 0}
        };
        vector<int> connections;
        countConnections(adjacencyMatrix, connections);
        assert((connections.size() == 3 && connections[0] == 1 && connections[1] == 1 && connections[2] == 0));
    }

    cout << "All tests passed!" << endl;
}

int main() {
    runTests();
    return 0;
} 
