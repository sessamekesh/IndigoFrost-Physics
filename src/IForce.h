#ifndef FROSTDLL_API
#ifdef _WINDLL
#define FROSTDLL_API __declspec(dllexport)
#else
#define FROSTDLL_API __declspec(dllimport)
#endif
#endif

#ifndef FROST_IFORCE_H
#define FROST_IFORCE_H

/////////////////////////////////////////
// IForce: An interface that all forces
//  should follow.
/////////////////////////////////////////

#include "Vect3.h"
#include "IPhysicsObject.h"

namespace Frost
{
	class IForce
	{
	public:
		virtual void ApplyForce(IPhysicsObject* affectedPhysicsObject, float duration) = 0;
	};
}

#endif