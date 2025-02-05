/**
 * @file
 *
 * @author OmniBlade
 *
 * @brief Interpolation tables and functions for scaling up 320 x 200 image content.
 *
 * @copyright Chronoshift is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#pragma once

#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#include "always.h"

class GraphicViewPortClass;
class GraphicBufferClass;

enum CopyEnum
{
    COPY_NONE = -1,
    COPY_INTERLEAVE,
    COPY_LINE_DOUBLE,
    COPY_LINE_INTERPOLATE,
};

#define INTERPOL_PAL_SIZE 256 * 256 //256x256 = 65536 pixels

void Create_Palette_Interpolation_Table();
void Read_Interpolation_Palette(const char *filename);
void Write_Interpolation_Palette(const char *filename);
void Rebuild_Interpolated_Palette(void *ipalette);
int Load_Interpolated_Palettes(const char *filename, BOOL append);
void Free_Interpolated_Palettes();

void Interpolate_2X_Scale(
    GraphicBufferClass &src, GraphicViewPortClass &dst, const char *filename);
void __cdecl Interpolate_Interleave(void *src, void *dst, int src_height, int src_width, int dst_pitch);
void __cdecl Interpolate_Line_Double(void *src, void *dst, int src_height, int src_width, int dst_pitch);
void __cdecl Interpolate_Line_Interpolate(void *src, void *dst, int src_height, int src_width, int dst_pitch);

#ifdef GAME_DLL
extern uint8_t *g_paletteInterpolationTable;
extern BOOL &g_palettesRead;
extern int &g_paletteCounter;
extern int &g_interpolationMode;
#else
extern uint8_t g_paletteInterpolationTable[INTERPOL_PAL_SIZE];
extern BOOL g_palettesRead;
extern int g_paletteCounter;
extern int g_interpolationMode;
#endif

#endif // INTERPOLATE_H
