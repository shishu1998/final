#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <time.h> /* time for randomizer*/ 

void serror(const char *msg)
{
    perror(msg);
    exit(1);
}

void cerror(const char *msg)
{
    perror(msg);
    exit(0);
}

int server(int argc, char *argv[]) {

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
       serror("ERROR opening socket");
    // Creates the socket socket() --> endpoints of sockets

    // assign unique new address
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 5001;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             serror("ERROR on binding");
    // assign unique new address

    // wait for a connection
    listen(sockfd,1);
    // wait for a connection

    // accepts the connection
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) 
         serror("ERROR on accept");
    // accepts the connection

    // send the odds are question
        n = write(newsockfd,new_str,strlen(new_str));
        if (n < 0) 
             serror("ERROR writing to socket");
    // send the odds are question

    //while (serverFlagCorrect != 1) {

        // reads the data being received
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) serror("ERROR reading from socket");
        // reads the data being received

        //printf("Buffer from client: <%s>\n", buffer);
        memcpy(charGuess, buffer, sizeof(charGuess));
        //printf("Message from client in charGuess: <%s>\n", charGuess);

        /* Put if statement here for error out if no \n at the end */
        int len = strlen(charGuess);
        const char *last_two = &charGuess[len-2];

        //printf("Last two characters of charGuess: <%s>\n", last_two);

        if (strncmp ( last_two, delimiter, 2) )
            serror (" ERROR Wrong protocol received");

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
            serror("ERROR on accept");
        // sends the answer


    //}        

    close(newsockfd);

    //closes the socket if random integer was found
    close(sockfd);

    return 0; 
}

int client(int argc, char *argv[]){    

    argv[1] = "localhost";
    argv[2] = "5001";
    printf("hostname: %s\n", argv[1]);
    printf("port: %s\n", argv[2]);


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


    /*if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    */
    portno = atoi(argv[2]);

    // Creates the socket socket() --> endpoints of sockets
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        cerror("ERROR opening socket");
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
        cerror("ERROR connecting");
    // connects to the service


    // reads the question being received
    bzero(question,256);
    n = read(sockfd,question,255);
    if (n < 0)
        cerror("ERROR reading from socket");
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
             cerror("ERROR writing to socket");
        // send the string that was processed

        // reads the data being received
        bzero(buffer,256);
        n = read(sockfd,buffer,255);
        if (n < 0) 
             cerror("ERROR reading from socket");
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
            cerror("ERROR Wrong message received");

    //}

    //printf ("Tries: %d \n", numberOfTries);

    //printf("%s\n",buffer);

    close(sockfd);
    return 0;
}

int main(int argc, char *argv[]) {
    char option[4];

    printf("\nWelcome to the wondorous game of odd-are!!\n");
    printf("This game was brought to you by Andrew Kratsios and Felipe Mansilla\n");
    //while((strcmp(option,"1")!=0) || (strcmp(option, "2")!=0)) {
    while((strcmp(option,"1\n") != 0) && (strcmp(option,"2\n") != 0)) {
        printf("\nWhat would you like to do?\n");
        printf("1. Create an odd-are\n");
        printf("2. Join an odds-are game\n");
        printf("Type your selections here: ");
        fgets(option, sizeof(option), stdin);
        //printf("%s\n",option );
        //printf("%d\n",(strcmp(option,"1\n") != 0));

        if (strcmp(option,"1\n") == 0) {
            printf("\nYou chose create an odds-are!\n");
            server(argc, argv);
        }
        else if (strcmp(option,"2\n")==0) {
            printf("\nYou chose join an odds-are!\n");
            client(argc, argv);
        }    
        else {
            printf("Invalid option...chose 1 or 2!\n");
        }
    }
}
