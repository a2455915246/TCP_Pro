// TCPClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <stdio.h>
#include <WINSOCK2.H>

#define BUF_SIZE 1024
int main(int argc, char* argv[])
{
	WSADATA wsd;		//�����׽��ֵİ汾��Ϣ
	SOCKET sClient;		//�ͻ����׽���
	int iRetVal;		//����ֵ
	char buf[BUF_SIZE];	//���ݻ�����
	//��ʼ���׽��ֶ�̬�⣬������1.1�汾
	if (WSAStartup(MAKEWORD(1,1),&wsd)!=0)
	{
		cout<<"��ʼ���׽��ֶ�̬��ʧ��"<<endl;
		return -1;
	}
	if (LOBYTE(wsd.wVersion)!=1||HIBYTE(wsd.wVersion)!=1)
	{
		WSACleanup();
		return -1;
	}
	//�����׽���
	sClient=socket(AF_INET,SOCK_STREAM,0);
	if (INVALID_SOCKET==sClient)
	{
		cout<<"�����׽���ʧ��"<<endl;
		WSACleanup();
		return -1;
	}
	cout<<"�ͻ�������..."<<endl;

	//�������׽��ֵ�ַ
	SOCKADDR_IN addrServ;		//��������ַ�ṹ
	addrServ.sin_family=AF_INET;
	addrServ.sin_port=htons(6666);
	addrServ.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");	//��������ַ

	//���������������
	iRetVal=connect(sClient,(SOCKADDR *)&addrServ,sizeof(SOCKADDR));
	if (SOCKET_ERROR==iRetVal)
	{
		cout<<"����������ʧ��"<<endl;
		closesocket(sClient);
		WSACleanup();
		return -1;
	}
	cout<<"���ӷ������ɹ�..."<<endl;
	//���������������
	iRetVal=send(sClient,"Client",strlen("Client")+1,0);
	if (SOCKET_ERROR==iRetVal)
	{
		cout<<"���ݷ���ʧ��"<<endl;
		closesocket(sClient);
		WSACleanup();
		return -1;
	}
	//���շ������ش�����
	iRetVal=recv(sClient,buf,BUF_SIZE,0);
	if (SOCKET_ERROR==iRetVal)
	{
		cout<<"��������ʧ��"<<endl;
		closesocket(sClient);
		WSACleanup();
		return -1;
	}
	cout<<buf<<endl;
	closesocket(sClient);
	WSACleanup();
	return 0;
}
