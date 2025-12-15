#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <ctime>
#include <string>
#include <climits>
#define ll long long
using namespace std;

#define INF 1000

//==================== SẮP XẾP =================
//kich thuoc bang bam co dinh 65
const int M = 65;


//luu ho ten va do dai cua ten
struct name {
	string s;
	int len;
};


struct SinhVien {
	ll mssv;
	name hoten;
	double dtb, hp;
};


struct List {
	//mang list co sau khi chuyen tu bang bam sang mang list de sort mssv, diem trung binh, hoc phi
	SinhVien* list;
	int n;
};

//them 1 phan tu vao mang
void push(SinhVien*& a, int& n, SinhVien x) {
	if (a == nullptr) {
		n = 1;
		a = new SinhVien[n];
		a[0] = x;
		return;
	}
	SinhVien* newarr = new SinhVien[n + 1];
	for (int i = 0; i < n; i++) {
		newarr[i] = a[i];
	}
	newarr[n] = x;
	delete[]a;
	a = newarr;
	n++;
}

//lay du lieu ( mssv , do dai cua ten , diem trung binh , hoc phi )
ll getVal(SinhVien x, int chon1) {
	switch (chon1)
	{
	case 1: {
		return x.mssv;
		break;
	}
	case 2: {
		return x.hoten.len;
		break;
	}
	case 3: {
		return x.dtb * 10;
		break;
	}
	case 4: {
		return x.hp * 100;
		break;
	}

	default:
		break;
	}

}

//xuat bang bam
void output(SinhVien** a, int* sz) {
	cout << "DANH SACH HIEN TAI \n";
	for (int i = 0; i < M; i++) {
		if (a[i] == nullptr)continue;
		for (int j = 0; j < sz[i]; j++) {
			cout << a[i][j].mssv << " " << a[i][j].hoten.s << " " << a[i][j].dtb << " " << a[i][j].hp << endl;
		}

	}
}
//xuat mang list
void output2(SinhVien* list, int n) {
	cout << "DANH SACH HIEN TAI\n";
	for (int i = 0; i < n; i++) {
		cout << list[i].mssv << " " << list[i].hoten.s << " " << list[i].dtb << " " << list[i].hp << endl;
	}
}

//ham tinh do dai ten;
int calLen(SinhVien x) {
	int n = x.hoten.s.length();
	int res = 0;
	for (int i = n - 1; i >= 0; i--) {

		if (x.hoten.s[i - 1] == ' ') {
			res++;
			break;
		}
		res++;

	}
	return res;
}

//ham lay ma ascii chu cai dau cua ten
ll getIdx(SinhVien x) {
	ll res = 0;
	for (int i = x.hoten.s.length() - 1; i >= 0; i--) {
		if (x.hoten.s[i - 1] == ' ') {
			res = x.hoten.s[i] - '0';
			break;
		}
	}
	return res;
}

void readData(SinhVien**& a, int*& sz) {
	ifstream fin;
	fin.open("SinhVien.txt");
	while (!fin.eof())
	{
		SinhVien x;
		fin >> x.mssv;
		fin.ignore();
		getline(fin, x.hoten.s, '#');
		x.hoten.len = 0;
		fin >> x.dtb;
		fin.ignore();
		fin >> x.hp;
		//bien idx luu gia tri sau khi hash
		ll idx = getIdx(x) % M;
		push(a[idx], sz[idx], x);
	}
	fin.close();



}


//so sanh mssv;
ll cmpMSSV(SinhVien a, SinhVien b) {
	return a.mssv - b.mssv;
}

//so sanh do dai cua ten
ll cmpTen(SinhVien a, SinhVien b) {
	return a.hoten.len - b.hoten.len;
}

//so sanh diem trung binh
ll cmpDTB(SinhVien a, SinhVien b) {
	return a.dtb - b.dtb > 0 ? 1 : a.dtb - b.dtb < 0 ? -1 : 0;
}

