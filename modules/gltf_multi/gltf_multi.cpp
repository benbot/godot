#include "gltf_multi.h"
#include "modules/gltf/structures/gltf_mesh.h"
#include "scene/3d/multimesh_instance_3d.h"
#include "scene/3d/node_3d.h"
#include "scene/resources/multimesh.h"
#include <stdexcept>

void GLTFMulti::_bind_methods() {
}

Node3D *GLTFMulti::generate_scene_node(Ref<GLTFState> p_state, Ref<GLTFNode> p_gltf_node, Node *p_scene_parent) {
	ERR_FAIL_NULL_V(p_state, nullptr);
	ERR_FAIL_NULL_V(p_gltf_node, nullptr);
	ERR_FAIL_NULL_V(p_scene_parent, nullptr);

	String name = p_gltf_node->get_name();
	if (!name.contains("-multi-")) {
		return nullptr;
	}

	Vector<String> vec = name.split("-");

	String mesh_name = "";
	String multi_name = "";

	bool found_multi = false;
	for (String s : vec) {
		if (s == "multi" && !found_multi) {
			found_multi = true;
			break;
		}

		if (found_multi) {
			mesh_name += s;
			break;
		}

		multi_name += s;
	}
	MultiMeshInstance3D *multi_mesh_instance;

	bool new_multi = false;
	try {
		multi_mesh_instance = multis.at(multi_name);
		Ref<MultiMesh> multi_mesh = multi_mesh_instance->get_multimesh();
		int instance = multi_mesh->get_instance_count();
		multi_mesh->set_instance_count(instance + 1);
		multi_mesh->set_instance_transform(instance, p_gltf_node->get_xform().);
		should_skip = true;

		return nullptr;
	} catch (std::out_of_range e) {
		multi_mesh_instance = memnew(MultiMeshInstance3D);
		multis[multi_name] = multi_mesh_instance;
		new_multi = true;
	}

	Ref<MultiMesh> multi_mesh = memnew(MultiMesh);
	Ref<GLTFMesh> mesh = p_state->get_meshes()[p_gltf_node->get_mesh()];
	Ref<Mesh> import_mesh = mesh->get_mesh();
	multi_mesh->set_mesh(import_mesh);

	int instance = multi_mesh->get_instance_count();
	multi_mesh->set_instance_count(instance + 1);
	multi_mesh->set_instance_transform(instance, p_gltf_node->get_xform());

	multi_mesh_instance->set_multimesh(multi_mesh);
	multi_mesh_instance->set_name(multi_name);

	if (new_multi) {
		return multi_mesh_instance;
	}

	return nullptr;
}

bool GLTFMulti::should_skip_add_to_scene() {
	return should_skip;
}

bool GLTFMulti::is_dirty() {
	if (multis.empty()) {
		return false;
	}

	return true;
}

void GLTFMulti::clean() {
	multis.clear();
}
