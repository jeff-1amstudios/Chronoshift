/**
 * @file
 *
 * @author OmniBlade
 * @author CCHyper
 *
 * @brief Class containing information about terrain overlays.
 *
 * @copyright Chronoshift is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#include "overlaytype.h"
#include "overlaydata.h"
#include "gamefile.h"
#include "coord.h"
#include "drawshape.h"
#include "globals.h"
#include "iomap.h"
#include "lists.h"
#include "mixfile.h"
#include <cstdio>

using std::snprintf;

#ifndef GAME_DLL
TFixedIHeapClass<OverlayTypeClass> g_OverlayTypes;
#endif

OverlayTypeClass::OverlayTypeClass(OverlayType overlay, const char *name, int uiname, LandType land, int damage_levels,
    int strength, BOOL radar_visible, BOOL a8, BOOL legal_target, BOOL crushable, BOOL ore, BOOL high, BOOL theater,
    BOOL wall, BOOL crate) :
    ObjectTypeClass(RTTI_OVERLAYTYPE, overlay, crushable, true, false, legal_target, true, false, false, uiname, name),
    Type(overlay),
    Land(land),
    DamageLevels(damage_levels),
    OverlayStrength(strength),
    Theater(theater),
    Wall(wall),
    High(high),
    Ore(ore),
    Boolean16(a8),
    Crate(crate),
    RadarVisible(radar_visible)
{
}

OverlayTypeClass::OverlayTypeClass(const OverlayTypeClass &that) :
    ObjectTypeClass(that),
    Type(that.Type),
    Land(that.Land),
    DamageLevels(that.DamageLevels),
    OverlayStrength(that.OverlayStrength),
    Theater(that.Theater),
    Wall(that.Wall),
    High(that.High),
    Ore(that.Ore),
    Boolean16(that.Boolean16),
    Crate(that.Crate),
    RadarVisible(that.RadarVisible)
{
}

void *OverlayTypeClass::operator new(size_t size)
{
    DEBUG_ASSERT(size == sizeof(OverlayTypeClass));
    return g_OverlayTypes.Allocate();
}

void OverlayTypeClass::operator delete(void *ptr)
{
    DEBUG_ASSERT(ptr != nullptr);
    g_OverlayTypes.Free(ptr);
}

void OverlayTypeClass::Init_Heap()
{
    // Allocation order MUST match OverlayTypes enum.
    new OverlayTypeClass(OverlaySandbag);
    new OverlayTypeClass(OverlayCyclone);
    new OverlayTypeClass(OverlayBrick);
    new OverlayTypeClass(OverlayBarbwire);
    new OverlayTypeClass(OverlayWood);
    new OverlayTypeClass(OverlayGold1);
    new OverlayTypeClass(OverlayGold2);
    new OverlayTypeClass(OverlayGold3);
    new OverlayTypeClass(OverlayGold4);
    new OverlayTypeClass(OverlayGems1);
    new OverlayTypeClass(OverlayGems2);
    new OverlayTypeClass(OverlayGems3);
    new OverlayTypeClass(OverlayGems4);
    new OverlayTypeClass(OverlayV12);
    new OverlayTypeClass(OverlayV13);
    new OverlayTypeClass(OverlayV14);
    new OverlayTypeClass(OverlayV15);
    new OverlayTypeClass(OverlayV16);
    new OverlayTypeClass(OverlayV17);
    new OverlayTypeClass(OverlayV18);
    new OverlayTypeClass(OverlayFlagSpot);
    new OverlayTypeClass(OverlayWoodCrate);
    new OverlayTypeClass(OverlaySteelCrate);
    new OverlayTypeClass(OverlayFence);
    new OverlayTypeClass(OverlayWaterCrate);
}

OverlayType OverlayTypeClass::From_Name(const char *name)
{
    DEBUG_ASSERT(name != nullptr);

    if (strcasecmp(name, "<none>") == 0 || strcasecmp(name, "none") == 0) {
        return OVERLAY_NONE;
    }

    if (name != nullptr) {
        for (OverlayType overlay = OVERLAY_FIRST; overlay < OVERLAY_COUNT; ++overlay) {
            if (strcasecmp(name, Name_From(overlay)) == 0) {
                return overlay;
            }
        }
    }

    return OVERLAY_NONE;
}

const char *OverlayTypeClass::Name_From(OverlayType overlay)
{
    DEBUG_ASSERT(overlay != OVERLAY_NONE);
    DEBUG_ASSERT(overlay < OVERLAY_COUNT);

    return overlay != OVERLAY_NONE && overlay < OVERLAY_COUNT ? As_Reference(overlay).m_Name : "<none>";
}

void OverlayTypeClass::Init(TheaterType theater)
{
    DEBUG_ASSERT(theater < THEATER_COUNT);
    DEBUG_ASSERT(theater != THEATER_NONE);

    char filename[512];

    if (theater != g_lastTheater) {
        for (OverlayType i = OVERLAY_FIRST; i < OVERLAY_COUNT; ++i) {
            OverlayTypeClass &overlay = As_Reference(i);

            snprintf(filename,
                sizeof(filename),
                "%s.%s",
                overlay.m_Name,
                overlay.Theater ? g_theaters[theater].ext : "shp");
            overlay.m_ImageData = GameFileClass::Retrieve(filename);

            g_isTheaterShape = overlay.Theater;
            overlay.m_RadarIconData = Get_Radar_Icon(overlay.m_ImageData, 0, -1, 3);
            g_isTheaterShape = false;
        }
    }
}

OverlayTypeClass &OverlayTypeClass::As_Reference(OverlayType overlay)
{
    return g_OverlayTypes[overlay];
}

OverlayTypeClass *OverlayTypeClass::As_Pointer(OverlayType overlay)
{
    return overlay < OVERLAY_COUNT && overlay != OVERLAY_NONE ? &g_OverlayTypes[overlay] : nullptr;
}

/**
 * @brief 
 *
 * @address 0x00549CF8 (beta)
 */
