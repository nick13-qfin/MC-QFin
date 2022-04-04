#pragma once
#include "extrapolation_policies.h"

namespace interp
{
	class flat_extrap : public base_extrapolation<flat_extrap>
	{
	public:
		template<class vector_t>
		double left_extrap(double x, const vector_t& x_vec, const vector_t& y_vec) const
		{
			return y_vec.front();
		}

		template<class vector_t>
		double right_extrap(double x, const vector_t& x_vec, const vector_t& y_vec) const
		{
			return y_vec.back();
		}


	};
}