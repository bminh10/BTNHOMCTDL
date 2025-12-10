#include<iostream>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;

struct toado {
	int x; int y;
};

struct Graph {
	char** matrix;
	int m, n;
	toado pacman;
	toado apple;
	int** visited;
	toado steps[4] = { {-1,0},{0,1},{1,0},{0,-1} };
	toado** parent;
};

void readData(Graph&g) {
	ifstream fin;
	fin.open("pacman.txt");
	fin >> g.m >> g.n;
	fin >> g.pacman.x >> g.pacman.y >> g.apple.x >> g.apple.y;
	/*g.pacman.x--;
	g.pacman.y--;
	g.apple.x--;
	g.apple.y--;*/

	g.matrix = new char* [g.m];
	g.parent = new toado* [g.m];
	g.visited = new int* [g.m];
	for (int i = 0; i < g.m; i++) {
		g.matrix[i] = new char[g.n];
		g.visited[i] = new int[g.n];
		g.parent[i] = new toado[g.n];
	}

	for (int i = 0; i < g.m; i++) {
		for (int j = 0; j < g.n; j++) {
			g.visited[i][j] = 0;
			g.parent[i][j] = { 0,0 };
		}
	}
	
	for (int i = 0; i < g.m; i++) {
		for (int j = 0; j < g.n; j++) {
			fin >> g.matrix[i][j];
		}
	}

	fin.close();
}

void output(Graph g) {
	for (int i = 0; i < g.m; i++) {
		for (int j = 0; j < g.n; j++) {
			cout << g.matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int process(Graph&g,toado start, toado goal) {
	queue<toado>q;
	q.push(start);
	while (!q.empty()) {
		toado r = q.front();
		q.pop();
		if (r.x == goal.x && r.y == goal.y) {
			return 1;
		}
		g.visited[r.x][r.y] = 1;
		for(int i = 0 ; i < 4 ; i++){
			int x = r.x + g.steps[i].x;
			int y = r.y + g.steps[i].y;
			if (x < g.m && y < g.n && x >= 0 && y >= 0 && g.visited[x][y] == 0 && g.matrix[x][y] != '*') {
				q.push({ x,y });
				g.visited[x][y] = -1;
				g.parent[x][y] = r;
			}

		}

	}
	return -1;
}

void display(Graph g,toado start,toado goal) {
	for (int i = 0; i < g.m; i++) {
		for (int j = 0; j < g.n; j++) {
			cout << "{" << g.parent[i][j].x << " " << g.parent[i][j].y << "}" << "\t" ;
		}
		cout << endl;
	}

	int res = 0;
	stack<toado>s;
	toado idx = g.parent[goal.x][goal.y];
	while (idx.x!= start.x || idx.y != start.y) {
		s.push(idx);
		idx = g.parent[idx.x][idx.y];
		res++;
	}
	s.push(start);
	cout << res;


}


void del(Graph &g) {
	for (int i = 0; i < g.m; i++) {
		delete[]g.matrix[i];
		delete[]g.parent[i];
		delete[]g.visited[i];
	}
	delete[]g.matrix;
	delete[]g.parent;
	delete[]g.visited;
}

int main() {
	Graph g;
	readData(g);
	output(g);
	int val =process(g, g.pacman, g.apple);
	if (val != -1) {
		display(g, g.pacman, g.apple);

	}
	else {
		cout << "Khong co duong di\n";
	}


	del(g);

	return 0;
}