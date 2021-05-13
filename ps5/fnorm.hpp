//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_FNORM_HPP
#define AMATH583_FNORM_HPP

#include "Timer.hpp"
#include "Vector.hpp"
#include "amath583.hpp"
#include "norm_utils.hpp"

#include <cassert>
#include <cmath>
#include <future>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

double worker_a(const Vector& x, size_t begin, size_t end) {
  double sum_of_squares = 0.0;
  // Loop through each element and update the sum of squares
  for (size_t i = begin; i < end; ++i){
    sum_of_squares += x(i) * x(i);
  }
  return sum_of_squares;
}

double partitioned_two_norm_a(const Vector& x, size_t partitions) {
  size_t blocksize = x.num_rows() / partitions;
  // Vector of futures
  std::vector<std::future<double>> futures_;

  // Launch asynchronous tasks
  for (size_t p = 0; p < partitions; ++p) {
    futures_.push_back(std::async(std::launch::async, worker_a, std::cref(x), p*blocksize, (p+1)*blocksize));
  }
  
  // Get Values from asynchronous tasks and combine to get total sum
  double sum = 0.0;
  for (size_t p = 0; p < partitions; ++p) {
    sum += futures_[p].get();
  } 
  return std::sqrt(sum);
}

double partitioned_two_norm_b(const Vector& x, size_t partitions) {
  size_t blocksize = x.num_rows() / partitions;
  // Vector of futures
  std::vector<std::future<double>> futures_;

  // Launch asynchronous tasks - use deferred method
  for (size_t p = 0; p < partitions; ++p) {
    futures_.push_back(std::async(std::launch::deferred, worker_a, std::cref(x), p*blocksize, (p+1)*blocksize));
  }
  
  // Get Values from asynchronous tasks and combine to get total sum
  double sum = 0.0;
  for (size_t p = 0; p < partitions; ++p) {
    sum += futures_[p].get();
  } 
  return std::sqrt(sum);
}

#endif    // AMATH_583_FNORM_HPP
