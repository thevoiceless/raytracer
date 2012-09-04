#pragma once

struct Material
{
	double k_diff_R, k_diff_G, k_diff_B;
	double k_ambient_R, k_ambient_G, k_ambient_B;
	double k_spec;
	double n_spec;
};