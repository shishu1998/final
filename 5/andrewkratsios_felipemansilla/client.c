#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[1024];
    char question[1024];
    char oddsInt[4];

    int integerGuess, clientFlagCorrect;
    int numberOfTries;
    char charGuess[1024], answerServer[1];
    char* delimiter = "\\n";


    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);

    // Creates the socket socket() --> endpoints of sockets
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    // Creates the socket socket() --> endpoints of sockets

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    // connects to the service in connect()
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    // connects to the service


    // reads the question being received
    bzero(question,256);
    n = read(sockfd,question,255);
    if (n < 0)
        error("ERROR reading from socket");
    // reads the question being received
    printf("Odds Are received:\n%s\n",question);


    /** initialization of variables **/
    clientFlagCorrect = 0;
    numberOfTries = 0;

    //while (clientFlagCorrect != 1) {
        numberOfTries = numberOfTries + 1;

        /** initialization of variables **/
        integerGuess = 0;
        memset(charGuess, 0, sizeof(charGuess));

        // ask the user for the guessed number
        printf("Guess: ");
        bzero(buffer,sizeof(buffer));
        fgets(buffer,sizeof(buffer)-1,stdin);
        //printf("Buffer to be processed : <%s>\n", buffer);
        // ask the user for the guessed number

        /** process the integer to string and add a delimiter **/
        integerGuess = atoi(buffer);
        //printf("integerGuess : <%d> \n", integerGuess);
        sprintf( charGuess, "%d", integerGuess);    
        strcat( charGuess, delimiter);
        //printf("String Guess : <%s> \n", charGuess);

        memset(buffer,0,sizeof(buffer));
        memcpy(buffer, charGuess, sizeof(charGuess));
        //printf("Buffer to send : <%s>\n",buffer);
        /** process the integer to string and add a delimiter **/

        // send the string that was processed
        n = write(sockfd,buffer,strlen(buffer));
        if (n < 0) 
             error("ERROR writing to socket");
        // send the string that was processed

        // reads the data being received
        bzero(buffer,256);
        n = read(sockfd,buffer,255);
        if (n < 0) 
             error("ERROR reading from socket");
        // reads the data being received

        //printf("Buffer received : <%s>\n",buffer);

        memcpy(&answerServer, buffer, sizeof(answerServer));
        //printf ("Value of answerServer : <%c> \n", *answerServer);

        /** Client response **/
        if (strncmp ( & answerServer[0],"L",sizeof(answerServer)) == 0)
            printf("You don't have to do the dare! \n");
        else if (strncmp ( & answerServer[0],"H",sizeof(answerServer)) == 0)
            printf("You don't have to do the dare! \n");
        else if (strncmp ( & answerServer[0],"O",sizeof(answerServer)) == 0){
            printf("You must do the dare! \n");
            clientFlagCorrect = 1;
        }
        else
            error("ERROR Wrong message received");

    //}

    //printf ("Tries: %d \n", numberOfTries);

    //printf("%s\n",buffer);

    close(sockfd);
    return 0;
}