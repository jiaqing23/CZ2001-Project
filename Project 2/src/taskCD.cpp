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
vector<int> G[MAX_N];
int hospital[MAX_N];
vector<pi> hospt_dist[MAX_N], pre[MAX_N]; //(hospital, distance), (pre, # of pre's hospital)

struct bfsElm{
	int v, hospt, dist, hospt_rank;
};

void bfs(){
	queue<bfsElm> que;
	for(int i = 0; i < h; i++){
		que.push({hospital[i], hospital[i], 0, 0});
		hospt_dist[hospital[i]].pb({hospital[i], 0});
		pre[hospital[i]].pb({-1, -1});
	}
	
	while(!que.empty()){
		bfsElm now = que.front(); que.pop();
		
		for(int i = 0; i < (int)G[now.v].size(); i++){
			int to = G[now.v][i];
			if((int)hospt_dist[to].size() < k){
				int can = 1;
				for(int j = 0; j < (int)hospt_dist[to].size(); j++){
					if(hospt_dist[to][j].fi == now.hospt){
						can = 0;
						break;
					}
				}
				
				if(!can) continue;
				que.push({to, now.hospt, now.dist+1, (int)hospt_dist[to].size()});
				hospt_dist[to].pb({now.hospt, now.dist+1});
				pre[to].pb({now.v, now.hospt_rank});
			}
		}
	}
}

int main(int argc, char** argv){
	//ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	
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
		if(100*i/(n-1) >= count){
			count++;
			bar.update(1);	
			bar.print();
		}
		fprintf(f, "--------------------------------------------------------------\n");
		fprintf(f, "Vertex %d\n", i);
		for(int j = 0; j < k; j++){
			fprintf(f, "%d-th hospital", j+1);
			pi now = {i, j}; 
			
			if((int)pre[i].size() < j + 1) {
				fprintf(f, ": Not exists\n");
				continue;
			}
		
			fprintf(f, " is %d (distance = %d): ", hospt_dist[i][j].fi, hospt_dist[i][j].se);
			while(now.fi != -1){
				if(pre[now.fi][now.se].fi==-1) fprintf(f, "%d\n", now.fi);
				else fprintf(f, "%d -> ", now.fi);
				
				now = pre[now.fi][now.se];
			}
		}
	}
	fprintf(f, "--------------------------------------------------------------\n");
	fclose(f);
	cout << "\nFile write finished.\n";
	
	return 0;
}
