#include <stdio.h>
#include <stdlib.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <unistd.h>
#include <string.h> 
#define PORT 8000
#define SIZE 5000 

/* A enter Celsius and return Fahrenheit */ 


int main( void ){

    int len; 
    int socket_client = socket( AF_INET, SOCK_STREAM, 0 ); 
    struct sockaddr_in addr; 
    char *str; 
    char str_read[SIZE]; 

    if( socket_client == -1 ){ 
        perror( "socket_client error: "); 
        exit(1); 
    }

    addr.sin_family = AF_INET; 
    addr.sin_addr.s_addr = inet_addr( "127.0.0.1" ); 
    addr.sin_port = htons( PORT ); 
    len = sizeof( addr ); 

    if( -1 == connect( socket_client, (struct sockaddr *) &addr, len ) ){ 
        perror( "socket_client connection fail: " ); 
        exit(1); 
    } 

    str = "hellow world from client!!"; 

    if( write( socket_client, str, strlen( str ) ) == -1 ){  
        perror( "socket_client fails to send msg to server: " ); 
        exit(1); 
    } 

    if( read( socket_client, str_read, SIZE ) == -1 ){  
        perror( "socket_client fails to recieve msg from server: " ); 
        exit(1); 
    } 

    printf( "The message sends to server \"%s\".\n", str ); 
    printf( "The message responsed from server \"%s\".\n", str_read ); 

    close( socket_client ); 

    return 0; 
} 

