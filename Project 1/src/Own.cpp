#include <bits/stdc++.h>

using namespace std::chrono; 
using namespace std;

typedef long long ll;

const ll MAX_P = 1000000;

string S, P;
ll pre[130][MAX_P];
ll lp[MAX_P];

void Own(){
	ll found = 0;
	ll n = S.length();
	ll m = P.length();

	for(ll i = 0; i < 129; i++) pre[i][0] = -1;
	
	for(ll j = 1; j < m; j++){
		for(ll i = 0; i < 129; i++){
			if((int)(P[j-1]) == i) pre[i][j] = j-1;
			else pre[i][j] = pre[i][j-1]; 
		}
	}
	
	lp[0] = 0;
	for(ll i = 1; i < m; i++){
		lp[i] = 0;
		for(ll j = 0; i + j < m; j++){
			if(P[i+j]!=P[j]) break;
			lp[i] = j+1;
		}
	}
	
	ll l = 0, r = 0, j, i = 0;
	while(i < n - m + 1){
		j = 0;
		if(i <= r) j = min(r - i, lp[i-l]);
		while(j < m && S[i+j] == P[j]) j++;
		if(i + j - 1 > r) l = i, r = i + j - 1;
		
		if(j == m){
			cout << "Found at index " << i << endl;
			found++;
			i++;
		}
		else{ //fail matching at P[j]
			i += (j - pre[(int)(S[i + j])][j]); //find P[pre[S[i+j]] to match with S[i+j], if -1, skip S[i+j].
		}

	}
	
	if(!found) cout << "Not found :(\n";
	else cout << "Found " << found << " occurances :)\n";
}

int main(int argc, char** argv){
	//ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	
	P = "", S = ""; 
	
	if ( (argc <= 1) || (argv[argc-1] == NULL) || (argv[argc-1][0] == '-') ) {
		cout << "P: "; cin >> P;
		cout << "S: "; 
    }
    else if(argc > 2){
		cout << "Invalid input! Please key in only one pattern string without space!";
		return 0;
    }
    else{
		P = argv[1];
	}
	
	for(ll i = 0; i < P.length(); i++){
		if(P[i]>='a' && P[i]<='z') P[i] = P[i] -'a' + 'A';
	}
	
	string tem;
	int count = 0;
	while(cin >> tem){
		for(ll i = 0; i < tem.length(); i++){
			if(tem[i]>='a' && tem[i]<='z') tem[i] = tem[i] -'a' + 'A';
		}
		S += tem;
		count++;
		if(count%100000==0) cout << "Reading line #" << count << endl;
	}
	cout << '\n';

	auto start = high_resolution_clock::now(); 
	Own();
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<microseconds>(stop - start); 
	cout << "Used time: " << duration.count()/(double)1e6 << " seconds";

	return 0;
}
