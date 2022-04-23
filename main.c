#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_integration.h>

float rectangle_integration_x_pow_2(float a, float b, int n)
{
    float sum = 0.0f;
    float interval = (b - a) / n;

    for (float i = 0; i < n; i++)
    {
        float middle = interval * (i + 0.5f);
        float value = powf(middle, 2);
        float area = value * interval;
        sum += area;
    }

    return sum;
}

float rectangle_integration_x_square_root(float a, float b, int n)
{
    float sum = 0.0f;
    float interval = (b - a) / n;

    for (float i = 0; i < n; i++)
    {
        float middle = interval * (i + 0.5f);
        float value = 1.0f / sqrtf(middle);
        float area = value * interval;
        sum += area;
    }

    return sum;
}

void find_n(const char *label, float (*f)(float a, float b, int n), float target, float max_error, int n_increment)
{
    for (int n = 1;; n = n + n_increment)
    {
        float value = f(0, 1, n);
        if (fabs(value - target) < max_error)
        {
            printf("custom integration | %s | max error: %f, value found: %f, value expected: %f, n: %d\n", label, max_error, value, target, n);
            return;
        }
    }
}

double x_pow_2(double x, void *params)
{
    return pow(x, 2);
}

double one_by_sqrt_x(double x, void *params)
{
    return 1.0 / sqrt(x);
}

void find_n_gsl(const char *label, double (*f)(double x, void *params), double max_error)
{
    const int workspace_size = 1000;
    gsl_integration_workspace *workspace = gsl_integration_workspace_alloc(workspace_size);

    double result;
    double abserr;

    gsl_function gsl_func;
    gsl_func.function = f;
    int something = gsl_integration_qag(&gsl_func, 0, 1, 0, max_error, workspace_size, 1, workspace, &result, &abserr);
    printf("gsl integration | %s | max error: %f, value found: %f, n: %zu\n", label, max_error, result, workspace->size);
    gsl_integration_workspace_free(workspace);
}

int main()
{
    const float threshold3 = 1e-3;
    const float threshold4 = 1e-4;
    const float threshold5 = 1e-5;
    const float threshold6 = 1e-6;

    // The actual value of integration for x^2 from 0 to 1
    const float xpow2_target = 0.33333333f;
    // The actual value of integration for 1/x^(1/2) from 0 to 1
    const float onebysqrtx_target = 2.0f;

    // Custom integration
    // x^2
    find_n("x^2", rectangle_integration_x_pow_2, xpow2_target, threshold3, 1);
    find_n("x^2", rectangle_integration_x_pow_2, xpow2_target, threshold4, 1);
    find_n("x^2", rectangle_integration_x_pow_2, xpow2_target, threshold5, 1);
    find_n("x^2", rectangle_integration_x_pow_2, xpow2_target, threshold6, 1);

    // 1/x^(1/2)
    find_n("1 / sqrt(x)", rectangle_integration_x_square_root, onebysqrtx_target, threshold3, 100);
    find_n("1 / sqrt(x)", rectangle_integration_x_square_root, onebysqrtx_target, threshold4, 100);
    find_n("1 / sqrt(x)", rectangle_integration_x_square_root, onebysqrtx_target, threshold5, 100);
    find_n("1 / sqrt(x)", rectangle_integration_x_square_root, onebysqrtx_target, threshold6, 100);

    // Integration with the GSL library
    // x^2
    find_n_gsl("x^2", x_pow_2, threshold3);
    find_n_gsl("x^2", x_pow_2, threshold4);
    find_n_gsl("x^2", x_pow_2, threshold5);
    find_n_gsl("x^2", x_pow_2, threshold6);

    // 1/x^(1/2)
    find_n_gsl("1 / sqrt(x)", one_by_sqrt_x, threshold3);
    find_n_gsl("1 / sqrt(x)", one_by_sqrt_x, threshold4);
    find_n_gsl("1 / sqrt(x)", one_by_sqrt_x, threshold5);
    find_n_gsl("1 / sqrt(x)", one_by_sqrt_x, threshold6);

    return 0;
}