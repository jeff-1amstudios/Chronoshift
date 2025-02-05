/**
 * @file
 *
 * @author CCHyper
 * @author OmniBlade
 *
 * @brief Base class for UI elements, provides basic input handling.
 *
 * @copyright Chronoshift is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#pragma once

#ifndef GADGET_H
#define GADGET_H

#include "keyboard.h"
#include "link.h"
#include "remap.h"
#include "trect.h"

 // Redraw flags used by the game menu loops.
#define NO_REDRAW 0
#define REDRAW_GADGETS 1
#define REDRAW_ALL 2

class ControlClass;

enum GadgetMasks {
    UNK_BIT = 0x4000,
    BTN_BIT = 0x8000
};

// TODO, not sure, looks like EditClass only mask?
#define     GADGET_INPUT_RENAME(id)        (KeyNumType)((UNK_BIT | id))

// All UI controls are this number + the control ID.
// Otherwise, input will return a standard KeyNumType.
#define     GADGET_INPUT_RENAME2(id)         (KeyNumType)((BTN_BIT | id))

enum GadgetInput
{
    INPUT_NONE = 0x0,
    MOUSE_LEFT_PRESS = 0x1,
    MOUSE_LEFT_HELD = 0x2,
    MOUSE_LEFT_RLSE = 0x4,
    MOUSE_LEFT_UP = 0x8,
    MOUSE_RIGHT_PRESS = 0x10,
    MOUSE_RIGHT_HELD = 0x20,
    MOUSE_RIGHT_RLSE = 0x40, // this allows Action() to be called at one place
    MOUSE_RIGHT_UP = 0x80,
    KEYBOARD_INPUT = 0x100, // Respond to none mouse event?
};

DEFINE_ENUMERATION_BITWISE_OPERATORS(GadgetInput);

class GadgetClass : public LinkClass
{
public:
    GadgetClass() {}
    GadgetClass(unsigned input_flag, BOOL sticky = false);
    GadgetClass(int x, int y, int w, int h, unsigned input_flag, BOOL sticky = false);
    GadgetClass(GadgetClass &that);
    virtual ~GadgetClass();

    virtual GadgetClass *Get_Next() const override;
    virtual GadgetClass *Get_Prev() const override;
    virtual GadgetClass *Remove() override;
    virtual KeyNumType Input();
    virtual void Draw_All(BOOL redraw = true);
    virtual void Delete_List();
    virtual ControlClass *Extract_Gadget(unsigned id);
    virtual void Flag_List_To_Redraw();
    virtual void Disable();
    virtual void Enable();
    virtual unsigned Get_ID() const;
    virtual void Flag_To_Redraw();
    virtual void Peer_To_Peer(unsigned flags, KeyNumType &key, ControlClass &peer);
    virtual void Set_Focus();
    virtual void Clear_Focus();
    virtual BOOL Has_Focus();
    virtual BOOL Is_List_To_Redraw();
    virtual BOOL Is_To_Redraw() { return m_ToRedraw; }
    virtual void Set_Position(int x, int y);
    virtual BOOL Draw_Me(BOOL redraw);
    virtual void Sticky_Process(unsigned flags);
    virtual BOOL Action(unsigned flags, KeyNumType &key);
    virtual BOOL Clicked_On(KeyNumType &a1, unsigned flags, int x, int y);

    GadgetClass &operator=(GadgetClass &that);

    void Set_Size(int w, int h);
    void Set_XPos(int x) { m_XPos = x; }
    void Set_YPos(int y) { m_YPos = y; }
    void Set_Width(int w) { m_Width = w; }
    void Set_Height(int h) { m_Height = h; }
    void Set_Sticky(BOOL sticky) { m_IsSticky = sticky; }
    int Get_XPos() { return m_XPos; }
    int Get_YPos() { return m_YPos; }
    int Get_Width() { return m_Width; }
    int Get_Height() { return m_Height; }

    static RemapControlType *Get_Color_Scheme() { return ColorScheme; }
    static void Set_Color_Scheme(RemapControlType *remap) { ColorScheme = remap; }

protected:
#ifdef GAME_DLL
    static RemapControlType *&ColorScheme;
    static GadgetClass *&StuckOn;
    static GadgetClass *&LastList;
    static GadgetClass *&Focused;
#else
    static RemapControlType *ColorScheme;
    static GadgetClass *StuckOn;
    static GadgetClass *LastList;
    static GadgetClass *Focused;
#endif

protected:
    int m_XPos;
    int m_YPos;
    int m_Width;
    int m_Height;

#ifndef CHRONOSHIFT_NO_BITFIELDS
    BOOL m_ToRedraw : 1; // & 1
    BOOL m_IsSticky : 1; // & 2
    BOOL m_IsDisabled : 1; // & 4
#else
    bool m_ToRedraw;
    bool m_IsSticky;
    bool m_IsDisabled;
#endif

    unsigned m_InputFlag;
};

#endif // GADGET_H
