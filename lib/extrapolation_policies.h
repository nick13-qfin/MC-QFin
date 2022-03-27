#pragma once

namespace utils
{
	template<class derived_extr>
	class base_extrapolation
	{

	};

	class unchecked_boundaries : public base_extrapolation<unchecked_boundaries>
	{

	};

	template<class T>
	constexpr bool is_extrapolation = std::is_base_of_v< base_extrapolation<T>, T>;

	template<class T>
	concept extrapolation_type = is_extrapolation<T>;
}