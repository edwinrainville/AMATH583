//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_RNORM_HPP
#define AMATH583_RNORM_HPP

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

// Main Recursive two-norm algorithm 
double recursive_worker_a(const Vector& x, size_t begin, size_t end, size_t level) { 
    // if the level number is zero, compute the two norm 
    if (level == 0) {
      double sum = 0;
      // code that computes the sum of squares of x from begin to end into sum
      for (size_t i = begin; i < end; ++i) {
        sum += x(i) * x(i);
      }
    return sum;
  } else {
      return recursive_worker_a(x, begin, begin+(end-begin)/2, level-1)
         + recursive_worker_a(x, begin+(end-begin)/2, end , level-1) ;
  }
  }

// Dispatch to the actual recursive function -- start with 0 and num_rows() as begin and end
double recursive_two_norm_a(const Vector& x, size_t levels) {
  // Vector of futures
  std::vector<std::future<double>> futures_;

    // Launch asynchronous tasks
  for (size_t p = 0; p < levels; ++p) {
    futures_.push_back(std::async(std::launch::async, recursive_worker_a, std::cref(x), (p * x.num_rows())/levels , ((p+1) * x.num_rows())/levels, levels));
  }

   // Get Values from asynchronous tasks and combine to get total sum
  double sum = 0.0;
  for (size_t p = 0; p < levels; ++p) {
    sum += futures_[p].get();
  }
  return std::sqrt(sum);
}

// Write me
double recursive_worker_b(const Vector& x, size_t begin, size_t end, size_t level) { 
      // if the level number is zero, compute the two norm 
    if (level == 0) {
      double sum = 0;
      // code that computes the sum of squares of x from begin to end into sum
      for (size_t i = begin; i < end; ++i) {
        sum += x(i) * x(i);
      }
    return sum;
  } else {
      return recursive_worker_b(x, begin, begin+(end-begin)/2, level-1)
         + recursive_worker_b(x, begin+(end-begin)/2, end , level-1) ;
  }
 }

// Dispatch to the actual recursive function -- start with 0 and num_rows() as begin and end
double recursive_two_norm_b(const Vector& x, size_t levels) {
  // Vector of futures
  std::vector<std::future<double>> futures_;

    // Launch asynchronous tasks
  for (size_t p = 0; p < levels; ++p) {
    futures_.push_back(std::async(std::launch::deferred, recursive_worker_b, std::cref(x), (p * x.num_rows())/levels , ((p+1) * x.num_rows())/levels, levels));
  }

   // Get Values from asynchronous tasks and combine to get total sum
  double sum = 0.0;
  for (size_t p = 0; p < levels; ++p) {
    sum += futures_[p].get();
  }
  return std::sqrt(sum);
}

#endif    // AMATH583_RNORM_HPP