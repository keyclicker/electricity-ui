/**
  * This file is usinng as precompiled header.
*/

#ifndef STATIC_HPP_INCLUDED
#define STATIC_HPP_INCLUDED

#include <Eigen/Dense>

#include <boost/multiprecision/cpp_dec_float.hpp>

using cpp_float = boost::multiprecision::number<
					boost::multiprecision::cpp_dec_float<20> >;

using MatrixXb = Eigen::Matrix< cpp_float,
								Eigen::Dynamic,
								Eigen::Dynamic >;

using VectorXb = Eigen::Matrix< cpp_float,
								Eigen::Dynamic,
								1 >;

using boost::multiprecision::pow;

#endif
