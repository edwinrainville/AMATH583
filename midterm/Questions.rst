AMATH 583 - Midterm Questions 
Written By: EJ Rainville, Spring 2021
--------------------------------------------------------------------------
To-Do 6:  Does Compressed Sparse Row (CSR) format or Compressed Sparse Column (CSC) 
format have higher performance for sparse matrix by vector product? Explain and quantify which one has higher performance. 

The performance values for the Compressed Sparse Row (CSR) and Compressed Sparese Column (CSC) sparse matrix by vector 
algorithms are shown in the table below. 

 N(Grid) N(Matrix)         NNZ         COO       COO^T         CSR       CSR^T         CSC       CSC^T         AOS       AOS^T
      64      4096       20224      1.3432     1.71057     2.63338     2.04221     1.88808     2.38258     1.40941     1.57588
     128     16384       81408     1.31104     1.69991     2.60506     2.02615     2.04683     2.47641     1.25368     1.50819
     256     65536      326656     1.13143     1.34124     2.22557     1.64656     1.63328     1.92883     1.06035     1.22743
     512    262144     1308672     1.07378     1.13182     1.99417     1.26137     1.23898     1.86953    0.978446    0.922412
    1024   1048576     5238784    0.828124    0.948756     1.57506     1.27505     1.17553      1.7337    0.790112    0.822471
    2048   4194304    20963328    0.860034    0.995292     1.21088     1.01333     1.02573     1.37464    0.757141    0.755435

The highest performance was by the CSR algorithm for a problem size of 4096 with 20224 non-zero elements with a 
peformance of 2.6 Gflops/sec. The performance for the CSC algorithm was 1.88 GFlops/sec for the same size problem. The ratio 
of performance between the CSR and CSC algorithms is approximately 1.4 meaning that the CSR algorithm performs 
almost 40% better than the CSC algorithm. This is most likely due to how the data is being stored and how it can 
be accessed quickly. The matrices are row-major ordered meaning that each element in a row is physically stored 
next in memory making the time to access the next element in a row is very short while the next element in a column 
is not as fast to access. Since the values are not stored as locally in the CSC version extra time to access each 
element is needed thus reducing the overall performance.


--------------------------------------------------------------------------
1. How does the performance (in GFLOP/s) for sparse-matrix by vector
product compare to what you previously achieved for dense-matrix by
dense-matrix product?  Explain, and quantify if you can, (e.g., using
the roofline model).

The performance values for the sparse-matrix by vector product are shown in the followng table. 

 N(Grid) N(Matrix)         NNZ         COO       COO^T         CSR       CSR^T         CSC       CSC^T         AOS       AOS^T
      64      4096       20224      1.3432     1.71057     2.63338     2.04221     1.88808     2.38258     1.40941     1.57588
     128     16384       81408     1.31104     1.69991     2.60506     2.02615     2.04683     2.47641     1.25368     1.50819
     256     65536      326656     1.13143     1.34124     2.22557     1.64656     1.63328     1.92883     1.06035     1.22743
     512    262144     1308672     1.07378     1.13182     1.99417     1.26137     1.23898     1.86953    0.978446    0.922412
    1024   1048576     5238784    0.828124    0.948756     1.57506     1.27505     1.17553      1.7337    0.790112    0.822471
    2048   4194304    20963328    0.860034    0.995292     1.21088     1.01333     1.02573     1.37464    0.757141    0.755435

Here we see that the Compressed Sparse Row (CSR) format has the highest performance values 
for most problem sizes. The CSR matrix-vector product is surpassed slightly by Compressed Sparse 
Column (CSC) transpose format for larger problem sizes. The dense-matrix multiplications had significantly
higher performance values ranging up to 20 GFlops/sec as shown in the following table from the previous assignment. 

   N      mult_0      mult_1      mult_2      mult_3     mul_t_0     mul_t_1     mul_t_2     mul_t_3
       8     2.64335      3.6346     7.26921     7.93004     3.35502     3.35502     7.26921     7.93004
      16     2.22953     2.37362     8.40776     17.8934     2.35758     2.34964     7.84094     14.8477
      32     2.17813     2.67286     8.71251     25.8886     2.47569     2.87651     8.46823        22.1
      64     1.99784     2.63668     7.88712      26.677     2.37439      2.6521     7.81912     22.6755
     128     1.81777     2.16889     7.16237     25.0683     2.12611     2.30575     7.35793     20.9308
     256     1.16191     1.36703     4.89954     21.5009     1.95118     2.01877     7.14385     19.9513
     512    0.890288     1.28373     4.37019     20.0643     1.81654     1.77097     6.61566     16.5422