//so sanh hoc phi
ll cmpHP(SinhVien a, SinhVien b) {
	return a.hp - b.hp > 0 ? 1 : a.hp - b.hp < 0 ? -1 : 0;
}

void shellSort(SinhVien*& a, int n, ll func(SinhVien a, SinhVien b), int chon2) {
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			SinhVien tmp = a[i];
			int j;
			switch (chon2)
			{
			case 1: {
				for (j = i; j >= gap && func(a[j - gap], tmp) > 0; j -= gap) {
					a[j] = a[j - gap];
				}
				break;

			}
			case 2: {
				for (j = i; j >= gap && func(a[j - gap], tmp) < 0; j -= gap) {
					a[j] = a[j - gap];
				}
				break;
			}
			default:
				break;
			}
			a[j] = tmp;
		}

	}

}

//tim max
ll findMax(SinhVien* a, int n, int chon1) {
	ll max = INT_MIN;
	for (int i = 0; i < n; i++) {
		int val = getVal(a[i], chon1);
		if (max < val) {
			max = val;
		}
	}
	return max;
}

void countingSort(SinhVien*& a, int n, int chon1, int chon2, int exp = 0) {
	ll max = 0;
	if (exp != 0) {
		max = 9;
	}
	else {
		max = findMax(a, n, chon1);
	}
	int* cnt = new int[max + 1];
	for (int i = 0; i <= max; i++) {
		cnt[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		int val = exp != 0 ? (getVal(a[i], chon1) / exp) % 10 : getVal(a[i], chon1);
		cnt[val]++;
	}

	for (int i = 1; i <= max; i++) {
		cnt[i] += cnt[i - 1];
	}
	SinhVien* output = new SinhVien[n];
	for (int i = n - 1; i >= 0; i--) {
		int val = exp != 0 ? (getVal(a[i], chon1) / exp) % 10 : getVal(a[i], chon1);
		output[cnt[val] - 1] = a[i];
		cnt[val]--;
	}

	if (chon2 == 1 || exp != 0) {
		for (int i = 0; i < n; i++) {
			a[i] = output[i];
		}
	}
	else if (exp == 0) {
		int idx = 0;
		for (int i = n - 1; i >= 0; i--) {
			a[idx] = output[i];
			idx++;
		}
	}
	delete[]output;
	delete[]cnt;
}

void radixSort(SinhVien*& a, int n, int chon1, int chon2) {
	ll max = findMax(a, n, chon1);
	for (int exp = 1; max / exp != 0; exp *= 10) {
		countingSort(a, n, chon1, chon2, exp);
	}
	if (chon2 == 2) {
		for (int i = 0; i < n / 2; i++) {
			swap(a[i], a[(n - 1) - i]);
		}
	}

}

ll divide(ll x)
{
	ll sum = 1;
	while (x != 0)
	{
		sum *= 10;
		x /= 10;
	}
	return sum / 10;
}

void bucketSort(SinhVien*& a, int n, int chon1, int chon2) {
	SinhVien** bucket = new SinhVien * [n];
	int* sz = new int[n];
	for (int i = 0; i < n; i++) {
		bucket[i] = nullptr;
		sz[i] = 0;
	}

	ll m = findMax(a, n, chon1);

	ll div = divide(m);
	if (div == 0) div = 1;
	for (int i = 0; i < n; i++) {
		ll bucketI = getVal(a[i], chon1) / div;
		if (bucketI >= n) bucketI = n - 1;

		push(bucket[bucketI], sz[bucketI], a[i]);
	}

	for (int i = 0; i < n; i++) {
		if (sz[i] <= 1) continue;
		radixSort(bucket[i], sz[i], chon1, 1);
	}


	int idx = 0;

	for (int i = 0; i < n; i++) {
		if (bucket[i] == nullptr)continue;
		for (int j = 0; j < sz[i]; j++) {
			a[idx] = bucket[i][j];
			idx++;
		}
	}
	if (chon2 == 2)
	{
		int l = 0; int r = n - 1;
		while (l < r)
		{
			swap(a[l], a[r]);
			l++;
			r--;
		}
	}
	for (int i = 0; i < n; i++) {
		delete[] bucket[i];
	}
	delete[] bucket;
	delete[] sz;

}




//ham thao tac
void process(SinhVien**& a, int*& sz, int chon, int chon1, int chon2, List& l) {
	for (int i = 0; i < M; i++) {
		if (a[i] == nullptr)continue;
		for (int j = 0; j < sz[i]; j++) {
			a[i][j].hoten.len = calLen(a[i][j]);
		}
	}

	if (chon1 != 2) {

		for (int i = 0; i < M; i++) {
			if (a[i] == nullptr)continue;
			for (int j = 0; j < sz[i]; j++) {
				push(l.list, l.n, a[i][j]);
			}
		}

		switch (chon)
		{
		case 1: {
			switch (chon1)
			{
			case 1: {
				shellSort(l.list, l.n, cmpMSSV, chon2);
				break;
			}
			case 3: {
				shellSort(l.list, l.n, cmpDTB, chon2);
				break;
			case 4: {
				shellSort(l.list, l.n, cmpHP, chon2);
				break;
			}
			}
			default:
				break;
			}
			break;
		}
		case 2: {
			countingSort(l.list, l.n, chon1, chon2);
			break;
		}
		case 3: {
			radixSort(l.list, l.n, chon1, chon2);
			break;
		}
		case 4: {
			bucketSort(l.list, l.n, chon1, chon2);
			break;
		}
		default:
			break;
		}

	}
	else {
		for (int i = 0; i < M; i++) {
			if (a[i] == nullptr)continue;
			switch (chon)
			{
			case 1: {
				shellSort(a[i], sz[i], cmpTen, chon2);

				break;
			}
			case 2: {
				countingSort(a[i], sz[i], chon1, chon2);
				break;
			}
			case 3: {
				radixSort(a[i], sz[i], chon1, chon2);
				break;
			}
			case 4: {
				bucketSort(a[i], sz[i], chon1, chon2);
				break;
			}
			default:
				break;
			}
		}
	}



	if (chon1 != 2) {
		output2(l.list, l.n);
	}
	else {
		output(a, sz);

	}

}


//==================== ĐỒ THỊ =================
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
	//co trong so hoac khong have : true
	bool ts;
	// co huong hay khong have : true
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
//tạo đồ thị ngẫu nhin
void randomGraph(Graph& m) {
	srand(time(NULL));
	//đỉnh ngẫu nhiên từ 4 đến 9 đỉnh
	m.n = rand() % 5 + 4;
	m.matrix = new int* [m.n];
	for (int i = 0; i < m.n; i++) {
		m.matrix[i] = new int[m.n];
	}


	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			if (i == j)m.matrix[i][j] = 0;
			else {
				//trọng số ngẫu nhiên từ 1 tới 9
				m.matrix[i][j] = rand() % 9 + 1;
			}
			m.matrix[j][i] = m.matrix[i][j];
		}
	}

	m.dir = false;
	m.ts = true;
	m.type = 1;

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

