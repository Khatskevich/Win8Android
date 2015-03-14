#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    int n, i, m, len;
    char stri[101];
    cin>>stri;
    for ( i = 0; i < strlen(stri); i++)
    {
        stri[i] = tolower(stri[i]);
        if( stri[i]!='a' && stri[i]!='o' && stri[i]!='y' &&
            stri[i]!='e' && stri[i]!='u' && stri[i]!='i')
            cout<<'.'<<stri[i];
    }
    cout<<endl;
    return 0;
}
