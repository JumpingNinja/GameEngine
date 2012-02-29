#ifndef _VERLET_H_
#define _VERLET_H_

/* Module Verlet */

#include "VerletPoint.h"
#include "VerletConstraint.h"


void VerletDeleteAll()
{
	VerletConstraint::DeleteAll();
	VerletPoint::DeleteAll();
}

#endif
