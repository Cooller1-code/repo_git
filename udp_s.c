/**UDP收发文字服务器端 
*吴汝桐
*socket编程作业
*/

//1.编写使用UDP协议的服务器程序
//2.编写使用UDP协议的客户端程序
//3.客户端向服务器发送字符串，服务器打印收到的字符串
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 3344 
#define MAX_BUFFER_SIZE 1024

int main(int argc,char *argv)
{
	//本地的socket地址 
    struct sockaddr_in server_addr;
    //客户端的socket地址 
    struct sockaddr_in client_addr;
    
    //服务器监听的socket 
    int server_fd;
    
    //定义数据长度
    int addr_size;
    int nbytes;
    
    //接收数据的内存 
    char buffer[1024];

	//创建socket 
    server_fd = socket(AF_INET,SOCK_DGRAM,0);
    if(server_fd < 0)
    {
        fprintf(stderr,"create socket error:%s\n",strerror(errno));
        exit(1);
    }

    bzero(&server_addr,sizeof(struct sockaddr_in));
    //设置本机的socket地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    //绑定Socket
    if(bind(server_fd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr_in))  < 0)
    {
        fprintf(stderr,"bind error:%s\n",strerror(errno));
        exit(1);
    }
    
    while(1)
    {
        bzero(buffer,sizeof(buffer));
        addr_size = sizeof(struct sockaddr);
        nbytes = recvfrom(server_fd,buffer,MAX_BUFFER_SIZE,0,(struct sockaddr*)&client_addr,&addr_size);
        buffer[nbytes] = 0;
        fprintf(stdout,"server have received:%s\n",buffer);
    }
    
    //关闭监听的socket
    close(server_fd);
    
    return 0;
}
