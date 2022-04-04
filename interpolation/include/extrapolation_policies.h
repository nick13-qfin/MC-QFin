#pragma once

namespace interp
{
	template<class derived_extr>
	class base_extrapolation
	{
	public:
		const derived_extr& true_this() const
		{
			return static_cast<const derived_extr&>(*this);
		}

		template<class vector_t>
		double left_extrap(double x, const vector_t& x_vec, const vector_t& y_vec) const
		{
			return true_this().left_extrap(x, x_vec, y_vec);
		}

		template<class vector_t>
		double right_extrap(double x, const vector_t& x_vec, const vector_t& y_vec) const
		{
			return true_this().right_extrap(x, x_vec, y_vec);
		}

	};

	class unchecked_boundaries : public base_extrapolation<unchecked_boundaries>
	{

	};

	template<class T>
	constexpr bool is_extrapolation = std::is_base_of_v< base_extrapolation<T>, T>;

	template<class T>
	concept extrapolation_type = is_extrapolation<T>;
}
