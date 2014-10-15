#ifndef FROST_IRR_TEST_SCENE_NODE
#define FROST_IRR_TEST_SCENE_NODE

#include <irrlicht.h>
#include <vector>
#include <FrostWorldMan.h>

class FrostCollisionTestSceneNode : public irr::scene::ISceneNode
{
public:
	FrostCollisionTestSceneNode(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 idm, Frost::IPhysicsNode* physicsNode);

	virtual void OnRegisterSceneNode();

	virtual void render();

	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const { return _box; }
	virtual irr::u32 getMaterialCount() const { return 1; }
	virtual irr::video::SMaterial& getMaterial(irr::u32 index) { return _material; }

	virtual void updateAbsolutePosition();

private:
	irr::core::aabbox3d<irr::f32> _box;

	std::vector<irr::video::S3DVertex> _verts;
	std::vector<irr::u32> _indices;
	irr::video::SMaterial _material;

	Frost::IPhysicsNode* _frostNode;
};

irr::core::vector3df convFrostVect(const Frost::Vect3& o);

#endif
