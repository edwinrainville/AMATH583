Problem Set #5
Written By: EJ Rainville, Spring 2021
---------------------------------------

Question 1
----
* At what problem size do the answers between the computed norms start to differ?

The norm computed with reversed values begins to differ from the other norms with a problem size
of approixmately 85. The norm computed with sorted values begins to differ from the other norm 
at a problem size of approximately 19000. 

* How do the absolute and relative errors change as a function of problem size? 

The relative difference stays approximately the same as the problem size increases while the 
absolute difference increases with increasing problem size. 

* Does the Vector class behave strictly like a member of an abstract vector class? 

The Vector class does not behave strictly like a member of an abstract vector class


* Do you have any concerns about this kind of behavior? 

Yes, I am concerned that as we get to larger problems errors can become significant 
even though they are small relative to the problem. This can be important if you are computing 
a large problem with small values or many orders of magnitude difference between values. 



pnorm
-----

* What was the data race?

The data race that was occuring is a low-level data race due to multiple threads trying to update a shared variable at almost 
the same time. The variable "partial" in the function worker_a is shared and therefore as multiple threads try to access
it with no protection there is a chance that each thread could load the current value onto the thread stack then update the
value and write it back out without "knowing" that the other thread had also operated on the original value thus the overall shared value
would not be updated for each operation and the final value would be incorrect. The paper titled "High-level Data Races" written by
Artho et al. was used as a supplement for understanding data races, article can be found at this link http://www.runtime-verification.org/course/resources/lecture9/hldataraces.pdf.


* What did you do to fix the data race?  Explain why the race is actually eliminated (rather than, say, just made less likely).

In order to fix this data race, I used a lock guard within the worker_a function. By using a lock_guard to solve the problem it guarantees that
a data race will not occur because only one thread can access the shared value "partial" at a specific time. The thread that accesses the shared value will update the
shared value prior to another thread being able to access it which guarantees that the data race problem is eliminated. 

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?

The values from the pnorm.exe test are shown in the following table. 
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     5.80935     5.15728     8.15183     10.8691     9.71949             0             0   1.92318e-16             0
     2097152     4.94401     4.78229     8.45794     11.2463     10.8873             0   5.43881e-16   4.07911e-16   9.51792e-16
     4194304     4.78802     4.53929     8.06597     10.8101     10.5917             0    9.6159e-16   1.92318e-16   5.76954e-16
     8388608     4.68034     4.58201      8.1382     11.1277     11.4791             0    1.3595e-16   6.79751e-16             0
    16777216     3.65858     3.07436     5.26639     5.90153     7.07473             0   3.84567e-16   1.34599e-15   3.84567e-16
    33554432     3.82387     3.73866     4.64421     4.70939     4.03056             0   7.20652e-15   7.61444e-15   6.79861e-15

Here, we can see that the data race is eliminated with the relative error being below machine precision for all problem sizes. We also see that
there is significant speedup for the multiple threads; however, the speedup is not proportional for each thread since these threads are 
running concurrently rather than directly in parallel. We see that four threads in general gives the highest performance since it is most likely
the "sweet spot" that allows for more concurrent computation but does not break the job into too many parts that there is time spent organizing 
the threads rather than computing on them which is most likelly the case for 8 threads since we see a reduction in performance. For a problem size of 
1048576, we see a speed up for 1, 2, 4 and 8 threads of 0.8877, 1.403, 1.8709 and 1.673 respectively.  



fnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads for ``partitioned_two_norm_a``?

The performance values from the 'partitioned_two_norm_a' function are shown in the following table. 

           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     3.85812     4.76805     7.95927     8.71403     8.21811             0             0   1.92318e-16             0
     2097152     5.22148     4.94401     8.60009      11.499      11.499             0   5.43881e-16   4.07911e-16   9.51792e-16
     4194304     4.89989     4.72332      8.2565     10.9227      11.275             0    9.6159e-16   1.92318e-16   5.76954e-16
     8388608     4.76209     4.60135     8.26151     11.3596     11.8535             0    1.3595e-16   5.43801e-16             0
    16777216      4.1943     4.12072     6.82794     7.67585     8.63533             0   3.84567e-16   1.34599e-15   3.84567e-16
    33554432     4.18124     4.10452     5.02688     4.37191     3.64722             0   7.20652e-15   7.61444e-15   6.66264e-15

  Here we see that 4 and 8 threads are very simialar in their performance and genreallt have the best performance except for very large
  problems where 2 threads has hgiher performance. The speedup values for the largest problem size of 33554432 for 1, 2, 4 and 8 threads 
  are 0.981, 1.202, 1.0545, and 0.8722 respectively so there was not much speedup from multithreading this problem for large problems. 
  For the smallest problem of 1048576 we see speedup values for 1, 2, 4 and 8 threads as 1.235, 2.063, 2.258, and 2.13 respectively. Which
  shows for these smaller problems, parititioning the computions into multiple threads and concurrently computing them leads to significant 
  speedup. 