An important point to note here is the size of the matrices used for computations between the sparse-matrix by
vector product and the dense-matrix matrix product. The matrices for the sparse computation are much larger 
and the computations were completed very quickly while the matrices for the dense-matrix product took a very long
time to compute even for smaller problems.  The highest performing sparse-matrix by vector product had a performance 
of 2.98 GFlops/sec for the Column Spares Row matrix-vector product for a grid size of 64 and a matrix size of 4096. 
Since that was the smallest size computed for the sparse-matrix vector product and my computer has not been able
to compute that size matrix for the dense product we can estimate the performance using the roofline model and then 
estimate the ratio between the two methods. Recalling the roofline model for this machine, we saw that the maximum 
performance possible was 46.4 GFLOPS/sec. This performance could only be achieved by an algortihm with very high
arithmetic intensity above approximately an arithmetic intensity of two. For an unoptimized matrix-matrix product and the 
matrix vector product we saw that the arithmetic intensity was 1/12 flop/byte(3 doubles and two operations). Applying this 
to the roofline model, we see that the performance is bandwidth limited at this intensity. Using a matrix size of 4096, 
we see that the sparse matrix only needs to store approximately 0.16 MB of data which means that it can fit in the L3 cache 
of size 6.3 MB. Since this sparse problem can fit in the L3 cache the estimated performance from the roofline model is 
4 GFlops/sec which is close to that of the measured performace. For the dense matrix product of size 4096, approximately 
134.2 MB of data need to stored and computed with which means that this problem cannot fit in the cache and is then in DRAM 
which reduces the locality and therefore the performance of the computation. Using the same arithmetic intensity, the 
roofline model estimates that the performance would be around 2 GFlops/sec which means that the ratio between the 
sparse-matrix vector product and dense matrix matrix product is estimated to be 2 meaning the sparse matrix vector 
product performs twice as well as the dense matrix product. 


--------------------------------------------------------------------------
2. Referring to the roofline model and the sparse matrix-vector and dense matrix-matrix algorithms, 
what performance ratio would you theoretically expect to see if neither algorithm was able to 
obtain any reuse from cache?

If neither the sparse matrix-vector product or the dense matrix-matrix product algorithms were
able to reuse from cache we would expect the ratio of sparse-matrix vector product performance to
dense matrix product performance to be approximately 2 based on the roofline model for this machine.
Both algorithms to have an arithmetic intensity of 1/12 (3 double precision value and 2 operations) 
which means that they are both limited in performance by the bandwidth of the cache or DRAM. Since the 
dense matrix product muct store and access so much more data than the sparse matrix computation does, 
the dense matrix product cannot fully fit in a cache for most problem sizes meaning the locality is reduced
and in turn so is the performance. The sparse matrix vector product has much less data storage and access meaning
for many problems the data can be stored in cache and accessed quickly to improve performance. 


--------------------------------------------------------------------------
3. How does the performance (in GFLOP/s) for sparse-matrix by vector
product for COO compare to CSR?  Explain, and quantify if you can,
(e.g., using the roofline model).

The performance of the Compressed Sparse Row (CSR) format is much higher than the performance of the 
Coordinate (COO) matrix format. The performance difference between the two can be quanitfied as the following, 
for the smallest matrix tested (Grid = 64, Matrix = 4096) the ratio of performance of CSR to COO was 1.96 ~ 2 meaning
that CSR performs twice as well as COO for this problem size. For the largest matrix tested (Grid = 2048, Matrix = 4194304) 
the ratio of performance of CSR to COO was 1.4. These differences in performance are expected since the CSR format has
less data access required than the COO format since the row index array is eliminated and the column index array
is reduced in the CSR format compared to the COO format that is storing all of the indices for the rows and columns
of each nonzero matrix entry. Since the CSR format is storing less data, more of the data can be stored in cache 
which improves the locality of the data and therefore improves the performance. Since the CSR format contains 
much less data than the COO format, larger problems can fit into the L1 and L2 caches compared to problems of the
same size in the COO format that would have to be in L3 cache or DRAM thus reducing the performance by the significant
factors that we measured. Using the roofline model for a problem size of 4096 that has 20224 nonzero elements, we expect
that the COO algorithm will need to store 0.24 MB of data ((2 indices * 2 bytes * 20224 elements) + (20224 elements * 8 bytes))
while the  CSR algorithm will only need to store at max 0.2 MB ((20224 running total integers * 2 bytes ) + (20224 elements * 8 bytes)) 
and most likely stores much less than this depending on the matrix which means it can fit more into cache and improve locality which
then improves performance. 


