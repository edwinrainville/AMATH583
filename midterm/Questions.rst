To-Do 6:  Why is Compressed Sparse Row (CSR) format the standard for many 
computations rather than Compressed Sparse Column (CSC) format? 


1. How does the performance (in GFLOP/s) for sparse-matrix by vector
product compare to what you previously achieved for dense-matrix by
dense-matrix product?  Explain, and quantify if you can, (e.g., using
the roofline model).

In general, we see that the sparse-matrix by vector product has a lower performance
than the dense-matrix by dense-matrix products. To quantify this, the highest performing 
sparse-matrix by vector product had a performance of 2.98 GFlops/sec for the Column Spares Row
matrix-vector product for a grid size of 64 and a matrix size of 4096. 


2. Referring to the roofline model and the sparse matrix-vector and dense matrix-matrix algorithms, 
what performance ratio would you theoretically expect to see if neither algorithm was able to 
obtain any reuse from cache?


3. How does the performance (in GFLOP/s) for sparse-matrix by vector
product for COO compare to CSR?  Explain, and quantify if you can,
(e.g., using the roofline model).

The performance of the Compressed Sparse Row (CSR) format is much higher than 
the performance of the Coordinate (COO) matrix format. For the smallest matrix tested (Grid = 64, Matrix = 4096) 
the performance of CSR was 53% higher than that of COO and for the largest matrix tested
(Grid = 2048, Matrix = 4194304) the performance of CSR was 39% higher than that of
COO. These differences in performance are expected since 


4. How does the performance (in GFLOP/s) for sparse-matrix by dense
matrix product (**SPMM**) compare to sparse-matrix by vector product
(**SPMV**)? The performance for SPMM should be about the same as for
SPMV in the case of a 1 column dense matrix.  What is the trend with
increasing numbers of columns?  Explain, and quantify if you can,
using the roofline model.


5. How does the performance of sparse matrix by dense matrix product (in
GFLOP/s) compare to the results you got dense matrix-matrix product in
previous assignments?  Explain, and quantify if you can, using the
roofline model.

To-Do 10: What is the most important thing that I learned from this assignment? 
What is one thing that I am still unclear on? 

