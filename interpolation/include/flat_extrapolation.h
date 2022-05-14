#pragma once
#include "extrapolation_policies.h"

namespace interp
{
	class flat_extrap : public base_extrapolation<flat_extrap>
	{
	public:
		template<vector_type V>
		double left_extrap(double x, const V& x_vec, const V& y_vec) const
		{
			return y_vec.front();
		}

		template<vector_type V>
		double right_extrap(double x, const V& x_vec, const V& y_vec) const
		{
			return y_vec.back();
		}


	};
}