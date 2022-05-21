#include<iostream>
#include </usr/include/x86_64-linux-gnu/sys/stat.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
int main()
{

    char sPath[255];
    char dPath[255];

    cout << "Please enter the source file path: ";
    
    cin >> sPath;

    cout << "Please enter the destination file path wth .img extension: ";
    
    cin >> dPath;

    char pass[60];

    cout << "Please enter your sudo password: ";

    cin >> pass;




    char cmd[255];
    char sudo[255];
    char temp[255];
    strcpy(cmd,"dd if=");
    strcat(cmd,sPath);
    strcat(cmd," of=");
    strcat(cmd,dPath);
    strcat(cmd," bs=1k conv=noerror");

    strcpy(temp,"echo ");
    strcat(temp,pass);
    strcat(temp," | sudo -S ");

    strcpy(sudo,temp);
    strcat(sudo,cmd);
    system(sudo);


    system("clear");

    cout << "image created successfully..." << endl;

    char output[255];
    strcpy(output,"fdisk -l ");
    strcat(output,dPath);
    system(output);


    return 0;
}