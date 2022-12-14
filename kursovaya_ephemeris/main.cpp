#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#include "checksum.h"

#define IS_OK(g) (g.req.sv >= 1 && g.req.sv <= 37)

using namespace std;

// ?????????? ????????? ??????? 168 ????

void printGPSEphem3(GPSEphem3* g)
{
    printf("???????? GPS (Required data + Optional data(big):\n");
    printf("\t %u %u %u \n", g->req.sv, g->req.tow, g->req.flags);
    printf("\t %d %d %d \n", g->req.iodc, g->req.toc, g->req.ura);
    printf("\t %u %d  %f \n", g->req.healthS, g->req.wn, g->req.tgd);

    printf("\t %f  %f  %f \n", g->req.af2, g->req.af1, g->req.af0);
    printf("\t %d %d  %lf \n", g->req.toe, g->req.iode, g->req.rootA);
    printf("\t %lf  %lf  %lf \n", g->req.ecc, g->req.m0, g->req.omega0);

    printf("\t %lf  %lf  %f \n", g->req.inc0, g->req.argPer, g->req.deln);
    printf("\t %f  %f  %f \n", g->req.omegaDot, g->req.incDot, g->req.crc);
    printf("\t %f  %f  %f  %f \n", g->req.crs, g->req.cuc, g->req.cic, g->req.cis);

    printf("\t %u %d %d \n", g->opt.navType, g->opt.lTope, g->opt.lTopc);
    printf("\t %lf  %f  %d \n", g->opt.dADot, g->opt.fDelnDot, g->opt.cURAoe);
    printf("\t %d %d %d \n", g->opt.cURAoc, g->opt.cURAoc1, g->opt.cURAoc2);

    printf("\t %f %f \n", g->opt.isc.Isc1.fIscL1CA, g->opt.isc.Isc1.fIscL2C);

    printf("\t %f  %f \n", g->opt.isc.Isc1.fIscL5I5, g->opt.isc.Isc1.fIscL5Q5);
    printf("\t %f  %f  %f \n", g->opt.isc.Isc2.fIscL1CP, g->opt.isc.Isc2.fIscL1CD, g->opt.DAf0);

    printf("??????????? ?????: \t ????????: %u \n", g->cs);
}

// ?????????? ????????? ??????? 160 ????

void printGPSEphem2(GPSEphem2* g)
{
    printf("???????? GPS (Required data + Optional data(small)): \n");
    printf("\t %u %u %u \n", g->req.sv, g->req.tow, g->req.flags);
    printf("\t %d %d %d \n", g->req.iodc, g->req.toc, g->req.ura);
    printf("\t %u %d  %f \n", g->req.healthS, g->req.wn, g->req.tgd);

    printf("\t %f  %f  %f \n", g->req.af2, g->req.af1, g->req.af0);
    printf("\t %d %d  %lf \n", g->req.toe, g->req.iode, g->req.rootA);
    printf("\t %lf  %lf  %lf \n", g->req.ecc, g->req.m0, g->req.omega0);

    printf("\t %lf  %lf  %f \n", g->req.inc0, g->req.argPer, g->req.deln);
    printf("\t %f  %f  %f \n", g->req.omegaDot, g->req.incDot, g->req.crc);
    printf("\t %f  %f  %f  %f \n", g->req.crs, g->req.cuc, g->req.cic, g->req.cis);

    printf("\t %u %d %d \n", g->opt.navType, g->opt.lTope, g->opt.lTopc);
    printf("\t %lf  %f %d \n", g->opt.dADot, g->opt.fDelnDot, g->opt.cURAoe);
    printf("\t %d %d %d \n", g->opt.cURAoc, g->opt.cURAoc1, g->opt.cURAoc2);

    printf("\t %f  %f \n", g->opt.isc.fIscL1CA, g->opt.isc.fIscL2C);
    printf("\t %f  %f \n", g->opt.isc.fIscL5I5, g->opt.isc.fIscL5Q5);

    printf("??????????? ?????: \t ????????: %u \n", g->cs);
}

// ?????????? ????????? ??????? 123 ????

