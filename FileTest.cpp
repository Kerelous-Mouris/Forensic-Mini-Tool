#include<iostream>
#include </usr/include/x86_64-linux-gnu/sys/stat.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
int main()
{

    char x[255];

    cout << "Please enter the INode number to get the file: ";
    
    cin >> x;
    
    char cmd[255];
    strcpy(cmd,"find -inum ");
    strcat(cmd,x);
    system(cmd);
    return 0;
}