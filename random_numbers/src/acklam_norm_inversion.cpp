#include "../include/acklam_norm_inversion.h"

namespace rng
{
	double acklam_inversion::invert(double p) const
	{
		if ((p > 0.0) && (p < p_low))
		{
			auto q = sqrt(-2 * log(p));
			return (((((c_1 * q + c_2) * q + c_3) * q + c_4) * q + c_5) * q + c_6) /
				((((d_1 * q + d_2) * q + d_3) * q + d_4) * q + 1);
		}
		else if ((p <= p_high) && (p >= p_low))
		{
			auto q = p - 0.5;
			auto r = q * q;
			return (((((a_1 * r + a_2) * r + a_3) * r + a_4) * r + a_5) * r + a_6) * q /
				(((((b_1 * r + b_2) * r + b_3) * r + b_4) * r + b_5) * r + 1);
		}
		else if (p > p_high)
		{
			auto q = sqrt(-2 * log(1 - p));
			return -(((((c_1 * q + c_2) * q + c_3) * q + c_4) * q + c_5) * q + c_6) /
				((((d_1 * q + d_2) * q + d_3) * q + d_4) * q + 1);
		}

		return -HUGE_VAL;
	}

}