#pragma once
#include<chrono>

namespace utils
{
	class stopwatch
	{

		std::chrono::high_resolution_clock::time_point start_;
		std::chrono::high_resolution_clock::time_point end_;

	public:
		void start()
		{
			start_ = std::chrono::high_resolution_clock::now();
		}

		void stop()
		{
			end_ = std::chrono::high_resolution_clock::now();
		}

		double elapsed_millisec() const
		{
			std::chrono::duration<double, std::milli> res = end_ - start_;
			return res.count();
		}

	};
}