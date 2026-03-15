#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <algorithm>

using namespace std;

long long porownania = 0;
long long zamiany = 0;

int partition(vector<int>& tab, int low, int high, bool demo){
	int pivot = tab[low];
	if (demo) cout << "Pivot: " << pivot << " (zakres " << low << "-" << high << ")" << endl;
	int i = low;
	for (int j = low + 1; j <= high; j++){
		porownania++;
		if (tab[j] >= pivot){
			i++;
			swap(tab[i], tab[j]);
			zamiany++;
		}
	}
	swap(tab[low], tab[i]);
	zamiany++;
	return i;
}

void quicksortiter(vector<int>& tab, int n){
	if (n < 2){
		return;
	}
	bool demo = (n <= 12);
	stack<int> s;
	s.push(0);
	s.push(n-1);
	while (!s.empty()){
		int high = s.top();
		s.pop();
		int low = s.top();
		s.pop();
		int p_index = partition(tab, low, high, demo);
		if (p_index - 1 > low){
			s.push(low);
			s.push(p_index - 1);
		}
		if (p_index + 1 < high){
			s.push(p_index + 1);
			s.push(high);
		}
	}
}

int main() {
	system("chcp 1250");
	srand(time(NULL));

    int n;
    cout << "Podaj liczbe elementow n: ";
    cin >> n;
    
    porownania = 0;
    zamiany = 0;

    vector<int> dane;
    for (int i = 0; i < n; i++) {
        int liczba;
        cout << "Podaj liczbe " << i + 1 << ": ";
        cin >> liczba;
        dane.push_back(liczba);
    }

    cout << "\nPrzed: ";
    for (int x : dane) cout << x << " ";
    cout << endl;

    clock_t start1 = clock();
    quicksortiter(dane, dane.size());
    clock_t stop1 = clock();

    cout << "\nPo: ";
    for (int x : dane) cout << x << " ";
    cout << "\nCzas: " << (double)(stop1 - start1) / CLOCKS_PER_SEC << "s" << endl;
    cout << "\nPorownania: " << porownania << ", zamiany: " << zamiany << endl;
    
    cout << "\nLosowanie tablicy.\n";
    porownania = 0;
    zamiany = 0;

    int k = rand() % 50 + 15; 
    vector<int> data;
    for (int i = 0; i < k; i++) data.push_back(rand() % 1000);

    cout << "Rozmiar: " << k;
    if  (k <= 12){
		cout << "\nwylosowane liczby: \n";
		for (int x : data) cout << x << " ";
    	cout << endl;	
	}
    clock_t start2 = clock();
    quicksortiter(data, data.size());
    clock_t stop2 = clock();
    if  (k <= 12){
		cout << "po sortowaniu: \n";
		for (int x : data) cout << x << " ";
    	cout << endl;	
	}
    cout << "\nCzas: " << (double)(stop2 - start2) / CLOCKS_PER_SEC << "s" << endl;
	cout << "\nPorownania: " << porownania << ", zamiany: " << zamiany << endl;

	return 0;
}

