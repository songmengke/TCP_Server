#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib,"ws2_32.lib")

FILE *ioutfileServer;
FILE *ioutfileClient;
void CreateServer_4602();
void CreateServer_4600(char LightStatus[]);
DWORD WINAPI threadproServer(LPVOID pParam);
void SetStatus(char []);
void ExitSystem()
{
	if(ioutfileServer!=NULL)
		fclose(ioutfileServer);
	if(ioutfileClient!=NULL)
		fclose(ioutfileClient);
	WSACleanup();
	exit(0);
}
void SetStatus(char s[])
{
	printf("setstatus:%s\n",s);
	char light1,light2,light3,light4,door,window;
	FILE *Light1=fopen("./Status/Light1State.txt","r+");
	FILE *Light2=fopen("./Status/Light2State.txt","r+");
	FILE *Light3=fopen("./Status/Light3State.txt","r+");
	FILE *Light4=fopen("./Status/Light4State.txt","r+");
	FILE *Door=fopen("./Status/DoorState.txt","r+");
	FILE *Window=fopen("./Status/WindowState.txt","r+");
	light1=s[0];light2=s[1];light3=s[2];
	light4=s[3];door=s[4];window=s[5];
	fprintf(Light1,"%c",light1);
	fprintf(Light2,"%c",light2);
	fprintf(Light3,"%c",light3);
	fprintf(Light4,"%c",light4);
	fprintf(Door,"%c",door);
	fprintf(Window,"%c",window);
	fclose(Light1);fclose(Light2);fclose(Light3);
	fclose(Light4);fclose(Door);fclose(Window);

}
void CreateServer_4602()
{
	//���socket�������տͻ��˴����ĵƹ����ָ��
	SOCKET m_SockServer;
	struct sockaddr_in serveraddr;//���ص�ַ��Ϣ,�ṹ�����������Ĵ��뽫��Ҫ������Ա
	struct sockaddr_in serveraddrfrom;//���ӵĵ�ַ��Ϣ

	int iPort=4602;//�趨Ϊ�̶��˿�
	int iBindResult=-1;//�󶨽��
	int iWhileCount=200;
	int num1=0,num2=0;
	struct hostent* localHost;
	char* localIP;

	SOCKET m_Server;
	/*��ȡ״̬��Ϣ���䷢�ͳ�ȥ*/
	
	char cWelcomBuffer[100];

	int len=sizeof(struct sockaddr);
	int iWhileListenCount=15;

	DWORD nThreadId = 0;
	int ires;//���͵ķ���ֵ

	char cSendBuffer[1024];//������Ϣ����
	char cShowBuffer[1024];//������Ϣ����
	char cRecvBuffer[1024];

	ioutfileServer= fopen("MessageServer.txt","a");//�򿪼�¼��Ϣ���ļ�
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
	while(iWhileListenCount>0)
	{
		printf("start listen port 4602:\n");
		listen(m_SockServer,0);//����ֵ�жϵ��������Ƿ�ʱ
		m_Server=accept(m_SockServer,(struct sockaddr*)&serveraddrfrom,&len);
			if(m_Server!=INVALID_SOCKET)
			{
				printf("start receive message from client:\n");
			while(1)
			{
				num1 = recv(m_Server,cRecvBuffer,6,0);
				if(num1 >= 0)
				{	
					cRecvBuffer[num1]='\0';
					printf("%s\n",cRecvBuffer);
					
					
					SetStatus(cRecvBuffer);
					num2=send(m_Server,cRecvBuffer,6,0);
					CreateServer_4600(cRecvBuffer);
					printf("%s\n",cRecvBuffer);
					if(strcmp("exit",cRecvBuffer)==0)
					{
						ExitSystem();
					}
				}
			}
				break;
		}
		printf(".");
		iWhileListenCount--;
		if(iWhileListenCount<=0)
		{
			printf("\n��������ʧ��\n");
			exit(0);
		}
	}
	
	while(1){}	
}
DWORD WINAPI threadproServer(LPVOID pParam)//������������Ϣ���߳�
{
	
	SOCKET hsock=(SOCKET)pParam;
	char cRecvBuffer[1024];
	char cShowBuffer[1024];
	int num1=0,num2=0;
	if(hsock!=INVALID_SOCKET)
		printf("start receive message from client:\n");
	while(1)
	{
		num1 = recv(hsock,cRecvBuffer,1024,0);
		if(num1 >= 0)
		{
			cRecvBuffer[num1]='\0';
			num2=send(hsock,cRecvBuffer,6,0);
			printf("%s\n",cRecvBuffer);
		
			if(strcmp("exit",cRecvBuffer)==0)
			{
				ExitSystem();
			}
		}
	}
	return 0;
}
void CreateServer_4600(char LightState[])
{
	//���socket�����򿪷��巢�͵ƹ����ָ��
	SOCKET m_SockServer;
	struct sockaddr_in serveraddr;//���ص�ַ��Ϣ,�ṹ�����������Ĵ��뽫��Ҫ������Ա
	struct sockaddr_in serveraddrfrom;//���ӵĵ�ַ��Ϣ

	int iPort=4600;//�趨Ϊ�̶��˿�
	int iBindResult=-1;//�󶨽��
	int iWhileCount;

	struct hostent* localHost;
	char* localIP;

	SOCKET m_Server;
	/*��ȡ״̬��Ϣ���䷢�ͳ�ȥ*/
	int len=sizeof(struct sockaddr);
	int iWhileListenCount=20;
	DWORD nThreadId = 0;
	int ires;//���͵ķ���ֵ

	char cSendBuffer[1024];//������Ϣ����
	char cShowBuffer[1024];//������Ϣ����

	ioutfileServer= fopen("MessageServer.txt","a");//�򿪼�¼��Ϣ���ļ�
	m_SockServer = socket ( AF_INET,SOCK_STREAM,  0);
	

	//scanf("%d",&iPort);
	iPort=4600;
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
	
		printf("�ӷ���˿�ʼ����4600�˿�\n");
		listen(m_SockServer,0);//����ֵ�жϵ��������Ƿ�ʱ
		m_Server=accept(m_SockServer,(struct sockaddr*)&serveraddrfrom,&len);
			if(m_Server!=INVALID_SOCKET)
			{
				//�����ӳɹ������ͻ�ӭ��Ϣ
				printf("���ӳɹ�\n");
			
				send(m_Server,LightState,sizeof(LightState),0);
				closesocket(m_Server);
				closesocket(m_SockServer);
			}	
}

