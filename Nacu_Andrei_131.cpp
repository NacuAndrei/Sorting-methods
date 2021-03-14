#include <bits/stdc++.h>

using namespace std;

ifstream fin("teste.in");

unsigned long long llrand() /// luata de pe internet
{
    unsigned long long r = 0;
    for (int i = 0; i < 5; ++i)
    {
        r = (r << 15) | (rand() & 0x7FFF);
    }
    return r & 0xFFFFFFFFFFFFFFFFULL;
}
///v[i] == llrand() % Max; vector auxiliar si afisare toate sortarile
void generator(int v[], int n, int Max, int tip)
{
    int i, x=llrand();
    switch (tip)
    {
        case 1:
            for(int i = 0; i < n; i++)
                v[i] = llrand() % (Max + 1);
            break;

        case 2:
            for(int i = 0; i < n; i++)
                v[i] = x;
            break;

         case 3:
            for(int i = 0; i < n; i++)
                v[i] = llrand() % (Max + 1);

            for(int i = 0 ; i < n-1; i++)
                for(int j = i+1; j < n; j++)
                    if(v[i]>v[j] and i % 2 == 0)
                        swap(v[i], v[j]);
            break;

        case 4:
            for(int i = 0; i < n; i++)
                v[i] = llrand() % (Max + 1);

            for(int i = 0 ; i < n-1; i++)
                for(int j = i+1; j < n; j++)
                    if(v[i]<v[j] and i % 2 == 1)
                        swap(v[i], v[j]);
    }
}

void fctSort(int n, int v[])
{
    sort(v, v+n);
}

void BubbleSort (int n, int v[])
{
    if(n >= 100000)
        cout<<"Nu functioneaza, deci nu il execut: ";

    else
        for(int i = 0; i < n-1; i++)
        {
            for(int j = i+1; j < n; j++)
                if(v[i] >= v[j])
                    swap(v[i], v[j]);
        }
}

///O(n log n)
int afisMerge[1000];
void MergeSort(int v[], int st, int dr)
{
    if(dr >= 10000)
        cout<<"Nu functioneaza, deci nu il execut: ";

    else if(st < dr)
    {
        srand (time(NULL));
        int mij = rand() % (dr-st) + st;
        MergeSort(v, st, mij);
        MergeSort(v, mij + 1, dr);

        int i = st, j = mij + 1, k = 0;

        while(i <= mij && j <= dr)
            if(v[i] < v[j])
                afisMerge[++k] = v[i++];
            else
                afisMerge[++k] = v[j++];

        while(i <= mij)
            afisMerge[++k] = v[i++];
        while(j <= dr)
            afisMerge[++k] = v[j++];

        for(i = st, j = 1 ; i <= dr ; i ++, j ++)
            v[i] = afisMerge[j];
    }
}

void QuickSort(int v[], int st, int dr)
{
    if(dr >= 10000)
        cout<<"Nu functioneaza, deci nu il execut: ";

    else if(st < dr)
    {
        srand(time(NULL));
        int mij = rand() % (dr-st) + st;
        int i = st, j = dr, d = 0;
        while(i < j)
        {
            if(v[i] > v[j])
            {
                swap(v[i], v[j]);
                d = 1 - d;
            }
            i += d;
            j -= 1 - d;
        }
        QuickSort(v, st, i - 1);
        QuickSort(v, i + 1, dr);
    }
}

void countSort(int v[], int n, int Max)
{
    int frecv[Max+1], j = 0;
    memset(frecv,0,sizeof(frecv));

    for(int i = 0; i < n; i++)
        frecv[v[i]]++;


    for(int i = 0; i <= Max; i++)
        while(frecv[i] != 0)
        {
            v[j] = i;
            j++;
            frecv[i]--;
        }

}

