#include "Material.h"

string Material::toString()
{
	stringstream ss;
	ss << k_diff_R << ", " << k_diff_G << ", " << k_diff_B << ", " << k_ambient_R << ", " << k_ambient_G << ", " << k_ambient_B << ", " << k_spec << ", " << n_spec;
	return ss.str();
}