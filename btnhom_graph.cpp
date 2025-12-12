#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
using namespace std;




struct Graph {
	//ma tran ke
	int** matrix;
	//danh sach ke
	int** list;
	//kich thuoc danh sach cua 1 dinh
	int* sz;
	// so dinh
	int n;
	//cach luu tru do thi
	int type;
	//co trong so hoac khong
	int ts;
	// co huong hay khong
	int dir;
	// mang danh dau da xoa dinh
	int* canuse;
	//ham check ho tro cho dem canh
	int** check;
	//mang tham
	int* visited;
	//mang de duyet duong di
	int* parent;
	//mang ho tro viec tim thanh phan lien thong
	int* label;
};

//tao rong do thi
void init(Graph& m) {
	m.matrix = nullptr;
	m.list = nullptr;
	m.sz = nullptr;
	m.canuse = nullptr;
	m.check = nullptr;
	m.visited = nullptr;
	m.parent = nullptr;
	m.label = nullptr;
	m.dir = 0;
}

//tao do thi
void createGraph(Graph& m) {
	cout << "Nhap so dinh: ";
	cin >> m.n;
	switch (m.type)
	{
	case 1:
	{
		m.matrix = new int* [m.n];
		for (int i = 0; i < m.n; i++) {
			m.matrix[i] = new int[m.n];
		}
		for (int i = 0; i < m.n; i++) {
			for (int j = 0; j < m.n; j++) {
				m.matrix[i][j] = 0;
			}
		}
		break;
	}
	case 0:
	{
		m.list = new int* [m.n];
		m.sz = new int[m.n];
		for (int i = 0; i < m.n; i++) {
			m.list[i] = nullptr;
			m.sz[i] = 0;
		}

		break;
	}
	default:
		break;
	}
	m.canuse = new int[m.n];
	m.visited = new int[m.n];
	m.parent = new int[m.n];
	m.label = new int[m.n];
	for (int i = 0; i < m.n; i++) {
		m.canuse[i] = 1;
		m.label[i] = 0;
		m.parent[i] = 0;
		m.visited[i] = 0;
	}
	m.check = new int* [m.n];
	for (int i = 0; i < m.n; i++) {
		m.check[i] = new int[m.n];
	}
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			m.check[i][j] = 0;
		}
	}

}

//ham xuat do thi
void output(Graph m) {
	cout << "DO THI HIEN TAI \n";
	switch (m.type)
	{
	case 1: {
		for (int i = 0; i < m.n; i++) {
			if (m.canuse[i] == 0)continue;
			cout << "Dinh " << i + 1 << ": ";
			for (int j = 0; j < m.n; j++) {
				if (m.canuse[j] == 1) {
					cout << m.matrix[i][j] << " ";
				}
			}
			cout << endl;
		}
		break;
	}
	case 0: {
		for (int i = 0; i < m.n; i++) {
			if (m.canuse[i] == 0)continue;
			cout << "Dinh " << i + 1 << ": ";
			for (int j = 0; j < m.sz[i]; j++) {
				int dinh = m.list[i][j];
				if (m.canuse[dinh] == 1) {
					cout << dinh + 1 << " ";
				}
			}
			cout << endl;
		}
		break;
	}
	default:
		break;
	}

}



