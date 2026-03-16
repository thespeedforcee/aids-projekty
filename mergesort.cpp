#include <iostream>
#include<vector>
#include<ctime>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;
vector<int> generujLosowe(int n) {
    vector<int> v(n);
    for(int i = 0; i < n; i++) v[i] = rand() % 100000;
    return v;
}

vector<int> generujRosnace(int n) {
    vector<int> v = generujLosowe(n);
    sort(v.begin(), v.end()); 
    return v;
}

vector<int> generujMalejace(int n) {
    vector<int> v = generujLosowe(n);
    sort(v.rbegin(), v.rend()); 
    return v;
}

vector<int> generujA_ksztaltne(int n) {
    vector<int> v = generujRosnace(n);
    vector<int> wynik(n);
    int lewy = 0, prawy = n - 1;
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) { wynik[lewy] = v[i]; lewy++;}
        else{ wynik[prawy] = v[i]; prawy--;}
    }
    return wynik;
}

vector<int> generujV_ksztaltne(int n) {
    vector<int> v = generujMalejace(n);
    vector<int> wynik(n);
    int lewy = 0, prawy = n - 1;
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) {wynik[lewy] = v[i]; lewy++;}
        else{wynik[prawy] = v[i]; prawy--;}
    }
    return wynik;
}

