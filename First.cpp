#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

long long orientation(pair<int, int> a, pair<int, int> b, pair<int, int> O) {
    return (long long)(a.first - O.first) * (b.second - O.second)
        - (long long)(a.second - O.second) * (b.first - O.first);
}

long long squared_distance(pair<int, int> a, pair<int, int> b) {
    long long dx = (long long)a.first - b.first;
    long long dy = (long long)a.second - b.second;
    return dx * dx + dy * dy;
}

void SOrted(vector<pair<int, int>>& Coordinate) {
    sort(Coordinate.begin() + 1, Coordinate.end(),
        [&](const auto& a, const auto& b) {
            long long orient = orientation(a, b, Coordinate[0]);
            if (orient != 0) return orient > 0;
            return squared_distance(a, Coordinate[0]) < squared_distance(b, Coordinate[0]);
        });

    int m = 1;
    for (size_t i = 1; i < Coordinate.size(); ++i) {
        while (i < Coordinate.size() - 1 &&
            orientation(Coordinate[i], Coordinate[i + 1], Coordinate[0]) == 0) {
            ++i;
        }
        Coordinate[m++] = Coordinate[i];
    }
    Coordinate.resize(m);
}

void Stack_craft(stack<size_t>& myStack, const vector<pair<int, int>>& Coordinate) {
    if (Coordinate.size() < 2) return;
    myStack.push(0);
    if (Coordinate.size() > 1) myStack.push(1);

    for (size_t i = 2; i < Coordinate.size(); ++i) {
        while (myStack.size() >= 2) {
            size_t top = myStack.top();
            myStack.pop();
            size_t next = myStack.top();
            if (orientation(Coordinate[next], Coordinate[top], Coordinate[i]) > 0) {
                myStack.push(top);
                break;
            }
            
        }
        myStack.push(i);
    }
}

//4
vector<vector<int>> createGraph(int N, int E) {
    vector<vector<int>> graph(N); 

    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v; 
        graph[u].push_back(v);  
        graph[v].push_back(u); 
    }

    return graph;
}


int main() {
    //Задача1
    {
        int n;
        cin >> n;

        vector<pair<int, int>> coordinate(n);
        for (int i = 0; i < n; ++i) {
            cin >> coordinate[i].first >> coordinate[i].second;
        }

        size_t min_ind = 0;
        for (size_t i = 1; i < n; ++i) {
            if (coordinate[i].second < coordinate[min_ind].second ||
                (coordinate[i].second == coordinate[min_ind].second &&
                    coordinate[i].first < coordinate[min_ind].first)) {
                min_ind = i;
            }
        }
        swap(coordinate[0], coordinate[min_ind]);
        SOrted(coordinate);
        stack<size_t> myStack;
        Stack_craft(myStack, coordinate);

        vector<size_t> hull;
        while (!myStack.empty()) {
            hull.push_back(myStack.top());
            myStack.pop();
        }
        reverse(hull.begin(), hull.end());

        cout << "Convex Hull:" << endl;
        for (size_t elem : hull) {
            cout << elem << ": " << coordinate[elem].first << " " << coordinate[elem].second << endl;
        }

        // Не в оболочке
        cout << "Not on Hull:" << endl;
        vector<bool> onHull(n, false);
        for (size_t idx : hull) onHull[idx] = true;
        for (size_t i = 0; i < n; i++) {
            if (!onHull[i]) {
                cout << i << ": " << coordinate[i].first << " " << coordinate[i].second << endl;
            }
        }
}

   //Задача4
    /* {
            int N, E;
            cin >> N >> E;  // Ввод N и E

            auto graph = createGraph(N, E);

            // Пример вывода для проверки (опционально)
            for (int i = 0; i < N; ++i) {
                cout << "Вершина " << i << ": ";
                for (int neighbor : graph[i]) {
                    cout << neighbor << " ";
                }
                cout << endl;
            }

            return 0;
       }
*/
}

/*
* Пример к зАдаче1
9
1 -1
3 -1
0 2
3 1
2 2
4 2
3 1
3 3
2 4
*/