void GetStatus(char welcome[])
{
	FILE *Light1=fopen("./Status/Light1State.txt","r+");
	FILE *Light2=fopen("./Status/Light2State.txt","r+");
	FILE *Light3=fopen("./Status/Light3State.txt","r+");
	FILE *Light4=fopen("./Status/Light4State.txt","r+");
	FILE *Door=fopen("./Status/DoorState.txt","r+");
	FILE *Window=fopen("./Status/WindowState.txt","r+");
	FILE *Temp1=fopen("./Status/Temperature1.txt","r+");
	FILE *Temp2=fopen("./Status/Temperature2.txt","r+");
	FILE *Wet=fopen("./Status/Wet.txt","r+");
	FILE *PM25=fopen("./Status/PM25.txt","r+");
	FILE *Employee1=fopen("./Status/Employee1.txt","r+");
	FILE *Employee2=fopen("./Status/Employee2.txt","r+");
	FILE *Employee3=fopen("./Status/Employee3.txt","r+");
	

	char light1[5],light2[5],light3[5],light4[5],door[5],window[5],temp1[20],temp2[10],wet[10],pm25[10],emp1[5],emp2[5],emp3[5];

	char cWelcomBuffer[25]="A\0";
	fscanf(Light1,"%s",light1);
	fscanf(Light2,"%s",light2);
	fscanf(Light3,"%s",light3);
	fscanf(Light4,"%s",light4);
	fscanf(Door,"%s",door);
	fscanf(Window,"%s",window);
	fscanf(Temp1,"%s",temp1);
	fscanf(Temp2,"%s",temp2);
	fscanf(Wet,"%s",wet);
	fscanf(PM25,"%s",pm25);
	fscanf(Employee1,"%s",emp1);
	fscanf(Employee2,"%s",emp2);
	fscanf(Employee3,"%s",emp3);

	/*ÿ���ַ���ĩβ����A*/
	strcat(window,"A");
	strcat(temp1,"A");
	strcat(temp2,"A");
	strcat(wet,"A");
	strcat(pm25,"A");
	strcat(emp1,"A");
	strcat(emp2,"A");
	/*ƴ���ַ�����cWelcomBuffer*/
	strcat(cWelcomBuffer,light1);
	strcat(cWelcomBuffer,light2);
	strcat(cWelcomBuffer,light3);
	strcat(cWelcomBuffer,light4);
	strcat(cWelcomBuffer,door);
	strcat(cWelcomBuffer,window);
	strcat(cWelcomBuffer,temp1);
	strcat(cWelcomBuffer,temp2);
	strcat(cWelcomBuffer,wet);
	strcat(cWelcomBuffer,pm25);
	strcat(cWelcomBuffer,emp1);
	strcat(cWelcomBuffer,emp2);
	strcat(cWelcomBuffer,emp3);

	//printf("%s%s%s%s%s%s%s%s%s%s\n",light1,light2,light3,light4,door,window,temp1,temp2,wet,pm25);
	//printf("%d %d %d %d %d %d %d %d %d %d\n",strlen(light1),strlen(light2),strlen(light3),strlen(light4),strlen(door),strlen(window),strlen(temp1),strlen(temp2),strlen(wet),strlen(pm25));
	printf("%s %d\n",cWelcomBuffer,strlen(cWelcomBuffer));
	/*�ر����д򿪵��ļ�*/
	fclose(Light1);fclose(Light2);fclose(Light3);fclose(Light4);
	fclose(Door);fclose(Window);fclose(Temp1);
	fclose(Temp2);fclose(Wet);fclose(PM25);
	fclose(Employee1);fclose(Employee2);fclose(Employee3);
	strcpy(welcome,cWelcomBuffer);
}
void CreateServer()
{
	//��������������
	int num1=0,num2=0;
	char cRecvBuffer[1024];
	char cWelcomBuffer[28];
	cWelcomBuffer[28]='\0';

	SOCKET m_SockServer;
	struct sockaddr_in serveraddr;//���ص�ַ��Ϣ,�ṹ�����������Ĵ��뽫��Ҫ������Ա
	struct sockaddr_in serveraddrfrom;//���ӵĵ�ַ��Ϣ

	int iPort=4601;//�趨Ϊ�̶��˿�
	int iBindResult=-1;//�󶨽��
	int iWhileCount=20;

	struct hostent* localHost;
	char* localIP;
	
	char test[]="A111111A28A26A300A222A111\r\n";

	GetStatus(cWelcomBuffer);
	//strcat(cWelcomBuffer,"\0");
	printf("%s\n",cWelcomBuffer);
	printf("%d\n",strlen(cWelcomBuffer));
	SOCKET m_Server;

	
	int len=sizeof(struct sockaddr);
	int iWhileListenCount=20;

	DWORD nThreadId = 0;
	int ires;//���͵ķ���ֵ

	char cSendBuffer[1024];//������Ϣ����
	char cShowBuffer[1024];//������Ϣ����

	ioutfileServer= fopen("MessageServer.txt","a");//�򿪼�¼��Ϣ���ļ�
	m_SockServer = socket ( AF_INET,SOCK_STREAM,  0);
	
	//scanf("%d",&iPort);

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
	while(iWhileListenCount>0)
	{
		printf("start listen port 4601:\n");
		listen(m_SockServer,0);//����ֵ�жϵ��������Ƿ�ʱ
		m_Server=accept(m_SockServer,(struct sockaddr*)&serveraddrfrom,&len);
			if(m_Server!=INVALID_SOCKET)
			{
				//�����ӳɹ������ͻ�ӭ��Ϣ
				num2=send(m_Server,cWelcomBuffer,28,0);
				if(num2>0)
				{
					printf("���ͳɹ�\n");
					//�������շ����
					CreateServer_4602();
				}
				else
				{
					num2=send(m_Server,cWelcomBuffer,strlen(cWelcomBuffer),0);
				}
				
				
				
				//UserCreateServer();
				break;
			}
		printf(".");
		iWhileListenCount--;
		if(iWhileListenCount<=0)
		{
			printf("\n��������ʧ��\n");
			exit(0);
		}
	}
	while(1)
	{}

}
int CheckIP(char *cIP)
{
	char IPAddress[128];//IP��ַ�ַ���
	char IPNumber[4];//IP��ַ��ÿ�����ֵ
	int iSubIP=0;//IP��ַ��4��֮һ
	int iDot=0;//IP��ַ��'.'�ĸ���
	int iResult=0;
	int iIPResult=1;
	int i;//ѭ�����Ʊ���
	memset(IPNumber,0,4);
	strncpy(IPAddress,cIP,128);
	for(i=0;i<128;i++)
	{
		if(IPAddress[i]=='.')
		{
			iDot++;
			iSubIP=0;
			if(atoi(IPNumber)>255)
				iIPResult = 0;
			memset(IPNumber,0,4);
		}
		else
		{
			IPNumber[iSubIP++]=IPAddress[i];
		}
		if(iDot==3 && iIPResult!=0)
			iResult= 1;
	}
	return iResult;
}
int main(void)
{
	int iSel=0;
	WSADATA wsd;									
	WSAStartup(MAKEWORD(2,2),&wsd);
	CreateServer();
	return 0;
}