void countSortRadix(int v[], int n, int exp)
{
    /// exp = 1
    int afis[n], i, frecv[10] = {0};

    for (i = 0; i < n; i++)
        frecv[(v[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        frecv[i] += frecv[i-1];

    for (i = n - 1; i >= 0; i--)
    {
        afis[frecv[(v[i] / exp) % 10] - 1] = v[i];
        frecv[(v[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        v[i] = afis[i];
}

void radixsort(int v[], int n, int Max)
{
    int exp;

    for (exp = 1; Max/exp > 0; exp *= 10)
        countSortRadix(v, n, exp);
}

int TipSortare()
{
    int tip;
    cin>>tip;
    return tip;
}

bool VerifSortare(int n, int v[])
{
    for(int i = 0; i < n-1; i++)
        if(v[i]>v[i+1])
            return 0;       ///Sortare gresita
    return 1;               ///Sortare corecta
}

void SaveVector(int n, int v[], int aux[])
{
    for(int i = 0; i < n; i++)
        aux[i] = v[i];
}

void Raspuns(int T, int n, int Max)
{
    cout<<endl<<"Introduceti numarul de teste T: \n";
    cin>>T;
    for(int i=1; i<=T; i++)
    {
        fin>>n>>Max;
        cout<<endl<<"Pentru testul "<<i<<":\n";
        cout<<"Introduceti numarul de numere N: \n";
        cin>>n;
        cout<<endl<<"Introduceti numarul maxim Max: \n";
        cin>>Max;

        int v[n], aux[n];
        SaveVector(n, v, aux);

        int categorie;
        cout<<"Introduceti cifra corespunzatoare tipului de vector: \n"<<"1.Complet random\n"<<"2.Constant\n"<<"3.Aproape sortat crescator\n"<<"4.Aproape sortat descrescator\n";
        cin>>categorie;
        generator(v, n, Max, 1);
        ///double t = clock();

        cout<<"Functie sort: ";
        double t = clock();
        fctSort(n, v);
        t = clock() - t;
        t = t/CLOCKS_PER_SEC;
        cout<<t<<" secunde\n";
        if (VerifSortare(n, v))
            cout<<"Sortare CORECTA\n";
        else
            cout<<"Sortare GRESITA\n";
        SaveVector(n, v, aux);

        cout<<"\nBubbleSort: ";
        t = clock();
        BubbleSort(n, v);
        t = clock() - t;
        t = t/CLOCKS_PER_SEC;
        cout<<t<<" secunde\n";
        if (VerifSortare(n, v))
            cout<<"Sortare CORECTA\n";
        else
            cout<<"Sortare GRESITA\n";
        SaveVector(n, v, aux);

        cout<<"\nMergeSort: ";
        t = clock();
        MergeSort(v, 0, n);
        t = clock() - t;
        t = t/CLOCKS_PER_SEC;
        cout<<t<<" secunde\n";
        if (VerifSortare(n, v))
            cout<<"Sortare CORECTA\n";
        else
            cout<<"Sortare GRESITA\n";
        SaveVector(n, v, aux);

        cout<<"\nQuickSort: ";
        t = clock();
        QuickSort(v, 0, n);
        t = clock() - t;
        t = t/CLOCKS_PER_SEC;
        cout<<t<<" secunde\n";
        if (VerifSortare(n, v))
            cout<<"Sortare CORECTA\n";
        else
            cout<<"Sortare GRESITA\n";
        SaveVector(n, v, aux);

        cout<<"\nCountingSort: ";
        t = clock();
        countSort(v, n, Max);
        t = clock() - t;
        t = t/CLOCKS_PER_SEC;
        cout<<t<<" secunde\n";
        if (VerifSortare(n, v))
            cout<<"Sortare CORECTA\n";
        else
            cout<<"Sortare GRESITA\n";
        SaveVector(n, v, aux);

        cout<<"\nRadixSort: ";
        t = clock();
        radixsort(v, n, Max);
        t = clock() - t;
        t = t/CLOCKS_PER_SEC;
        cout<<t<<" secunde\n";
        if (VerifSortare(n, v))
            cout<<"Sortare CORECTA\n";
        else
            cout<<"Sortare GRESITA\n";
        SaveVector(n, v, aux);
    }
}

int main()
{

    int T, n, Max;
    Raspuns(T, n, Max);
    return 0;
}
