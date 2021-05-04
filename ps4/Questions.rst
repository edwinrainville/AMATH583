


What level of SIMD/vector support does the CPU your computer provide?

My computer provides support for:
    CPUID_EBX_AVX2
    CPUID_ECX_SSE3
    CPUID_ECX_SSSE3
    CPUID_ECX_FMA
    CPUID_ECX_SSE41
    CPUID_ECX_SSE42
    CPUID_ECX_AES
    CPUID_ECX_XSAVE
    CPUID_ECX_AVX
    CPUID_ECX_F16C
The highest level of SIMD/vector support for my CPU is AVX2. 


What is the maximum operand size that your computer will support?

Since the highest level of SIMD/vector support is AVX2 the maximum operand size that my computer will support is a 256 bit operand. 





What is the clock speed of your CPU?  (You may need to look this up via "About this Mac" or "lscpu").

The base frequency of the clock is 2.3 GHz while the maximum frequency is 3.8 GHZ 





Based on the output from bandwidth.exe on your computer, what do you expect L1 cache and L2 cache sizes to be?  What are the corresponding bandwidths?   How do the cache sizes compare to what "about this mac" (or equivalent) tells you about your CPU?  (There is no "right" answer for this question -- but I do want you to do the experiment.)

I exepct the L1 cache for this compute to be 32k bytes and the L2 cache to be 32K bytes since there is a steep drop off in bytes/sec between these two values of about 2^10 bytes/sec. 
The expected size of the L1 cache for this computer is 32768 bytes, the L2 cache is 262144 bytes and the l3 cache is 6291456 bytes. So this test gives a very good estimate of the size of the L1 cache.
This information was found using the command "/usr/sbin/sysctl -a" which is from a stak overflow post at this link https://stackoverflow.com/questions/5446134/determine-values-of-several-system-variables-in-the-terminal-in-a-mac

From the docker approach, we see that there is a very steep drop off around 32K whcih indicatest that is the size of the L1 cache which agrees wiht our previous result and the actual stated size of the L1 cache.





What is the (potential) maximum compute performance of your computer?  (The horizontal line.)  What are the L1, L2, and RAM bandwidths?  How do those bandwidths correspond to  what was measured above with the bandwidth program?

The maximum compute performance of this computer is 46.4 GFlOPs/sec. The L1 bandwidth is 145.4 GB/s, L2 is 97.2 GB/s and L3 is 57.4 GB/s and DRAM is 31.6 GB/s. 


Based on the clock speed of your CPU and its maximum Glop rate, what is the (potential) maximum number of *double precision* floating point operations that can be done per clock cycle?  (Hint: Glops / sec :math:`\div` GHz = flops / cycle.)  There are several hardware capabilities that can contribute to supporting more than one operation per cycle: fused multiply add (FMA) and AVX registers.  Assuming FMA contributes a factor of two, SSE contributes a factor of two,  AVX/AVX2 contribute a factor of four, and AVX contributes a factor of eight of eight, what is the expected maximum number of floating point operations your CPU could perform per cycle, based on the capabilities your CPU advertises via cpuinfo (equiv. lscpu)?  Would your answer change for single precision (would any of the previous assumptions change)?  

What is the maximum compute performance of your computer?  (The horizontal line.)  What are the L1, L2, and DRAM bandwidths?  How do those bandwidths correspond to what was measured above?



Referring to the figures about how data are stored in memory, what is it about the best performing pair of loops that is so advantageous?

The best performing pair is 'ikj' ordering and this is advantageous because 


What will the data access pattern be when we are executing ``mult_trans`` in i,j,k order?  What data are accessed in each if the matrices at step (i,j,k) and what data are accessed at step (i, j, k+1)? Are these accesses advantageous in any way?

The max number of double precision floating point operations that can be done per clock cycle is 20.17 flops/cycle. 




Referring again to how data are stored in memory, explain why hoisting  ``C(i,j)`` out of the inner loop is so beneficial in mult_trans with the "ijk" loop ordering.

What optimization is applied in going from ``mult_2`` to ``mult_3``?

How does your maximum achieved performance for ``mult`` (any version) compare to what bandwidth and roofline predicted?





