#include<cstring>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<iostream>
#include<unistd.h>
#include<string>

int main(){

    std::cout<<"connecting ..."<<std::endl;
    int socket_id=socket(AF_INET,SOCK_DGRAM,0);
    if(socket_id==-1){
        std::cout<<"couldn't establish socket..."<<std::endl;
        return -1;
    }


    std::string ip;
    std::cout<<"ip:";
    std::cin>>ip;
    struct sockaddr_in addr_sock_local;
    memset(&addr_sock_local,0,sizeof(addr_sock_local));
    addr_sock_local.sin_family=AF_INET;
   // addr_sock_local.sin_addr.s_addr=INADDR_ANY;
    addr_sock_local.sin_addr.s_addr=inet_addr(ip.c_str());
    addr_sock_local.sin_port=htons(3000);


    if(bind(socket_id,(struct sockaddr*)& addr_sock_local,sizeof(addr_sock_local))<0)
    {
        std::cout<<"couldn't bind socket"<<std::endl;
        close(socket_id);
        return -1;
    }

    std::cout<<"connection established under id= "<<socket_id<<std::endl;
    //running the send recieve 

    bool run=true;
    while(run){
        std::string message;
        std::cout<<"You: ";
        std::cin>>message;
        ssize_t er_send = sendto(socket_id,message.c_str(),message.length(),0,(struct sockaddr*)& addr_sock_local,sizeof(addr_sock_local));
        char buffer[1024];
        socklen_t len=sizeof(addr_sock_local);
        ssize_t msg_rec=recvfrom(socket_id,buffer,sizeof(buffer)-1,0,(struct sockaddr*)& addr_sock_local,&len);
        if(msg_rec<0){
            std::cout<<"error in recieving"<<std::endl;
        }
        buffer[msg_rec]='\0';
        std::cout<<"other: "<<buffer<<std::endl;
        if(strcmp(buffer,"exit")==0){
            run=false;
        }
    }

    close(socket_id);
    return 0;
}

