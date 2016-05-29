// TCPServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream.h"
#include "stdio.h"
#include "WINSOCK2.H"

#define BUF_SIZE 1024

int main(int argc, char* argv[])
{
	WSADATA wsd;		//WSADATA�����������׽��ֿ�ð汾��Ϣ
	SOCKET sServer;		//�������׽���
	int iRetVal;		//����ֵ
	char buf[BUF_SIZE];

	//��ʼ���׽��ֶ�̬�⣬MAKEWORD�귵��һ��DWORD�ͱ�����ָ���汾��
	//���óɹ���wsd�ṹ���wVersion��Ա���������а汾��Ϣ
	if (WSAStartup(MAKEWORD(1,1),&wsd)!=0)
	{
		cout<<"��ʼ���׽��ֶ�̬��ʧ��"<<endl;
		return -1;
	}
	//�жϰ汾�Ƿ���ȷ���أ��������1.1�汾�򷵻�
	if (LOBYTE(wsd.wVersion)!=1||HIBYTE(wsd.wVersion)!=1)
	{
		WSACleanup();		//�����׽�����Դ
		return -1;
	}
	//����socket()���������׽��֣�ע������ʽ�׽���
	sServer=socket(AF_INET,SOCK_STREAM,0);
	if (INVALID_SOCKET==sServer)
	{
		cout<<"�����׽���ʧ��"<<endl;
		WSACleanup();
		return -1;
	}
	//�������׽��ֵ�ַ
	SOCKADDR_IN addrServ;		//��������ַ
	addrServ.sin_family=AF_INET;		//AF_INET������InternetЭ��
	addrServ.sin_port=htons(6666);		//ָ���������˿ڣ�htons()����
	addrServ.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	//���׽���
	iRetVal=bind(sServer,(SOCKADDR *)&addrServ,sizeof(SOCKADDR));
	if (SOCKET_ERROR==iRetVal)
	{
		cout<<"���׽���ʧ��"<<endl;
		closesocket(sServer);		//�ر��׽���
		WSACleanup();				//�ͷ��׽�����Դ
		return -1;
	}
	//����
	iRetVal=listen(sServer,3);
	if (SOCKET_ERROR==iRetVal)
	{
		cout<<"����ʧ��"<<endl;
		WSACleanup();
		return -1;
	}
	cout<<"�������Ѿ��������������ͻ�������"<<endl;
	SOCKADDR_IN addrClient;				//�ͻ��˵�ַ
	int len=sizeof(addrClient);
	//���տͻ�������
	while(1)
	{
		ZeroMemory(buf,BUF_SIZE);
		SOCKET sClient;				//�ͻ����׽���
		//���ܿͻ������󣬽�������
		sClient=accept(sServer,(SOCKADDR *)&sClient,&len);
		if (INVALID_SOCKET==sClient)
		{
			cout<<"���տͻ�������ʧ��"<<endl;
			closesocket(sServer);		//�ر��׽���
			WSACleanup();				//�ͷ��׽�����Դ
			return -1;
		}
		//���տͻ�������
		iRetVal=recv(sClient,buf,BUF_SIZE,0);
		if (SOCKET_ERROR==iRetVal)
		{
			cout<<"��������ʧ��"<<endl;
			closesocket(sServer);		//�رշ������׽���
			closesocket(sClient);		//�رտͻ����׽���
			WSACleanup();
			return -1;
		}
		cout<<buf<<endl;				//�������
		//���ͻ��˵�Ӧ������
		char sendBuf[100];
		sprintf(sendBuf,"Welcome %s to Server",inet_ntoa(addrClient.sin_addr));
		send(sClient,sendBuf,strlen(sendBuf)+1,0);
		//�ر��׽�����Դ
		closesocket(sClient);
	}	
		//�˳�
		closesocket(sServer);		//�رշ������׽���
		WSACleanup();				//���winsock dll
	
	
	return 0;
}
