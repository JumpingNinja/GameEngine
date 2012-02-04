//
//  Constants.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 02/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "Constants.h"
/*
template <class T> const T& max ( const T& a, const T& b ) {
    return (a<b)?b:a;     // or: return comp(a,b)?b:a; for the comp version
}

template <class T> const T& min ( const T& a, const T& b ) {
    return (a>b)?b:a;     // or: return comp(a,b)?b:a; for the comp version
}
*/

float gb::timerate(1.f);

void wobble(float &current_position, float const& target_position, float const& force,float const& friction, float &m_spd)
{
	m_spd=(m_spd+((target_position-current_position)/2)*force)*(1-friction);
	current_position+=m_spd;
}