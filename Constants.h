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

///@brief Classe d'accès global

class gb {
public:
    static float timerate;
};