//ham them dinh
void addVertex(Graph& m, int v) {
	if (v == 0)return;
	int newsize = m.n + v;
	switch (m.type)
	{
	case 1: {
		int** newmatrix = new int* [newsize];
		for (int i = 0; i < newsize; i++) {
			newmatrix[i] = new int[newsize];
		}

		for (int i = 0; i < newsize; i++) {
			for (int j = 0; j < newsize; j++) {
				newmatrix[i][j] = 0;
			}
		}
		for (int i = 0; i < m.n; i++) {
			for (int j = 0; j < m.n; j++) {
				newmatrix[i][j] = m.matrix[i][j];
			}
		}
		for (int i = 0; i < m.n; i++) {
			delete[]m.matrix[i];
		}
		delete[]m.matrix;
		m.matrix = newmatrix;

		break;
	}
	case 0: {
		int** newlist = new int* [newsize];
		for (int i = 0; i < newsize; i++) {
			newlist[i] = nullptr;
		}
		for (int i = 0; i < m.n; i++) {
			for (int j = 0; j < m.sz[i]; j++) {
				newlist[i][j] = m.list[i][j];
			}
		}
		for (int i = 0; i < m.n; i++) {
			delete[]m.list[i];
		}
		delete[]m.list;
		m.list = newlist;

		int* newsz = new int[newsize];
		for (int i = 0; i < newsize; i++) {
			newsz[i] = 0;
		}

		for (int i = 0; i < m.n; i++) {
			newsz[i] = m.sz[i];
		}
		delete[]m.sz;
		m.sz = newsz;

		break;
	}
	default:
		break;
	}
	int* newcanuse = new int[newsize];
	for (int i = 0; i < newsize; i++) {
		newcanuse[i] = 1;
	}
	for (int i = 0; i < m.n; i++) {
		newcanuse[i] = m.canuse[i];
	}
	delete[]m.canuse;
	m.canuse = newcanuse;

	int** newcheck = new int* [newsize];
	for (int i = 0; i < newsize; i++) {
		newcheck[i] = new int[newsize];
	}
	for (int i = 0; i < newsize; i++) {
		for (int j = 0; j < newsize; j++) {
			newcheck[i][j] = 0;
		}
	}
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			newcheck[i][j] = m.check[i][j];
		}
	}
	for (int i = 0; i < m.n; i++) {
		delete[]m.check[i];
	}
	delete[]m.check;
	m.check = newcheck;

	m.n = newsize;

}

//ham xoa dinh
void delVertex(Graph& m, int v) {
	if (v < 0 && v > m.n) {
		cout << "Vuot pham vi\n";
		return;
	}
	if (m.canuse[v] == 1) {
		m.canuse[v] = 0;
	}
	else {
		cout << "DInh nay da bi xoa \n";
	}
}

//ham them 1 phan tu vao mang
void push(int*& a, int& n, int x)
{
	if (a == nullptr) {
		n = 1;
		a = new int[n];
		a[0] = x;
		return;
	}
	int* newarr = new int[n + 1];
	for (int i = 0; i < n; i++) {
		newarr[i] = a[i];
	}
	newarr[n] = x;
	delete[]a;
	a = newarr;
	n++;

}


//ham them canh
void addEdge(Graph& m, int a, int b) {
	if (m.canuse[a] == 0 || m.canuse[b] == 0) {
		cout << "Khong the them canh vao do thi\n";
		return;
	}

	switch (m.type)
	{
	case 1: {
		if (m.ts == 1) {
			int ts;
			cout << "Nhap trong so cho canh " << a + 1 << "->" << b + 1 << ": ";
			cin >> ts;
			m.matrix[a][b] = ts;
			m.matrix[b][a] = ts;
		}
		else {

			m.matrix[a][b] = 1;
			m.matrix[b][a] = 1;
		}

		break;
	}

	case 0: {
		if (m.dir == 0) {
			push(m.list[a], m.sz[a], b);
			push(m.list[b], m.sz[b], a);
		}
		else {
			push(m.list[a], m.sz[a], b);
		}
		break;
	}

	default:
		break;
	}

}

//ham ho tro xoa canh cho danh sach ke
void pop(int*& a, int& n, int x) {
	if (n == 1) {
		a = nullptr;
		n = 0;
		return;
	}
	int* newarr = new int[n - 1];
	int idx = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] == x)continue;
		newarr[idx] = a[i];
		idx++;
	}
	delete[]a;
	a = newarr;
	n--;
}

//ham xoa canh
void delEdge(Graph& m, int a, int b) {
	if (m.canuse[a] == 0 || m.canuse[b] == 0) {
		cout << "Khong the xoa canh\n";
		return;
	}

	switch (m.type)
	{
	case 1: {
		m.matrix[a][b] = 0;
		m.matrix[b][a] = 0;

		break;
	}

	case 0: {

		if (m.dir == 1) {
			pop(m.list[a], m.sz[a], b);
		}
		else {
			pop(m.list[a], m.sz[a], b);
			pop(m.list[b], m.sz[b], a);
		}

		break;
	}

	default:
		break;
	}

}





