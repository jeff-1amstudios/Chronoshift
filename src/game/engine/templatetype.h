/**
 * @file
 *
 * @author OmniBlade
 * @author CCHyper
 *
 * @brief Class containing information about terrain templates.
 *
 * @copyright Redalert++ is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#pragma once

#ifndef TEMPLATETYPE_H
#define TEMPLATETYPE_H

#include "always.h"
#include "heap.h"
#include "land.h"
#include "objecttype.h"
#include "theater.h"

class NoInit;

enum TemplateType
{
    TEMPLATE_NONE = -1,
    TEMPLATE_FIRST = 0,
    TEMPLATE_CLEAR = 0,
    TEMPLATE_WATER = 1,
    TEMPLATE_WATER2 = 2,
    TEMPLATE_SHORE01 = 3,
    TEMPLATE_SHORE02 = 4,
    TEMPLATE_SHORE03 = 5,
    TEMPLATE_SHORE04 = 6,
    TEMPLATE_SHORE05 = 7,
    TEMPLATE_SHORE06 = 8,
    TEMPLATE_SHORE07 = 9,
    TEMPLATE_SHORE08 = 10,
    TEMPLATE_SHORE09 = 11,
    TEMPLATE_SHORE10 = 12,
    TEMPLATE_SHORE11 = 13,
    TEMPLATE_SHORE12 = 14,
    TEMPLATE_SHORE13 = 15,
    TEMPLATE_SHORE14 = 16,
    TEMPLATE_SHORE15 = 17,
    TEMPLATE_SHORE16 = 18,
    TEMPLATE_SHORE17 = 19,
    TEMPLATE_SHORE18 = 20,
    TEMPLATE_SHORE19 = 21,
    TEMPLATE_SHORE20 = 22,
    TEMPLATE_SHORE21 = 23,
    TEMPLATE_SHORE22 = 24,
    TEMPLATE_SHORE23 = 25,
    TEMPLATE_SHORE24 = 26,
    TEMPLATE_SHORE25 = 27,
    TEMPLATE_SHORE26 = 28,
    TEMPLATE_SHORE27 = 29,
    TEMPLATE_SHORE28 = 30,
    TEMPLATE_SHORE29 = 31,
    TEMPLATE_SHORE30 = 32,
    TEMPLATE_SHORE31 = 33,
    TEMPLATE_SHORE32 = 34,
    TEMPLATE_SHORE33 = 35,
    TEMPLATE_SHORE34 = 36,
    TEMPLATE_SHORE35 = 37,
    TEMPLATE_SHORE36 = 38,
    TEMPLATE_SHORE37 = 39,
    TEMPLATE_SHORE38 = 40,
    TEMPLATE_SHORE39 = 41,
    TEMPLATE_SHORE40 = 42,
    TEMPLATE_SHORE41 = 43,
    TEMPLATE_SHORE42 = 44,
    TEMPLATE_SHORE43 = 45,
    TEMPLATE_SHORE44 = 46,
    TEMPLATE_SHORE45 = 47,
    TEMPLATE_SHORE46 = 48,
    TEMPLATE_SHORE47 = 49,
    TEMPLATE_SHORE48 = 50,
    TEMPLATE_SHORE49 = 51,
    TEMPLATE_SHORE50 = 52,
    TEMPLATE_SHORE51 = 53,
    TEMPLATE_SHORE52 = 54,
    TEMPLATE_SHORE53 = 55,
    TEMPLATE_SHORE54 = 56,
    TEMPLATE_SHORE55 = 57,
    TEMPLATE_SHORE56 = 58,
    TEMPLATE_SHORECLIFF01 = 59,
    TEMPLATE_SHORECLIFF02 = 60,
    TEMPLATE_SHORECLIFF03 = 61,
    TEMPLATE_SHORECLIFF04 = 62,
    TEMPLATE_SHORECLIFF05 = 63,
    TEMPLATE_SHORECLIFF06 = 64,
    TEMPLATE_SHORECLIFF07 = 65,
    TEMPLATE_SHORECLIFF08 = 66,
    TEMPLATE_SHORECLIFF09 = 67,
    TEMPLATE_SHORECLIFF10 = 68,
    TEMPLATE_SHORECLIFF11 = 69,
    TEMPLATE_SHORECLIFF12 = 70,
    TEMPLATE_SHORECLIFF13 = 71,
    TEMPLATE_SHORECLIFF14 = 72,
    TEMPLATE_SHORECLIFF15 = 73,
    TEMPLATE_SHORECLIFF16 = 74,
    TEMPLATE_SHORECLIFF17 = 75,
    TEMPLATE_SHORECLIFF18 = 76,
    TEMPLATE_SHORECLIFF19 = 77,
    TEMPLATE_SHORECLIFF20 = 78,
    TEMPLATE_SHORECLIFF21 = 79,
    TEMPLATE_SHORECLIFF22 = 80,
    TEMPLATE_SHORECLIFF23 = 81,
    TEMPLATE_SHORECLIFF24 = 82,
    TEMPLATE_SHORECLIFF25 = 83,
    TEMPLATE_SHORECLIFF26 = 84,
    TEMPLATE_SHORECLIFF27 = 85,
    TEMPLATE_SHORECLIFF28 = 86,
    TEMPLATE_SHORECLIFF29 = 87,
    TEMPLATE_SHORECLIFF30 = 88,
    TEMPLATE_SHORECLIFF31 = 89,
    TEMPLATE_SHORECLIFF32 = 90,
    TEMPLATE_SHORECLIFF33 = 91,
    TEMPLATE_SHORECLIFF34 = 92,
    TEMPLATE_SHORECLIFF35 = 93,
    TEMPLATE_SHORECLIFF36 = 94,
    TEMPLATE_SHORECLIFF37 = 95,
    TEMPLATE_SHORECLIFF38 = 96,
    TEMPLATE_BOULDER1 = 97,
    TEMPLATE_BOULDER2 = 98,
    TEMPLATE_BOULDER3 = 99,
    TEMPLATE_BOULDER4 = 100,
    TEMPLATE_BOULDER5 = 101,
    TEMPLATE_BOULDER6 = 102,
    TEMPLATE_PATCH01 = 103,
    TEMPLATE_PATCH02 = 104,
    TEMPLATE_PATCH03 = 105,
    TEMPLATE_PATCH04 = 106,
    TEMPLATE_PATCH07 = 107,
    TEMPLATE_PATCH08 = 108,
    TEMPLATE_PATCH13 = 109,
    TEMPLATE_PATCH14 = 110,
    TEMPLATE_PATCH15 = 111,
    TEMPLATE_RIVER01 = 112,
    TEMPLATE_RIVER02 = 113,
    TEMPLATE_RIVER03 = 114,
    TEMPLATE_RIVER04 = 115,
    TEMPLATE_RIVER05 = 116,
    TEMPLATE_RIVER06 = 117,
    TEMPLATE_RIVER07 = 118,
    TEMPLATE_RIVER08 = 119,
    TEMPLATE_RIVER09 = 120,
    TEMPLATE_RIVER10 = 121,
    TEMPLATE_RIVER11 = 122,
    TEMPLATE_RIVER12 = 123,
    TEMPLATE_RIVER13 = 124,
    TEMPLATE_FALLS1 = 125,
    TEMPLATE_FALLS1A = 126,
    TEMPLATE_FALLS2 = 127,
    TEMPLATE_FALLS2A = 128,
    TEMPLATE_FORD1 = 129,
    TEMPLATE_FORD2 = 130,
    TEMPLATE_BRIDGE1 = 131,
    TEMPLATE_BRIDGE1D = 132,
    TEMPLATE_BRIDGE2 = 133,
    TEMPLATE_BRIDGE2D = 134,
    TEMPLATE_SLOPE01 = 135,
    TEMPLATE_SLOPE02 = 136,
    TEMPLATE_SLOPE03 = 137,
    TEMPLATE_SLOPE04 = 138,
    TEMPLATE_SLOPE05 = 139,
    TEMPLATE_SLOPE06 = 140,
    TEMPLATE_SLOPE07 = 141,
    TEMPLATE_SLOPE08 = 142,
    TEMPLATE_SLOPE09 = 143,
    TEMPLATE_SLOPE10 = 144,
    TEMPLATE_SLOPE11 = 145,
    TEMPLATE_SLOPE12 = 146,
    TEMPLATE_SLOPE13 = 147,
    TEMPLATE_SLOPE14 = 148,
    TEMPLATE_SLOPE15 = 149,
    TEMPLATE_SLOPE16 = 150,
    TEMPLATE_SLOPE17 = 151,
    TEMPLATE_SLOPE18 = 152,
    TEMPLATE_SLOPE19 = 153,
    TEMPLATE_SLOPE20 = 154,
    TEMPLATE_SLOPE21 = 155,
    TEMPLATE_SLOPE22 = 156,
    TEMPLATE_SLOPE23 = 157,
    TEMPLATE_SLOPE24 = 158,
    TEMPLATE_SLOPE25 = 159,
    TEMPLATE_SLOPE26 = 160,
    TEMPLATE_SLOPE27 = 161,
    TEMPLATE_SLOPE28 = 162,
    TEMPLATE_SLOPE29 = 163,
    TEMPLATE_SLOPE30 = 164,
    TEMPLATE_SLOPE31 = 165,
    TEMPLATE_SLOPE32 = 166,
    TEMPLATE_SLOPE33 = 167,
    TEMPLATE_SLOPE34 = 168,
    TEMPLATE_SLOPE35 = 169,
    TEMPLATE_SLOPE36 = 170,
    TEMPLATE_SLOPE37 = 171,
    TEMPLATE_SLOPE38 = 172,
    TEMPLATE_ROAD01 = 173,
    TEMPLATE_ROAD02 = 174,
    TEMPLATE_ROAD03 = 175,
    TEMPLATE_ROAD04 = 176,
    TEMPLATE_ROAD05 = 177,
    TEMPLATE_ROAD06 = 178,
    TEMPLATE_ROAD07 = 179,
    TEMPLATE_ROAD08 = 180,
    TEMPLATE_ROAD09 = 181,
    TEMPLATE_ROAD10 = 182,
    TEMPLATE_ROAD11 = 183,
    TEMPLATE_ROAD12 = 184,
    TEMPLATE_ROAD13 = 185,
    TEMPLATE_ROAD14 = 186,
    TEMPLATE_ROAD15 = 187,
    TEMPLATE_ROAD16 = 188,
    TEMPLATE_ROAD17 = 189,
    TEMPLATE_ROAD18 = 190,
    TEMPLATE_ROAD19 = 191,
    TEMPLATE_ROAD20 = 192,
    TEMPLATE_ROAD21 = 193,
    TEMPLATE_ROAD22 = 194,
    TEMPLATE_ROAD23 = 195,
    TEMPLATE_ROAD24 = 196,
    TEMPLATE_ROAD25 = 197,
    TEMPLATE_ROAD26 = 198,
    TEMPLATE_ROAD27 = 199,
    TEMPLATE_ROAD28 = 200,
    TEMPLATE_ROAD29 = 201,
    TEMPLATE_ROAD30 = 202,
    TEMPLATE_ROAD31 = 203,
    TEMPLATE_ROAD32 = 204,
    TEMPLATE_ROAD33 = 205,
    TEMPLATE_ROAD34 = 206,
    TEMPLATE_ROAD35 = 207,
    TEMPLATE_ROAD36 = 208,
    TEMPLATE_ROAD37 = 209,
    TEMPLATE_ROAD38 = 210,
    TEMPLATE_ROAD39 = 211,
    TEMPLATE_ROAD40 = 212,
    TEMPLATE_ROAD41 = 213,
    TEMPLATE_ROAD42 = 214,
    TEMPLATE_ROAD43 = 215,
    TEMPLATE_ROUGH01 = 216,
    TEMPLATE_ROUGH02 = 217,
    TEMPLATE_ROUGH03 = 218,
    TEMPLATE_ROUGH04 = 219,
    TEMPLATE_ROUGH05 = 220,
    TEMPLATE_ROUGH06 = 221,
    TEMPLATE_ROUGH07 = 222,
    TEMPLATE_ROUGH08 = 223,
    TEMPLATE_ROUGH09 = 224,
    TEMPLATE_ROUGH10 = 225,
    TEMPLATE_ROUGH11 = 226,
    TEMPLATE_ROAD44 = 227,
    TEMPLATE_ROAD45 = 228,
    TEMPLATE_RIVER14 = 229,
    TEMPLATE_RIVER15 = 230,
    TEMPLATE_RIVERCLIFF01 = 231,
    TEMPLATE_RIVERCLIFF02 = 232,
    TEMPLATE_RIVERCLIFF03 = 233,
    TEMPLATE_RIVERCLIFF04 = 234,
    TEMPLATE_BRIDGE1A = 235,
    TEMPLATE_BRIDGE1B = 236,
    TEMPLATE_BRIDGE1C = 237,
    TEMPLATE_BRIDGE2A = 238,
    TEMPLATE_BRIDGE2B = 239,
    TEMPLATE_BRIDGE2C = 240,
    TEMPLATE_BRIDGE3A = 241,
    TEMPLATE_BRIDGE3B = 242,
    TEMPLATE_BRIDGE3C = 243,
    TEMPLATE_BRIDGE3D = 244,
    TEMPLATE_BRIDGE3E = 245,
    TEMPLATE_BRIDGE3F = 246,
    TEMPLATE_F01 = 247,
    TEMPLATE_F02 = 248,
    TEMPLATE_F03 = 249,
    TEMPLATE_F04 = 250,
    TEMPLATE_F05 = 251,
    TEMPLATE_F06 = 252,
    TEMPLATE_ARRO0001 = 253,
    TEMPLATE_ARRO0002 = 254,
    TEMPLATE_ARRO0003 = 255,
    TEMPLATE_ARRO0004 = 256,
    TEMPLATE_ARRO0005 = 257,
    TEMPLATE_ARRO0006 = 258,
    TEMPLATE_ARRO0007 = 259,
    TEMPLATE_ARRO0008 = 260,
    TEMPLATE_ARRO0009 = 261,
    TEMPLATE_ARRO0010 = 262,
    TEMPLATE_ARRO0011 = 263,
    TEMPLATE_ARRO0012 = 264,
    TEMPLATE_ARRO0013 = 265,
    TEMPLATE_ARRO0014 = 266,
    TEMPLATE_ARRO0015 = 267,
    TEMPLATE_FLOR0001 = 268,
    TEMPLATE_FLOR0002 = 269,
    TEMPLATE_FLOR0003 = 270,
    TEMPLATE_FLOR0004 = 271,
    TEMPLATE_FLOR0005 = 272,
    TEMPLATE_FLOR0006 = 273,
    TEMPLATE_FLOR0007 = 274,
    TEMPLATE_GFLR0001 = 275,
    TEMPLATE_GFLR0002 = 276,
    TEMPLATE_GFLR0003 = 277,
    TEMPLATE_GFLR0004 = 278,
    TEMPLATE_GFLR0005 = 279,
    TEMPLATE_GSTR0001 = 280,
    TEMPLATE_GSTR0002 = 281,
    TEMPLATE_GSTR0003 = 282,
    TEMPLATE_GSTR0004 = 283,
    TEMPLATE_GSTR0005 = 284,
    TEMPLATE_GSTR0006 = 285,
    TEMPLATE_GSTR0007 = 286,
    TEMPLATE_GSTR0008 = 287,
    TEMPLATE_GSTR0009 = 288,
    TEMPLATE_GSTR0010 = 289,
    TEMPLATE_GSTR0011 = 290,
    TEMPLATE_LWAL0001 = 291,
    TEMPLATE_LWAL0002 = 292,
    TEMPLATE_LWAL0003 = 293,
    TEMPLATE_LWAL0004 = 294,
    TEMPLATE_LWAL0005 = 295,
    TEMPLATE_LWAL0006 = 296,
    TEMPLATE_LWAL0007 = 297,
    TEMPLATE_LWAL0008 = 298,
    TEMPLATE_LWAL0009 = 299,
    TEMPLATE_LWAL0010 = 300,
    TEMPLATE_LWAL0011 = 301,
    TEMPLATE_LWAL0012 = 302,
    TEMPLATE_LWAL0013 = 303,
    TEMPLATE_LWAL0014 = 304,
    TEMPLATE_LWAL0015 = 305,
    TEMPLATE_LWAL0016 = 306,
    TEMPLATE_LWAL0017 = 307,
    TEMPLATE_LWAL0018 = 308,
    TEMPLATE_LWAL0019 = 309,
    TEMPLATE_LWAL0020 = 310,
    TEMPLATE_LWAL0021 = 311,
    TEMPLATE_LWAL0022 = 312,
    TEMPLATE_LWAL0023 = 313,
    TEMPLATE_LWAL0024 = 314,
    TEMPLATE_LWAL0025 = 315,
    TEMPLATE_LWAL0026 = 316,
    TEMPLATE_LWAL0027 = 317,
    TEMPLATE_STRP0001 = 318,
    TEMPLATE_STRP0002 = 319,
    TEMPLATE_STRP0003 = 320,
    TEMPLATE_STRP0004 = 321,
    TEMPLATE_STRP0005 = 322,
    TEMPLATE_STRP0006 = 323,
    TEMPLATE_STRP0007 = 324,
    TEMPLATE_STRP0008 = 325,
    TEMPLATE_STRP0009 = 326,
    TEMPLATE_STRP0010 = 327,
    TEMPLATE_STRP0011 = 328,
    TEMPLATE_WALL0001 = 329,
    TEMPLATE_WALL0002 = 330,
    TEMPLATE_WALL0003 = 331,
    TEMPLATE_WALL0004 = 332,
    TEMPLATE_WALL0005 = 333,
    TEMPLATE_WALL0006 = 334,
    TEMPLATE_WALL0007 = 335,
    TEMPLATE_WALL0008 = 336,
    TEMPLATE_WALL0009 = 337,
    TEMPLATE_WALL0010 = 338,
    TEMPLATE_WALL0011 = 339,
    TEMPLATE_WALL0012 = 340,
    TEMPLATE_WALL0013 = 341,
    TEMPLATE_WALL0014 = 342,
    TEMPLATE_WALL0015 = 343,
    TEMPLATE_WALL0016 = 344,
    TEMPLATE_WALL0017 = 345,
    TEMPLATE_WALL0018 = 346,
    TEMPLATE_WALL0019 = 347,
    TEMPLATE_WALL0020 = 348,
    TEMPLATE_WALL0021 = 349,
    TEMPLATE_WALL0022 = 350,
    TEMPLATE_WALL0023 = 351,
    TEMPLATE_WALL0024 = 352,
    TEMPLATE_WALL0025 = 353,
    TEMPLATE_WALL0026 = 354,
    TEMPLATE_WALL0027 = 355,
    TEMPLATE_WALL0028 = 356,
    TEMPLATE_WALL0029 = 357,
    TEMPLATE_WALL0030 = 358,
    TEMPLATE_WALL0031 = 359,
    TEMPLATE_WALL0032 = 360,
    TEMPLATE_WALL0033 = 361,
    TEMPLATE_WALL0034 = 362,
    TEMPLATE_WALL0035 = 363,
    TEMPLATE_WALL0036 = 364,
    TEMPLATE_WALL0037 = 365,
    TEMPLATE_WALL0038 = 366,
    TEMPLATE_WALL0039 = 367,
    TEMPLATE_WALL0040 = 368,
    TEMPLATE_WALL0041 = 369,
    TEMPLATE_WALL0042 = 370,
    TEMPLATE_WALL0043 = 371,
    TEMPLATE_WALL0044 = 372,
    TEMPLATE_WALL0045 = 373,
    TEMPLATE_WALL0046 = 374,
    TEMPLATE_WALL0047 = 375,
    TEMPLATE_WALL0048 = 376,
    TEMPLATE_WALL0049 = 377,
    TEMPLATE_BRIDGE1H = 378,
    TEMPLATE_BRIDGE2H = 379,
    TEMPLATE_BRIDGE1AX = 380,
    TEMPLATE_BRIDGE2AX = 381,
    TEMPLATE_BRIDGE1X = 382,
    TEMPLATE_BRIDGE2X = 383,
    TEMPLATE_XTRA0001 = 384,
    TEMPLATE_XTRA0002 = 385,
    TEMPLATE_XTRA0003 = 386,
    TEMPLATE_XTRA0004 = 387,
    TEMPLATE_XTRA0005 = 388,
    TEMPLATE_XTRA0006 = 389,
    TEMPLATE_XTRA0007 = 390,
    TEMPLATE_XTRA0008 = 391,
    TEMPLATE_XTRA0009 = 392,
    TEMPLATE_XTRA0010 = 393,
    TEMPLATE_XTRA0011 = 394,
    TEMPLATE_XTRA0012 = 395,
    TEMPLATE_XTRA0013 = 396,
    TEMPLATE_XTRA0014 = 397,
    TEMPLATE_XTRA0015 = 398,
    TEMPLATE_XTRA0016 = 399,
    TEMPLATE_ANTHILL = 400,
    TEMPLATE_LAST = 400,
    TEMPLATE_COUNT,
};

DEFINE_ENUMERATION_OPERATORS(TemplateType);

class TemplateTypeClass : public ObjectTypeClass
{
public:
    TemplateTypeClass(TemplateType type, int theater, const char *name, int uiname);
    TemplateTypeClass(TemplateTypeClass const &that);
    TemplateTypeClass(const NoInitClass &noinit) : ObjectTypeClass(noinit) {}
    ~TemplateTypeClass() {}

    void *operator new(size_t size);
    void *operator new(size_t size, void *ptr) { return ptr; }
    void operator delete(void *ptr);
    #ifndef COMPILER_WATCOM // Watcom doesn't like this, MSVC/GCC does.
        void operator delete(void *ptr, void *place) {}
    #endif

    virtual uint32_t Coord_Fixup(uint32_t coord) const override;
    virtual BOOL Create_And_Place(int16_t cellnum, HousesType house = HOUSES_NONE) const override;
    virtual ObjectClass *Create_One_Of(HouseClass *house) const override;
    virtual const int16_t *Occupy_List(BOOL a1 = false) const override;

    LandType Land_Type(int sub_icon) const;
    void Code_Pointers() {}
    void Decode_Pointers() {}

    int Get_Width() { return Width; }
    int Get_Height() { return Height; }

    static TemplateType From_Name(const char *name);
    static const char *Name_From(TemplateType tem);
    static TemplateTypeClass *As_Pointer(TemplateType tem);
    static TemplateTypeClass &As_Reference(TemplateType tem);
    static void Init_Heap();
    static void One_Time() {}
    static void Init(TheaterType theater);
    static void MapEditor_418A1C();

private:
    TemplateType Type; 
    int Theater;
    int Width;
    int Height;
};

#ifndef RAPP_STANDALONE
#include "hooker.h"
extern TFixedIHeapClass<TemplateTypeClass> &TemplateTypes;
#else
extern TFixedIHeapClass<TemplateTypeClass> TemplateTypes;
#endif

#endif // TEMPLATETYPE_H
