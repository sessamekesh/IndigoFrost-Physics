/*
This source file is part of the Indigo Frost physics engine

The MIT License (MIT)

Copyright (c) 2014 Kamaron Peterson (aggieblue92)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


/////////////////////////////////////////
// CollisionBox: ICollisionGeometry object
//  that represents a box.
// Uses the BasicContact for collisions
/////////////////////////////////////////

#ifndef FROST_COLLISION_BOX_H
#define FROST_COLLISION_BOX_H

#include "ICollisionGeometry.h"
#include "BasicContact.h"
#include <cmath>

namespace Frost
{
	class CollisionBox : public ICollisionGeometry
	{
		friend class CollisionSphere;

	public:
		/////////////////// CTORS //////////////////////

		// Construct a box with the given dimension at the origin
		CollisionBox(const FLOAT3& size);

		// Construct a box with the given dimensions, at the given position and orientation
		CollisionBox(const FLOAT3& size, const FLOAT3& position, const Quaternion& orientation);

		// Construct a box with the given dimensions, at the given position and orientation, and attach the given physical object.
		CollisionBox(const FLOAT3& size, const FLOAT3& position, const Quaternion& orientation, std::shared_ptr<IPhysicsObject> toAttach);

		// Copy ctor
		CollisionBox(const CollisionBox& other);

		//////////////////// OVERRIDES //////////////////

		// Returns whether or not the box is in contact with the other collision geometry
		virtual bool isTouching(const ICollisionGeometry& other) const;

		// Appends a list of contacts (if any) between the two geometry objects to o_list
		virtual void genContacts(const ICollisionGeometry& other, std::vector<std::shared_ptr<IContact>>& o_list) const;

		///////////////// GETTERS/SETTERS ///////////////
		virtual Vect3 getSize() const;

	protected:
		Vect3 _size; // Halfsize of the box

	protected:
	public:
		virtual bool isTouchingB(const CollisionBox& b) const;
		virtual void genContactsB(const CollisionBox& b, std::vector<std::shared_ptr<IContact>>& o) const;

		virtual bool isTouchingS(const CollisionSphere& s) const;
		virtual void genContactsS(const CollisionSphere& s, std::vector<std::shared_ptr<IContact>>& o) const;

		// This code is all used in box-box collisions...
		enum COLLISION_BOX_FACE
		{
			COLLISION_BOX_FACE_X_POS,
			COLLISION_BOX_FACE_X_NEG,
			COLLISION_BOX_FACE_Y_POS,
			COLLISION_BOX_FACE_Y_NEG,
			COLLISION_BOX_FACE_Z_POS,
			COLLISION_BOX_FACE_Z_NEG
		};

		COLLISION_BOX_FACE getFaceDirectionOfLocalPoint(const Vect3& pt_l) const;

	private:
		// Dear reader: I'm so sorry. But, I've always wanted to make something where I could
		//  honestly say that the system was powered by black magic and virgin sacrifices.
		// Now, I can. These functions are used in what forms the meat and potatoes of the
		//  collision resolution in the physics engine.
		void blackMagic(const Vect3Normal&, std::vector<Vect3>&) const;
		void blackMagic(const CollisionBox&, std::vector<Vect3>&, std::vector<Vect3>&) const;
		void performDarkRitual(const Vect3Normal&, const Vect3&, const Vect3&, const Vect3&, const Vect3&, std::vector<std::shared_ptr<IContact>>&, std::shared_ptr<IPhysicsObject> otherObject, const CollisionBox& oBox) const;
		bool performDarkRitual(const Vect3Normal&, const Vect3&, const Vect3&, const Vect3&, const Vect3&, std::shared_ptr<IPhysicsObject> otherObject) const;
		virtual std::shared_ptr<IContact> summonDemons(const Vect3&, const Vect3&, std::shared_ptr<IPhysicsObject>, std::shared_ptr<IPhysicsObject>) const;
	};
}

#endif