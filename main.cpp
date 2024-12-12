#include "Headers/NetworkModule.h"

int main()
{
    NetworkModule network;
    network.start_server(12345);

    return 0;
}