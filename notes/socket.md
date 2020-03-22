## Socket 

### Libraries 
* **netinet/in.h** <br/> 
    Defines a struct sockaddr_in to store the information about server's ip, type of domain, and port that used for client connects to server. 
    ```
        struct sockaddr_in{ 
            short sin_family; // Type of domina. e.g. AF_INET
            struct in_addr; // reference to struct in_addr;  
            unsigned int sin_port; // the port, must converted from string to bytes by htons(). 
            char sin_zero[8]; // not used. Must be zero. 
        }; 

        struct in_addr{ 
            unsigned long s_addr; // The ip converted from string format to integer format of address by inet_addr(). 
        }; 

    ```
* **sys/socket.h** <br/> 
    Define and communicate using socket. 
    ```
        int socket( int domain, int type, int protocol ); 
            Return -1 if not success or a file descriptor. 
            domain: 
                AF_INET: transit information through internet. 
                AF_UNIX/AF_LOCAL: transit information through processes. 

            type: 
                SOCK_STREAM: Provides sequenced, reliable, bidirectional, connection-mode byte streams, 
                             and may provide a transmission mechanism for out-of-band data. Use the protocol a.k.a TCP
                SOCK_STREAM: Provides datagrams, which are connectionless-mode, unreliable messages of fixed maximum length. Use the protocol a.k.a UDP.
                SOCK_SEQPACKET: 
            protocol: 
                0 by default. 


        int connect( int socket, const struct sockaddr *address, socklen_t address_len ); 
            Used by client endpoint to connect to the server. 
            Requests a connection to be made on a socket or -1.
            socket: 
                A file descriptor that created from _int socket( int, int, int )_ 
            struct sockaddr *: 
                All information of that socket. 
                Points to a sockaddr structure containing the peer address. 
                The length and format of the address depend on the address family of the socket.
            socklen_t: 
                the length of sockaddr. 

        int bind( int socket, struct sockaddr *addr, int addrlen ); 
            Used by server endpoint to bind the server ip to itself. Return 0 for sucess, or -1. 
            socket: 
                The file descriptor. 
            sockaddr *addr: 
                the same as connect(). 
            socklen_t: 
                the length of addr. 

        // communication functions 
        ssize_t recv( int socket, void * buffer, size_t length, int flags ); 
        ssize_t send( int socket, const void * message, size_t length, int flags ); 

    ```
### Procedures 
[procudure](./socket.png) 
#### Client Endpoint 

#### Server Endpoint 

#### Referneces 
* http://zake7749.github.io/2015/03/17/SocketProgramming/?fbclid=IwAR0x8nxUhfVeLQC1YdYx8JAig6UyKP9-CDwYeO2uJmSe8-fW4ybPX0hD3UM
* https://bellinellishih1003.blogspot.com/2015/10/socket1-linux-ossocketudptcpsocket.html?fbclid=IwAR0M-Ni8TGnTFnpu1JrrqeUmZIQFy8bK2RKFr0ZzHdcf_pUSCuDFqc94iok
* https://github.com/EZLippi/Tinyhttpd/blob/master/simpleclient.c 