//ham kiem tra do thi hop le + dem canh
int isGraph(Graph& m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			m.check[i][j] = 0;
		}
	}

	int res = 0;
	switch (m.type)
	{
	case 1: {
		for (int i = 0; i < m.n; i++) {
			if (m.canuse[i] == 0)continue;
			for (int j = 0; j < m.n; j++) {
				if (m.matrix[i][j] > 0 && m.check[j][i] == 0 && m.canuse[j] == 1) {
					res++;
					m.check[i][j] = 1;
				}
			}
		}
		break;
	}
	case 0: {
		for (int i = 0; i < m.n; i++) {
			if (m.canuse[i] == 0)continue;
			for (int j = 0; j < m.sz[i]; j++) {
				int dinh = m.list[i][j];
				if (m.check[dinh][i] == 0 && m.canuse[dinh] == 1) {
					res++;
					m.check[i][dinh] = 1;
				}
			}
		}
		break;
	}
	default:
		break;
	}

	if (res <= (m*(m-1)/2)) {
		return res;
	}
	else {
		return -1;
	}
}

//ham ho tro tim thanh phan lien thong
void duyet(Graph& m, int start, int label) {
	for (int i = 0; i < m.n; i++) {
		m.visited[i] = 0;
	}
	stack<int>s;
	s.push(start);
	while (!s.empty())
	{
		int r = s.top();
		m.visited[r] = 1;
		m.label[r] = label;
		bool flag = false;
		switch (m.type)
		{
		case 1: {
			for (int i = 0; i < m.n; i++) {
				if (m.canuse[i] == true && m.matrix[r][i] > 0 && m.visited[i] == 0 && m.label[i] == 0) {
					s.push(i);
					flag = true;
					break;
				}
			}
			break;
		}
		case 0: {
			for (int i = 0; i < m.sz[r]; i++) {
				int dinh = m.list[r][i];
				if (m.canuse[dinh] == true && m.visited[dinh] == 0 && m.label[dinh] == 0) {
					s.push(dinh);
					flag = true;
					break;
				}
			}
			break;
		}
		default:
			break;
		}
		if (flag == false) {
			s.pop();
		}
	}
}

//ham dem thanh phan lien thong
void cntTPLT(Graph& m) {
	int label = 0;
	for (int i = 0; i < m.n; i++) {
		if (m.label[i] == 0) {
			label++;
			duyet(m, i, label);
		}
	}

	if (label == 1) {
		cout << "Do thi lien thong \n";
	}
	else {
		cout << "Do thi khong lien thong \n";
		for (int i = 1; i <= label; i++) {
			cout << "Thanh phan lien thong thu " << i << ": ";
			for (int j = 0; j < m.n; j++) {
				if (m.label[j] == i) {
					cout << j + 1 << " ";
				}
			}
			cout << endl;
		}
	}


}

//kiem tra chu trinh tren do thi vo huong
bool checkCycleNoDir(Graph& m, int v, int& start, int& goal) {
	for (int i = 0; i < m.n; i++) {
		m.visited[i] = 0;
		m.parent[i] = 0;
	}
	stack<int>s;
	s.push(v);
	while (!s.empty())
	{
		int r = s.top();
		m.visited[r] = 1;
		bool flag = false;
		switch (m.type)
		{

		case 1: {
			for (int i = 0; i < m.n; i++) {
				if (m.canuse[i] == true && m.matrix[r][i] > 0 && m.visited[i] == 0) {
					s.push(i);
					flag = true;
					m.parent[i] = r;
					break;
				}
				else if (m.matrix[r][i] > 0 && i != m.parent[r]) {
					start = i;
					goal = r;
					return true;
				}
			}
			break;
		}
		case 0: {
			for (int i = 0; i < m.sz[r]; i++) {
				int dinh = m.list[r][i];
				if (m.canuse[dinh] == true && m.visited[dinh] == 0) {
					s.push(dinh);
					flag = true;
					m.parent[dinh] = r;
					break;
				}
				else if (dinh != m.parent[r]) {
					start = dinh;
					goal = r;
					return true;
				}
			}
			break;
		}
		default:
			break;
		}
		if (flag == false) {
			s.pop();
		}
	}
	return false;
}

