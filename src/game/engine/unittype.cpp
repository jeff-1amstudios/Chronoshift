/**
 * @file
 *
 * @author CCHyper
 * @author OmniBlade
 *
 * @brief Class holding static info on unit objects.
 *
 * @copyright Chronoshift is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#include "unittype.h"
#include "unitdata.h"
#include "gameini.h"
#include "gamefile.h"
#include "coord.h"
#include "globals.h"
#include "mixfile.h"
#include "shape.h"
#include "iomap.h"
#include <cstdio>
#include <algorithm>

using std::snprintf;

#ifndef GAME_DLL
TFixedIHeapClass<UnitTypeClass> g_UnitTypes;
#endif

/**
 * 0x0056E09C
 */
UnitTypeClass::UnitTypeClass(UnitType type, int uiname, const char *name, AnimType death_anim, RemapType remap,
    int def_fire_coord, int pri_fire_coord_a, int pri_fire_coord_b, int sec_fire_coord_a, int sec_fire_coord_b,
    BOOL crate_goodie, BOOL nominal, BOOL crusher, BOOL harvester, BOOL radar_invisible, BOOL insignificant, BOOL turret, BOOL turret_spins,
    BOOL unk3, BOOL unk4, BOOL largeimage, BOOL is_viceroid, BOOL radarjammer, BOOL mgapgen, int facings, MissionType mission, MissionType alt_mission) :
    TechnoTypeClass(RTTI_UNITTYPE, type, uiname, name, remap, def_fire_coord, pri_fire_coord_a, pri_fire_coord_b,
        sec_fire_coord_a, sec_fire_coord_b, nominal, radar_invisible, true, true, insignificant, false, false, turret, true,
        true, facings, SPEED_TRACK),
    m_CrateGoodie(crate_goodie),
    m_Crusher(crusher),
    m_Harvester(harvester),
    m_TurretSpins(turret_spins),
    m_Bit16(unk3),
    m_Bit32(unk4),
    m_IsLarge(largeimage),
    m_IsViceroid(is_viceroid),
    m_IsRadarJammer(radarjammer),
    m_IsMobileGapGen(mgapgen),
    m_NoMovingFire(false),
    m_Type(type),
    m_UnkMissionA(mission),
    m_UnkMissionB(alt_mission),
    m_ExplosionAnim(death_anim),
    m_UnkInt(0)
{
    m_Speed = SPEED_WHEEL;
}

/**
 * 0x00578DE0
 */
UnitTypeClass::UnitTypeClass(UnitTypeClass const &that) :
    TechnoTypeClass(that),
    m_CrateGoodie(that.m_CrateGoodie),
    m_Crusher(that.m_Crusher),
    m_Harvester(that.m_Harvester),
    m_TurretSpins(that.m_TurretSpins),
    m_Bit16(that.m_Bit16),
    m_Bit32(that.m_Bit32),
    m_IsLarge(that.m_IsLarge),
    m_IsViceroid(that.m_IsViceroid),
    m_IsRadarJammer(that.m_IsRadarJammer),
    m_IsMobileGapGen(that.m_IsMobileGapGen),
    m_NoMovingFire(that.m_NoMovingFire),
    m_Type(that.m_Type),
    m_UnkMissionA(that.m_UnkMissionA),
    m_UnkMissionB(that.m_UnkMissionB),
    m_ExplosionAnim(that.m_ExplosionAnim),
    m_UnkInt(that.m_UnkInt)
{
}

/**
 * 0x0056E290
 */
void *UnitTypeClass::operator new(size_t size)
{
    DEBUG_ASSERT(size == sizeof(UnitTypeClass) && size == g_UnitTypes.Heap_Size());
    return g_UnitTypes.Allocate();
}

/**
 * 0x0056E2A4
 */
void UnitTypeClass::operator delete(void *ptr)
{
    DEBUG_ASSERT(ptr != nullptr);
    g_UnitTypes.Free(ptr);
}

/**
 * Calculate the maximum number of pips at could be displayed over the object.
 *
 * 0x00578CA8
 */
