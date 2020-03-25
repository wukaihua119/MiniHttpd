## Socket 

### Libraries 
* **netinet/in.h** <br/> 
    Defines a struct sockaddr_in to store the information about server's ip, type of domain, and port that used for client connects to server. 
    ```
        struct sockaddr_in{ 
            short sin_family; // Type of domina. e.g. AF_INET
            struct in_addr; // reference to struct in_addr;  
            unsigned int sin_port; // the port, must converted from string to bytes by htons() defined in <arpa/inet.h>. 
            char sin_zero[8]; // not used. Must be zero. 
        }; 

        struct in_addr{ 
            unsigned long s_addr; // The ip converted from string format to integer format of address by inet_addr() defined in <arpa/inet.h>. 
        }; 

        // MACROS 
        INADDR_ANY: used when you are binding the socket in server side. 
                    ```INADDR_ANY``` is used when you don't need to bind a socket to a specific IP. 
                    When you use this value as the address when calling bind(), the socket accepts connections to all the IPs of the machine.


    ```

* **arpa/inet.h** <br/> 
    Define for internet operations. 
    ``` 
        in_addr_t inet_addr( const char *cp ); 
            IPv4 address manipulation. 
            Convert the string pointed to by cp, in the standard IPv4 dotted decimal notation, to an integer value suitable for use as an Internet address.
            [REFERENCE](https://pubs.opengroup.org/onlinepubs/009695399/functions/inet_addr.html)
            The in_addr_t is defined in *<netinet/in.h>*. 

        char *inet_ntoa( struct in_addr in ); 
            convert the Internet host address specified by in to a string in the Internet standard dot notation.
            struct in_addr is defined in *<netinet/in.h>*. 

        htonl(), htons(), ntohl() and ntohs() are defined in this header. 
        Inclusion of the *<netinet/in.h>* header may also make visible all symbols from *<arpa/inet.h>*.
    ``` 

* **sys/socket.h** <br/> 
    Define and communicate using socket. 
    ```
        int socket( int domain, int type, int protocol ); 
            Return -1 if not success or a file descriptor. 
            domain: 
                AF_INET: transit information through internet aka IPv4. The PF_INET is the same as AF_INET. AF = Address Family, PF = Protocol Family.  
                         [The difference between both](http://students.mimuw.edu.pl/SO/Linux/Kod/include/linux/socket.h.html) 
                         and [here](https://blog.csdn.net/fivedoumi/article/details/72424784). 
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

        int listen( int socket, int backlog ); 
            Listen for socket connections and limit the queue of incoming connections
            Return -1 if failed or 0. 
            socket: 
                The file descriptor. 
            backlog: 
                The maximun capability of the queue. 

        int accept( int socket, struct sockaddr *address, socklen_t *address_len ); 
            Extracts the first connection on the queue of pending connections, creates a new socket with the same socket type protocol 
            and address family as the specified socket, and allocates a new file descriptor for that socket.
            Return -1 if failed or 0. 
            socket: 
                The file descriptor that is created by socket(), has been bind(), and has issued a successful call to listen(). 
            address: 
                A struct sockaddr that is to store the received client socket information.
            address_len: 
                The length of the received soceket. 

        int setsockopt( int s, int level, int optname, const void *optval, socklen_t len ); 
            Used to set socket options. 
            [Reference](http://c.biancheng.net/cpp/html/374.html)  

        // communication functions 
        ssize_t recv( int socket, void * buffer, size_t length, int flags ); 
        ssize_t send( int socket, const void * message, size_t length, int flags ); 

    ```
    
### Procedures 
[procudure](./socket.png) 

#### Client Endpoint 
1. setting socket about ip address, port, type of protocol with socket( int, int, int ) and struct sockaddr_in. 
2. connect the client socket to server socket with connect(). 
3. start to write/read/send/recv and other manipulate 
4. use close() to terminate the socket 

#### Server Endpoint 
1. setting socket about ip address, port, type of protocol with socket( int, int, int ) and struct sockaddr_in. 
2. binding the server's ip address to its socket with bind().  
3. check the message put in queue by socket using listen() due to the server deals with only one message at a time. 
4. dealing with the first message and remove it in queue using accept(). Every time the message accepted from queue will be remove from queue and always create a new socket. 
5. start to write/read/send/recv and other manipulate 
6. use close() to terminate the socket 

#### Referneces 
* http://zake7749.github.io/2015/03/17/SocketProgramming/?fbclid=IwAR0x8nxUhfVeLQC1YdYx8JAig6UyKP9-CDwYeO2uJmSe8-fW4ybPX0hD3UM
* https://bellinellishih1003.blogspot.com/2015/10/socket1-linux-ossocketudptcpsocket.html?fbclid=IwAR0M-Ni8TGnTFnpu1JrrqeUmZIQFy8bK2RKFr0ZzHdcf_pUSCuDFqc94iok
* https://github.com/EZLippi/Tinyhttpd/blob/master/simpleclient.c 
