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

// считывание сообщений длинной 168 байт

void printGPSEphem3(GPSEphem3* g) {
    printf("Эфермиды GPS (Required data + Optional data(big):\n");
    printf("\t %u %u %u \n", g->req.sv, g->req.tow, g->req.flags);
    printf("\t %d %d %d \n", g->req.iodc, g->req.toc, g->req.ura);
    printf("\t %u %d %e \n", g->req.healthS, g->req.wn, g->req.tgd);
    printf("\t %e %e %e \n", g->req.af2, g->req.af1, g->req.af0);
    printf("\t %d %d %e \n", g->req.toe, g->req.iode, g->req.rootA);
    printf("\t %e %e %e \n", g->req.ecc, g->req.m0, g->req.omega0);
    printf("\t %e %e %e \n", g->req.inc0, g->req.argPer, g->req.deln);
    printf("\t %e %e %e \n", g->req.omegaDot, g->req.incDot, g->req.crc);
    printf("\t %e %e %e %e \n", g->req.crs, g->req.cuc, g->req.cic, g->req.cis);
    printf("\t %u %d %d \n", g->opt.navType, g->opt.lTope, g->opt.lTopc);
    printf("\t %e %e %d \n", g->opt.dADot, g->opt.fDelnDot, g->opt.cURAoe);
    printf("\t %d %d %d \n", g->opt.cURAoc, g->opt.cURAoc1, g->opt.cURAoc2);
    printf("\t %e %e \n", g->opt.isc.Isc1.fIscL1CA, g->opt.isc.Isc1.fIscL2C);
    printf("\t %e %e \n", g->opt.isc.Isc1.fIscL5I5, g->opt.isc.Isc1.fIscL5Q5);
    printf("\t %e %e %e \n", g->opt.isc.Isc2.fIscL1CP, g->opt.isc.Isc2.fIscL1CD, g->opt.DAf0);
    printf("Контрольная сумма: \t Заданная: %u \n", g->cs);
}

// считывание сообщений длинной 160 байт

void printGPSEphem2(GPSEphem2* g) {
printf("Эфермиды GPS (Required data + Optional data(small)): \n");
    printf("\t %u %u %u \n", g->req.sv, g->req.tow, g->req.flags);
    printf("\t %d %d %d \n", g->req.iodc, g->req.toc, g->req.ura);
    printf("\t %u %d %e \n", g->req.healthS, g->req.wn, g->req.tgd);
    printf("\t %e %e %e \n", g->req.af2, g->req.af1, g->req.af0);
    printf("\t %d %d %e \n", g->req.toe, g->req.iode, g->req.rootA);
    printf("\t %e %e %e \n", g->req.ecc, g->req.m0, g->req.omega0);
    printf("\t %e %e %e \n", g->req.inc0, g->req.argPer, g->req.deln);
    printf("\t %e %e %e \n", g->req.omegaDot, g->req.incDot, g->req.crc);
    printf("\t %e %e %e %e \n", g->req.crs, g->req.cuc, g->req.cic, g->req.cis);
    printf("\t %u %d %d \n", g->opt.navType, g->opt.lTope, g->opt.lTopc);
    printf("\t %e %e %d \n", g->opt.dADot, g->opt.fDelnDot, g->opt.cURAoe);
    printf("\t %d %d %d \n", g->opt.cURAoc, g->opt.cURAoc1, g->opt.cURAoc2);
    printf("\t %e %e \n", g->opt.isc.fIscL1CA, g->opt.isc.fIscL2C);
    printf("\t %e %e \n", g->opt.isc.fIscL5I5, g->opt.isc.fIscL5Q5);
    printf("Контрольная сумма: \t Заданная: %u \n", g->cs);
}

// считывание сообщений длинной 123 байт

void printGPSEphem1(GPSEphem1* g) {
    printf("Эфемериды GPS (Only required data):\n");
    printf("\t %u %u %u \n", g->req.sv, g->req.tow, g->req.flags);
    printf("\t %d %d %d \n", g->req.iodc, g->req.toc, g->req.ura);
    printf("\t %u %d %e \n", g->req.healthS, g->req.wn, g->req.tgd);
    printf("\t %e %e %e \n", g->req.af2, g->req.af1, g->req.af0);
    printf("\t %d %d %e \n", g->req.toe, g->req.iode, g->req.rootA);
    printf("\t %e %e %e \n", g->req.ecc, g->req.m0, g->req.omega0);
    printf("\t %e %e %e \n", g->req.inc0, g->req.argPer, g->req.deln);
    printf("\t %e %e %e \n", g->req.omegaDot, g->req.incDot, g->req.crc);
    printf("\t %e %e %e %e \n", g->req.crs, g->req.cuc, g->req.cic, g->req.cis);
    printf("Контрольная сумма: \t Заданная: %u \n", g->cs);
}

int main() {
    setlocale(LC_ALL, "rus");
    FILE* file = fopen("rks.dat", "r+b");
    assert(file);
    const char idef[] = {0x0A, 'G', 'E', '\0'}; // щаблон идентификатора
    char buf[4] = {0}; // массив для текущих 4 байт сообщения
    int count = 0; // номер сообщения
    char mesSize[4] = {0}; // массив для дескриптора
    unsigned char mes[173] = {0}; // массив хранения сообщения
    mes[0] = 'G';
    mes[1] = 'E';
    // подсчет сообщений с нужным идентификатором
    fread(buf, 1, 2, file);
    while(fread(buf + 2, 1, 1, file) > 0) { // пока не конец файла
        if (strcmp(buf, idef) == 0)
        count++;
        for(int i = 0; i < 3; i++)
        buf[i] = buf[i + 1];
    }
    printf("Всего сообщений: %d \n\n", count);
    fseek(file, 0, SEEK_SET); // возвращаемся в начало файда
    count = 0;
    fseek(file, 2, SEEK_SET);
    fread(buf, 1, 2, file);
    while (fread(buf + 2, 1, 1, file) > 0) {
        if (strcmp(buf, idef) == 0) { // Если найдено сообщение с подходящим идентификатором
            count++;
            fread(mesSize, 1, 3, file); // считываем дескриптор
            long size = strtol(mesSize, NULL, 16); // определение размера сообщения
            dataSize s = (size == 168) ? REQOPT_DATA2 : (size == 160) ?
            REQOPT_DATA1 : (size == 123) ? REQ_DATA : WRONG_DATA;
            if (s == REQOPT_DATA2) {// если нашлось сообщение размером 168 байт
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
                printf("\t\t\t Пересчитанная: %u\n\n", cs(mes, 172));
            }
            else
            if (s == REQOPT_DATA1) { // если нашлось сообщение размером 160 байт
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
                printf("\t\t\t Пересчитанная: %u\n\n", cs(mes, 164));
            } else {
                if (s == REQ_DATA) { // если нашлось сообщение размером 123 байта
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
                    printf("\t\t\t Пересчитанная: %u\n\n", cs(mes, 127));
                } else {
                    printf("%d. Сообщение неверного размера\n\n", count);
                    continue;
                }
            }
        }
        for(int i = 0; i < 3; i++)
        buf[i] = buf[i + 1];
    }
    return 0;
}
