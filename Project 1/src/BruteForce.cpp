#include <bits/stdc++.h>

using namespace std::chrono; 
using namespace std;

typedef long long ll;

string S, P;

void brute_force(){
	ll found = 0;
	ll n = S.length();
	ll m = P.length();
	for(ll i = 0; i < n-m+1; i++){
		for(ll j = 0; j < m; j++){
			if(S[i+j] != P[j]) break;
			if(j == m-1){
				cout << "Found at index " << i << endl;
				found++;
			} 
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
	
	cout << endl;

	auto start = high_resolution_clock::now(); 
	brute_force();
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<microseconds>(stop - start); 
	cout << "Used time: " << duration.count()/(double)1e6 << " seconds";

	return 0;
}
