#include <iostream>
#include <locale.h>
#include <chrono>
#include <time.h>
#include <windows.h>
#include<fstream>
using namespace std;
int N; // Liczebnosc zbioru.
float czas;
void bubble(int i,int j,int d[])
{
    ofstream zapis;
    zapis.open("wynikbabelkowy.txt", ios::in | ios::out | ios::app );// tworzy i otwiera plik
    double roznica=0;
    cout.setf(ios::fixed); //notacja zwykla
    cout.precision(6); //liczba miejsc po przecinku, dokladnosc naszego wyniku
    clock_t start, koniec; //inicjacja zmiennych zegarowych
    start=clock(); //zapisanie czasu od ktorego zaczelismy
    for(j = 0; j < N - 1; j++)
        for(i = 0; i < N - 1; i++)
        if(d[i] > d[i + 1]) swap(d[i], d[i + 1]);

    koniec=clock();//zapisanie czasu na którym skonczylismy
    roznica=(koniec-start)/(double)CLOCKS_PER_SEC;//obliczenie roznicy, czyli czasu wykonania sie algorytmu
    cout<<"Czas wykonania sortowania babelkowego dla: "<<N<<" elementow. Wynosi: "<<roznica<<" sekund."<<endl;
    //mozliwosc wypisania posortowanej tablicy:
    for (i = 0; i < N; i++)
    { // wypisanie posortowanej tablicy
        cout << "tablica[" << i << "] = " << d[i] << endl;
        zapis<<"tablica[" << i << "] =" << d[i]<< endl;
    }
    zapis.close();

}
void counting(int A[], int B[], int k, int rozmiar)
{

int i;
int *C = new int [k+1]; // utworzenie tablicy na statystyki; wszystkie liczby w tablicy sa nie wieksze od k, a C[i] okresla ile razy wystapila liczb i
for (i = 0; i <= k; i++) // zerowanie tablicy pomocniczej
C[i] = 0;
for (i = 0; i < rozmiar; i++)
C[(A[i])]++;
// C[i] zawiera teraz liczbe wystapien liczby i w ciagu wejsciowym
for (i = 1; i <= k; i++)
C[i] += C[i-1];
// C[i] zawiera teraz liczbe elementow mniejszych lub rownych i
for (i = rozmiar-1; i >= 0; i--)
{
B[(C[(A[i])])-1] = A[i]; // wpisanie do tablicy wynikowej pod okreslony indeks A[i]
C[(A[i])]--; // zmniejszenie indeksu C[i] - odejmujemy wpisana przed chwila liczbe
}

delete [] C; //usuwamy tablice C
}
int max_liczba(int tablica[], int rozmiar)
{
int max = tablica[0];
for (int i = 1; i < rozmiar; i++)
{
if (max < tablica[i])
max = tablica[i];
}
return max;
}
int pseudolosowe(int N,int tablica_wejsciowa1[])
{
    ofstream pliklos;
    pliklos.open("losowe.txt", ios::in | ios::out | ios::app );// tworzy i otwiera plik
    for(int i = 0; i < N; i++)
        {
        tablica_wejsciowa1[i]=rand() % 100000;//wylosowanie liczb do tablicy z zakresu 0-99999
        pliklos<<tablica_wejsciowa1[i]<<" ";

        }
        pliklos.close();
}
int main()
{


    cout<<"Podaj ilosc elementow do losowania ";
    cin>>N;
    //Babelkowy
    int i,j;
    int tablica_wejsciowa1[N];
    pseudolosowe(N,tablica_wejsciowa1);//wywolanie funkcji losujacej
    bubble(i,j,tablica_wejsciowa1);//wywolanie
    delete [] tablica_wejsciowa1;
    //Zliczanie
    int ilosc_liczb=N;

// utworzenie dwoch dynamiczny tablic
int *tablica_wejsciowa = new int [ilosc_liczb]; // tablica zawierajaca ciag wejsciowy
int *tablica_wyjsciowa = new int [ilosc_liczb]; // tablica zawierajaca posortowany ciag
srand((unsigned)time(NULL));
    pseudolosowe(N,tablica_wejsciowa);//wywolanie funkcji losujacej
double roznica;
cout.setf(ios::fixed); //notacja zwykla
cout.precision(6); //liczba miejsc po przecinku, dokladnosc naszego wyniku
clock_t start, koniec; //inicjacja zmiennych zegarowych
start=clock(); //zapisanie czasu startu mierzenia
int k = max_liczba(tablica_wejsciowa, ilosc_liczb); // wyszukanie najwiekszej liczby w ciagu wejsciowym
    counting(tablica_wejsciowa,tablica_wyjsciowa, k, ilosc_liczb); // wywolanie funkcji sortujacej
koniec=clock();//zapisanie konca mierzenia
roznica=(koniec-start)/(double)CLOCKS_PER_SEC;//obliczenie roznicy, czyli czasu wykonania
cout<<endl;
cout<<"Czas wykonania sortowania przez zliczanie dla: "<<N<<" elementow. Wynosi: "<<roznica<<" sekund."<<endl;
//mozliwosc wypisania posortowanej tablicy
    ofstream plik;
    plik.open("wynikzliczanie.txt", ios::in | ios::out | ios::app );// tworzy i otwiera plik
for (i = 0; i < ilosc_liczb; i++)
    { // wypisanie posortowanej tablicy
        cout << "tablica[" << i << "] = " << tablica_wyjsciowa[i] << endl;
        plik<<"tablica[" << i << "] = " << tablica_wyjsciowa[i] << endl;
    }

    plik.close();
// zwolnienie tablic
delete [] tablica_wejsciowa;
delete [] tablica_wyjsciowa;

    return 0;
}
