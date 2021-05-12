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
the "sweet spot" that allows for more concurrent computation but does not break the job into too many parts that there is 



fnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads for ``partitioned_two_norm_a``?

* How much parallel speedup do you see for 1, 2, 4, and 8 threads for ``partitioned_two_norm_b``?  

* Explain the differences you see between ``partitioned_two_norm_a`` and ``partitioned_two_norm_b``.


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
