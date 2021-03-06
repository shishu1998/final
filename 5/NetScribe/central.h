#ifndef CENTRAL_SERVER_H_
#define CENTRAL_SERVER_H_

/* PREPROCESSOR DEFINITIONS ***************************************************/

#define MAX_CLIENT_PER_ROOM 8
#define MAX_SUBSERVER_COUNT 100 // maximum number of subservers (chat/co-editing rooms the server can handle)
#define MAX_CLIENT_COUNT 500 // maximum number of client connections

#define CLIENT_PORT 11235

#define CONN_REQUEST "Connection Request: "

/* DATATYPE DEFINITIONS *******************************************************/

typedef struct client { // a client connection
    char name[16];
    int room; // which room this client is in
    int room_id; // id in the local/client side room
    int socket_id; // central server <-> client connection
} client;

typedef struct subserver { // wrapper struct subserver, a list of pointers to client connections
    int user_ids[MAX_CLIENT_PER_ROOM];
} subserver;

typedef struct message {
    int remote_client_id; // id of the client on the central server
    int local_client_id; // id of the client on the local server
    int to_distribute; // boolean, true if to distribute, false if internal
    char *cmd; // the command
    char *content; // the content of the command
} message;

/* GLOBAL VARIABLES ***********************************************************/
client *users_list[MAX_CLIENT_COUNT] = {0};
subserver *rooms_list[MAX_SUBSERVER_COUNT] = {0};

/* FUNCTION HEADERS ***********************************************************/
void debug(char *statement, ...);
void check_error(int ret_val);
void handle_cmd_line_args(int argc, char *argv[]); // handles command line arguments
int establish_connection(); // sets up the socket file
void handle_client(int socket); // handles client arguments

#endif // CENTRAL_SERVER_H_
