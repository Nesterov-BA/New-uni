#include "rungeKutta.hpp"
#include "gaussian.hpp"
#include <cmath>
#include <cstdio>
#include <iterator>
#include <vector>

void jacobiMatrix(double p1, double p2, std::vector<double> (*func)(double, double), double** matrix)
{
    double eps = 1.e-7;
    std::vector<double> res(2);
    std::vector<double> resX(2);
    std::vector<double> resY(2);
    res = func(p1, p2);
    resX = func(p1 + eps, p2);
    resY = func(p1, p2 + eps);
    resX[0] -= res[0];
    resX[0] /= eps;
    matrix[0][0] = resX[0];
    resX[1] -= res[1];
    resX[1] /= eps;
    matrix[0][1] = resX[1];
    resY[0] -= res[0];
    resY[0] /= eps;
    matrix[1][0] = resY[0];
    resY[1] -= res[1];
    resY[1] /= eps;
    matrix[1][1] = resY[1];
}

void probe(double* start, std::vector<double> (*function)(double, double))
{
    FILE* minimumStarts = fopen("starts.csv", "w");
    fprintf(minimumStarts, "p2,x1,alpha\n");
    double start4[4] = {0, 0, 0, 0};
    alpha = 0.01;
    double step = 0.1;
    while(alpha < 10.02)
    {
        if(fabs(alpha - 1.01) < 1.e-7)
          alpha = 1.02;
        printf("alpha = %lf\n", alpha);
        printf("Start = %lf, %lf\n", start[0], start[1]);
        if(findMinimum(start, function) < 0)
        {
            printf("something wrong!\n");
            break;
        }
        printf("Start = %lf, %lf\n\n", start[0], start[1]);
        if(fabs(alpha - 0.01) < 1.e-7)
        {
            start4[0] = start[0];
            start4[3] = start[1];
        }
        fprintf(minimumStarts, "%lf,%lf,%lf\n", start[0], start[1], alpha);
        modf(alpha, &step);
        step /= 10;
        step += 0.1;
        printf("Step = %lf\n", step);
        alpha +=step;
    }
    alpha = 10.01;
    printf("alpha = %lf\n", alpha);
    printf("Start = %lf, %lf\n", start[0], start[1]);
    if(findMinimum(start, function) < 0)
    {
        printf("something wrong!\n");
    }
    printf("Start = %lf, %lf\n\n", start[0], start[1]);
    fprintf(minimumStarts, "%lf,%lf,%lf\n", start[0], start[1], alpha);



}

int findMinimum(double* start, std::vector<double> (*function)(double, double))
{
    double correction[2];
    double** jacobi = new double*[2];
    jacobi[0] = new double[2];
    jacobi[1] = new double[2];
    double coefficent = -1;
    std::vector<double> errorVector(2);
    double currNorm;
    int count = 0;
    while(true)
    {
        count++;
        coefficent = 1;
        errorVector = function(start[0], start[1]);
        if(l2Norm(errorVector, 2) < 1.e-7)
        {
            printf("Small Error!\n");
            printf("Error = (%.e, %.e)\n", errorVector[0], errorVector[1]);
            return 0;
            break;
        }
        correction[0] = errorVector[0];
        correction[1] = errorVector[1];
        currNorm = l2Norm(errorVector, 2);
        jacobiMatrix(start[0], start[1], function, jacobi);
//        printf("\nJacobi matrix:\n|%lf  %lf|\n|%lf  %lf|\n", jacobi[0][0], jacobi[0][1], jacobi[1][0], jacobi[1][1]);
 //       printf("Error = (%lf, %lf)\n", errorVector[0], errorVector[1]);
        gauss(jacobi, correction);
 //       printf("Correction = (%lf, %lf)\n", correction[0], correction[1]);
        std::vector<double> res = function(start[0] + correction[0]*coefficent, start[1] + correction[1]*coefficent);
        while(l2Norm(function(start[0] + correction[0]*coefficent, start[1] + correction[1]*coefficent), 2) > currNorm)
        {
            res = function(start[0] + correction[0]*coefficent, start[1] + correction[1]*coefficent);
  //          printf("Coeff Res = (%lf, %lf)\n", res[0], res[1]);
            coefficent /= 2;
            if(fabs(coefficent) < 1.e-13)
            {
                printf("Small Coefficent\n");
                printf("Res = (%lf, %lf)\n", errorVector[0], errorVector[1]);
                return -1;
            }
        }

 //       printf("Res = (%lf, %lf)\n", res[0], res[1]);
        start[0] += correction[0]*coefficent;
        start[1] += correction[1]*coefficent;
//        printf("New Start = (%lf, %lf)\n", start[0], start[1]);
        if(l2Norm(function(start[0], start[1]), 2) < 1.e-7)
        {
            printf("Small Error!\n");
            printf("Res = (%.e, %.e)\n", res[0], res[1]);
            return 0;
            break;
        }
        if(count > 100)
        {
            printf("Big Count!\n");
            printf("Res = (%lf, %lf)\n", res[0], res[1]);
            return -1;
            break;
        }
    }
}

void solve(double* start, std::vector<double> (*function)(double, double))
{
    std::vector<double> corr(2);
    while(l2Norm(function(start[0], start[1]), 2) > 1.e-7)
    {
        corr = function(start[0], start[1]);
        start[0] -= corr[0];
        corr = function(start[0], start[1]);
        start[1] -= corr[1];
    }
}
