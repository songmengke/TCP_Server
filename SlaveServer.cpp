#include <stdio.h>
#include <winsock2.h>
#include<windows.h>
#pragma comment (lib,"ws2_32.lib")

void SetStatus(char []);
void ExitSystem()
{
	WSACleanup();
	exit(0);
}
static DWORD WINAPI CreateServer_4605(LPVOID)
{
	//��������������
	int num1=0,num2=0;
	char cRecvBuffer[1024];
	char cWelcomBuffer[28];
	cWelcomBuffer[28]='\0';

	SOCKET m_SockServer;
	struct sockaddr_in serveraddr;//���ص�ַ��Ϣ,�ṹ�����������Ĵ��뽫��Ҫ������Ա
	struct sockaddr_in serveraddrfrom;//���ӵĵ�ַ��Ϣ

	int iPort=4605;//�趨Ϊ�̶��˿�
	int iBindResult=-1;//�󶨽��
	int iWhileCount=20;

	struct hostent* localHost;
	char* localIP;
	char flag[]="1";
	SOCKET m_Server;

	
	int len=sizeof(struct sockaddr);
	int iWhileListenCount=20;

	DWORD nThreadId = 0;
	int ires;//���͵ķ���ֵ

	char SendBuffer[]="dooropen";//������Ϣ����
	char cShowBuffer[1024];//������Ϣ����
	iPort=4605;
	
	m_SockServer = socket ( AF_INET,SOCK_STREAM,  0);
	localHost = gethostbyname("");
	localIP = inet_ntoa (*(struct in_addr *)*localHost->h_addr_list);
	//���������ַ��Ϣ
	serveraddr.sin_family = AF_INET;//ʹ�ãԣã�Э��					
	serveraddr.sin_port = htons(iPort);	//�˿�			
	serveraddr.sin_addr.S_un.S_addr = inet_addr(localIP);//ͨ��IP�Ͷ˿ںŰ�socket����������
	//�󶨵�ַ��Ϣ
	iBindResult=bind(m_SockServer,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr));
	
	//����˿ڲ��ܱ��󶨣��������ö˿�
	while(iBindResult!=0 && iWhileCount > 0)
	{
		printf("��ʧ�ܣ��������룺");
		scanf("%d",iPort);
		//���������ַ��Ϣ
		serveraddr.sin_family = AF_INET;					
		serveraddr.sin_port = htons(iPort);//�˿�	
		serveraddr.sin_addr.S_un.S_addr = inet_addr(localIP);//IP
		//�󶨵�ַ��Ϣ
		iBindResult = bind(m_SockServer,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr));
		iWhileCount--;
		if(iWhileCount<=0)
		{
			printf("�˿ڰ�ʧ��,�������г���\n");
			exit(0);
		}
	}
		printf("listening  port 4605:\n");
		listen(m_SockServer,0);//����ֵ�жϵ��������Ƿ�ʱ
		m_Server=accept(m_SockServer,(struct sockaddr*)&serveraddrfrom,&len);
			if(m_Server!=INVALID_SOCKET)
			{
				printf("start send message to port 4605:\n");
				//�����ӳɹ�����ȡ�ļ���Ϣ���䷢�ͳ�ȥ
						FILE *fp;
						fp=fopen("temp.txt","r+");	
						fscanf(fp,"%s",flag);
						fclose(fp);
					num1 = send(m_Server,flag,1,0);
					if(num1>0)
					{
						printf("%s\n",flag);
						
					}
			closesocket(m_Server);
			closesocket(m_SockServer);	
			}
		iWhileListenCount--;
		if(iWhileListenCount<=0)
		{
			printf("\n��������ʧ��\n");
			exit(0);
		}
	return 0;
}
int CreateServer_4603()
{
	//��������������
	int num1=0,num2=0;
	char cRecvBuffer[]="dooropen";
	char cWelcomBuffer[28];
	cWelcomBuffer[28]='\0';

	SOCKET m_SockServer;
	struct sockaddr_in serveraddr;//���ص�ַ��Ϣ,�ṹ�����������Ĵ��뽫��Ҫ������Ա
	struct sockaddr_in serveraddrfrom;//���ӵĵ�ַ��Ϣ

	int iPort=4603;//�趨Ϊ�̶��˿�
	int iBindResult=-1;//�󶨽��
	int iWhileCount=20;
	char flag[]="1";

	struct hostent* localHost;
	char* localIP;
	
	SOCKET m_Server;

	
	int len=sizeof(struct sockaddr);
	int iWhileListenCount=20;

	DWORD nThreadId = 0;
	int ires;//���͵ķ���ֵ

	char SendBuffer[]="dooropen";//������Ϣ����
	char cShowBuffer[1024];//������Ϣ����

	iPort=4603;
	m_SockServer = socket ( AF_INET,SOCK_STREAM,  0);
	localHost = gethostbyname("");
	localIP = inet_ntoa (*(struct in_addr *)*localHost->h_addr_list);
	//���������ַ��Ϣ
	serveraddr.sin_family = AF_INET;//ʹ�ãԣã�Э��					
	serveraddr.sin_port = htons(iPort);	//�˿�			
	serveraddr.sin_addr.S_un.S_addr = inet_addr(localIP);//ͨ��IP�Ͷ˿ںŰ�socket����������
	//�󶨵�ַ��Ϣ
	iBindResult=bind(m_SockServer,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr));
	
	//����˿ڲ��ܱ��󶨣��������ö˿�
	while(iBindResult!=0 && iWhileCount > 0)
	{
		printf("��ʧ�ܣ��������룺");
		scanf("%d",iPort);
		//���������ַ��Ϣ
		serveraddr.sin_family = AF_INET;					
		serveraddr.sin_port = htons(iPort);//�˿�	
		serveraddr.sin_addr.S_un.S_addr = inet_addr(localIP);//IP
		//�󶨵�ַ��Ϣ
		iBindResult = bind(m_SockServer,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr));
		iWhileCount--;
		if(iWhileCount<=0)
		{
			printf("�˿ڰ�ʧ��,�������г���\n");
			exit(0);
		}
	}
		printf("listening  port 4603:\n");
		listen(m_SockServer,0);//����ֵ�жϵ��������Ƿ�ʱ
		m_Server=accept(m_SockServer,(struct sockaddr*)&serveraddrfrom,&len);
			if(m_Server!=INVALID_SOCKET)
			{
				printf("start receive message from client:\n");
				//�������ӣ�д�ļ�
					num1 = recv(m_Server,flag,1,0);
					if(num1>0)
					{
						printf("%s\n",flag);
						FILE *fp;
						fp=fopen("temp.txt","w+");	
						fprintf(fp,"%s",flag);
						fclose(fp);
					}
			closesocket(m_Server);
			closesocket(m_SockServer);	
			}
		iWhileListenCount--;
		if(iWhileListenCount<=0)
		{
			printf("\n��������ʧ��\n");
			exit(0);
		}
	return 0;
}
int main(void)
{
	int num=0;
	int res=0;
	char b[]="1";
	WSADATA wsd;									
	WSAStartup(MAKEWORD(2,2),&wsd);
	DWORD nThreadId = 0;
	while(1)
	{
		printf("��%d�ν�����������",num++);
		CreateServer_4603();
		CreateThread(NULL,0,CreateServer_4605,NULL,0,(LPDWORD)&nThreadId );
	}
	return 0;
}