#include "register_types.h"
#include "gltf_multi.h"
#include "modules/gltf/gltf_document.h"
#include "modules/register_module_types.h"

void initialize_gltf_multi_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_EDITOR) {
		return;
	}

	Ref<GLTFMulti> a;
	a.instantiate();
	GLTFDocument::register_gltf_document_extension(a);
}

void uninitialize_gltf_multi_module(ModuleInitializationLevel p_level) {
}
