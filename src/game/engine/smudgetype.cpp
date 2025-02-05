/**
 * @file
 *
 * @author OmniBlade
 * @author CCHyper
 *
 * @brief Class containing information about terrain smudges.
 *
 * @copyright Chronoshift is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#include "smudgetype.h"
#include "smudgedata.h"
#include "gamefile.h"
#include "drawshape.h"
#include "lists.h"
#include "mixfile.h"
#include "iomap.h"
#include <cstdio>

using std::snprintf;

#ifndef GAME_DLL
TFixedIHeapClass<SmudgeTypeClass> g_SmudgeTypes;
#endif

SmudgeTypeClass::SmudgeTypeClass(
    SmudgeType smudge, const char *name, int uiname, int width, int height, BOOL bib, BOOL crater) :
    ObjectTypeClass(RTTI_SMUDGETYPE, smudge, true, true, false, false, true, true, false, uiname, name),
    m_Type(smudge),
    m_Width(width),
    m_Height(height),
    m_Crater(crater),
    m_Bib(bib)
{
}

SmudgeTypeClass::SmudgeTypeClass(SmudgeTypeClass const &that) :
    ObjectTypeClass(that),
    m_Type(that.m_Type),
    m_Width(that.m_Width),
    m_Height(that.m_Height),
    m_Crater(that.m_Crater),
    m_Bib(that.m_Bib)
{
}

void *SmudgeTypeClass::operator new(size_t size)
{
    DEBUG_ASSERT(size == sizeof(SmudgeTypeClass));
    return g_SmudgeTypes.Allocate();
}

void SmudgeTypeClass::operator delete(void *ptr)
{
    DEBUG_ASSERT(ptr != nullptr);
    g_SmudgeTypes.Free(ptr);
}

BOOL SmudgeTypeClass::Create_And_Place(cell_t cellnum, HousesType house) const
{
    // TODO requires SmudgeClass
#ifdef GAME_DLL
    BOOL(*func)(const SmudgeTypeClass*, cell_t, HousesType) = reinterpret_cast<BOOL(*)(const SmudgeTypeClass*, cell_t, HousesType)>(0x00549E50);
    return func(this, cellnum, house);
#elif 0
    DEBUG_ASSERT(this != nullptr);

    return new SmudgeClass(m_Type, Cell_To_Coord(cellnum), house) != nullptr;
#else
    return false;
#endif
}

ObjectClass *SmudgeTypeClass::Create_One_Of(HouseClass *house) const
{
    // TODO requires OverlayClass
#ifdef GAME_DLL
    ObjectClass *(*func)(const SmudgeTypeClass*, HouseClass*) = reinterpret_cast<ObjectClass *(*)(const SmudgeTypeClass*, HouseClass*)>(0x00549EB0);
    return func(this, house);
#elif 0
    DEBUG_ASSERT(this != nullptr);
    // DEBUG_ASSERT(house != nullptr);

    SmudgeClass *sptr = new SmudgeClass(m_Type);
    DEBUG_ASSERT(sptr != nullptr);
    return sptr;
#else
    return nullptr;
#endif
}

const int16_t *SmudgeTypeClass::Occupy_List(BOOL a1) const
{
    static int16_t _occupy[32];

    int16_t *list = _occupy;
    for (int i = 0; i < m_Width; ++i) {
        for (int j = 0; j < m_Height; ++j) {
            *list++ = j * 128 + i;
        }
    }

    *list = LIST_END;

    return _occupy;
}

const int16_t *SmudgeTypeClass::Overlap_List() const
{
    return Occupy_List(false);
}

void SmudgeTypeClass::Draw_It(int x, int y, int frame) const
{
    if (Get_Image_Data() != nullptr) {
        g_isTheaterShape = true;
        CC_Draw_Shape(Get_Image_Data(), frame, x, y, WINDOW_TACTICAL, SHAPE_WIN_REL);
        g_isTheaterShape = false;
    }
}

SmudgeType SmudgeTypeClass::From_Name(const char *name)
{
    DEBUG_ASSERT(name != nullptr);

    if (strcasecmp(name, "<none>") == 0 || strcasecmp(name, "none") == 0) {
        return SMUDGE_NONE;
    }

    if (name != nullptr) {
        for (SmudgeType type = SMUDGE_FIRST; type < SMUDGE_COUNT; ++type) {
            if (strcasecmp(name, Name_From(type)) == 0) {
                return type;
            }
        }
    }

    return SMUDGE_NONE;
}

const char *SmudgeTypeClass::Name_From(SmudgeType type)
{
    return type != SMUDGE_NONE && type < SMUDGE_COUNT ? As_Reference(type).m_Name : "<none>";
}

void SmudgeTypeClass::Init_Heap()
{
    // Order of allocation MUST match order of SmudgeType enum.
    new SmudgeTypeClass(SmudgeCrater1);
    new SmudgeTypeClass(SmudgeCrater2);
    new SmudgeTypeClass(SmudgeCrater3);
    new SmudgeTypeClass(SmudgeCrater4);
    new SmudgeTypeClass(SmudgeCrater5);
    new SmudgeTypeClass(SmudgeCrater6);
    new SmudgeTypeClass(SmudgeScorch1);
    new SmudgeTypeClass(SmudgeScorch2);
    new SmudgeTypeClass(SmudgeScorch3);
    new SmudgeTypeClass(SmudgeScorch4);
    new SmudgeTypeClass(SmudgeScorch5);
    new SmudgeTypeClass(SmudgeScorch6);

    new SmudgeTypeClass(SmudgeBibx1);
    new SmudgeTypeClass(SmudgeBibx2);
    new SmudgeTypeClass(SmudgeBibx3);
}

void SmudgeTypeClass::Init(TheaterType theater)
{
    DEBUG_ASSERT(theater < THEATER_COUNT);
    DEBUG_ASSERT(theater != THEATER_NONE);

    char filename[256];

    if (theater != g_lastTheater) {
        for (SmudgeType i = SMUDGE_FIRST; i < SMUDGE_COUNT; ++i) {
            SmudgeTypeClass &smudge = As_Reference(i);
            const char *name = smudge.m_ImageName[0] != '\0' ? smudge.m_ImageName : smudge.m_Name;
            snprintf(filename, sizeof(filename), "%s.%s", name, g_theaters[theater].ext);
            smudge.m_ImageData = GameFileClass::Retrieve(filename);
        }
    }
}

SmudgeTypeClass &SmudgeTypeClass::As_Reference(SmudgeType type)
{
    DEBUG_ASSERT(type != SMUDGE_NONE);
    DEBUG_ASSERT(type < SMUDGE_COUNT);

    return g_SmudgeTypes[type];
}

SmudgeTypeClass *SmudgeTypeClass::As_Pointer(SmudgeType type)
{
    return (type < SMUDGE_COUNT) && (type != SMUDGE_NONE) ? &g_SmudgeTypes[type] : nullptr;
}

/**
 * @brief 
 *
 * @address 0x0056DC90 (beta)
 */
void SmudgeTypeClass::Prep_For_Add()
{
    for (SmudgeType i = SMUDGE_FIRST; i < SMUDGE_COUNT; ++i) {
        SmudgeTypeClass *stptr = As_Pointer(i);
        if (stptr != nullptr) {
            if (stptr->m_ImageData != nullptr) {
                Map.Add_To_List(stptr);
            }
        }
    }
}
