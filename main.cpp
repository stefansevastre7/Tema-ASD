#include <iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
//#define MAX_NUM 100000
#include <chrono>
using namespace std;
using namespace std::chrono;
ifstream f("date.in");
ofstream g("date.in");
ofstream fout("date.out");
void randnum(long long  n, long long maxx)
{
    int random;
    srand(time(NULL));
    for(int i=0; i<n; i++)
    {
        random=rand()% maxx;
        g<<random<<" ";
    }
    g<<endl;
}
long long maxim(long long v[], long long n)
{
    long long maxi=v[1];
    for(long long i=2; i<=n; i++)
        if(v[i]>maxi)
            maxi=v[i];
    return maxi;
}
long long verificare(long long v[], long long n)
{
    for(long long i=1; i<n; i++)
        if(v[i]>v[i+1])
            return 0;

    return 1;
}
void BubbleSort(long long v[], long long n)
{
    for(long long i=1; i<n; i++)
        for(long long j=i+1; j<=n; j++)
            if(v[i]>v[j])
                swap(v[i],v[j]);
}
void CountSort(long long v[],long long x[],long long  n)
{
    long long k=maxim(v,n);
    long long a[k],i,j;

    for( i=0; i<k+1; i++)
        a[i]=0;
    for( j=1; j<=n; j++)
        a[v[j]]++;
    for( i=1; i<=k; i++)
        a[i]+=a[i-1];

    for( j=n; j>=1; j--)
    {
        x[a[v[j]]]=v[j];
        a[v[j]]=a[v[j]]-1;
    }
}
void swapp(long long *a, long long *b)
{
    long long t=*a;
    *a=*b;
    *b=t;
}
long long QuickSort0(long long v[], long long mic, long long mare)
{
    long long pivot=v[mare];
    long long i=mic-1;
    for (long long j=mic; j<=mare-1; j++)
    {
        if(v[j]<pivot)
        {
            i++;
            swapp(&v[i], &v[j]);
        }
    }
    swapp(&v[i+1],&v[mare]);
    return (i+1);
}
void QuickSort(long long v[], long long mic, long long mare)
{
    if (mic<mare)
    {
        long long  pi=QuickSort0(v, mic, mare);

        QuickSort(v, mic, pi-1);
        QuickSort(v, pi+1, mare);
    }
}
void Afisare(long long v[], long long n)
{
    for(long long i=1; i<=n; i++)
        fout<<v[i]<<" ";
    fout<<endl;
}
void MergeSort0(long long v[], long long s, long long m, long long d)
{
    long long i,j,k;
    long long n1=m-s+1;
    long long n2=d-m;
    long long S[n1], D[n2];
    for (i=0; i<n1; i++)
        S[i]=v[s+i];
    for (j=0; j<n2; j++)
        D[j]=v[m+1+j];
    i=0;
    j=0;
    k=s;
    while (i<n1 && j<n2)
    {
        if (S[i]<=D[j])
        {
            v[k]=S[i];
            i++;
        }
        else
        {
            v[k]=D[j];
            j++;
        }
        k++;
    }
    while (i<n1)
    {
        v[k]=S[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        v[k]=D[j];
        j++;
        k++;
    }
}
void MergeSort(long long v[], long long s, long long d)
{
    if (s<d)
    {
        long long m = s+(d-s)/2;

        MergeSort(v, s, m);
        MergeSort(v, m+1, d);

        MergeSort0(v, s, m, d);
    }
}
void RadixSort0(long long v[], long long n, long long exp)
{
    long long output[n];
    long long i, fr[10] = {0};
    for (i=0; i<n; i++)
        fr[(v[i]/exp)%10]++;
    for (i=1; i<10; i++)
        fr[i]+=fr[i-1];
    for (i=n-1; i>=0; i--)
    {
        output[fr[(v[i]/exp)%10]-1]=v[i];
        fr[(v[i]/exp)%10]--;
    }
    for(i=0; i<n; i++)
        v[i]=output[i];
}
void RadixSort(long long v[], long long n)
{
    long long m=maxim(v, n);
    for(long long exp=1; m/exp>0; exp*=10)
        RadixSort0(v,n,exp);
}
long long n,v[1000000],i,a[1000000],b[1000000],c[1000000],d[1000000],e[1000000],maxx,x[1000000];
int main()
{   cout<<"Introdu numarul de numere ce trebuie generate: ";
    cin>>n;
    cout<<"Introdu valoarea maxima ce trebuie generata: ";
    cin>>maxx;
    g<<n<<endl;
    randnum(n, maxx);
    g.close();

    f>>n;
    for(i=1; i<=n; i++)
        f>>v[i];
    for(i=1; i<=n; i++)
    {
        a[i]=v[i];
        b[i]=v[i];
        c[i]=v[i];
        d[i]=v[i];
        e[i]=v[i];
    }
    auto start=high_resolution_clock::now();
    QuickSort(a,1,n);
    Afisare(a,n);
    auto stop=high_resolution_clock::now();
    auto duration=duration_cast<microseconds>(stop-start);
    fout<<"Timp executare Quick Sort: "<<duration.count()<<" microseconds"<<endl;
    if(verificare(a,n)!=0)
        fout<<"Quick Sort sorteaza:)"<<endl<<endl;
    else
        fout<<"Quick Sort nu sorteaza:("<<endl<<endl;


    auto start1=high_resolution_clock::now();
    BubbleSort(b,n);
    Afisare(b,n);
    auto stop1=high_resolution_clock::now();
    auto duration1=duration_cast<microseconds>(stop1-start1);
    fout<<"Timp executare Bubble Sort: "<<duration1.count()<<" microseconds"<<endl;
    if(verificare(b,n)!=0)
        fout<<"Bubble Sort sorteaza:)"<<endl<<endl;
    else
        fout<<"Bubble Sort nu sorteaza:("<<endl<<endl;


    auto start3=high_resolution_clock::now();
    CountSort(d,x,n);
    Afisare(x,n);
    auto stop3=high_resolution_clock::now();
    auto duration3=duration_cast<microseconds>(stop3-start3);
    fout<<"Timp executare Count Sort: "<<duration3.count()<<" microseconds"<<endl;
    if(verificare(x,n)!=0)
        fout<<"Count Sort sorteaza:)"<<endl<<endl;
    else
        fout<<"Count Sort nu sorteaza:("<<endl<<endl;

    auto start4=high_resolution_clock::now();
    MergeSort(e,1,n);
    Afisare(e,n);
    auto stop4=high_resolution_clock::now();
    auto duration4=duration_cast<microseconds>(stop4-start4);
    fout<<"Timp executare Merge Sort: "<<duration4.count()<<" microseconds"<<endl;
    if(verificare(e,n)!=0)
        fout<<"Merge Sort sorteaza:)"<<endl<<endl;
    else
        fout<<"Merge Sort nu sorteaza:("<<endl<<endl;


    auto start2=high_resolution_clock::now();
    RadixSort(c,n+1);
    Afisare(c,n);
    auto stop2=high_resolution_clock::now();
    auto duration2=duration_cast<microseconds>(stop2-start2);
    fout<<"Timp executare Radix Sort: "<<duration2.count()<<" microseconds"<<endl;
    if(verificare(c,n)!=0)
        fout<<"Radix Sort sorteaza:)"<<endl<<endl;
    else
        fout<<"Radix Sort nu sorteaza:("<<endl<<endl;


    return 0;
}
