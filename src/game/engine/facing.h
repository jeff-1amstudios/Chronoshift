/**
 * @file
 *
 * @author CCHyper
 * @author OmniBlade
 *
 * @brief Classes, types and functions related to managing the facings and directions of objects.
 *
 * @copyright Chronoshift is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#pragma once

#ifndef FACING_H
#define FACING_H

#include "always.h"
#include "keyboard.h"

#define FACING_COUNT_NONE 0
#define FACING_COUNT_1 1
#define FACING_COUNT_4 4
#define FACING_COUNT_8 8
#define FACING_COUNT_16 16
#define FACING_COUNT_32 32

// these are pretty much the standard 8 compass
#ifdef COMPILER_WATCOM
enum FacingType
#else
enum FacingType : uint8_t
#endif
{
    FACING_FIRST = 0,
    FACING_NORTH = 0, // North
    FACING_NORTH_EAST = 1, // North East
    FACING_EAST = 2, // East
    FACING_SOUTH_EAST = 3, // South East
    FACING_SOUTH = 4, // South
    FACING_SOUTH_WEST = 5, // South West
    FACING_WEST = 6, // West
    FACING_NORTH_WEST = 7, // North West
    FACING_COUNT = 8,
    FACING_FIXUP_MARK = 0xFE,
    FACING_NONE = 0xFF,
    FACING_ORDINAL_TEST = 1,
    FACING_EDGE_LEFT = 0xFF,
    FACING_EDGE_RIGHT = 1,
};

DEFINE_ENUMERATION_OPERATORS(FacingType);

#ifdef COMPILER_WATCOM
enum DirType
#else
enum DirType : uint8_t
#endif
{
    DIR_FIRST = 0,
    DIR_NORTH = 0, // 0 degrees
    DIR_NORTH_NORTH_EAST = 16,
    DIR_NORTH_EAST = 32, // 45 degrees
    DIR_EAST_NORTH_EAST = 48,
    DIR_EAST = 64, // 90 degrees
    DIR_EAST_SOUTH_EAST = 80,
    DIR_SOUTH_EAST = 96, // 135 degrees
    DIR_SOUTH_SOUTH_EAST = 112,
    DIR_SOUTH = 128, // 180 degrees
    DIR_SOUTH_SOUTH_WEST = 144,
    DIR_SOUTH_WEST = 160, // 225 degrees
    DIR_WEST_SOUTH_WEST = 176,
    DIR_WEST = 192, // 270 degrees
    DIR_WEST_NORTH_WEST = 208,
    DIR_NORTH_WEST = 224, // 315 degrees
    DIR_NORTH_WEST_NORTH = 240,
    DIR_LAST = 255,
    DIR_NONE = 255,
};

DEFINE_ENUMERATION_OPERATORS(DirType);
DEFINE_ENUMERATION_BITWISE_OPERATORS(DirType);

// forward decs
class NoInitClass;

// rename these to Get_*
DirType Desired_Facing8(int x1, int y1, int x2, int y2);
DirType Desired_Facing256(int x1, int y1, int x2, int y2);

DirType Facing_To_Direction(FacingType facing);
FacingType Direction_To_Facing(DirType direction);

// todo, rename and check?
DirType Round_Direction_To_8(DirType dir);
DirType Round_Direction_To_16(DirType dir);
DirType Round_Direction_To_32(DirType dir);
DirType Round_Direction_To_64(DirType dir);
DirType Round_Direction_To_128(DirType dir);

FacingType KN_To_Facing(KeyNumType kn);

const char *Name_From_Facing(FacingType facing, BOOL abbreviated = false);
FacingType Facing_From_Name(const char *name);

const char *Facing_Name_From_Direction(DirType dir);

const char *Name_From_Direction(DirType dir);

class FacingClass
{
public:
    FacingClass() : m_Current(DIR_NORTH), m_Desired(DIR_NORTH) {}
    FacingClass(const DirType dir) : m_Current(dir), m_Desired(dir) {}
    FacingClass(const DirType current, DirType desired) : m_Current(current), m_Desired(desired) {}
    FacingClass(const FacingClass &that) : m_Current(that.m_Current), m_Desired(that.m_Desired) {}
    FacingClass(const NoInitClass &noinit) {}
    ~FacingClass() {}

    FacingClass &operator=(const FacingClass &that)
    {
        if (this != &that) {
            m_Current = that.m_Current;
            m_Desired = that.m_Desired;
        }
        return *this;
    }

    void operator=(const DirType dir)
    {
        m_Current = dir;
        m_Desired = dir;
    }

    void operator=(const FacingType facing)
    {
        m_Current = Facing_To_Direction(facing);
        m_Desired = Facing_To_Direction(facing);
    }

    BOOL Set_Current(const DirType dir);
    BOOL Set_Desired(const DirType dir);
    DirType Get_Current() const { return m_Current; }
    DirType Get_Desired() const { return m_Desired; }
    BOOL Rotation_Adjust(int adjust);

    BOOL Has_Changed() const { return m_Current != m_Desired; }
    BOOL Has_Not_Changed() const { return m_Current == m_Desired; }

public:
    static uint8_t const Facing8[256];
    static uint8_t const Facing16[256];
    static uint8_t const Facing32[256];
    static uint8_t const Facing64[256];

public:
    static int8_t const Rotation8[256];
    static int8_t const Rotation16[256];
    static int8_t const Rotation32[256];
    static int8_t const Rotation64[256];

private:
    DirType m_Current;
    DirType m_Desired;
};

// sub_41B710 in SS
// TODO Same as sub_44BEA4?
inline FacingType SS_41B710(FacingType facing, int chirality)
{
    return (FacingType)(((unsigned)facing - (unsigned)chirality) & (FACING_COUNT - 1)); // 7
}

// sub_44BEA4 in SS
// TODO rename, Subtract Facing?
inline FacingType Reverse_Adjust(FacingType facing, FacingType chirality)
{
    return (facing - chirality) % FACING_COUNT; // 7
}

// sub_41B73C in SS
// TODO, this one takes a integer, values from random ranged are parsed into it, so how sure what a2 is...
inline FacingType SS_41B73C(FacingType facing, int chirality)
{
    return (FacingType)(((unsigned)chirality + (unsigned)facing) & (FACING_COUNT - 1)); // 7
}

// sub_41B768 in SS
inline FacingType Facing_Adjust(FacingType facing, FacingType chirality)
{
    return (chirality + facing) % FACING_COUNT; // 7
}

inline FacingType Opposite_Facing(FacingType facing)
{
    return (FacingType)(facing ^ (FACING_COUNT / 2)); // 4
}

#endif // FACING_H
