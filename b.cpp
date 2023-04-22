#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <stdio.h>
#include <bitset>
#include <cstdint>
#include <cassert>
#include <functional>
#include <complex>
#include <random>

using namespace std;

#define f first
#define s second
#define mp make_pair

int n, m;
char a[100][100];
int dist[100][100];
int d1[] = {0, 0, 1, -1};
int d2[] = {1, -1, 0, 0};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int a, int b){
    return a + rng() % (b - a + 1);
}
void dijkstra(){
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= m; ++j){
            dist[i][j] = 1e9;
        }
    }
    //finding min time path
    set<pair<int, pair<int, int>>> setik;
    for (int i = 1; i <= n; ++i){
        if (a[i][1] == '.'){
            setik.insert(mp(0, mp(i, 1)));
            dist[i][1] = 0;
        }
        if (a[i][m] == '.'){
            setik.insert(mp(0, mp(i, m)));
            dist[i][m] = 0;
        }
    }
    for (int i = 1; i <= m; ++i){
        if (a[1][i] == '.'){
            setik.insert(mp(0, mp(1, i)));    
            dist[1][i] = 0;
        }
        if (a[n][i] == '.'){
            setik.insert(mp(0, mp(n, i)));
            dist[n][i] = 0;
        }
    }
    while (setik.size() > 0){
        pair<int, pair<int, int>> cur = *setik.begin();
        int x = cur.s.f, y = cur.s.s;
        setik.erase(cur);
        for (int i = 0; i < 4; ++i){
            int nx = x + d1[i], ny = y + d2[i];
            if ((nx >= 1 && ny >= 1 && nx <= n && ny <= m) && a[nx][ny] == '.' && dist[nx][ny] > dist[x][y] + 1){
                dist[nx][ny] = dist[x][y] + 1;
                setik.insert(mp(dist[nx][ny], mp(nx, ny)));
            }
        }
    }
}
int main()
{
    int record = 1e9;
    //freopen("input.txt", "r", stdin);
    while (1){
        cout << "Do you want to continue/start the game ? (answers yes/no only)\n";
        string s;
        cin >> s;
        if (s == "no"){
            exit(0);
        }
        //creating new table
        n = rand(1, 20);
        m = rand(1, 20);
        cout << n << " " << m << '\n'; //table width and height
        int x = rand(1, n);
        int y = rand(1, m);
        cout << x << " " << y << '\n'; //starting point
        int timer = rand(1, n * m);
        cout << timer << '\n';
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= m; ++j){
                char c;
                //. - пустая клетка, #-блокированная клетка в лабиринте
                int z = rand(0, 1);
                if (x == i && y == j){
                    cout << '.';
                    a[i][j] = '.';
                    //starting point must be empty!
                    continue;
                }
                if (z == 0){
                    c = '.';
                }
                else{
                    c = '#';
                }
                a[i][j] = c;
                cout << c;
            }
            cout << '\n';
        }
        dijkstra();
        if (dist[x][y] == 1e9){
            cout << "You lost\n";
        }
        else{
            if (record > dist[x][y]){
                record = dist[x][y];
                cout << "New record: " << record << " !\n";
            }
            else{
                cout << "Same record: " << record << " !\n";
            }
        }
    }
}

