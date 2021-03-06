#pragma once
#include "interpolator_base.h"
namespace interp
{

	template<extrap_type E>
	class pwc_interp : public base_interp1d<pwc_interp, E>
	{
		using base = base_interp1d<pwc_interp, E>;
		std::vector<double> x_;
		std::vector<double> f_;


	public:
		pwc_interp(const std::vector<double>& x, const std::vector<double>& f)
			: x_{ x }, f_{ f } {}

		pwc_interp(std::vector<double>&& x, std::vector<double>&& f)
			: x_(std::move(x)), f_(std::move(f)) {}

		double interpolate(double p) const
		{
			const auto i0 = base::index_first_elem_above(x_, p);
			return f_[i0];
		}

	};
}