void printGPSEphem1(GPSEphem1* g)
{
    printf("????????? GPS (Only required data):\n");
    printf("\t %u %u %u \n", g->req.sv, g->req.tow, g->req.flags);
    printf("\t %d %d %d \n", g->req.iodc, g->req.toc, g->req.ura);
    printf("\t %u %d  %f \n", g->req.healthS, g->req.wn, g->req.tgd);

    printf("\t %f  %f  %f \n", g->req.af2, g->req.af1, g->req.af0);
    printf("\t %d %d  %lf \n", g->req.toe, g->req.iode, g->req.rootA);
    printf("\t %lf  %lf  %lf \n", g->req.ecc, g->req.m0, g->req.omega0);

    printf("\t %lf  %lf  %f \n", g->req.inc0, g->req.argPer, g->req.deln);
    printf("\t %f  %f  %f \n", g->req.omegaDot, g->req.incDot, g->req.crc);
    printf("\t %f  %f  %f  %f \n", g->req.crs, g->req.cuc, g->req.cic, g->req.cis);

    printf("??????????? ?????: \t ????????: %u \n", g->cs);
}

int main()
{
    setlocale(LC_ALL, "rus");
    FILE* file = fopen("rks.dat", "r+b");
    assert(file);
    const char idef[] = {0x0A, 'G', 'E', '\0'}; // ?????? ??????????????
    char buf[4] = {0}; // ?????? ??? ??????? 4 ???? ?????????
    int count = 0; // ????? ?????????
    char mesSize[4] = {0}; // ?????? ??? ???????????
    unsigned char mes[173] = {0}; // ?????? ???????? ?????????
    mes[0] = 'G';
    mes[1] = 'E';

    // ??????? ????????? ? ?????? ???????????????

    fread(buf, 1, 2, file);
    while(fread(buf + 2, 1, 1, file) > 0) // ???? ?? ????? ?????
    {
        if (strcmp(buf, idef) == 0)
            count++;
        for(int i = 0; i < 3; i++)
            buf[i] = buf[i + 1];
    }
    printf("????? ?????????: %d \n\n", count);

    fseek(file, 0, SEEK_SET); // ???????????? ? ?????? ?????
    count = 0;
    fseek(file, 2, SEEK_SET);
    fread(buf, 1, 2, file);
    while (fread(buf + 2, 1, 1, file) > 0)
    {
        if (strcmp(buf, idef) == 0) // ???? ??????? ????????? ? ?????????? ???????????????
        {
            count++;
            fread(mesSize, 1, 3, file); // ????????? ??????????
            long size = strtol(mesSize, NULL, 16); // ??????????? ??????? ?????????
            dataSize s = (size == 168) ? REQOPT_DATA2 : (size == 160) ? REQOPT_DATA1 : (size == 123) ? REQ_DATA : WRONG_DATA;
            if (s == REQOPT_DATA2) // ???? ??????? ????????? ???????? 168 ????
            {
                GPSEphem3 g;
                fread((void*)&g, 1, 168, file);
                if (!IS_OK(g))
                    continue;
                mes[2] = '0';
                mes[3] = 'A';
                mes[4] = '8';
                memcpy(mes + 5, (void*)&g, 168);
                printf("%d. ", count);
                printGPSEphem3(&g);
                printf("\t\t\t ?????????????: %u\n\n", cs(mes, 172));
            }
            else
            if (s == REQOPT_DATA1) // ???? ??????? ????????? ???????? 160 ????
            {
                GPSEphem2 g;
                fread((void*)&g, 1, 160, file);
                if (!IS_OK(g))
                    continue;
                mes[2] = '0';
                mes[3] = 'A';
                mes[4] = '0';
                memcpy(mes + 5, (void*)&g, 160);
                printf("%d. ", count);
                printGPSEphem2(&g);
                printf("\t\t\t ?????????????: %u\n\n", cs(mes, 164));
            }
            else
            if (s == REQ_DATA) // ???? ??????? ????????? ???????? 123 ?????
            {
                GPSEphem1 g;
                fread((void*)&g, 1, 123, file);
                if (!IS_OK(g))
                    continue;
                mes[2] = '0';
                mes[3] = '7';
                mes[4] = 'B';
                memcpy(mes + 5, (void*)&g, 123);
                printf("%d. ", count);
                printGPSEphem1(&g);
                printf("\t\t\t ?????????????: %u\n\n", cs(mes, 127));
            }
            else
            {
                printf("%d. ????????? ????????? ???????\n\n", count);
                continue;
            }
        }
        for(int i = 0; i < 3; i++)
            buf[i] = buf[i + 1];
    }
    return 0;
}
