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
	//这个是主调服务端
	int num1=0,num2=0;
	char cRecvBuffer[1024];
	char cWelcomBuffer[28];
	cWelcomBuffer[28]='\0';

	SOCKET m_SockServer;
	struct sockaddr_in serveraddr;//本地地址信息,结构体变量，后面的代码将会要填充其成员
	struct sockaddr_in serveraddrfrom;//连接的地址信息

	int iPort=4605;//设定为固定端口
	int iBindResult=-1;//绑定结果
	int iWhileCount=20;

	struct hostent* localHost;
	char* localIP;
	char flag[]="1";
	SOCKET m_Server;

	
	int len=sizeof(struct sockaddr);
	int iWhileListenCount=20;

	DWORD nThreadId = 0;
	int ires;//发送的返回值

	char SendBuffer[]="dooropen";//发送消息缓存
	char cShowBuffer[1024];//接收消息缓存
	iPort=4605;
	
	m_SockServer = socket ( AF_INET,SOCK_STREAM,  0);
	localHost = gethostbyname("");
	localIP = inet_ntoa (*(struct in_addr *)*localHost->h_addr_list);
	//设置网络地址信息
	serveraddr.sin_family = AF_INET;//使用ＴＣＰ协议					
	serveraddr.sin_port = htons(iPort);	//端口			
	serveraddr.sin_addr.S_un.S_addr = inet_addr(localIP);//通过IP和端口号绑定socket到本地主机
	//绑定地址信息
	iBindResult=bind(m_SockServer,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr));
	
	//如果端口不能被绑定，重新设置端口
	while(iBindResult!=0 && iWhileCount > 0)
	{
		printf("绑定失败，重新输入：");
		scanf("%d",iPort);
		//设置网络地址信息
		serveraddr.sin_family = AF_INET;					
		serveraddr.sin_port = htons(iPort);//端口	
		serveraddr.sin_addr.S_un.S_addr = inet_addr(localIP);//IP
		//绑定地址信息
		iBindResult = bind(m_SockServer,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr));
		iWhileCount--;
		if(iWhileCount<=0)
		{
			printf("端口绑定失败,重新运行程序\n");
			exit(0);
		}
	}
		printf("listening  port 4605:\n");
		listen(m_SockServer,0);//返回值判断单个监听是否超时
		m_Server=accept(m_SockServer,(struct sockaddr*)&serveraddrfrom,&len);
			if(m_Server!=INVALID_SOCKET)
			{
				printf("start send message to port 4605:\n");
				//有连接成功，读取文件信息将其发送出去
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
			printf("\n建立连接失败\n");
			exit(0);
		}
	return 0;
}
int CreateServer_4603()
{
	//这个是主调服务端
	int num1=0,num2=0;
	char cRecvBuffer[]="dooropen";
	char cWelcomBuffer[28];
	cWelcomBuffer[28]='\0';

	SOCKET m_SockServer;
	struct sockaddr_in serveraddr;//本地地址信息,结构体变量，后面的代码将会要填充其成员
	struct sockaddr_in serveraddrfrom;//连接的地址信息

	int iPort=4603;//设定为固定端口
	int iBindResult=-1;//绑定结果
	int iWhileCount=20;
	char flag[]="1";

	struct hostent* localHost;
	char* localIP;
	
	SOCKET m_Server;

	
	int len=sizeof(struct sockaddr);
	int iWhileListenCount=20;

	DWORD nThreadId = 0;
	int ires;//发送的返回值

	char SendBuffer[]="dooropen";//发送消息缓存
	char cShowBuffer[1024];//接收消息缓存

	iPort=4603;
	m_SockServer = socket ( AF_INET,SOCK_STREAM,  0);
	localHost = gethostbyname("");
	localIP = inet_ntoa (*(struct in_addr *)*localHost->h_addr_list);
	//设置网络地址信息
	serveraddr.sin_family = AF_INET;//使用ＴＣＰ协议					
	serveraddr.sin_port = htons(iPort);	//端口			
	serveraddr.sin_addr.S_un.S_addr = inet_addr(localIP);//通过IP和端口号绑定socket到本地主机
	//绑定地址信息
	iBindResult=bind(m_SockServer,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr));
	
	//如果端口不能被绑定，重新设置端口
	while(iBindResult!=0 && iWhileCount > 0)
	{
		printf("绑定失败，重新输入：");
		scanf("%d",iPort);
		//设置网络地址信息
		serveraddr.sin_family = AF_INET;					
		serveraddr.sin_port = htons(iPort);//端口	
		serveraddr.sin_addr.S_un.S_addr = inet_addr(localIP);//IP
		//绑定地址信息
		iBindResult = bind(m_SockServer,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr));
		iWhileCount--;
		if(iWhileCount<=0)
		{
			printf("端口绑定失败,重新运行程序\n");
			exit(0);
		}
	}
		printf("listening  port 4603:\n");
		listen(m_SockServer,0);//返回值判断单个监听是否超时
		m_Server=accept(m_SockServer,(struct sockaddr*)&serveraddrfrom,&len);
			if(m_Server!=INVALID_SOCKET)
			{
				printf("start receive message from client:\n");
				//接受连接，写文件
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
			printf("\n建立连接失败\n");
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
		printf("第%d次接受连接请求",num++);
		CreateServer_4603();
		CreateThread(NULL,0,CreateServer_4605,NULL,0,(LPDWORD)&nThreadId );
	}
	return 0;
}