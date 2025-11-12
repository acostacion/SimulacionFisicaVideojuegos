#include "Axis.h"

Axis::Axis() {
	_tfs = {
		new physx::PxTransform(physx::PxVec3(0.0)),
		new physx::PxTransform(physx::PxVec3(1.0, 0.0, 0.0)),
		new physx::PxTransform(physx::PxVec3(0.0, 1.0, 0.0)),
		new physx::PxTransform(physx::PxVec3(0.0, 0.0, 1.0))
	};

	_renderItems = {
		new RenderItem(CreateShape(physx::PxSphereGeometry(0.25f)), _tfs[0], Vector4(1.0, 1.0, 1.0, 1.0)),
		new RenderItem(CreateShape(physx::PxSphereGeometry(0.25f)), _tfs[1], Vector4(1.0, 0.0, 0.0, 1.0)),
		new RenderItem(CreateShape(physx::PxSphereGeometry(0.25f)), _tfs[2], Vector4(0.0, 1.0, 0.0, 1.0)),
		new RenderItem(CreateShape(physx::PxSphereGeometry(0.25f)), _tfs[3], Vector4(0.0, 0.0, 1.0, 1.0))
	};

	for (int i = 0; i < _renderItems.size(); i++) RegisterRenderItem(_renderItems[i]);
}

Axis::~Axis() {
	for (int i = 0; i < _renderItems.size(); i++) {
		DeregisterRenderItem(_renderItems[i]);
		delete _renderItems[i];
	}
	_renderItems.clear();

	for (int i = 0; i < _tfs.size(); i++){
		delete _tfs[i];
	}
	_tfs.clear();
}