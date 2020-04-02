#include <stdio.h>
#include <stdlib.h>

#include "../3rd/ini/iniparser.h"

int read_conf(const char *p, dictionary *d)
{
    d = iniparser_load(p);
    if (!d)
    {
        fprintf(stderr, "Need Cfg file, See README.");
        return -1;
    }
    iniparser_dump(d);
    return 0;
}

int main(int argc, char *argv[])
{
    dictionary *d = NULL;
    read_conf("config/config.cfg", d);
    return 0;
}