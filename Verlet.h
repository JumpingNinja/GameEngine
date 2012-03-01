#ifndef _VERLET_H_
#define _VERLET_H_

/* Module Verlet */

#include "VerletPoint.h"
#include "VerletConstraint.h"
#include "VerletRigid.h"


void VerletDeleteAll()
{
	VerletRigid::DeleteAll();
	VerletConstraint::DeleteAll();
	VerletPoint::DeleteAll();
}

#endif
