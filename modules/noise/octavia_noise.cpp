#ifndef FASTNOISE_LITE_H
#define FASTNOISE_LITE_H

#include "core/io/image.h"
#include "core/object/ref_counted.h"
#include "noise.h"
#include "scene/resources/gradient.h"

class OctaviaNoise : public Noise {
	GDCLASS(OctaviaNoise, Noise);
	OBJ_SAVE_TYPE(OctaviaNoise);

public:
protected:
	static void _bind_methods();
	void _validate_property(PropertyInfo &p_property) const;

private:
public:
	OctaviaNoise();
	~OctaviaNoise();

	// Interface methods.
	real_t get_noise_1d(real_t p_x) const override;

	real_t get_noise_2dv(Vector2 p_v) const override;
	real_t get_noise_2d(real_t p_x, real_t p_y) const override;

	real_t get_noise_3dv(Vector3 p_v) const override;
	real_t get_noise_3d(real_t p_x, real_t p_y, real_t p_z) const override;

	void _changed();
};

#endif // FASTNOISE_LITE_H
