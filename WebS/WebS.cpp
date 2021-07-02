#include "webserver.h"
int main()
{
    WebServer server(23333,3,60000, false,6);
    server.Start();
}
