#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back

typedef pair<int, int> pi;

const int MAX_N = 1111111; 
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

int main(){
	//ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	
	cout << "File read start...\n";
	
	ifstream file;
	file.open ("hospital.txt");
	file >> h;
	for(int i = 0; i < h; i++) file >> hospital[i];
	file.close();
	
	file.open ("roadNet-PA.txt");
	file >> n >> m;
	for(int i = 0; i < m; i++){
		int from, to;
		file >> from >> to;
		G[from].pb(to);
		G[to].pb(from);
	}
	file.close();
	
	cout << "File read finished.\n";
	
	bfs();
	
	ofstream output;
	output.open("output.txt");
	for(int i = 0; i < n; i++){
		if(i%10000==0) cout << i << endl;
		output << "Vertex " << i << ": ";
		if(pre[i] == -100) {
			output << "unreachable from any hospital\n";
			continue;
		}
		int now = i;
		while(now != -1){
			output << now << "-\n"[pre[now]==-1];
			now = pre[now];
		}
	}
	output.close();
	
	return 0;
}