--------------------------------------------------------------------------
4. How does the performance (in GFLOP/s) for sparse-matrix by dense
matrix product (**SPMM**) compare to sparse-matrix by vector product
(**SPMV**)? The performance for SPMM should be about the same as for
SPMV in the case of a 1 column dense matrix.  What is the trend with
increasing numbers of columns?  Explain, and quantify if you can,
using the roofline model.

The performnce of the sparse-matrix by dense matrix product performance was very similar to the performance
of the sparse-matrix by vector product performance although the performance of the sparse-matrix vector product was 
a bit better than the sparse-matrix by dense-matrix product. The performance values for the sparse-matrix by dense-matrix
product can be seen in the table below. 

 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC         AOS
      64      4096       20224       1     1.25851     1.17985     1.51889    0.746574
     128     16384       81408       1     1.29934     1.20484     1.44057    0.693886
     256     65536      326656       1     1.11225     1.02735     1.29406    0.587696
     512    262144     1308672       1     1.12172     1.01681     1.10419    0.508405
    1024   1048576     5238784       1      1.0222     1.00384     1.02847    0.560673
    2048   4194304    20963328       1    0.883996    0.937657    0.978289    0.554795

Here we can see that the highest performance was from the Compressed Sparse Column (CSC) format for the smallest problem 
(Grid = 64, Matrix = 4096, NNZ = 20224). Since there are 20224 nonzero elements in this matrix, we expect that each is a 
64 bit double precision value and therefore the total space needed for this matrix is approximately 0.2 MB 
((20224 running total integers * 2 bytes ) + (20224 elements * 8 bytes)). The space needed for the vector is also expected
to be approximately 0.03 MB (4096 elements * 8 bytes) meaning the total space required for this problem is 0.23 MB. As we saw in 
the previous assignment, the L1 cache is 32 kB, the L2 cache is 262 kB and the L3 cache is 6.3 MB. Therefore this problem
can entirely fit in the L3 cache which improves the locality and therefore improves the performance. The sparse matrix by dense
matrix product requires more space since the corresponding dense matrix requires 134.2 MB bringing the total space required to 
134.4 MB which cannot fit in the L3 cache and therefore must be stored in DRAM which reduces locality and in turn reduces performance
as we see. The ratio of measured performance between the sparse matrix by vector product to the sparse-matrix by dense matrix product is
approximately 2.2 ~ 2. Using the roofline model with this size matrix and an arithmetic intensity of 1/12 we expect an estimated performance 
ratio of approximately 2 which agrees with the measured ratio above. 


--------------------------------------------------------------------------
5. How does the performance of sparse matrix by dense matrix product (in
GFLOP/s) compare to the results you got dense matrix-matrix product in
previous assignments?  Explain, and quantify if you can, using the
roofline model.

As seen in the table above, the maximum performance for the sparse matrix by dense matrix product was the CSC algorithm 
for a matrix size of 4096 with a performance of 1.51 Gflops/sec. The highest performance of a dense matrix-matrix product 
was 26.67 Gflops/sec for a matrix size of 64 which is significantly smaller than the matrix above as seen in the table above.
As mentioned previously, the smallest matrix computed for the sparse matrix by dense matrix products was 4096 while the 
largest that my computer could compute in a reasonable amount of time was a size of 512. Since this both of these algorithms 
have an arithmetic intensity of 1/12 as developed in previous questions, we know that the performance is bandwidth limited 
by cache or DRAM depending on the size of the problem. Lets take for example the problem with size 4096, here we expect the 
amount of data stored by the sparse matrix by dense matrix product to be 134.2 MB as computed in the previous question. We 
then exepect the amount of data stored for the dense matrix-matrix product to be approximately 268 MB since there are two dense
matrices both of size 134 MB. Both of these problems are too large to fit in the L3 cache of 6.3 MB so we expect both problems to
bes stored in DRAM so the expeceted performance ratio between the two algorithms using the roofline model is 1 since we expect them
to have the same performance. While these problems may have the same performance, the amount of computations and data that need to 
be stored in the sparse matrix by dense matrix product is significantly reduced meaning that while the rate may be the same, the 
computation will be completed faster for the sparse matrix by dense matrix product which in the end is a very important characteristic
for high performance computing.   


--------------------------------------------------------------------------
To-Do 10: What is the most important thing that I learned from this assignment? 
What is one thing that I am still unclear on? 

The most important thing that I learned from this assignment was how much storing less information by using a compressed 
represenation can improve computations by improving locality and in turn performance. Using the compressed matrix representations
also helps to reduce the required data for computations and so a large matrix problem can be computed much faster. I am still a bit
unclear on the differences in performance between the CSR and CSC formats. I understand that it is mostly how the data is stored and
accessed between the two with the differences in row or column major ordering but it is surprising that such similar algorithms have 
such drastically different results.