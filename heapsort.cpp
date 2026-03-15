#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

long long porownania = 0;
long long zamiany = 0;

void heapify(vector<int>& arr, int n, int i) {
    int smallest = i; 
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l<n){
    	porownania++;
    	if (arr[l] < arr[smallest]){
    		smallest = l;
		}
	}
    if (r<n){
    	porownania++;
    	if (arr[r] < arr[smallest]){
    		smallest = r;
		}
	}
    if (smallest != i){
    	swap(arr[i], arr[smallest]);
    	zamiany++;
    	heapify(arr, n, smallest);
    }
}

void heapSort(vector<int>& arr) {
	int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(arr, n, i);
    }
        
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        zamiany++;
        heapify(arr, i, 0);
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
    heapSort(dane);
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
    heapSort(data);
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

