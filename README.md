# Question-Paper-Generator-Using-OpenMP

Description: This is a semester project for the course Parallel and Distributed Computing where I used ```openmp``` in ```C++``` to generate maths questions(quiz) in parallel. The questions are simple arithmetic, geometric and harmonic series fill-in-the-blanks. It randomly adds blanks anywhere in the series. It prints the local results of each thread in order to know the working of threads and also prints the time it takes to execute the whole program. Number of threads can be changed inside the code ```#define NumThreads n``` to check the efficiency of the parallel execution. 12 questions are generated for each paper, there are 10 terms per question and 5 papers are generated everytime the code is run, each paper is saved in ```Paper n.txt``` file inside ```files/Batch n/``` folder. Number of papers, questions and terms in a question can be changed inside the code ```#define N n``` and ```#define Q n``` respectively. 

<b>How to run: </b>
1. Compile main.cpp using command ```g++ main.cpp -o main -fopenmp``` in the terminal(command prompt)
2. Execute the compiled code using command ```./main```
