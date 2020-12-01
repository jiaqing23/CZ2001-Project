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
int hospital[MAX_N], visited[MAX_N], pre[MAX_N], d[MAX_N];
vector<int> G[MAX_N];

void bfs(){
	for(int i = 0; i < n+10; i++){
		pre[i] = -100; //initialize
	}
	
	queue<int> que;
	for(int i = 0; i < h; i++){
		que.push(hospital[i]);
		pre[hospital[i]] = -1;
		d[hospital[i]] = 0;
		visited[hospital[i]] = 1;
	}
	
	while(!que.empty()){
		int v = que.front(); que.pop();
		for(int i = 0; i < (int)G[v].size(); i++){
			int to = G[v][i];
			if(!visited[to]){
				que.push(to);
				visited[to] = 1;
				d[to] = d[v] + 1;
				pre[to] = v;
			}
		}
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
		fprintf(f, "Vertex %d:\n", i);
		if(pre[i] == -100) {
			fprintf(f, "Unreachable from any hospital\n");
			continue;
		}
		
		int now = i;
		int tem = now;
		while(now != -1){
			if(pre[now]==-1) fprintf(f, "%d\n", now);
			else fprintf(f, "%d -> ", now);
			now = pre[now];
			if(now!=-1) tem = now;
		}
		fprintf(f, "Nearest hospital: %d (distance: %d)\n", tem, d[i]);
	}
	fprintf(f, "--------------------------------------------------------------\n");
	fclose(f);
	cout << "\nFile write finished.\n";
	
	
	return 0;
}

