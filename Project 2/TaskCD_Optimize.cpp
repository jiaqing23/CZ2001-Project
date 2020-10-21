#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back

typedef pair<int, int> pi;

const int MAX_N = 1111111;
int n, m, h, k;
int hospital[MAX_N];
vector<int> G[MAX_N];
vector<pi> hospt_dist[MAX_N], pre[MAX_N]; //(hospital, distance), (pre, # of pre's hospital)
set<int> hospt[MAX_N];

struct bfsElm{
	int v, hospt, dist, hospt_rank;
};

void bfs(){
	queue<bfsElm> que;
	for(int i = 0; i < h; i++){
		que.push({hospital[i], hospital[i], 0, 0});
		hospt_dist[hospital[i]].pb({hospital[i], 0});
		hospt[hospital[i]].insert(hospital[i]);
		pre[hospital[i]].pb({-1, -1});
	}
	
	while(!que.empty()){
		bfsElm now = que.front(); que.pop();
		
		for(int i = 0; i < (int)G[now.v].size(); i++){
			int to = G[now.v][i];
			if((int)hospt_dist[to].size() < k){
				if(hospt[to].count(now.hospt)) continue;
				que.push({to, now.hospt, now.dist+1, (int)hospt_dist[to].size()});
				hospt_dist[to].pb({now.hospt, now.dist+1});
				hospt[to].insert(now.hospt);
				pre[to].pb({now.v, now.hospt_rank});
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	
	cin >> h;
	for(int i = 0; i < h; i++) cin >> hospital[i];
	
	cin >> n >> m >> k;
	for(int i = 0; i < m; i++){
		int from, to;
		cin >> from >> to;
		G[from].pb(to);
		G[to].pb(from);
	}
	
	bfs();
	
	
	for(int i = 0; i < n; i++){
		cout << "Vertex " << i << "\n";
		for(int j = 0; j < k; j++){
			cout << j+1 << "-th hospital";
			pi now = {i, j}; 
			
			if((int)pre[i].size() < j + 1) {
				cout << ": Not exists\n";
				continue;
			}
			
			cout << " (dist=" << hospt_dist[i][j].se << "): ";
			while(now.fi != -1){
				cout << now.fi << "-\n"[pre[now.fi][now.se].fi==-1];
				now = pre[now.fi][now.se];
			}
		}
		cout << endl;
	}
	
	return 0;
}

/*
3
5 8 10
12 12 5
0 1 1 2 1 5 1 3 4 2 6 2 4 6 6 8 6 9 6 10 7 3 7 10
*/
