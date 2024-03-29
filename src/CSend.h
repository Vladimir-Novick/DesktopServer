#ifndef _CSEND_H
#define _CSEND_H


#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#define ICMP_ECHO 8
#define ICMP_ECHOREPLY 0

#define ICMP_MIN 8 // minimum 8 byte icmp packet (just header)

/* The IP header */
typedef struct iphdr {
	unsigned int h_len:4;          // length of the header
	unsigned int version:4;        // Version of IP
	unsigned char tos;             // Type of service
	unsigned short total_len;      // total length of the packet
	unsigned short ident;          // unique identifier
	unsigned short frag_and_flags; // flags
	unsigned char  ttl; 
	unsigned char proto;           // protocol (TCP, UDP etc)
	unsigned short checksum;       // IP checksum

	unsigned int sourceIP;
	unsigned int destIP;

}IpHeader;


typedef struct _ihdr {
  BYTE i_type;
  BYTE i_code; 
  USHORT i_cksum;
  USHORT i_id;
  USHORT i_seq;

  ULONG timestamp;
}IcmpHeader;

#define STATUS_FAILED 0xFFFF
#define DEF_PACKET_SIZE 32
#define MAX_PACKET 128000



#define xmalloc(s) HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(s))
#define xfree(p)   HeapFree (GetProcessHeap(),0,(p))


//
//    SO_BROADCAST
//

class CCSend {
public:
	CCSend();
	int deltaTime;
   DWORD SendEcho(char *argv1,  int argv2,int timeout);
   VOID decode_resp(char *buf, int bytes,struct sockaddr_in *from);
   USHORT checksum(USHORT *buffer, int size) ;
   VOID fill_icmp_data(char * icmp_data, int datasize);
long g_seg_no;
long time_max;
long time_min;

};
#endif