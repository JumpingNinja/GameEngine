//
//  Constants.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 02/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once

/**
 Déclare des constantes
**/

template <class T> const T& max ( const T& a, const T& b ) {
    return (a<b)?b:a;     // or: return comp(a,b)?b:a; for the comp version
}

template <class T> const T& min ( const T& a, const T& b ) {
    return (a>b)?b:a;     // or: return comp(a,b)?b:a; for the comp version
}
template <class T> const T abs ( const T& a ) {
    return (a < static_cast<T>(0))?-a:a;
}

template <class T> bool isPositive ( const T& a ) {
    return (a >= static_cast<T>(0));
}

template <class T> bool sign ( const T& a ) {
    return (a >= static_cast<T>(0));
}

void wobble(float &current_position, float target_position, float force,float friction, float &m_spd);

///@brief Classe d'accès global

class gb {
public:
    static float timerate, timerate_to, m_spdTR;
    	// Directement pris de la SFML... /shame
	enum Key
    {
        A,            ///< The A key
        B,            ///< The B key
        C,            ///< The C key
        D,            ///< The D key
        E,            ///< The E key
        F,            ///< The F key
        G,            ///< The G key
        H,            ///< The H key
        I,            ///< The I key
        J,            ///< The J key
        K,            ///< The K key
        L,            ///< The L key
        M,            ///< The M key
        N,            ///< The N key
        O,            ///< The O key
        P,            ///< The P key
        Q,            ///< The Q key
        R,            ///< The R key
        S,            ///< The S key
        T,            ///< The T key
        U,            ///< The U key
        V,            ///< The V key
        W,            ///< The W key
        X,            ///< The X key
        Y,            ///< The Y key
        Z,            ///< The Z key
        Num0,         ///< The 0 key
        Num1,         ///< The 1 key
        Num2,         ///< The 2 key
        Num3,         ///< The 3 key
        Num4,         ///< The 4 key
        Num5,         ///< The 5 key
        Num6,         ///< The 6 key
        Num7,         ///< The 7 key
        Num8,         ///< The 8 key
        Num9,         ///< The 9 key
        Escape,       ///< The Escape key
        LControl,     ///< The left Control key
        LShift,       ///< The left Shift key
        LAlt,         ///< The left Alt key
        LSystem,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
        RControl,     ///< The right Control key
        RShift,       ///< The right Shift key
        RAlt,         ///< The right Alt key
        RSystem,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
        Menu,         ///< The Menu key
        LBracket,     ///< The [ key
        RBracket,     ///< The ] key
        SemiColon,    ///< The ; key
        Comma,        ///< The , key
        Period,       ///< The . key
        Quote,        ///< The ' key
        Slash,        ///< The / key
        BackSlash,    ///< The \ key
        Tilde,        ///< The ~ key
        Equal,        ///< The = key
        Dash,         ///< The - key
        Space,        ///< The Space key
        Return,       ///< The Return key
        Back,         ///< The Backspace key
        Tab,          ///< The Tabulation key
        PageUp,       ///< The Page up key
        PageDown,     ///< The Page down key
        End,          ///< The End key
        Home,         ///< The Home key
        Insert,       ///< The Insert key
        Delete,       ///< The Delete key
        Add,          ///< +
        Subtract,     ///< -
        Multiply,     ///< *
        Divide,       ///< /
        Left,         ///< Left arrow
        Right,        ///< Right arrow
        Up,           ///< Up arrow
        Down,         ///< Down arrow
        Numpad0,      ///< The numpad 0 key
        Numpad1,      ///< The numpad 1 key
        Numpad2,      ///< The numpad 2 key
        Numpad3,      ///< The numpad 3 key
        Numpad4,      ///< The numpad 4 key
        Numpad5,      ///< The numpad 5 key
        Numpad6,      ///< The numpad 6 key
        Numpad7,      ///< The numpad 7 key
        Numpad8,      ///< The numpad 8 key
        Numpad9,      ///< The numpad 9 key
        F1,           ///< The F1 key
        F2,           ///< The F2 key
        F3,           ///< The F3 key
        F4,           ///< The F4 key
        F5,           ///< The F5 key
        F6,           ///< The F6 key
        F7,           ///< The F7 key
        F8,           ///< The F8 key
        F9,           ///< The F8 key
        F10,          ///< The F10 key
        F11,          ///< The F11 key
        F12,          ///< The F12 key
        F13,          ///< The F13 key
        F14,          ///< The F14 key
        F15,          ///< The F15 key
        Pause,        ///< The Pause key
        LastKeyboardKey,
        MouseButton1, // Les bouttons de la souris
        MouseButton2,
        MouseButton3,
        MouseButton4,
        MouseButton5,
        LastMouseButton,
        Joy0_1, // Les bouttons des JoySticks
        Joy0_2,
        Joy0_3,
        Joy0_4,
        Joy0_5,
        Joy0_6,
        Joy0_7,
        Joy0_8,
        Joy0_9,
        Joy0_10,
        Joy0_11,
        Joy0_12,
        Joy0_13,
        Joy0_14,
        Joy0_15,
        Joy0_16,
        Joy0_17,
        Joy0_18,
        Joy0_19,
        Joy0_20,
        Joy0_21,
        Joy0_22,
        Joy0_23,
        Joy0_24,
        Joy0_25,
        Joy0_26,
        Joy0_27,
        Joy0_28,
        Joy0_29,
        Joy0_30,
        Joy0_31,
        Joy0_32,
        Joy1_1,
        Joy1_2,
        Joy1_3,
        Joy1_4,
        Joy1_5,
        Joy1_6,
        Joy1_7,
        Joy1_8,
        Joy1_9,
        Joy1_10,
        Joy1_11,
        Joy1_12,
        Joy1_13,
        Joy1_14,
        Joy1_15,
        Joy1_16,
        Joy1_17,
        Joy1_18,
        Joy1_19,
        Joy1_20,
        Joy1_21,
        Joy1_22,
        Joy1_23,
        Joy1_24,
        Joy1_25,
        Joy1_26,
        Joy1_27,
        Joy1_28,
        Joy1_29,
        Joy1_30,
        Joy1_31,
        Joy1_32,
        Joy2_1,
        Joy2_2,
        Joy2_3,
        Joy2_4,
        Joy2_5,
        Joy2_6,
        Joy2_7,
        Joy2_8,
        Joy2_9,
        Joy2_10,
        Joy2_11,
        Joy2_12,
        Joy2_13,
        Joy2_14,
        Joy2_15,
        Joy2_16,
        Joy2_17,
        Joy2_18,
        Joy2_19,
        Joy2_20,
        Joy2_21,
        Joy2_22,
        Joy2_23,
        Joy2_24,
        Joy2_25,
        Joy2_26,
        Joy2_27,
        Joy2_28,
        Joy2_29,
        Joy2_30,
        Joy2_31,
        Joy2_32,
        Joy3_1,
        Joy3_2,
        Joy3_3,
        Joy3_4,
        Joy3_5,
        Joy3_6,
        Joy3_7,
        Joy3_8,
        Joy3_9,
        Joy3_10,
        Joy3_11,
        Joy3_12,
        Joy3_13,
        Joy3_14,
        Joy3_15,
        Joy3_16,
        Joy3_17,
        Joy3_18,
        Joy3_19,
        Joy3_20,
        Joy3_21,
        Joy3_22,
        Joy3_23,
        Joy3_24,
        Joy3_25,
        Joy3_26,
        Joy3_27,
        Joy3_28,
        Joy3_29,
        Joy3_30,
        Joy3_31,
        Joy3_32,
        Joy4_1,
        Joy4_2,
        Joy4_3,
        Joy4_4,
        Joy4_5,
        Joy4_6,
        Joy4_7,
        Joy4_8,
        Joy4_9,
        Joy4_10,
        Joy4_11,
        Joy4_12,
        Joy4_13,
        Joy4_14,
        Joy4_15,
        Joy4_16,
        Joy4_17,
        Joy4_18,
        Joy4_19,
        Joy4_20,
        Joy4_21,
        Joy4_22,
        Joy4_23,
        Joy4_24,
        Joy4_25,
        Joy4_26,
        Joy4_27,
        Joy4_28,
        Joy4_29,
        Joy4_30,
        Joy4_31,
        Joy4_32,
        Joy5_1,
        Joy5_2,
        Joy5_3,
        Joy5_4,
        Joy5_5,
        Joy5_6,
        Joy5_7,
        Joy5_8,
        Joy5_9,
        Joy5_10,
        Joy5_11,
        Joy5_12,
        Joy5_13,
        Joy5_14,
        Joy5_15,
        Joy5_16,
        Joy5_17,
        Joy5_18,
        Joy5_19,
        Joy5_20,
        Joy5_21,
        Joy5_22,
        Joy5_23,
        Joy5_24,
        Joy5_25,
        Joy5_26,
        Joy5_27,
        Joy5_28,
        Joy5_29,
        Joy5_30,
        Joy5_31,
        Joy5_32,
        Joy6_1,
        Joy6_2,
        Joy6_3,
        Joy6_4,
        Joy6_5,
        Joy6_6,
        Joy6_7,
        Joy6_8,
        Joy6_9,
        Joy6_10,
        Joy6_11,
        Joy6_12,
        Joy6_13,
        Joy6_14,
        Joy6_15,
        Joy6_16,
        Joy6_17,
        Joy6_18,
        Joy6_19,
        Joy6_20,
        Joy6_21,
        Joy6_22,
        Joy6_23,
        Joy6_24,
        Joy6_25,
        Joy6_26,
        Joy6_27,
        Joy6_28,
        Joy6_29,
        Joy6_30,
        Joy6_31,
        Joy6_32,
        Joy7_1,
        Joy7_2,
        Joy7_3,
        Joy7_4,
        Joy7_5,
        Joy7_6,
        Joy7_7,
        Joy7_8,
        Joy7_9,
        Joy7_10,
        Joy7_11,
        Joy7_12,
        Joy7_13,
        Joy7_14,
        Joy7_15,
        Joy7_16,
        Joy7_17,
        Joy7_18,
        Joy7_19,
        Joy7_20,
        Joy7_21,
        Joy7_22,
        Joy7_23,
        Joy7_24,
        Joy7_25,
        Joy7_26,
        Joy7_27,
        Joy7_28,
        Joy7_29,
        Joy7_30,
        Joy7_31,
        Joy7_32,
        LastJoystickButton,
        Joy0_X,
        Joy0_Y,
        Joy0_Z,
        Joy0_R,
        Joy0_U,
        Joy0_V,
        Joy0_PovX,
        Joy0_PovY,
        Joy1_X,
        Joy1_Y,
        Joy1_Z,
        Joy1_R,
        Joy1_U,
        Joy1_V,
        Joy1_PovX,
        Joy1_PovY,
        Joy2_X,
        Joy2_Y,
        Joy2_Z,
        Joy2_R,
        Joy2_U,
        Joy2_V,
        Joy2_PovX,
        Joy2_PovY,
        Joy3_X,
        Joy3_Y,
        Joy3_Z,
        Joy3_R,
        Joy3_U,
        Joy3_V,
        Joy3_PovX,
        Joy3_PovY,
        Joy4_X,
        Joy4_Y,
        Joy4_Z,
        Joy4_R,
        Joy4_U,
        Joy4_V,
        Joy4_PovX,
        Joy4_PovY,
        Joy5_X,
        Joy5_Y,
        Joy5_Z,
        Joy5_R,
        Joy5_U,
        Joy5_V,
        Joy5_PovX,
        Joy5_PovY,
        Joy6_X,
        Joy6_Y,
        Joy6_Z,
        Joy6_R,
        Joy6_U,
        Joy6_V,
        Joy6_PovX,
        Joy6_PovY,
        Joy7_X,
        Joy7_Y,
        Joy7_Z,
        Joy7_R,
        Joy7_U,
        Joy7_V,
        Joy7_PovX,
        Joy7_PovY,

		NullKey,
        KeyCount ///< Le nombre total de touches.
    };
};
