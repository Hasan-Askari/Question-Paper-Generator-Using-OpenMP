#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <random>

#define N 5  // number of papers
#define Q 12 // number of questions in a paper
#define S 10 // number of term in a series
using namespace std;

/*
Creating IQ exams of N number and each exam consists of Q questions and each question(series) consists of S terms
*/

int blank()
{
    int result = (rand() % S);
    return result;
}

int intRand(const int & min, const int & max) {
    static thread_local std::mt19937 generator;
    std::uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}

void arithmetic_series(float *series) // 3
{
    float a = intRand(0, 100), d = intRand(1, 10);
    bool sign = intRand(0, 1);
    printf("\na = %f, d = %f, sign = %d arth_series\n", a, d, sign);
    int blnk = blank();
    series[0] = a;

    for (int i = 1; i < S; i++)
    {
        if (sign == 0)
            series[i] = series[i - 1] + d;
        else if (sign == 1)
            series[i] = series[i - 1] - d;
    }
}

void geometric_series(float *series) // 4
{
    float a = intRand(1, 100), r = intRand(1, 10);
    bool op = intRand(0, 1);
    printf("\na = %f, r = %d, op = %d geo_series\n", a, r, op);
    int blnk = blank();
    series[0] = a;

    for (int i = 1; i < S; i++)
    {
        if (op == 0)
            series[i] = series[i - 1] * r;
        else if (op == 1)
            series[i] = series[i - 1] / r;
    }
}

void harmonic_series(float *series) // 5
{
    float a = intRand(0, 100), d = intRand(1, 10);
    bool sign = intRand(0, 1);
    printf("\na = %f, d = %f, sign = %d harmonic_series\n", a, d, sign);
    int blnk = blank();
    series[0] = a;

    for (int i = 1; i < S; i++)
    {
        if (sign == 0)
            series[i] = 1 / (series[i - 1] + d);
        else if (sign == 1)
            series[i] = 1 / (series[i - 1] - d);
    }
}

void create_questions(float papers[][Q][S], int n, int ee) // 2
{
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        float series[S];
        // srand(int(time(NULL)) ^ omp_get_thread_num());
        #pragma omp for schedule(dynamic, 4)
        for (int i = 0; i < Q; i++)
        {
            int tid = omp_get_thread_num();
            printf("\nee tid = %d, i = %d", tid, i);

            if (tid == 0)
            {
                printf("\ntid = %d, i = %d, from create_papers()-%d, calling geometric\n", tid, i, ee);
                geometric_series(series); // 4
                for (int j = 0; j < S; j++)
                {
                    papers[n][i][j] = series[j];
                }
            }
            else if (tid == 1)
            {
                printf("\ntid = %d, i = %d, from create_papers()-%d, calling harmonic\n", tid, i, ee);
                harmonic_series(series); // 5
                for (int j = 0; j < S; j++)
                {
                    papers[n][i][j] = series[j];
                }
            }
            else
            {
                printf("\ntid = %d, i = %d, from create_papers()-%d, calling arithmetic\n", tid, i, ee);
                arithmetic_series(series); // 6
                for (int j = 0; j < S; j++)
                {
                    papers[n][i][j] = series[j];
                }
            }
        }
    }
}

void create_papers(float papers[][Q][S]) // 1
{
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        // srand(int(time(NULL)) ^ omp_get_thread_num());
        #pragma omp for
        for (int i = 0; i < N; i++)
        {
            int tid = omp_get_thread_num();
            printf("\ntid = %d, i = %d, create_papers()\n", tid, i);
            create_questions(papers, i, tid);
        }
    }
}

void print_papers(float papers[][Q][S])
{
    for (int i = 0; i < N; i++)
    {
        cout << "\tPaper Number: " << i + 1 << endl;
        for (int j = 0; j < Q; j++)
        {
            cout << "Question Number " << j + 1 << ":\t";
            for (int k = 0; k < S; k++)
            {
                cout << papers[i][j][k] << " ";
                if (k != S - 1)
                    cout << "+ ";
            }
            cout << endl;
        }
    }
    cout << papers[0][0][0] << " ";
    cout << papers[0][1][0] << " ";
}

int main()
{
    // srand((float) time(0));
    omp_set_num_threads(N*Q);
    omp_set_nested(1);
    float papers[N][Q][S];
    cout << "Hello World" << endl;
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                // srand(int(time(NULL)) ^ omp_get_thread_num());
                create_papers(papers); // 0
            }
        }
    }
    print_papers(papers);
}