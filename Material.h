#include <sstream>
#include <string>
#pragma once

using namespace std;

class Material
{
public:
	double k_diff_R, k_diff_G, k_diff_B;
	double k_ambient_R, k_ambient_G, k_ambient_B;
	double k_spec;
	double n_spec;

	Material(double kdiffr, double kdiffg, double kdiffb, double kambr, double kambg, double kambb, double kspec, double nspec) : k_diff_R(kdiffr), k_diff_G(kdiffg), k_diff_B(kdiffb), k_ambient_R(kambr), k_ambient_G(kambg), k_ambient_B(kambb), k_spec(kspec), n_spec(nspec) {}

	string toString();
};