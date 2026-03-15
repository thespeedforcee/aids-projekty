#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

long long porownania = 0;
long long zamiany = 0;

void shellSortKnuth(vector<int>& arr) {
    int n = arr.size();
    if (n < 2) return;

    int gap = 1;
    while (gap < n / 3) {
        gap = 3 * gap + 1;
    }

    while (gap >= 1) {
        if (n <= 12) {
            cout << "Aktualny przyrost: " << gap << endl;
        }

        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;

            while (j >= gap) {
                porownania++; 
                if (arr[j - gap] < temp) { 
                    arr[j] = arr[j - gap];
                    zamiany++; 
                    j -= gap;
                } else {
                    break; 
                }
            }
            arr[j] = temp;
        }
        gap /= 3;
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
    shellSortKnuth(dane);
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
    shellSortKnuth(data);
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
