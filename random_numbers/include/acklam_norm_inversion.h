#pragma once
#include <math.h>
#include <type_traits>

namespace rng
{
	template<class derived_inversion>
	class norm_inversion
	{
	public:
		const derived_inversion& true_this() const
		{
			return static_cast<const derived_inversion&>(*this);
		}

		double invert(double p) const
		{
			return true_this().invert(p);
		}
	};

	class acklam_inversion : public norm_inversion<acklam_inversion>
	{
		double a_1 = -3.969683028665376e+01;
		double a_2 = 2.209460984245205e+02;
		double a_3 = -2.759285104469687e+02;
		double a_4 = 1.383577518672690e+02;
		double a_5 = -3.066479806614716e+01;
		double a_6 = 2.506628277459239e+00;

		double b_1 = -5.447609879822406e+01;
		double b_2 = 1.615858368580409e+02;
		double b_3 = -1.556989798598866e+02;
		double b_4 = 6.680131188771972e+01;
		double b_5 = -1.328068155288572e+01;

		double c_1 = -7.784894002430293e-03;
		double c_2 = -3.223964580411365e-01;
		double c_3 = -2.400758277161838e+00;
		double c_4 = -2.549732539343734e+00;
		double c_5 = 4.374664141464968e+00;
		double c_6 = 2.938163982698783e+00;

		double d_1 = 7.784695709041462e-03;
		double d_2 = 3.224671290700398e-01;
		double d_3 = 2.445134137142996e+00;
		double d_4 = 3.754408661907416e+00;

		double p_low = 0.02425;
		double p_high = 1 - p_low;
	public:
		double invert(double p) const;
	};

	template<class T>
	concept norm_inv_type = std::is_base_of_v< norm_inversion<T>, T>;
}