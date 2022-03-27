#pragma once
#include <algorithm>
#include <vector>
#include "../lib/extrapolation_policies.h"

namespace utils
{
	size_t index_first_elem_above(const std::vector<double>& x, double x0)
	{
		const size_t n = x.size();
		for (size_t i = n - 2; i >= 0; --i)
		{
			if (x[i] <= x0)
				return i;
		}
		return n - 2;
	}


	template<template<class> class derived_interp, class extrap_policy_t>
	class base_interp1d
	{
		const derived_interp<extrap_policy_t>& true_this() const
		{
			return static_cast<const derived_interp<extrap_policy_t>&>(*this);
		}

		derived_interp<extrap_policy_t>& true_this() 
		{
			return static_cast<derived_interp<extrap_policy_t>&>(*this);
		}

	public:

		double value(double t) const
		{
			if constexpr (std::is_same<extrap_policy_t, unchecked_boundaries>)
				return true_this().value(t);
			else
			{
				//TODO check boundaries
				return true_this().value(t);
			}
		}

	};

	template<template<class> class derived_interp, class extrap_policy_t>
	using is_interp = std::is_base_of<
		base_interp1d<derived_interp, extrap_policy_t>,
		derived_interp<extrap_policy_t>>;

	template<class extrap_policy_t>
	class dummy_interp : public base_interp1d<dummy_interp, extrap_policy_t>
	{
	public:
		double value(double t) const
		{
			return 1.0;
		}
	};

	template<class extrap_policy_t>
	class pwc_interp : public base_interp1d<pwc_interp, extrap_policy_t>
	{
		
		std::vector<double> x_;
		std::vector<double> f_;
		

	public:
		pwc_interp(const std::vector<double>& x, const std::vector<double>& f)
			: x_{x}, f_{f} {}

		pwc_interp(std::vector<double>&& x, std::vector<double>&& f)
			: x_(std::move(x)), f_(std::move(f)) {}

		double value(double p) const
		{
			const auto i0 = index_first_elem_above(x_, p);
			return f_[i0];
		}

	};



}