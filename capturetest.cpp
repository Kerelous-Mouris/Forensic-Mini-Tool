#include <stdio.h>
#include <time.h>
#include <pcap.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

void my_packet_handler(
    u_char *args,
    const struct pcap_pkthdr *header,
    const u_char *packet
);
void print_packet_info(const u_char *packet, struct pcap_pkthdr packet_header);


int main(int argc, char *argv[]) {
    char *device;
    char error_buffer[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    int timeout_limit = 10000; /* In milliseconds */
    pcap_if_t *interfaces;
    if(pcap_findalldevs(&interfaces,error_buffer)==-1)
    {
        cout << "error in pcap findall devs" << endl;
        return -1;   
    }    

    device = interfaces->name;
    if (device == NULL) {
        char errormsg[255];
        strcpy(errormsg,"Error finding device: ");
        strcat(errormsg,error_buffer);
        cout <<  errormsg << endl;
        return 1;
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
        return 2;
     }
     
    pcap_loop(handle, 0, my_packet_handler, NULL);

    return 0;
}

void my_packet_handler(
    u_char *args,
    const struct pcap_pkthdr *packet_header,
    const u_char *packet_body
)
{
    print_packet_info(packet_body, *packet_header);
    return;
}

void print_packet_info(const u_char *packet, struct pcap_pkthdr packet_header) {
        cout << "Packet capture length: " <<  packet_header.caplen << endl;
        cout << "Packet total length " << packet_header.len << endl;
        
}