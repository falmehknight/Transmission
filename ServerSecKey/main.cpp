#include <cstdio>
#include "ServerOp.h"

int main()
{
    ServerOp op("config.json");
    op.startServer();

    return 0;
}
