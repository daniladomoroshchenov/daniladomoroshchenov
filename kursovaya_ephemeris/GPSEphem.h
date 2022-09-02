#pragma pack(push,1)
#define GPSEphem_H
#include <stdint.h>

typedef enum {REQ_DATA, REQOPT_DATA1, REQOPT_DATA2, WRONG_DATA} dataSize;

typedef struct GPSEphemeris1
{
    struct GpsEphReqData1
    {
    uint8_t sv;
    uint32_t tow;
    uint8_t flags;
    int16_t iodc;
    int32_t toc;
    int8_t ura;
    uint8_t healthS;
    int16_t wn;
    float tgd;
    float af2;
    float af1;
    float af0;
    int32_t toe;
    int16_t iode;
    double rootA;
    double ecc;
    double m0;
    double omega0;
    double inc0;
    double argPer;
    float deln;
    float omegaDot;
    float incDot;
    float crc;
    float crs;
    float cuc;
    float cus;
    float cic;
    float cis;
    } req; // Required data
    uint8_t cs;
} GPSEphem1;

typedef struct GPSEphemeris2
{
    struct GpsEphReqData2
    {
        uint8_t sv;
        uint32_t tow;
        uint8_t flags;
        int16_t iodc;
        int32_t toc;
        int8_t ura;
        uint8_t healthS;
        int16_t wn;
        float tgd;
        float af2;
        float af1;
        float af0;
        int32_t toe;
        int16_t iode;
        double rootA;
        double ecc;
        double m0;
        double omega0;
        double inc0;
        double argPer;
        float deln;
        float omegaDot;
        float incDot;
        float crc;
        float crs;
        float cuc;
        float cus;
        float cic;
        float cis;
    } req; // Required data
    struct GpsEphOptData2
    {
        uint8_t navType;
        int32_t lTope;
        int32_t lTopc;
        double dADot;
        float fDelnDot;
        int8_t cURAoe;
        int8_t cURAoc;
        int8_t cURAoc1;
        int8_t cURAoc2;
        struct GpsEphCnavIsc2 {
        float fIscL1CA;
        float fIscL2C;
        float fIscL5I5;
        float fIscL5Q5;
    }isc;
    float DAf0;
    } opt; // Optional data
    uint8_t cs;
} GPSEphem2;

typedef struct GPSEphemeris3
{
    struct GpsEphReqData3
    {
        uint8_t sv;
        uint32_t tow;
        uint8_t flags;
        int16_t iodc;
        int32_t toc;
        int8_t ura;
        uint8_t healthS;
        int16_t wn;
        float tgd;
        float af2;
        float af1;
        float af0;
        int32_t toe;
        int16_t iode;
        double rootA;
        double ecc;
        double m0;
        double omega0;
        double inc0;
        double argPer;
        float deln;
        float omegaDot;
        float incDot;
        float crc;
        float crs;
        float cuc;
        float cus;
        float cic;
        float cis;
    } req; // Required data
    struct GpsEphOptData3
    {
        uint8_t navType;
        int32_t lTope;
        int32_t lTopc;
        double dADot;
        float fDelnDot;
        int8_t cURAoe;
        int8_t cURAoc;
        int8_t cURAoc1;
        int8_t cURAoc2;
        union
        {
            struct GpsEphCnavIsc3
            {
                float fIscL1CA;
                float fIscL2C;
                float fIscL5I5;
                float fIscL5Q5;
            } Isc1;
            struct GpsEphCnav2Isc3
            {
                float fIscL1CP;
                float fIscL1CD;
            } Isc2;
        } isc;
        float DAf0;
    } opt; // Optional data
    uint8_t cs;
} GPSEphem3;

#pragma pack(pop)
