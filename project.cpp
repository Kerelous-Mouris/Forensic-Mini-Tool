#include <iostream>
#include </usr/include/x86_64-linux-gnu/sys/stat.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include <pcap.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <fstream>
using namespace std;

void findINodeNumber();
void findFileWithInode();
void makeImage();
void print_packet_info(const u_char *packet, struct pcap_pkthdr packet_header);
void caturePackets();


void my_packet_handler(
    u_char *args,
    const struct pcap_pkthdr *header,
    const u_char *packet
);

int main(){

    bool notFinished = true;
    int option;
    string c;
    while(notFinished){
        cout<<"Options Available to be done: "<<endl;
        cout<<"\t 1.Get the INode number of a file"<<endl;
        cout<<"\t 2.find a file with INode number"<<endl;
        cout<<"\t 3.save a bit-by-bit image of a drive"<<endl;
        cout<<"\t 4.capture packets of your network device"<<endl;
        cout<<"\t 5.exit"<<endl;
        cout<<"please choose which option to proceed: ";

        cin >> option;
        switch(option){
            case 1:
            findINodeNumber();
            break;
            case 2:
            findFileWithInode();
            break;
            case 3:
            makeImage();
            break;
            case 4:
            caturePackets();
            break;
            case 5:
            notFinished = false;
            cout << "Thanks for using the program"<<endl;
            continue;
            break;
            default:
            cout << "Invalid Option, please choose a valid option..."<<endl;
            break;        
        }

        cout << "Do you want to do any other tasks ? [y/n] ";
        cin >> c;
        if(c == "y" || c=="Y" || c =="yes" || c == "YES" || c == "Yes"){
            continue;
        }
        else{
            cout << "Thanks for using the program"<<endl;
            notFinished = false; 
        }

    }
    return 0;
}

void findFileWithInode(){
    char x[255];

    cout << "Please enter the INode number to get the file: ";
    
    cin >> x;
    
    char cmd[255];
    strcpy(cmd,"find -inum ");
    strcat(cmd,x);
    system(cmd);
}

void findINodeNumber(){
    char fname[255];
	std::cout << "Enter absolute path for your file : ";                 //eg: /home/student/g1q4.cpp
	std::cin >> fname;
	struct stat var;                             //a variable that can store the stat information if the file we provide.
	int ret = stat(fname, &var);                        //call the fuction stat for file name �fname� and store the values in �var�.

	if (ret < 0)
	{
		std::cout << "Invalid path plaese try again..." << std::endl;
	}
	else
	{
		std::cout << "Device id : " << var.st_dev << std::endl;
		std::cout << "Inode number : " << var.st_ino << std::endl;
		std::cout << "Mode: " << var.st_mode << std::endl;
		std::cout << "UID: " << var.st_uid << std::endl;
		std::cout << "GID: " << var.st_gid << std::endl;
		std::cout << "Size: " << var.st_size << std::endl;
	}

	//you can get this structure by $man fstat (trick, not to be used in exams)
	struct stat
	{
		dev_t     st_dev;     /* ID of device containing file */
		ino_t     st_ino;     /* inode number */
		off_t     st_size;    /* total size, in bytes */
		unsigned short    st_mode;    /* protection */
		short   st_nlink;   /* number of hard links */
		short     st_uid;     /* user ID of owner */
		short     st_gid;     /* group ID of owner */
	};
}



void makeImage(){
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
}


void caturePackets(){

    char *device;
    char error_buffer[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    int timeout_limit = 10; /* In milliseconds */
    pcap_if_t *interfaces;
    if(pcap_findalldevs(&interfaces,error_buffer)==-1)
    {
        cout << "error in pcap findall devs" << endl;
    }    

    device = interfaces->name;
    if (device == NULL) {
        char errormsg[255];
        strcpy(errormsg,"Error finding device: ");
        strcat(errormsg,error_buffer);
        cout <<  errormsg << endl;
    }

    /* Open device for live capture */
    handle = pcap_open_live(
            device,
            BUFSIZ,
            0,
            timeout_limit,
            error_buffer
        );
    if (handle == NULL) {
        char errormsg2[255];
        // strcpy(errormsg2,stderr)
        strcpy(errormsg2,"Error finding device: ");
        strcat(errormsg2,device);
        strcat(errormsg2,error_buffer);
        cout <<  errormsg2 << endl;
     }
     
    pcap_loop(handle, 20, my_packet_handler, NULL);

    pcap_breakloop(handle);
    
    
}

void my_packet_handler(
    u_char *args,
    const struct pcap_pkthdr *packet_header,
    const u_char *packet_body
)
{
    print_packet_info(packet_body, *packet_header);
}

void print_packet_info(const u_char *packet, struct pcap_pkthdr packet_header) {
        cout << "Packet capture length: " <<  packet_header.caplen << endl;
        cout << "Packet total length " << packet_header.len << endl;
        
}