string nazwaTypu(int typ) {
    if(typ == 1) return "Losowe";
    if(typ == 2) return "Rosnace";
    if(typ == 3) return "Malejace";
    if(typ == 4) return "A-ksztaltne";
    if(typ == 5) return "V-ksztaltne";
    return "";
}
void mymerge(vector<int> &v,int left,int mid,int right,int &ilepor)
{
    int rozm_lewa = mid - left + 1;
    int rozm_prawa = right - mid;

    vector<int> leftv(rozm_lewa),rightv(rozm_prawa);
    for(int i=0;i<rozm_lewa;i++)
    {
        leftv[i] = v[left+i];
    }
    for(int i=0;i<rozm_prawa;i++)
    {
        rightv[i] = v[mid + i + 1];
    }
    int i=0,j=0;
    int k=left;

    //sortowanie i scalanie
    while(i<rozm_lewa && j<rozm_prawa)
    {
        ilepor++;
        if(leftv[i]>=rightv[j])
        {
            v[k] = leftv[i];
            i++;
        }
        else{
            v[k] = rightv[j];
            j++;
        }
        k++;
    }
    //jesli zostaly jakies elementy w jednym z wektorow bo mialy nierowne rozmiary
    while(i<rozm_lewa)
    {
        v[k] = leftv[i];
        i++;
        k++;
    }
    while(j<rozm_prawa)
    {
        v[k] = rightv[j];
        j++;
        k++;
    }
}
void mergesort(vector<int> &v,int left,int right,int &ilescalen,int &ilepor)
{
    //jesli tylko jeden element
    if(left>=right)
    {
        return;
    }
    int mid = left + (right-left)/2;
    mergesort(v,left,mid,ilescalen,ilepor);
    mergesort(v,mid+1,right,ilescalen,ilepor);
    ilescalen++;
    mymerge(v,left,mid,right,ilepor);
}
int main()
{
    srand(time(0));
    int tryb;
    cout << "Wybierz tryb pracy programu:" << endl;
    cout << "1. Tryb Demo (Wpisywanie reczne z wypisywaniem na ekran)" << endl;
    cout << "2. Tryb Eksperymentalny (generacja pod wykresy)" << endl;
    cout << "Wybor: ";
    cin >> tryb;
    if(tryb == 1)
    {
        vector<int> v;
        int n,a;
        cout<<"Podaj ilosc elementow: "<<endl;
        cin>>n;
        for(int i=0;i<n;i++)
        {
            cin>>a;
            v.push_back(a);
        }
        cout<<"Ciag przed posortowaniem: "<<endl;
        for(int i=0;i<n;i++)
        {
            cout<<v[i]<<" ";
        }
        cout<<endl;

        int ilescalen = 0,ilepor = 0;
        clock_t start_time = clock();
        mergesort(v,0,v.size()-1,ilescalen,ilepor);
        clock_t end_time = clock();
        double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        cout << endl<<"Czas sortowania: " << fixed << setprecision(6) << seconds << " sekundy" << endl;
        cout<<endl<<"Ciag po posortowaniu: "<<endl;
        
        for(int i=0;i<n;i++)
        {
            cout<<v[i]<<" ";
        }
        cout<<endl<<"liczba porownan: "<<ilepor<<endl<<"liczba scalen: "<<ilescalen<<endl;

    }
    else{
        int wzr_lin[] = {1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
        int wzr_wykl[] = {1000,2000,4000,8000,16000,32000,64000,128000,256000,512000};

        cout<<"Dla wzrostu liniowego: "<<endl;
        cout << "Rozmiar;Typ;Czas[s];Odchylenie" << endl;
        for(int i=0;i<10;i++)
        {
            for(int typ = 1;typ<=5;typ++)
            {
                double czasy[10];
                double suma_czasow = 0;
                
                for(int j=0;j<10;j++)
                {
                    vector<int> v;
                    if(typ==1){v = generujLosowe(wzr_lin[i]);}
                    else if(typ==2){v = generujRosnace(wzr_lin[i]);}
                    else if(typ==3){v = generujMalejace(wzr_lin[i]);}        
                    else if(typ==4){v = generujA_ksztaltne(wzr_lin[i]);}
                    else{v = generujV_ksztaltne(wzr_lin[i]);}

                    int por = 0, scal = 0;
                    
                    clock_t start = clock();
                    mergesort(v,0,v.size()-1,scal,por);
                    clock_t end = clock();

                    double sekundy = (double)(end - start) / CLOCKS_PER_SEC;
                    czasy[j] = sekundy;
                    suma_czasow += sekundy;
                }
                double sredni_czas = suma_czasow / 10.0;
                
                // odchylenie standardowe
                double wariancja = 0;
                for(int p = 0; p < 10; p++) {
                    wariancja += pow(czasy[p] - sredni_czas, 2);
                }
                double odchylenie = sqrt(wariancja / 10.0);
                
                cout << wzr_lin[i] << ";" << nazwaTypu(typ) << ";" << fixed << setprecision(6) << sredni_czas << ";" << odchylenie << endl;
            }
        }

        cout<<"Dla wzrostu wykladniczego: "<<endl;
        cout << "Rozmiar;Typ;Czas[s];Odchylenie" << endl;

        for(int i=0;i<10;i++)
        {
            for(int typ = 1;typ<=5;typ++)
            {
                double czasy[10];
                double suma_czasow = 0;
                
                for(int j=0;j<10;j++)
                {
                    vector<int> v;
                    if(typ==1){v = generujLosowe(wzr_wykl[i]);}
                    else if(typ==2){v = generujRosnace(wzr_wykl[i]);}
                    else if(typ==3){v = generujMalejace(wzr_wykl[i]);}        
                    else if(typ==4){v = generujA_ksztaltne(wzr_wykl[i]);}
                    else{v = generujV_ksztaltne(wzr_wykl[i]);}

                    int por = 0, scal = 0;
                    
                    clock_t start = clock();
                    mergesort(v,0,v.size()-1,scal,por);
                    clock_t end = clock();

                    double sekundy = (double)(end - start) / CLOCKS_PER_SEC;
                    czasy[j] = sekundy;
                    suma_czasow += sekundy;
                }
                double sredni_czas = suma_czasow / 10.0;
                
                // odchylenie standardowe
                double wariancja = 0;
                for(int p = 0; p < 10; p++) {
                    wariancja += pow(czasy[p] - sredni_czas, 2);
                }
                double odchylenie = sqrt(wariancja / 10.0);

                cout << wzr_wykl[i] << ";" << nazwaTypu(typ) << ";" << fixed << setprecision(6) << sredni_czas << ";" << odchylenie << endl;
            }
        }
    }
    
    return 0;

}