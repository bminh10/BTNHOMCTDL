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
	bool ts;
	// co huong hay khong
	bool dir;
	// mang danh dau da xoa dinh
	bool* canuse;
	//ham check ho tro cho dem canh
	int** check;
	//mang tham
	int* visited;
	//mang de duyet duong di
	int* parent;
	//mang ho tro viec tim thanh phan lien thong
	int* label;
};

//========== Khởi tạo đồ thị ==========
void init(Graph& m) {
	m.matrix = nullptr;
	m.list = nullptr;
	m.sz = nullptr;
	m.canuse = nullptr;
	m.check = nullptr;
	m.visited = nullptr;
	m.parent = nullptr;
	m.label = nullptr;

	m.dir = false;
	m.ts = false;
}

//========== Tạo đồ thị ==========
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
	m.canuse = new bool[m.n];
	m.visited = new int[m.n];
	m.parent = new int[m.n];
	m.label = new int[m.n];
	for (int i = 0; i < m.n; i++) {
		m.canuse[i] = true;
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

//========== Xuất đồ thị ==========
void output(Graph m) {
	cout << "DO THI HIEN TAI \n";
	switch (m.type)
	{
	case 1: {
		for (int i = 0; i < m.n; i++) {
			if (!m.canuse[i]) continue;
			cout << "Dinh " << i + 1 << ": ";
			for (int j = 0; j < m.n; j++) {
				if (m.canuse[j]) {
					cout << m.matrix[i][j] << " ";
				}
			}
			cout << endl;
		}
		break;
	}
	case 0: {
		for (int i = 0; i < m.n; i++) {
			if (!m.canuse[i]) continue;
			cout << "Dinh " << i + 1 << ": ";
			for (int j = 0; j < m.sz[i]; j++) {
				int dinh = m.list[i][j];
				if (m.canuse[dinh]) {
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


//========== Kiểm tra đỉnh/cạnh ==========
// kiểm tra đỉnh hợp lệ 
bool existVertex(Graph& m, int u) {
    return (u >= 0 && u < m.n);
}

// kiểm tra cạnh tồn tại 
bool existEdge(Graph& m, int u, int v) {
	if (!existVertex(m, u) || !existVertex(m, v)) return false;
	if (m.type == 1) {
		return m.matrix[u][v] != 0;
	} else { // danh sách kề
		for (int i = 0; i < m.sz[u]; i++) {
			if (m.list[u][i] == v) return true;
		}
		return false;
	}
}

//========== Thêm/Xóa đỉnh ==========
//ham them dinh
void addVertex(Graph& m, int v) {
	if (v == 0) return;
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
			delete[] m.matrix[i];
		}
		delete[] m.matrix;
		m.matrix = newmatrix;

		break;
	}
	case 0: {
		int** newlist = new int* [newsize];
		for (int i = 0; i < newsize; i++) {
			newlist[i] = nullptr;
		}
		for (int i = 0; i < m.n; i++) {
			if (m.sz[i] > 0) {
				newlist[i] = new int[m.sz[i]];
				for (int j = 0; j < m.sz[i]; j++) newlist[i][j] = m.list[i][j];
			}
		}
		for (int i = 0; i < m.n; i++) {
			delete[] m.list[i];
		}
		delete[] m.list;
		m.list = newlist;

		int* newsz = new int[newsize];
		for (int i = 0; i < newsize; i++) {
			newsz[i] = 0;
		}

		for (int i = 0; i < m.n; i++) {
			newsz[i] = m.sz[i];
		}
		delete[] m.sz;
		m.sz = newsz;

		break;
	}
	default:
		break;
	}


	bool* newcanuse = new bool[newsize];
	for (int i = 0; i < newsize; i++) {
		newcanuse[i] = true;
	}
	for (int i = 0; i < m.n; i++) {
		newcanuse[i] = m.canuse[i];
	}
	delete[] m.canuse;
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
		delete[] m.check[i];
	}
	delete[] m.check;
	m.check = newcheck;

	m.n = newsize;

}

//ham xoa dinh
void delVertex(Graph& m, int v) {
	if (!existVertex(m, v)) {
		cout << "Vuot pham vi\n";
		return;
	}
	if (m.canuse[v]) {
		m.canuse[v] = false;
		if (m.type == 1) {
			for (int i = 0; i < m.n; i++) {
				m.matrix[v][i] = 0;
				m.matrix[i][v] = 0;
			}
		} else {
            // xóa list của v 
			if (m.list[v] != nullptr) {
				delete[] m.list[v];
				m.list[v] = nullptr;
				m.sz[v] = 0;
			}
			// xóa v trong các list khác
			for (int i = 0; i < m.n; i++) {
				if (m.list[i] == nullptr) continue;
				int write = 0;
				for (int j = 0; j < m.sz[i]; j++) {
					if (m.list[i][j] == v) continue;
					m.list[i][write++] = m.list[i][j];
				}
				if (write == 0) {
					delete[] m.list[i];
					m.list[i] = nullptr;
					m.sz[i] = 0;
				} else {
					int* tmp = new int[write];
					for (int k = 0; k < write; k++) tmp[k] = m.list[i][k];
					delete[] m.list[i];
					m.list[i] = tmp;
					m.sz[i] = write;
				}
			}
			
		}
	}
	else {
		cout << "Dinh nay da bi xoa \n";
	}
}

//========== Thêm phần tử động vào mảng ==========
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
	delete[] a;
	a = newarr;
	n++;

}

//========== Thêm/Xóa cạnh ==========
 //ham them canh
void addEdge(Graph& m, int a, int b) {
	// kiểm tra đỉnh hợp lệ
	if (!existVertex(m, a) || !existVertex(m, b)) {
		cout << "Dinh khong hop le\n";
		return;
	}

	// không cho self-loop
	if (a == b) {
		cout << "No for (u == v)\n";
		return;
	}

	// không cho phép cạnh trùng
	if (existEdge(m, a, b)) {
		cout << "Canh da ton tai\n";
		return;
	}

	switch (m.type)
	{
	case 1: {
		if (m.ts) {
			int ts;
			cout << "Nhap trong so cho canh " << a + 1 << "->" << b + 1 << ": ";
			cin >> ts;
			m.matrix[a][b] = ts;
			if (!m.dir) m.matrix[b][a] = ts;
		}
		else {
			m.matrix[a][b] = 1;
			if (!m.dir) m.matrix[b][a] = 1;
		}

		break;
	}

	case 0: {
		if (!m.dir) {
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
	if (a == nullptr || n == 0) return;
	if (n == 1) {
		delete[] a;
		a = nullptr;
		n = 0;
		return;
	}
	int* newarr = new int[n - 1];
	int idx = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] == x) continue;
		newarr[idx] = a[i];
		idx++;
	}
	delete[] a;
	a = newarr;
	n--;
}

//ham xoa canh
void delEdge(Graph& m, int a, int b) {
	// kiểm tra đỉnh hợp lệ
	if (!existVertex(m, a) || !existVertex(m, b)) {
		cout << "Dinh khong hop le\n";
		return;
	}

	// không cho xóa nếu cạnh không tồn tại
	if (!existEdge(m, a, b)) {
		cout << "Canh khong ton tai\n";
		return;
	}

	switch (m.type)
	{
	case 1: {
		m.matrix[a][b] = 0;
		if (!m.dir) m.matrix[b][a] = 0;
		break;
	}

	case 0: {

		if (m.dir) {
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

//========== Kiểm tra đồ thị & đếm cạnh ==========
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
			if (!m.canuse[i]) continue;
			for (int j = 0; j < m.n; j++) {
				if (m.matrix[i][j] > 0 && m.check[j][i] == 0 && m.canuse[j]) {
					res++;
					m.check[i][j] = 1;
				}
			}
		}
		break;
	}
	case 0: {
		for (int i = 0; i < m.n; i++) {
			if (!m.canuse[i]) continue;
			for (int j = 0; j < m.sz[i]; j++) {
				int dinh = m.list[i][j];
				if (m.check[dinh][i] == 0 && m.canuse[dinh]) {
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

	if (res <= (m.n * (m.n - 1) / 2)) {
		return res;
	}
	else {
		return -1;
	}
}

//========== Duyệt & Thành phần liên thông ==========
 //ham ho tro tim thanh phan lien thong
void dfs(Graph& m, int u, int label) {
    stack<int> s;
    s.push(u);

    while (!s.empty()) {
        int v = s.top(); s.pop();
        if (m.visited[v]) continue;

        m.visited[v] = true;
        m.label[v] = label;

        if (m.type == 1) {  // matrix
            for (int x = 0; x < m.n; x++) {
                if (!existVertex(m, x)) continue;
                if (m.matrix[v][x] > 0 && !m.visited[x]) {
                    s.push(x);
                }
            }
        }
        else { // list
            for (int i = 0; i < m.sz[v]; i++) {
                int x = m.list[v][i];
                if (!existVertex(m, x)) continue;
                if (!m.visited[x]) {
                    s.push(x);
                }
            }
        }
    }
}

void countConnected(Graph& m) {

    for (int i = 0; i < m.n; i++) {
        m.visited[i] = false;
        m.label[i] = 0;
    }

    int count = 0;

    for (int i = 0; i < m.n; i++) {
        if (existVertex(m, i) && !m.visited[i]) {
            count++;
            dfs(m, i, count);   
        }
    }


    if (count == 1) {
        cout << "Do thi lien thong\n";
        return;
    }

    cout << "Do thi khong lien thong\n";

    for (int t = 1; t <= count; t++) {
        cout << "Thanh phan lien thong thu " << t << ": ";
        for (int j = 0; j < m.n; j++) {
            if (existVertex(m, j) && m.label[j] == t)
                cout << j + 1 << " ";
        }
        cout << endl;
    }
}

//========== Kiểm tra chu trình ==========
 //ham kiem tra chu trinh - hoat dong cho ca do thi co huong va vo huong
//ham kiem chu trinh tren do thi co huong 
// 0 : dinh chua tham , 1 : dinh dang trong qua trinh tham , 2 : dinh da tham xong
bool checkCycle(Graph& m, int v, int& start, int& goal) {
	m.visited[v] = 1;
	
	if (m.type == 1) { // Ma tran ke
		for (int i = 0; i < m.n; i++) {
			if (!existVertex(m, i)) continue;
			if (m.matrix[v][i] > 0) {
				if (m.visited[i] == 0) {
					m.parent[i] = v;
					if (checkCycle(m, i, start, goal)) return true;
				}
				else if (m.dir && m.visited[i] == 1) {
					// Do thi co huong
					goal = v; start = i;
					return true;
				}
				else if (!m.dir && i != m.parent[v]) {
					// Do thi vo huong
					goal = v; start = i;
					return true;
				}
			}
		}
	}
	else if (m.type == 0) { // Danh sach ke
		for (int i = 0; i < m.sz[v]; i++) {
			int dinh = m.list[v][i];
			if (!existVertex(m, dinh)) continue;
			if (m.visited[dinh] == 0) {
				m.parent[dinh] = v;
				if (checkCycle(m, dinh, start, goal)) return true;
			}
			else if (m.dir && m.visited[dinh] == 1) {
				// Do thi co huong
				goal = v; start = dinh;
				return true;
			}
			else if (!m.dir && dinh != m.parent[v]) {
				// Do thi vo huong
				goal = v; start = dinh;
				return true;
			}
		}
	}
	
	// Co huong
	if (m.dir) m.visited[v] = 2;
	
	return false;
}

//========== Hiển thị chu trình ==========
void displayCycle(Graph m, int s, int g) {
	stack<int> cycle;
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

//========== Giải phóng đồ thị ==========
 //giai phong do thi
void del(Graph& m) {
	if (m.check != nullptr) {
		for (int i = 0; i < m.n; i++) {
			delete[] m.check[i];
		}
		delete[] m.check;
		m.check = nullptr;
	}
	if (m.matrix != nullptr) {
		for (int i = 0; i < m.n; i++) {
			delete[] m.matrix[i];
		}
		delete[] m.matrix;
		m.matrix = nullptr;
	}
	if (m.list != nullptr) {
		for (int i = 0; i < m.n; i++) {
			delete[] m.list[i];
		}
		delete[] m.list;
		m.list = nullptr;
	}
	delete[] m.sz; m.sz = nullptr;
	delete[] m.canuse; m.canuse = nullptr;
	delete[] m.visited; m.visited = nullptr;
	delete[] m.parent; m.parent = nullptr;
	delete[] m.label; m.label = nullptr;

	bool res = (m.sz == nullptr && m.list == nullptr && m.matrix == nullptr && m.canuse == nullptr && m.visited == nullptr && m.parent == nullptr && m.label == nullptr);
	if (res) {
		cout << "Giai phong thanh cong \n";
	}
}

//========== Kruskal & Prim ==========
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

	// hỏi user xem có trọng số hay không
	cout << "Do thi co trong so ( bam 1 ) / khong ( bam 0 ): ";
	{
		int tmp; cin >> tmp; m.ts = (tmp == 1);
	}

	init(m);
	createGraph(m);

	if (m.type == 0) {
		cout << "Do thi co huong ( bam 1 ) / Do thi vo huong ( bam 0 ) : ";
		{
			int tmp; cin >> tmp; m.dir = (tmp == 1);
		}
	}

	output(m);

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
			if (m.type == 1) kruskal(m);
			else cout << "Kruskal chi hoat dong tren ma tran ke co trong so.\n";
			break;

		case 6:
			if (m.type == 1) prim(m, 0); // chọn start = 0
			else cout << "Prim chi hoat dong tren ma tran ke co trong so.\n";
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


	// gọi hàm đếm thành phần liên thông (thay cho cntTPLT)
	countConnected(m);

	// kiểm tra chu trình: dùng hàm checkCycle có sẵn
	if (m.dir == 0) {
		for (int i = 0; i < m.n; i++) {
			m.visited[i] = 0;
			m.parent[i] = -1;
		}
		int s = -1, g = -1;
		bool res = false;
		for (int i = 0; i < m.n; i++) {
			if (m.visited[i] == 0) {
				// dùng hàm checkCycle đã có (dùng cho cả có hướng & vô hướng)
				res = checkCycle(m, i, s, g);
			}
			if (res == true) {
				break;
			}
		}
		if (res) {
			cout << "Co chu trinh \n";
			displayCycle(m, s, g);
		}
		else {
			cout << "Khong co chu trinh \n";
		}

	}
	else {
		for (int i = 0; i < m.n; i++) {
			m.visited[i] = 0;
			m.parent[i] = -1;
		}
		int s = -1, g = -1;
		bool res = false;
		for (int i = 0; i < m.n; i++) {
			if (m.visited[i] == 0) {
				res = checkCycle(m, i, s, g);
			}
			if (res == true) {
				break;
			}
		}
		if (res) {
			cout << "Co chu trinh \n";
			displayCycle(m, s, g);
		}
		else {
			cout << "Khong co chu trinh \n";
		}
	}

	del(m);
	return 0;
}
