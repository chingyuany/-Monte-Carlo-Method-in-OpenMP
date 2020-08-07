# Monte-Carlo-Method-in-OpenMP-and-MPI
The program is to use Monte Carlo Method to calculate 𝜋 in OpenMP and MPI


Instruction for the installation  

OpenMP  
Step1: export OMP_NUM_THREADS=8  
Step2: icc -openmp MonteCarlo_OpenMp.c -o MonteCarlo.x  
Step3: ./MonteCarlo.x  

MPI  
Step1:mpicc MonteCarlo_MPI.c -o MonteCarlo_MPI -lm
10000000 is the number of samples
Step2: mpirun -np 8  ./MonteCarlo_MPI 10000000