//ham xuat duong di cua chu trinh
void display(Graph m, int s, int g) {
	stack <int>cycle;
	int idx = m.parent[g];
	cycle.push(g + 1);
	while (idx != s)
	{
		cycle.push(idx + 1);
		idx = m.parent[idx];
	}
	cycle.push(s + 1);
	while (!cycle.empty())
	{
		cout << cycle.top() << " ";
		cycle.pop();
	}
	cout << s + 1 << endl;
}

//ham kiem chu trinh tren do thi co huong 
bool checkCycleDir(Graph& m, int v, int& start, int& goal) {

	stack<int>s;
	s.push(v);
	while (!s.empty())
	{
		int r = s.top();
		m.visited[r] = 1;
		bool flag = false;

		for (int i = 0; i < m.sz[r]; i++) {
			int dinh = m.list[r][i];
			if (m.canuse[dinh] == true && m.visited[dinh] == 0) {
				s.push(dinh);
				flag = true;
				m.parent[dinh] = r;
				break;
			}
			else if (m.visited[dinh] == 1) {
				start = dinh;
				goal = r;
				return true;
			}
		}

		if (flag == false) {
			m.visited[r] = 2;
			s.pop();
		}
	}
	return false;
}

//giai phong do thi
void del(Graph& m) {
	for (int i = 0; i < m.n; i++) {
		if (m.matrix != nullptr) {
			delete[]m.matrix[i];
		}
		if (m.list != nullptr) {
			delete[]m.list[i];
		}
		if (m.check != nullptr) {
			delete[]m.check[i];
		}
	}
	delete[]m.check;
	delete[]m.sz;
	delete[]m.list;
	delete[]m.matrix;
	delete[]m.canuse;
	delete[]m.visited;
	delete[]m.parent;
	delete[]m.label;
	m.label = nullptr;
	m.visited = nullptr;
	m.parent = nullptr;
	m.canuse = nullptr;
	m.sz = nullptr;
	m.list = nullptr;
	m.matrix = nullptr;
	m.check = nullptr;
	bool res = m.sz == nullptr && m.list == nullptr && m.matrix == nullptr && m.canuse == nullptr && m.visited == nullptr && m.parent == nullptr && m.label == nullptr ? true : false;
	if (res) {
		cout << "Giai phong thanh cong \n";
	}
}
// krusal vs prim
struct Edge {
	int u, v, w;
};

// tìm cha của một node trong Union-Find
int findRoot(int parent[], int x) {
	while (parent[x] != x) x = parent[x];
	return x;
}

// Kruskal
void kruskal(Graph m) {
	// Đếm số cạnh
	int cnt = 0;
	for (int i = 0; i < m.n; i++) {
		for (int j = i + 1; j < m.n; j++) {
			if (m.matrix[i][j] > 0) cnt++;
		}
	}

	// Tạo danh sách cạnh
	Edge* edges = new Edge[cnt];
	int idx = 0;
	for (int i = 0; i < m.n; i++) {
		for (int j = i + 1; j < m.n; j++) {
			if (m.matrix[i][j] > 0) {
				edges[idx].u = i;
				edges[idx].v = j;
				edges[idx].w = m.matrix[i][j];
				idx++;
			}
		}
	}

	// Sắp xếp các cạnh theo trọng số
	for (int i = 0; i < cnt - 1; i++) {
		for (int j = i + 1; j < cnt; j++) {
			if (edges[i].w > edges[j].w) {
				Edge tmp = edges[i];
				edges[i] = edges[j];
				edges[j] = tmp;
			}
		}
	}

	// Union-Find
	int* parent = new int[m.n];
	for (int i = 0; i < m.n; i++) parent[i] = i;

	cout << "Cay khung nho nhat (Kruskal):\n";
	int pick = 0;

	for (int i = 0; i < cnt; i++) {
		int ru = findRoot(parent, edges[i].u);
		int rv = findRoot(parent, edges[i].v);

		if (ru != rv) {
			cout << edges[i].u + 1 << " - " << edges[i].v + 1
				<< "  (w=" << edges[i].w << ")\n";
			parent[rv] = ru;
			pick++;
			if (pick == m.n - 1) break;
		}
	}

	delete[] edges;
	delete[] parent;
}

