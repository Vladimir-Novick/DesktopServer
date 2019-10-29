#pragma pack(4)
#include "stdafx.h"
#include "CSend.h"

DWORD CCSend::SendEcho(char *argv1, int argv2,int timeout){


/*  WSADATA wsaData;
  	int bwrote;
  SOCKET sockRaw;
  struct sockaddr_in dest,from;
  struct hostent * hp;
  int bread,datasize;
  int fromlen = sizeof(from);
  char *dest_ip;
  char *icmp_data;
  char *recvbuf;
  unsigned int addr=0;

  USHORT seq_no = 0;

  icmp_data = NULL;
  recvbuf = NULL;
  deltaTime = -1;

  if (WSAStartup(MAKEWORD(2,1),&wsaData) != 0){
	return GetLastError();
  }


  sockRaw = WSASocket (AF_INET,
					   SOCK_RAW,
					   IPPROTO_ICMP,
					   NULL, 0,0);
  
  if (sockRaw == INVALID_SOCKET) {
	return WSAGetLastError();
  }
  bread = setsockopt(sockRaw,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,
  					sizeof(timeout));
  if(bread == SOCKET_ERROR) {
	return WSAGetLastError();
  }
  bread = setsockopt(sockRaw,SOL_SOCKET,SO_SNDTIMEO,(char*)&timeout,
  					sizeof(timeout));
  if(bread == SOCKET_ERROR) {
	return WSAGetLastError();
  }
  memset(&dest,0,sizeof(dest));

  hp = gethostbyname(argv1);

  if (!hp){
	addr = inet_addr(argv1);
  }
  if ((!hp)  && (addr == INADDR_NONE) ) {
	return (DWORD) -1; // Unable to resolve 
  }

  if (hp != NULL)
	  memcpy(&(dest.sin_addr),hp->h_addr,hp->h_length);
  else
  	dest.sin_addr.s_addr = addr;

  if (hp)
	  dest.sin_family = hp->h_addrtype;
  else
	  dest.sin_family = AF_INET;

  dest_ip = inet_ntoa(dest.sin_addr);

	datasize = argv2;
	if (datasize == 0)
	  datasize = DEF_PACKET_SIZE;

	
  datasize += sizeof(IcmpHeader);  

  icmp_data = (char *)xmalloc(MAX_PACKET);
  recvbuf = (char *)xmalloc(MAX_PACKET);

  if (!icmp_data) {
	  return GetLastError();
  }
  

  memset(icmp_data,0,MAX_PACKET);
  fill_icmp_data(icmp_data,datasize);


	
	((IcmpHeader*)icmp_data)->i_cksum = 0;
	((IcmpHeader*)icmp_data)->timestamp = GetTickCount();

	g_seg_no++;
	((IcmpHeader*)icmp_data)->i_seq = g_seg_no;
	((IcmpHeader*)icmp_data)->i_cksum = checksum((USHORT*)icmp_data, 
											datasize);

	bwrote = sendto(sockRaw,icmp_data,datasize,0,(struct sockaddr*)&dest,
					sizeof(dest));
	if (bwrote == SOCKET_ERROR){
	  if (WSAGetLastError() == WSAETIMEDOUT) {
		xfree(icmp_data);
		xfree(recvbuf);
		return -1; // timed out 
	  }
	xfree(icmp_data);
	xfree(recvbuf);	  return WSAGetLastError(); //  sendto failed: 
	}
	if (bwrote < datasize ) {
	xfree(icmp_data);
	xfree(recvbuf);
		return -2; // Wrote %d bytes 
	}
	bread = recvfrom(sockRaw,recvbuf,MAX_PACKET,0,(struct sockaddr*)&from,
				 &fromlen);
	if (bread == SOCKET_ERROR){
	  if (WSAGetLastError() == WSAETIMEDOUT) {
	xfree(icmp_data);
	xfree(recvbuf);
		return WSAGetLastError(); // WSAETIMEDOUT
	  }
	  xfree(icmp_data);
	  xfree(recvbuf);
	  return WSAGetLastError();
	}
	decode_resp(recvbuf,bread,&from);

	xfree(icmp_data);
	xfree(recvbuf);
*/
  return 0;

}

VOID CCSend::decode_resp(char *buf, int bytes,struct sockaddr_in *from) {
	long d;

	IpHeader *iphdr;
	IcmpHeader *icmphdr;
	unsigned short iphdrlen;

	iphdr = (IpHeader *)buf;

	iphdrlen = iphdr->h_len * 4 ; // number of 32-bit words *4 = bytes

	if (bytes  < iphdrlen + ICMP_MIN) {
//		printf("\n Too few bytes from %s \n",inet_ntoa(from->sin_addr));
	}

	icmphdr = (IcmpHeader*)(buf + iphdrlen);

	if (icmphdr->i_type != ICMP_ECHOREPLY) {
//		fprintf(stderr,"\n non-echo type %d recvd \n",icmphdr->i_type);
		return;
	}
	if (icmphdr->i_id != (USHORT)GetCurrentProcessId()) {
//		fprintf(stderr,"\n someone else's packet! \n");
		return ;
	}
//	printf("%d b. from %s: ",bytes, inet_ntoa(from->sin_addr));
//	printf(" seq = %d. ",icmphdr->i_seq);
	d = GetTickCount()-icmphdr->timestamp;
	if (d > time_max ) { time_max = d; };
	if (d < time_min ) { time_min = d; };
//	printf(" time: %d ms min:%d max:%d",d,time_min,time_max);
//	printf("   \r");
	deltaTime = d;
		
}


USHORT CCSend::checksum(USHORT *buffer, int size) {

  unsigned long cksum=0;

  while(size >1) {
	cksum+=*buffer++;
	size -=sizeof(USHORT);
  }
  
  if(size ) {
	cksum += *(UCHAR*)buffer;
  }

  cksum = (cksum >> 16) + (cksum & 0xffff);
  cksum += (cksum >>16);
  return (USHORT)(~cksum);
}


VOID CCSend::fill_icmp_data(char * icmp_data, int datasize){

  IcmpHeader *icmp_hdr;
  char *datapart;

  icmp_hdr = (IcmpHeader*)icmp_data;

  icmp_hdr->i_type = ICMP_ECHO;
  icmp_hdr->i_code = 0;
  icmp_hdr->i_id = (USHORT)GetCurrentProcessId();
  icmp_hdr->i_cksum = 0;
  icmp_hdr->i_seq = 0;
  
  datapart = icmp_data + sizeof(IcmpHeader);

  memset(datapart,'E', datasize - sizeof(IcmpHeader));

}


CCSend::CCSend()
{
 
 g_seg_no = 0;
 time_max = 0;
 time_min = 99999999;
}