* How much parallel speedup do you see for 1, 2, 4, and 8 threads for ``partitioned_two_norm_b``?  

The performance values for the 'partitioned_two_norm_b' function are shown in the table below. 

           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     5.07953     5.26473     5.26473     4.65819     4.97944             0   1.15258e-15   1.34467e-15   1.34467e-15
     2097152     4.60996     4.71618     4.67311     4.50841     4.50841             0   2.71928e-15   2.03946e-15   2.03946e-15
     4194304     4.35094     4.35094     4.36907     4.33296      4.2625             0   9.61294e-16   3.84518e-16             0
     8388608     4.29338      4.2105     4.13075     4.13075     4.24326             0   1.49582e-15   1.08787e-15   5.43933e-16
    16777216     4.14984     4.03576     4.04967     3.45413     2.46724             0   5.00099e-15   4.03926e-15   3.84691e-15
    33554432     3.56962      3.8022     3.91305     3.89037     3.82387             0   3.67179e-15   4.62374e-15   5.57568e-15

Here we dont see nearly the same kind of performance that we see for the function abov and we see very consistent performance values 
for each number of threads forr any problem size. The speedup values for the smallest problem size for 1, 2, 4 and 8 threads are
1.03, 1.03, 0.918, and 0.98 which indicates that using any number of threads doesnt lead to any significant speedup for this algorithm. 
We see similar values for speedup for the largest problem as well. 


* Explain the differences you see between ``partitioned_two_norm_a`` and ``partitioned_two_norm_b``.

The difference between the two algorithms is the asynchronous launching policy where 'partitioned_two_norm_a' has a policy of
'std::launch::async' and 'partitioned_two_norm_b' has a policy of 'std::launch::deferred.' The policy for the 'partitioned_two_norm_a'
suggests that the asynchronous tasks are launched as soon as they are created so there are tasks being evaluated and launched while the 
rest of the tasks are being created and this concurrent computation results in the speedup we see above. In 'partitioned_two_norm_b' we are using a 
deferred launch policy meaning that the tasks are not launched until the result is asked for which means that no concurrent computation is occuring
while the tasks are being created but they are all concurrently computing once they are asked for which floods the CPU essentially the 
same as the sequential run which is why the performance is effectively the same as the sequential run. 


cnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?

* How does the performance of cyclic partitioning compare to blocked?  Explain any significant differences, referring to, say, performance models or CPU architectural models.


rnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?

* What will happen if you use ``std:::launch::deferred`` instead of ``std:::launch::async`` when launching tasks?  When will the computations happen?  Will you see any speedup?  For your convenience, the driver program will also call ``recursive_two_norm_b`` -- which you can implement as a copy of ``recursive_two_norm_a`` but with the launch policy changed.


General
-------

* For the different approaches to parallelization, were there any major differences in how much parallel speedup that you saw?

* You may have seen the speedup slowing down as the problem sizes got larger -- if you didn't keep trying larger problem sizes.  What is limiting parallel speedup for two_norm (regardless of approach)?  What would determine the problem sizes where you should see ideal speedup?  (Hint: Roofline model.)


Conundrum #1
------------

1. What is causing this behavior?

2. How could this behavior be fixed?

3. Is there a simple implementation for this fix?



Parallel matvec
---------------

* Which methods did you implement?

* How much parallel speedup do you see for the methods that you implemented for 1, 2, 4, and 8 threads?



Conundrum #2
------------

1. What are the two "matrix vector" operations that we could use?

2. How would we use the first in pagerank?  I.e., what would we have to do differently in the rest of pagerank.cpp to use that first operation?

3. How would we use the second?
