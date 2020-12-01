#include <bits/stdc++.h>
#include "pBar.cpp"

using namespace std;
using namespace std::chrono;

#define fi first
#define se second
#define pb push_back

typedef pair<int, int> pi;

const int MAX_N = 2000000; 
int n, m, h, k;
int hospital[MAX_N];
vector<pi> d[MAX_N];
vector<int> G[MAX_N];
const int INF = 99999999;

void bfs_util(int idx){
	queue<int> que;

	que.push(hospital[idx]);
	d[hospital[idx]].pb({0, hospital[idx]});

	while(!que.empty()){
		int v = que.front(); que.pop();
		for(int i = 0; i < (int)G[v].size(); i++){
			int to = G[v][i];
			if((int)d[to].size() <= idx){
				que.push(to);
				d[to].pb({d[v][idx].fi + 1, hospital[idx]});
			}
		}
	}
	
	for(int i = 0; i < n; i++){
		if((int)d[i].size() <= idx){
			d[i].pb({INF, hospital[idx]});
		}
	}
	
}

void bfs(){
	for(int i = 0; i < h; i++){
		bfs_util(i);
	}
	
	for(int i = 0; i < n; i++){
		sort(d[i].begin(), d[i].end());
	}
}

int main(int argc, char** argv){
	//ios_base::sync_with_stdio(false); 
	//cin.tie(0); cout.tie(0);
	
	string hospital_file, graph_file, output_file;
	
	cout << "Please make sure the following input filename is correct...\n";
	cout << "Graph filename [Example: roadNet-TX.txt]: "; cin >> graph_file;
	cout << "Hospital filename [Example: hospital.txt]: "; cin >> hospital_file;
	cout << "Output filename [Example: output.txt]: "; cin >> output_file; 
	
	cout << "Insert the value of k: ";
	cin >> k;
	
	cout << "File read start...\n";
	ifstream file;
	file.open (hospital_file);
	file >> h;
	for(int i = 0; i < h; i++) file >> hospital[i];
	file.close();
	
	file.open (graph_file);
	string line, dummy;
	getline(file, line);
	getline(file, line);
	getline(file, line);
	std::istringstream iss(line);
	iss >> dummy >> dummy >> n >> dummy >> m;
	getline(file, line);
	
	pBar bar2;
	int count2 = 1;
	for(int i = 0; i < m; i++){
		getline(file, line);
		std::istringstream iss(line);
		
		if(100*i/(m-1) >= count2){
			count2++;
			bar2.update(1);	
			bar2.print();
		}
		
		int from, to;
		iss >> from >> to;
		G[from].pb(to);
		G[to].pb(from);
	}
	file.close();
	cout << "\nFile read finished.\n";
	cout << "Nodes: " << n << endl;
	cout << "Edges: " << m << endl;
	
	
	cout << "\nFinding hospital...\n";
	auto start = high_resolution_clock::now(); 
	bfs();
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<microseconds>(stop - start); 
	cout << "Used time: " << duration.count()/(double)1e6 << " seconds\n\n";
	
	
	cout << "File write start...\n";
	const char *array = output_file.c_str();
	FILE* f = fopen(array, "w");
	int count = 1;
	pBar bar;
	for(int i = 0; i < n; i++){
		//if(i%10000==0) cout << i << endl;
		if(100*i/(n-1) >= count){
			count++;
			bar.update(1);	
			bar.print();
		}
		fprintf(f, "--------------------------------------------------------------\n");
		fprintf(f, "Vertex %d\n", i);
		for(int j = 0; j < k; j++){
			fprintf(f, "%d-th hospital", j+1);

			if((int)d[i].size() <= j || d[i][j].fi == INF) {
				fprintf(f, ": Not exists\n");
				continue;
			}
		
			fprintf(f, ": %d (distance = %d)\n", d[i][j].se, d[i][j].fi);
		}
	}
	fprintf(f, "--------------------------------------------------------------\n");
	fclose(f);
	cout << "\nFile write finished.\n";
	
	
	return 0;
}