//Nhap ma tran tu file
void readMatrixFromFile(Graph& m, const char* filename) {
	ifstream f(filename);
	if (!f) {
		cout << "Khong mo duoc file\n";
		return;
	}

	f >> m.n;

	// cap phat
	m.matrix = new int* [m.n];
	for (int i = 0; i < m.n; i++) {
		m.matrix[i] = new int[m.n];
	}

	// đọc ma trận
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			f >> m.matrix[i][j];
		}
	}

	// mặc định
	m.type = 1;      // ma tran ke
	m.ts = true;   // co trong so
	m.dir = false;
	for (int i = 0; i < m.n; i++) {
		for (int j = i; j < m.n; j++) {
			if (m.matrix[i][j] != m.matrix[j][i]) {
				m.dir = true;
				break;
			}
		}
		if (m.dir) break;
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

	f.close();
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
	return (u >= 0 && u < m.n) && m.canuse[u] == true;
}

// kiểm tra cạnh tồn tại 
bool existEdge(Graph& m, int u, int v) {
	if (!existVertex(m, u) || !existVertex(m, v)) return false;
	if (m.type == 1) {
		return m.matrix[u][v] != 0;
	}
	else { // danh sách kề
		for (int i = 0; i < m.sz[u]; i++) {
			if (m.list[u][i] == v) return true;
		}
		return false;
	}
}

