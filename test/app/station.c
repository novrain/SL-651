#include "station.h"

int main()
{
    Station station = {0};
    char const *configFile = "./config.json";

    int res = Station_StartBy(&station, configFile);
    // loop exit
    Station_dtor(&station);
    return res;
}