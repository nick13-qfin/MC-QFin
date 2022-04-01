#pragma once
#include <Eigen/Dense>

namespace mc
{
	template<class derived>
	class rng_base
	{
	public:
		derived& true_this() 
		{
			return static_cast<derived&>(*this);
		}

		double next()
		{
			return true_this().next();
		}

		void fill_matrix(Eigen::MatrixXd& out_matrix, size_t n_rows, size_t n_cols)
		{
			for (size_t i = 0; i < n_rows; i++)
			{
				for (size_t j = 0; j < n_cols; j++)
					out_matrix(i, j) = next();
			}
		}

		template<class vector_t>
		void fill_vector(vector_t& vec, size_t n)
		{
			for (size_t i = 0; i < n; i++)
				vec[i] = next();
		}
	};
}