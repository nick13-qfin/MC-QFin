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


	template<template<class> class derived_interp, extrapolation_type E>
	class base_interp1d
	{
		const derived_interp<E>& true_this() const
		{
			return static_cast<const derived_interp<E>&>(*this);
		}

		derived_interp<E>& true_this() 
		{
			return static_cast<derived_interp<E>&>(*this);
		}

	public:
		double interpolate(double t) const
		{
			if constexpr (std::is_same_v<unchecked_boundaries, E>)
				return true_this().interpolate(t);
			else
			{
				//TODO check boundaries
				return true_this().interpolate(t);
			}
		}

	};

	template<template<class> class derived_interp, extrapolation_type E>
	using is_interp = std::is_base_of<
		base_interp1d<derived_interp, E>,
		derived_interp<E>>;

	template<template<class> class derived_interp, extrapolation_type T>
	constexpr bool is_interp_type = std::is_base_of_v<
		base_interp1d<derived_interp, T>,
		derived_interp<T>>;

	template<class full_interp_t>
	concept interp_type = requires (full_interp_t f, double a)
	{
		f.interpolate(a);
	};
		

	template<extrapolation_type E>
	class dummy_interp : public base_interp1d<dummy_interp, E>
	{
	public:
		double interpolate(double t) const
		{
			return 1.0;
		}
	};

	template<extrapolation_type E>
	class pwc_interp : public base_interp1d<pwc_interp, E>
	{
		
		std::vector<double> x_;
		std::vector<double> f_;
		

	public:
		pwc_interp(const std::vector<double>& x, const std::vector<double>& f)
			: x_{x}, f_{f} {}

		pwc_interp(std::vector<double>&& x, std::vector<double>&& f)
			: x_(std::move(x)), f_(std::move(f)) {}

		double interpolate(double p) const
		{
			const auto i0 = index_first_elem_above(x_, p);
			return f_[i0];
		}

	};



}