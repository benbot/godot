#ifndef GLTF_MULTI_EXTENSION_H
#define GLTF_MULTI_EXTENSION_H

#include "core/templates/vector.h"
#include "modules/gltf/extensions/gltf_document_extension.h"
#include "scene/3d/multimesh_instance_3d.h"
#include "scene/3d/node_3d.h"
#include <map>

class GLTFMulti : public GLTFDocumentExtension {
protected:
	static void _bind_methods();

private:
	std::map<String, MultiMeshInstance3D *> multis;
	Vector<String> mesh_names;
	bool should_skip = false;

public:
	Node3D *generate_scene_node(Ref<GLTFState> p_state, Ref<GLTFNode> p_gltf_node, Node *p_scene_parent) override;
	bool is_dirty() override;
	void clean() override;
	bool should_skip_add_to_scene() override;
};

#endif // GLTF_MULTI_EXTENSION_H_