void prim(Graph m, int start = 0) {
	int* visited = new int[m.n];
	int* dist = new int[m.n];
	int* parent = new int[m.n];

	for (int i = 0; i < m.n; i++) {
		visited[i] = 0;
		dist[i] = 1e9;
		parent[i] = -1;
	}

	dist[start] = 0;

	for (int k = 0; k < m.n; k++) {

		// chọn đỉnh có dist nhỏ nhất
		int u = -1, minval = 1e9;
		for (int i = 0; i < m.n; i++) {
			if (!visited[i] && dist[i] < minval) {
				minval = dist[i];
				u = i;
			}
		}

		if (u == -1) break;
		visited[u] = 1;

		// cập nhật dist cho các đỉnh kề
		for (int v = 0; v < m.n; v++) {
			if (m.matrix[u][v] > 0 && !visited[v] && m.matrix[u][v] < dist[v]) {
				dist[v] = m.matrix[u][v];
				parent[v] = u;
			}
		}
	}

	cout << "Cay khung nho nhat (Prim):\n";
	for (int i = 0; i < m.n; i++) {
		if (parent[i] != -1) {
			cout << parent[i] + 1 << " - " << i + 1
				<< "  (w=" << m.matrix[i][parent[i]] << ")\n";
		}
	}

	delete[] visited;
	delete[] dist;
	delete[] parent;
}


int main() {
	Graph m;
	cout << "Dung ma tran ke ( bam 1 ) / danh sach ke ( bam 0 ): ";
	cin >> m.type;

	init(m);
	createGraph(m);
	output(m);

	if (m.type == 0) {
		cout << "Do thi co huong ( bam 1 ) / Do thi vo huong ( bam 0 ) : ";
		cin >> m.dir;
	}

	int c;
	do
	{
		cout << "MENU \n";
		cout << "1. Them dinh\n";
		cout << "2. xoa dinh\n";
		cout << "3. them canh\n";
		cout << "4. xoa canh\n";
		cout << "5. krusal\n";
		cout << "6. prim\n";
		int chose;
		cin >> chose;

		switch (chose)
		{
		case 1: {
			int v;
			cout << "Nhap so dinh can them: \n";
			cin >> v;

			addVertex(m, v);
			break;
		}
		case 2: {
			int v;
			cout << "Nhap dinh can xoa: \n";
			cin >> v;
			v--;
			delVertex(m, v);
			break;
		}
		case 3: {
			int a, b;
			cout << "Nhap canh a: ";
			cin >> a;
			cout << "Nhap canh b: ";
			cin >> b;
			a--; b--;
			addEdge(m, a, b);
			break;
		}
		case 4: {
			int a, b;
			cout << "Nhap canh a: ";
			cin >> a;
			cout << "Nhap canh b: ";
			cin >> b;
			a--; b--;
			delEdge(m, a, b);
			break;
		}
		case 5:
			kruskal(m);
			break;

		case 6:
			prim(m, 0); // chọn start = 0
			break;
		default:
			break;
		}
		output(m);
		int res = isGraph(m);
		if (res != -1) {
			cout << "So canh cua do thi hien tai : " << res << "\n";
		}
		cout << "Tiep tuc ( bam 1 )/ ket thuc ( bam 0 ) : ";
		cin >> c;
	} while (c == 1);


	cntTPLT(m);
	if (m.dir == 0) {
		for (int i = 0; i < m.n; i++) {
			m.visited[i] = 0;
			m.parent[i] = 0;
		}
		int s, g;
		bool res = false;
		for (int i = 0; i < m.n; i++) {
			res = checkCycleNoDir(m, i, s, g);
		}
		if (res) {
			cout << "Co chu trinh \n";
			display(m, s, g);
		}
		else {
			cout << "Khong co chu trinh \n";
		}

	}
	else {
		for (int i = 0; i < m.n; i++) {
			m.visited[i] = 0;
			m.parent[i] = 0;
		}
		int s, g;
		bool res = false;
		for (int i = 0; i < m.n; i++) {
			res = checkCycleDir(m, i, s, g);
		}
		if (res) {
			cout << "Co chu trinh \n";
			display(m, s, g);
		}
		else {
			cout << "Khong co chu trinh \n";
		}
	}

	del(m);
	return 0;
}

