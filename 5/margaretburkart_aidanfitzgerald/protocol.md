Mail protocol

4 bytes: max size of transmission (network byte order)
- Use htoni() <==> ntohi()

n bytes: the transmission itself

transmission := client_request | server_response

    client_request = COMMAND + "\n" + Content of the Message
        COMMAND := "LOGIN" | "SETUP" | "GET" | "SEND" | "LOGOUT"

    server_response = STATUS + "\n" + Content of the Message
        STATUS := "OK" | "FAIL" | "NONE"