int UnitTypeClass::Max_Pips() const
{
    // TODO, Maybe set these behaviours with bools in future to remove hard coded unit behaviour?
    switch (m_Type) {
        case UNIT_HARVESTER:
            return 7; // Harvester bails.

        case UNIT_MINELAYER:
            return m_Ammo;

        default:
            return Max_Passengers();
    };
}

/**
 * Fetches the width and height of the object.
 *
 * 0x00578C3C
 */
void UnitTypeClass::Dimensions(int &w, int &h) const
{
    w = std::min(m_UnkInt - (m_UnkInt / 4), 48);
    h = std::min(m_UnkInt - (m_UnkInt / 4), 48);
}

/**
 * Creates a UnitClass instance for the specified house and places it at the specified cell.
 *
 * 0x00578B50
 */
BOOL UnitTypeClass::Create_And_Place(cell_t cellnum, HousesType house) const
{
#ifdef GAME_DLL
    BOOL (*func)
    (const UnitTypeClass *, cell_t, HousesType) =
        reinterpret_cast<BOOL (*)(const UnitTypeClass *, cell_t, HousesType)>(0x00578B50);
    return func(this, cellnum, house);
#else
    /*UnitClass *uptr = new UnitClass(m_Type, HOUSES_NONE);

    if (uptr != nullptr) {
        DirType dir = (DirType)Scen.Get_Random_Value(DIR_FIRST, DIR_LAST);
        return uptr->Unlimbo(Cell_To_Coord(cellnum), dir);
    }*/

    return false;
#endif
}

/**
 * Creates a UnitClass for the specified house.
 *
 * 0x00578BD0
 */
ObjectClass *UnitTypeClass::Create_One_Of(HouseClass *house) const
{
#ifdef GAME_DLL
    ObjectClass *(*func)(const UnitTypeClass *, HouseClass *) =
        reinterpret_cast<ObjectClass *(*)(const UnitTypeClass *, HouseClass *)>(0x00578BD0);
    return func(this, house);
#else
    /*DEBUG_ASSERT(house != nullptr);

    return new UnitClass(m_Type, house->What_Type());*/
    return nullptr;
#endif
}

/**
 * Reads an object of this type from an ini file.
 *
 * 0x00578D34
 */
BOOL UnitTypeClass::Read_INI(GameINIClass &ini)
{
    if (TechnoTypeClass::Read_INI(ini)) {
        // TODO Allow setting additional unit parameters, will need some conditional code for units to get correct
        // default with original rules.ini.

        // m_CrateGoodie = ini.Get_Bool(m_Name, "CrateGoodie", m_CrateGoodie);
        // m_Crusher = ini.Get_Bool(m_Name, "Crusher", m_Crusher);
        // m_Harvester = ini.Get_Bool(m_Name, "Harvester", m_Harvester);
        // m_TurretSpins = ini.Get_Bool(m_Name, "TurretSpins", m_TurretSpins);
        // m_IsRadarJammer = ini.Get_Bool(m_Name, "IsRadarJammer", m_IsRadarJammer);
        // m_IsMobileGapGen = ini.Get_Bool(m_Name, "IsMobileGapGen", m_IsMobileGapGen);
        m_NoMovingFire = ini.Get_Bool(m_Name, "NoMovingFire", m_NoMovingFire);
        m_Speed = ini.Get_Bool(m_Name, "Tracked", m_Speed == SPEED_TRACK) ? SPEED_TRACK : SPEED_FOOT;

        if (m_MovementZone == MZONE_NORMAL && m_Crusher) {
            m_MovementZone = MZONE_CRUSHER;
        }

        return true;
    }

    return false;
}

/**
 * Fetches a reference to the actual object from a type enum value.
 *
 * 0x00578C24
 * @warning Heap allocation order MUST match the enum order in Init_Heap for this to work.
 */
UnitTypeClass &UnitTypeClass::As_Reference(UnitType type)
{
    DEBUG_ASSERT(type != UNIT_NONE);
    DEBUG_ASSERT(type < UNIT_COUNT);

    return g_UnitTypes[type];
}