void OverlayTypeClass::Prep_For_Add()
{
    for (OverlayType i = OVERLAY_FIRST; i < OVERLAY_COUNT; ++i) {
        OverlayTypeClass *otptr = As_Pointer(i);
        if (otptr != nullptr) {
            if (otptr->m_ImageData != nullptr) {
                if (!otptr->Wall && (!otptr->Ore || i == OVERLAY_GOLD_01 || i == OVERLAY_GEM_01)) {
                    Map.Add_To_List(otptr);
                }
            }
        }
    }
}

coord_t OverlayTypeClass::Coord_Fixup(coord_t coord) const
{
    return Coord_Top_Left(coord);
}

BOOL OverlayTypeClass::Create_And_Place(cell_t cellnum, HousesType house) const
{
    // TODO requires OverlayClass
#ifdef GAME_DLL
    BOOL(*func)(const OverlayTypeClass*, cell_t, HousesType) = reinterpret_cast<BOOL(*)(const OverlayTypeClass*, cell_t, HousesType)>(0x00524A5C);
    return func(this, cellnum, house);
#elif 0
    DEBUG_ASSERT(this != nullptr);

    return new OverlayClass(Type, cellnum, house) != nullptr;
#else
    return false;
#endif
}

ObjectClass *OverlayTypeClass::Create_One_Of(HouseClass *house) const
{
    // TODO requires OverlayClass
#ifdef GAME_DLL
    ObjectClass *(*func)(const OverlayTypeClass*, HouseClass*) = reinterpret_cast<ObjectClass *(*)(const OverlayTypeClass*, HouseClass*)>(0x00524A98);
    return func(this, house);
#elif 0
    DEBUG_ASSERT(this != nullptr);
    DEBUG_ASSERT(house != nullptr);

    return new OverlayClass(Type);
#else
    return nullptr;
#endif
}

const int16_t *OverlayTypeClass::Occupy_List(BOOL a1) const
{
    static const int16_t _simple[] = { 0, LIST_END };

    return _simple;
}

void OverlayTypeClass::Draw_It(int x, int y, int frame) const
{
    if (m_ImageData != nullptr) {
        g_isTheaterShape = Theater;
        CC_Draw_Shape(m_ImageData,
            frame,
            x + Map.Tac_Offset_X() + 12,
            y + Map.Tac_Offset_Y() + 12,
            WINDOW_0,
            SHAPE_GHOST | SHAPE_WIN_REL | SHAPE_CENTER,
            0,
            DisplayClass::UnitShadow);
        g_isTheaterShape = false;
    }
}

uint8_t *OverlayTypeClass::Radar_Icon(int frame) const
{
    if (m_RadarIconData != nullptr) {
        // TODO, correct casting, find out what stuct it is casting to.
        // Each radar icon is 3 x 3 bytes (hence 9 * frame number to get to relevant frame).
        // + 2 appears to account for some kind of header for when the data is generated.
        return (static_cast<uint8_t *>(m_RadarIconData) + 9 * frame + 2);
    }

    return nullptr;
}

#if 0
BOOL OverlayTypeClass::Read_INI(GameINIClass &ini)
{
    if (ObjectTypeClass::Read_INI(ini)) {
        Land = ini.Get_LandType(m_Name, "Land", Land);
        OverlayStrength = ini.Get_Int(m_Name, "Strength", OverlayStrength);
        Wall = ini.Get_BOOL(m_Name, "Wall", Wall);
        High = ini.Get_BOOL(m_Name, "High", High);
        Ore = ini.Get_BOOL(m_Name, "Ore", Ore);
        Crate = ini.Get_BOOL(m_Name, "Crate", Crate);
        DamageLevels = ini.Get_Int(m_Name, "DamageLevels", DamageLevels);
        Theater = ini.Get_BOOL(m_Name, "Theater", Theater);
        CellAnim = ini.Get_AnimType(m_Name, "CellAnim", CellAnim);

        return true;
    }

    return false;
}
#endif
