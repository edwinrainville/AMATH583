
PS2 Questions
=============

Add your answers to this file in plain text after each question.  Leave a blank line between the text of the question and the text of your answer and at least two lines between your answer and the next question.

.. role:: cpp(code)
   :language: c++


Inner Product
-------------

1. How would you use :cpp:`dot` to implement :cpp:`two_norm`?

You could use the "dot" product function that we developed to compute the two-norm by first computing the dot product of a vector x with itself (dot(x, x)) then taking the square root of that dot product (std::sqrt(dot(x, x))). Using this method would be identically equal to the two-norm for a vector.

Tensors
-------

2. What is the formula that we would use for indexing if we wanted "slab-major" ordering?  Hint:  What is the size of a slab?  It might be helpful to draw a picture of the data in 3D and see what the size is of a slab.

If we wanted to used "slab-major" ordering we would use the formula (L, M, N) where L is the number of slabs, M is the number of rows and N is the number of columns in the tensor. Therefore each slab, L, is a matrix of size MxN. 

3. (Extra credit.) I claim that there are six distinct indexing formulas.  Show that this claim is correct or that it is incorrect.

The claim that there are six distinct indexing formulas is correct and the formulas are the following: 
A. (L, M, N)
B. (L, N, M)
C. (M, N, L)
D. (M, L, N)
E. (N, L, M)
F. (N, M, L)
Here L is the number of slabs, M is the number of rows in each slab and N is the number of columns of each slab. Where the first two options would be slab-major ordering. 