# Question-Paper-Generator-Using-OpenMP

Description: This is a semester project for the course Parallel and Distributed Computing where I used openmp in C++ to generate maths questions(quiz) in parallel. 
The questions are simple arithmetic, geometric and harmonic series fill-in-the-blanks. It randomly adds blanks anywhere in the series. 
It prints the local results of each thread in order to know the working of threads and also prints the time it takes to execute the whole program. Number of threads can be changed inside the code ```#define NumThreads n``` to check the efficiency of the parallel execution. 

<b>How to run: </b>
1. Compile main.cpp using command "g++ main.cpp -o main -fopenmp" in the terminal(command prompt)
2. Execute the compiled code using command "./main"
