/**
 * @file
 *
 * @author OmniBlade
 * @author CCHyper
 *
 * @brief Low level sprite drawing functions for Dune2 sprite format (used for mouse in early C&C games).
 *
 * @copyright Chronoshift is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#pragma once

#ifndef MOUSESHAPE_H
#define MOUSESHAPE_H

#include "always.h"

#pragma pack(push, 1)
// Header for each frame in the old SHP format... only used for mouse now.
struct MouseShapeFrameHeader
{
    uint16_t flags;
    uint8_t lines;
    uint16_t width;
    uint8_t height; // always same as lines?
    uint16_t compressed_size;
    uint16_t uncompressed_size;
};

// Header for the old SHP format... only used for mouse now. Offset values need +2 to get actual frame pos.
struct MouseShapeHeader
{
    uint16_t frame_count;
    uint32_t offset;
};
#pragma pack(pop)

class MouseClass;
class GraphicViewPortClass;

int Get_Shape_Uncomp_Size(void *shape);
int Extract_Shape_Count(void *shape);
void *Extract_Shape(void *shape, int frame = 0);
int Get_Shape_Width(void *shape);
int Get_Shape_Height(void *shape);
int Restore_Shape_Height(void *shape);
int Get_Shape_Original_Height(void *shape);

void __cdecl Mouse_Shadow_Buffer(MouseClass &mouse, GraphicViewPortClass &viewport, void *buffer, int x_pos, int y_pos, int hspot_x, int hspot_y, BOOL save);
void __cdecl Mouse_Draw(MouseClass &mouse, GraphicViewPortClass &viewport, int x_pos, int y_pos);
void *__cdecl Mouse_Set_Cursor(MouseClass &mouse, int hspot_x, int hspot_y, void *shape);

#endif