UnitTypeClass *UnitTypeClass::As_Pointer(UnitType type)
{
    return (type < UNIT_COUNT) && (type != UNIT_NONE) ? &g_UnitTypes[type] : nullptr;
}

/**
 * Fetches the type enum value from a name string.
 *
 * 0x0057895C
 */
UnitType UnitTypeClass::From_Name(const char *name)
{
    if (name != nullptr) {
        for (UnitType unit = UNIT_FIRST; unit < UNIT_COUNT; ++unit) {
            if (strcasecmp(name, As_Reference(unit).m_Name) == 0) {
                return unit;
            }
        }
    }

    return UNIT_NONE;
}

/**
 * @brief 
 *
 * @address 0x005A5900 (beta)
 */
void UnitTypeClass::Prep_For_Add()
{
    for (UnitType i = UNIT_FIRST; i < UNIT_COUNT; ++i) {
        UnitTypeClass *utptr = As_Pointer(i);
        if (utptr != nullptr) {
            if (utptr->m_ImageData != nullptr) {
                Map.Add_To_List(utptr);
            }
        }
    }
}

/**
 * Initialises data that requires a one time load.
 *
 * 0x005789AC
 */
void UnitTypeClass::One_Time()
{
    char buffer[256];

    for (UnitType i = UNIT_FIRST; i < UNIT_COUNT; ++i) {
        UnitTypeClass &unit = As_Reference(i);
        const char *name = unit.m_ImageName[0] != '\0' ? unit.m_ImageName : unit.Get_Name();

        snprintf(buffer, sizeof(buffer), "%.4sicon.shp", name);
        unit.m_CameoData = GameFileClass::Retrieve(buffer);
        snprintf(buffer, sizeof(buffer), "%s.shp", name);
        unit.m_ImageData = GameFileClass::Retrieve(buffer);

        int big_dimension = 0;

        if (unit.m_ImageData != nullptr) {
            big_dimension = std::max(std::max(0, (int)Get_Build_Frame_Width(unit.m_ImageData)), (int)Get_Build_Frame_Height(unit.m_ImageData));
        }

        unit.m_UnkInt = std::max(big_dimension, 8);
    }

    // TODO original initialises these here, move them somewhere more appropriate when possible.
    if (g_WakeShapes == nullptr) {
        g_WakeShapes = GameFileClass::Retrieve("wake.shp");
    }

    if (g_TurretShapes == nullptr) {
        g_TurretShapes = GameFileClass::Retrieve("turr.shp");
    }

    if (g_SamShapes == nullptr) {
        g_SamShapes = GameFileClass::Retrieve("ssam.shp");
    }

    if (g_MGunShapes == nullptr) {
        g_MGunShapes = GameFileClass::Retrieve("mgun.shp");
    }
}

/**
 * @brief Initialises the memory heap for UnitTypeClass objects.
 * @warning Order of initialisation is important so enum matches position in the heap.
 *
 * @address 0x0056E2BC
 */
void UnitTypeClass::Init_Heap()
{
    // The order of heap initialisation MUST match the UnitType enum in unittype.h
    new UnitTypeClass(UnitHTank);
    new UnitTypeClass(UnitMTank);
    new UnitTypeClass(UnitMTank2);
    new UnitTypeClass(UnitLTank);
    new UnitTypeClass(UnitAPC);
    new UnitTypeClass(UnitMineLayer);
    new UnitTypeClass(UnitJeep);
    new UnitTypeClass(UnitHarvester);
    new UnitTypeClass(UnitArty);
    new UnitTypeClass(UnitMRJammer);
    new UnitTypeClass(UnitMGG);
    new UnitTypeClass(UnitMCV);
    new UnitTypeClass(UnitV2Launcher);
    new UnitTypeClass(UnitConvoyTruck);
    new UnitTypeClass(UnitAnt1);
    new UnitTypeClass(UnitAnt2);
    new UnitTypeClass(UnitAnt3);
    new UnitTypeClass(UnitChrono);
    new UnitTypeClass(UnitTesla);
    new UnitTypeClass(UnitMAD);
    new UnitTypeClass(UnitDemoTruck);
    new UnitTypeClass(UnitPhase);
}