//========== Thêm/Xóa đỉnh ==========
//ham them dinh
void addVertex(Graph& m, int v) {
	//so dinh can them
	if (v <= 0) return;
	int newsize = m.n + v;

	switch (m.type)
	{
	case 1: {
		int** newmatrix = new int* [newsize];
		//() : khoi tao lai moi phan tu bang 0
		for (int i = 0; i < newsize; i++) {
			newmatrix[i] = new int[newsize]();
		}
		//copy du lieu
		for (int i = 0; i < m.n; i++) {
			for (int j = 0; j < m.n; j++) {
				newmatrix[i][j] = m.matrix[i][j];
			}
		}

		for (int i = 0; i < m.n; i++) delete[] m.matrix[i];

		delete[] m.matrix;
		m.matrix = newmatrix;
		break;
	}
	case 0: {
		int** newlist = new int* [newsize];
		int* newsz = new int[newsize]();

		//copy du lieu
		for (int i = 0; i < newsize; i++) {
			if (m.sz[i] > 0) {
				newlist[i] = new int[m.sz[i]];
				for (int j = 0; j < m.sz[i]; j++) newlist[i][j] = m.list[i][j];
			}
			else {
				newlist[i] = nullptr;
			}
			newsz[i] = m.sz[i];
		}

		//khoi tao bien moi null
		for (int i = m.n; i < newsize; i++) newlist[i] = nullptr;

		//xoa du lieu cu
		for (int i = 0; i < m.n; i++) delete[] m.list[i];

		delete[] m.list;
		delete[] m.sz;

		m.list = newlist;
		m.sz = newsz;
		break;
	}
	default:
		break;
	}

	//Canuse
	bool* newcanuse = new bool[newsize];
	//copy cai cu + cai mo 
	for (int i = 0; i < m.n; i++) newcanuse[i] = m.canuse[i];
	for (int i = m.n; i < newsize; i++) newcanuse[i] = true;

	delete[] m.canuse;
	m.canuse = newcanuse;

	//Check
		//check + () : khoi tao 0 luon
	int** newcheck = new int* [newsize];
	for (int i = 0; i < newsize; i++) newcheck[i] = new int[newsize]();
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			newcheck[i][j] = m.check[i][j];
		}
	}
	for (int i = 0; i < m.n; i++) delete[] m.check[i];
	delete[] m.check;
	m.check = newcheck;

	//visited
	int* newvisited = new int[newsize];
	for (int i = 0; i < m.n; i++) newvisited[i] = m.visited[i];
	for (int i = m.n; i < newsize; i++) newvisited[i] = 0;
	delete[] m.visited;
	m.visited = newvisited;

	//parent
	int* newparent = new int[newsize];
	for (int i = 0; i < m.n; i++) newparent[i] = m.parent[i];
	for (int i = m.n; i < newsize; i++) newparent[i] = -1;
	delete[] m.parent;
	m.parent = newparent;

	//lable
	int* newlabel = new int[newsize];
	for (int i = 0; i < m.n; i++) newlabel[i] = m.label[i];
	for (int i = m.n; i < newsize; i++) newlabel[i] = 0;
	delete[] m.label;
	m.label = newlabel;

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
		}
		else {
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
				}
				else {
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
	//không cho thêm cạnh có 1 đỉnh đã bị xoá trước đó
	if (m.canuse[a] == false || m.canuse[b] == false) {
		cout << "Canh khong hop le \n";
		return;
	}

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
			m.matrix[b][a] = ts;
		}
		else {
			m.matrix[a][b] = 1;
			m.matrix[b][a] = 1;
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


//thuật toán duyệt đồ thị

void BFS(Graph& m, int start) {
	for (int i = 0; i < m.n; i++) {
		m.visited[i] = 0;
	}
	queue<int>q;
	q.push(start);

	while (!q.empty())
	{
		int r = q.front();
		q.pop();
		cout << r + 1 << " ";
		m.visited[r] = 1;
		switch (m.type)
		{
		case 1: {
			for (int i = 0; i < m.n; i++) {
				if (m.canuse[i] == true && m.matrix[r][i] > 0 && m.visited[i] == 0) {
					q.push(i);
					m.visited[i] = -1;

				}
			}
			break;
		}
		case 0: {
			for (int i = 0; i < m.sz[r]; i++) {
				int dinh = m.list[r][i];
				if (m.canuse[dinh] == true && m.visited[dinh] == 0) {
					q.push(dinh);
					m.visited[dinh] = -1;

				}
			}
			break;
		}
		default:
			break;
		}
	}
	cout << endl;
}

void DFS(Graph& m, int  start) {
	for (int i = 0; i < m.n; i++) {
		m.visited[i] = 0;
	}
	stack<int>q;
	q.push(start);

	while (!q.empty())
	{
		int r = q.top();
		if (m.visited[r] == 0) {
			cout << r + 1 << " ";
		}
		m.visited[r] = 1;
		bool flag = false;
		switch (m.type)
		{
		case 1: {
			for (int i = 0; i < m.n; i++) {
				if (existVertex(m, i) && m.matrix[r][i] > 0 && m.visited[i] == 0) {
					q.push(i);
					flag = true;

					break;
				}
			}
			break;
		}
		case 0: {
			for (int i = 0; i < m.sz[r]; i++) {
				int dinh = m.list[r][i];
				if (existVertex(m, dinh) && m.visited[dinh] == 0) {
					q.push(dinh);
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
			q.pop();
		}
	}
	cout << endl;
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


int countConnected(Graph& m) {

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
		return 1;
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
	return -1;
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

//========== Thuật toán đường đi ngắn nhất ==========
void printRes(Graph& m, int start, int end, int* d) {
	if (end == -1) {
		cout << start + 1 << endl;
		for (int i = 0; i < m.n; i++) {
			cout << start + 1 << " -> " << i + 1 << endl;

			if (d[i] == INF) {
				cout << "Khong co duong di\n\n";
				continue;
			}

			cout << "Tong do dai = " << d[i] << endl;
			cout << "Duong di: ";

			stack<int> st;
			for (int v = i; v != -1; v = m.parent[v])
				st.push(v + 1);

			while (!st.empty()) {
				cout << st.top();
				st.pop();
				if (!st.empty()) cout << " -> ";
			}
			cout << "\n";
		}
		return;
	}

	cout << start + 1 << " -> " << end + 1 << endl;
	if (d[end] == INF) {
		cout << "Khong co duong di\n";
		return;
	}

	cout << "Tong do dai = " << d[end] << endl;
	cout << "Duong di: ";

	stack<int> st;
	for (int v = end; v != -1; v = m.parent[v])
		st.push(v + 1);

	while (!st.empty()) {
		cout << st.top();
		st.pop();
		if (!st.empty()) cout << " -> ";
	}
	cout << endl;
}

//1. Dijkstra
void dijkstra(Graph& m, int start, int end) {
	if (!m.ts) {
		cout << "Do thi khong co trong so\n";
		return;
	}

	int* d = new int[m.n];
	for (int i = 0; i < m.n; i++) {
		d[i] = INF;
		m.visited[i] = false;
		m.parent[i] = -1;
	}

	d[start] = 0;

	for (int i = 0; i < m.n; i++) {
		int u = -1, minD = INF;
		for (int j = 0; j < m.n; j++)
			if (!m.visited[j] && d[j] < minD) {
				minD = d[j];
				u = j;
			}

		if (u == -1) break;
		m.visited[u] = true;

		for (int v = 0; v < m.n; v++) {
			if (m.matrix[u][v] > 0 &&
				!m.visited[v] &&
				d[u] + m.matrix[u][v] < d[v]) {
				d[v] = d[u] + m.matrix[u][v];
				m.parent[v] = u;
			}
		}
	}

	cout << "===== DIJKSTRA =====\n";
	printRes(m, start, end, d);

	delete[] d;
}

//2. Bellman Ford

void bellmanFord(Graph& m, int start, int end) {
	if (!m.ts) {
		cout << "Do thi khong co trong so\n";
		return;
	}

	int* d = new int[m.n];
	for (int i = 0; i < m.n; i++) {
		d[i] = INF;
		m.parent[i] = -1;
	}

	d[start] = 0;

	for (int k = 0; k < m.n - 1; k++) {
		for (int u = 0; u < m.n; u++) {
			if (d[u] == INF) continue;
			for (int v = 0; v < m.n; v++) {
				if (m.matrix[u][v] > 0 &&
					d[u] + m.matrix[u][v] < d[v]) {
					d[v] = d[u] + m.matrix[u][v];
					m.parent[v] = u;
				}
			}
		}
	}

	// check chu trinh am
	for (int u = 0; u < m.n; u++) {
		if (d[u] == INF) continue;
		for (int v = 0; v < m.n; v++) {
			if (m.matrix[u][v] > 0 &&
				d[u] + m.matrix[u][v] < d[v]) {
				cout << "Chu trinh am\n";
				delete[] d;
				return;
			}
		}
	}

	cout << "===== BELLMAN FORD =====\n";
	printRes(m, start, end, d);

	delete[] d;
}

//3. Floyd Warshall
void floydWarshall(Graph& m, int start, int end) {
	if (!m.ts) {
		cout << "Do thi khong co trong so\n";
		return;
	}

	if (end == -1) {
		cout << "Floyd Warshall chi ho tro 1 cap (start -> end)\n";
		return;
	}

	int d[100][100], next[100][100];

	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			if (i == j) {
				d[i][j] = 0;
				next[i][j] = j;
			}
			else if (m.matrix[i][j] > 0) {
				d[i][j] = m.matrix[i][j];
				next[i][j] = j;
			}
			else {
				d[i][j] = INF;
				next[i][j] = -1;
			}
		}
	}

	for (int k = 0; k < m.n; k++)
		for (int i = 0; i < m.n; i++)
			for (int j = 0; j < m.n; j++)
				if (d[i][k] != INF && d[k][j] != INF &&
					d[i][k] + d[k][j] < d[i][j]) {
					d[i][j] = d[i][k] + d[k][j];
					next[i][j] = next[i][k];
				}

	cout << "===== FLOYD WARSHALL =====\n";
	cout << start + 1 << " -> " << end + 1 << endl;

	if (d[start][end] == INF) {
		cout << "Khong co duong di\n";
		return;
	}

	cout << "Tong do dai = " << d[start][end] << endl;
	cout << "Duong di: ";

	int u = start;
	while (u != end) {
		cout << u + 1 << " -> ";
		u = next[u][end];
	}
	cout << end + 1 << endl;
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

	//Bien luu tong trong so
	int d = 0;

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
			d += edges[i].w;
			parent[rv] = ru;
			pick++;
			if (pick == m.n - 1) break;
		}
	}
	cout << "Tong trong so : " << d << endl;
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

	//bien luu tong trong so
	int d = 0;

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
			d += m.matrix[i][parent[i]];
		}
	}
	cout << "Tong trong so : " << d << endl;

	delete[] visited;
	delete[] dist;
	delete[] parent;
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

int main() {

	int  menu = 0;

	int c2;
	do
	{
		cout << "CHAO MUNG BAN DA DEN VOI APP SORTING VA GRAPH \n";
		cout << "Ung dung co the lam viec voi: \n";
		cout << "1.Thuat toan sap xep \n";
		cout << "2.Do thi \n";
		cout << "Ban muon lam viec voi ( chon 1 hoac 2 ):  ";
		cin >> menu;
		switch (menu)
		{
		case 1:
		{
			//luu tru du lieu bang hashtable
			SinhVien** a;
			//mang sz luu tru kich thuoc moi bucket
			int* sz;

			//luu tru du lieu bang mang khi nguoi dung chon sort theo mssv,diem trung binh,hoc phi
			List l;



			int c;
			do
			{
				a = nullptr;
				l.list = nullptr;
				l.n = 0;
				a = new SinhVien * [M];
				sz = new int[M];
				for (int i = 0; i < M; i++) {
					a[i] = nullptr;
					sz[i] = 0;
				}
				readData(a, sz);
				output(a, sz);
				cout << "MENU\n";
				cout << "1. Shell sort \n";
				cout << "2. counting sort \n";
				cout << "3. radix sort \n";
				cout << "4. bucket sort \n";
				int chon;

				do
				{
					cout << "Chon chuc nang: ";
					cin >> chon;
					if (chon > 4 || chon <= 0)
					{
						cout << "chuc nang khong ton tai !!!! \n";
					}
				} while (chon > 4 || chon <= 0);

				cout << "MENU\n";
				cout << "1. MSSV \n";
				cout << "2. Ten \n";
				cout << "3. DTB \n";
				cout << "4. HP\n";
				int chon1;

				do
				{
					cout << "Ban muon sort theo: ";
					cin >> chon1;
					if (chon1 > 4 || chon1 <= 0)
					{
						cout << "chuc nang khong ton tai !!!! \n";
					}
				} while (chon1 > 4 || chon1 <= 0);

				cout << "MENU\n";
				cout << "1. Tang dan \n";
				cout << "2. Giam dan\n";
				int chon2;
				do
				{
					cout << "Chon thu tu sap xep: ";
					cin >> chon2;
					if (chon2 > 2 || chon2 <= 0)
					{
						cout << "chuc nang khong ton tai !!!! \n";
					}
				} while (chon2 > 2 || chon2 <= 0);

				process(a, sz, chon, chon1, chon2, l);

				cout << "Tiep tuc ( bam 1 ) / ket thuc( bam 0 ): ";
				cin >> c;
			} while (c == 1);



			for (int i = 0; i < M; i++) {
				delete[]a[i];
			}
			delete[]l.list;
			delete[]a;
			delete[]sz;


			break;
		}
		case 2:
		{
			Graph m;
			init(m);

			// ===== CHON CACH NHAP DO THI =====
			cout << "Nhap do thi tu FILE (1) / Nhap tay (2) / Tao do thi ngau nhien (3): ";
			int choice;	cin >> choice;
			bool flag = true;
			if (choice == 1) {
				readMatrixFromFile(m, "matrix.txt");
				flag = false;
			}
			else if (choice == 2) {

				// ===== NHAP TAY =====

				cout << "Dung ma tran ke (1) / danh sach ke (0): ";
				cin >> m.type;

				if (m.type == 1) {
					int tmp;
					cout << "Do thi co trong so (1) / khong (0): ";
					cin >> tmp;
					m.ts = (tmp == 1);
				}
				else {
					m.ts = 0;
				}

				if (m.type == 0) {
					cout << "Do thi co huong ( bam 1 ) / vo huong ( bam 0 ): ";
					cin >> m.dir;
				}



				createGraph(m);
				cout << "=== DO THI NHAP TAY ===\n";
				flag = false;
			}
			else if (choice == 3) {
				randomGraph(m);
				flag = false;
			}
			else
			{
				cout << "chuc nang khong ton tai !!!! \n";

			}
			if (flag) break;



			output(m);

			int res1 = isGraph(m);
			if (res1 != -1) {
				cout << "So canh cua do thi hien tai : " << res1 << "\n";
			}

			// gọi hàm đếm thành phần liên thông (thay cho cntTPLT)
			res1 = countConnected(m);

			int c1 = 0;
			do
			{
				cout << "MENU \n";
				cout << "1. Them dinh\n";
				cout << "2. xoa dinh\n";
				cout << "3. them canh\n";
				cout << "4. xoa canh\n";
				cout << "5. bfs\n";
				cout << "6. dfs\n";
				if (m.type != 0) {
					cout << "7. krusal\n";
					cout << "8. prim\n";
					cout << "9. Dijkstra\n";
					cout << "10. Bellman Ford\n";
					cout << "11. Floyd Warshall\n";
				}
				cout << "Chon chuc nang: ";
				int chose;
				cin >> chose;

				switch (chose)
				{
				case 1: {
					int v;
					cout << "Nhap so dinh can them: ";
					cin >> v;

					addVertex(m, v);
					break;
				}
				case 2: {
					int v;
					cout << "Nhap dinh can xoa: ";
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
				case 5: {
					int v;
					cout << "Nhap dinh bat dau: ";
					cin >> v;
					v--;
					if (existVertex(m, v)) {
						cout << "Thu tu duyet : ";
						BFS(m, v);
					}
					else {
						cout << "Dinh khong ton tai \n";
					}

					break;
				}

					  if (m.type != 0) {
				case 6: {
					int v;
					cout << "Nhap dinh bat dau: ";
					cin >> v;
					v--;
					if (existVertex(m, v)) {
						cout << "Thu tu duyet : ";
						DFS(m, v);
					}
					else {
						cout << "Dinh khong ton tai \n";
					}


					break;
				}

				case 7: {

					if (res1 != -1) {
						if (m.type == 1) kruskal(m);
						else cout << "Kruskal chi hoat dong tren ma tran ke co trong so.\n";
					}
					else {
						cout << "Do thi khong lien thong nen khong the dung thuat toan ! \n";
					}
				}

					  break;


				case 8: {

					if (res1 != -1) {
						int v;
						cout << "Nhap dinh bat dau : ";
						cin >> v;
						v--;
						if (existVertex(m, v)) {
							if (m.type == 1) prim(m, v); // chọn start = 0
							else cout << "Prim chi hoat dong tren ma tran ke co trong so.\n";
						}
						else {
							cout << "Dinh khong ton tai !\n";
						}


					}

					break;
				}

				case 9: {

					int s, t;
					cout << "Nhap dinh bat dau: ";
					cin >> s;
					s--;

					cout << "Nhap dinh ket thuc (-1 neu muon tinh tat ca): ";
					cin >> t;


					if (t != -1) t--;



					dijkstra(m, s, t);

					break;
				}
				case 10: {

					int s, t;
					cout << "Nhap dinh bat dau: ";
					cin >> s;
					s--;

					cout << "Nhap dinh ket thuc (-1 neu muon tinh tat ca): ";
					cin >> t;
					if (t != -1) t--;

					bellmanFord(m, s, t);


					break;
				}
				case 11:
				{

					int s, t;
					cout << "Nhap dinh bat dau: ";
					cin >> s;
					s--;

					cout << "Nhap dinh ket thuc (-1 neu muon tinh tat ca): ";
					cin >> t;
					if (t != -1) t--;

					floydWarshall(m, s, t);


					break;
				}

					  }

				default:
					cout << "Chuc nang khong ton tai \n";
					break;
				}
				output(m);
				res1 = isGraph(m);
				if (res1 != -1) {
					cout << "So canh cua do thi hien tai : " << res1 << "\n";
				}

				// gọi hàm đếm thành phần liên thông (thay cho cntTPLT)
				res1 = countConnected(m);

				cout << "Tiep tuc ( bam 1 )/ ket thuc ( bam 0 ) : ";
				cin >> c1;
			} while (c1 == 1);




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

			break;
		}
		default:
			cout << "chuc nang khong ton tai !!!! \n";
			break;
		}


		cout << "tiep tuc su dung bam 1/ ket thuc bam 0: ";
		cin >> c2;
		system("cls");
	} while (c2 == 1);



	return 0;
}
