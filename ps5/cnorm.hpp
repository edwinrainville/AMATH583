//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_CNORM_HPP
#define AMATH583_CNORM_HPP

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

// Define worker function with 
double worker_a(const Vector& x, size_t begin, size_t end, size_t partitions) {
  size_t stride = partitions;
  double partial_x = 0.0;
  // Loop through each element and update the sum of squares
  for (size_t i = begin; i < end; i += stride){
    partial_x += x(i) * x(i); 
  }
  return partial_x;
}

// Define Cyclic norm using asynchronous tasks 
double cyclic_two_norm(const Vector& x, size_t partitions) {
  // Vector of futures
  std::vector<std::future<double>> futures_;

  // Launch asynchronous tasks
  for (size_t p = 0; p < partitions; ++p) {
    futures_.push_back(std::async(std::launch::async, worker_a, std::cref(x), p, x.num_rows(), partitions));
  }
  
  // Get Values from asynchronous tasks and combine to get total sum
  double sum = 0.0;
  for (size_t p = 0; p < partitions; ++p) {
    sum += futures_[p].get();
  } 
  return std::sqrt(sum);
}

#endif    // AMATH583_CNORM_HPP
