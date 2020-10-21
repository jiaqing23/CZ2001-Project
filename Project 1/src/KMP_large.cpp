#include <bits/stdc++.h>

using namespace std::chrono; 
using namespace std;

typedef long long ll;

const ll MAX_P = 10000000;

string S, P;
ll f[MAX_P];

vector<ll> found;
ll pos = 0, temj = 0;

void computeFailureFunction(){
	ll m = P.length();	
	f[0] = 0; f[1] = 0;
	for(ll i = 1; i < m; i++){
		ll j = f[i];
		while(j && P[i] != P[j]) j = f[j];
		f[i+1] = (P[i] == P[j]) ? (j+1) : 0;
	}
}

void KMP(){
	ll n = S.length();
	ll m = P.length();

	for(ll i = 0; i < n; i++){
		while(temj && S[i]!=P[temj]) temj = f[temj];
		if(S[i] == P[temj]) temj++;
		if(temj == m){
			found.push_back(i-m+1 + pos);
			temj = f[temj];
		} 
	}
}

double KMP_time(){
	auto start = high_resolution_clock::now(); 
	KMP();
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<microseconds>(stop - start); 
	return duration.count();
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
	
	computeFailureFunction();
	double totaltime = 0;
	
	string tem;
	int count = 0;
	while(cin >> tem){
		for(ll i = 0; i < tem.length(); i++){
			if(tem[i]>='a' && tem[i]<='z') tem[i] = tem[i] -'a' + 'A';
		}
		S += tem;
		count++;
		if(count%100000==0){
			cout << "Reading line #" << count << endl;
			totaltime += KMP_time();
			
			pos += S.length();
			S = "";
		}
	}
	totaltime += KMP_time();
	
	
	cout << '\n';

	
	for(ll i = 0; i < found.size(); i++) cout << "Found at index " << found[i] << endl;
	if(found.size() == 0) cout << "Not found :(\n";
	else cout << "Found " << found.size() << " occurances :)\n";
	cout << "Used time: " << totaltime/(double)1e6 << " seconds";

	return 0;
}
