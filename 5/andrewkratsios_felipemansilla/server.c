#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h> /* time for randomizer*/ 


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {

    argv[2] = "5001";
    printf("port: %s\n", argv[2]);

    int sockfd, newsockfd, portno, n;
    socklen_t clilen;
    char buffer[256];
    char question[1024];
    char option[4];
    char oddsInt[4];
    struct sockaddr_in serv_addr, cli_addr;

    int GuessedInteger, integerRandom, serverFlagCorrect;
    char charGuess[4], answerServer[1];
    char* delimiter = "\\n";

    /** initialization of variables **/
    serverFlagCorrect = 0;

    /** generate random integer from 1 to 100 **/
    srand (time(NULL));
    integerRandom = (rand() % 100) + 1;

    printf("Enter your odds are: ");
    fgets(question, sizeof(question), stdin);
    printf("Enter the number for your odds are: ");
    fgets(oddsInt, sizeof(oddsInt), stdin);
    printf("\n%s1 out of %s\n",question, oddsInt );
    printf("Enter your guess: ");
    scanf("%d",&integerRandom);
    printf("Waiting for opponent to connect...\n");

    char * new_str ;
    if((new_str = malloc(strlen(question)+strlen("1 out of ")+strlen(oddsInt)+1)) != NULL){
        new_str[0] = '\0';   // ensures the memory is an empty string
        strcat(new_str,question);
        strcat(new_str,"1 out of ");
        strcat(new_str,oddsInt);
    }

    /*if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    */

    // Creates the socket socket() --> endpoints of sockets
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
       error("ERROR opening socket");
    // Creates the socket socket() --> endpoints of sockets

    // assign unique new address
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 5001;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             error("ERROR on binding");
    // assign unique new address

    // wait for a connection
    listen(sockfd,1);
    // wait for a connection

    // accepts the connection
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) 
         error("ERROR on accept");
    // accepts the connection

    // send the odds are question
        n = write(newsockfd,new_str,strlen(new_str));
        if (n < 0) 
             error("ERROR writing to socket");
    // send the odds are question

    //while (serverFlagCorrect != 1) {

        // reads the data being received
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) error("ERROR reading from socket");
        // reads the data being received

        //printf("Buffer from client: <%s>\n", buffer);
        memcpy(charGuess, buffer, sizeof(charGuess));
        //printf("Message from client in charGuess: <%s>\n", charGuess);

        /* Put if statement here for error out if no \n at the end */
        int len = strlen(charGuess);
        const char *last_two = &charGuess[len-2];

        //printf("Last two characters of charGuess: <%s>\n", last_two);

        if (strncmp ( last_two, delimiter, 2) )
            error (" ERROR Wrong protocol received");

        /** process the string to integer for server comparison **/
        GuessedInteger = atoi(charGuess);
        printf("Opponents guess: %d \n", GuessedInteger);

        /** Server response for comparison**/
        if (GuessedInteger > integerRandom){
            memcpy(&answerServer, "L", sizeof(answerServer));
            printf("Your opponent doesn't have to do the dare.\n");
        }
        else if (GuessedInteger < integerRandom){
            memcpy(&answerServer, "H", sizeof(answerServer));
            printf("Your opponent doesn't have to do the dare.\n");
        }
        else if (GuessedInteger == integerRandom)
            {
                serverFlagCorrect = 1;
                memcpy(&answerServer, "O", sizeof(answerServer));
                printf("Your opponent must't do the dare!\n");
            }
        //printf("Value of answerServer: %c\n", *answerServer);
        /** Server response for comparison**/

        // sends the answer
        n = write(newsockfd, answerServer, 1);
        if (newsockfd < 0) 
            error("ERROR on accept");
        // sends the answer


    //}        

    close(newsockfd);

    //closes the socket if random integer was found
    close(sockfd);

    return 0; 
}
