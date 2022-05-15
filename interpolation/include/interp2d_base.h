#pragma once

namespace interp
{
	template<class derived_interp>
	class interp2d_base
	{
		const derived_interp& true_this() const
		{
			return static_cast<const derived_interp&>(*this);
		}

	public:
		double interpolate(double t, double x) const
		{
			return true_this().interpolate(t, x);
		}
	};

}