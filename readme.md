24.04.2022

MOWNIT

Juliusz Kościołek, Jakub Walusiak

- [Całkowanie Numeryczne](#całkowanie-numeryczne)
  - [Zadanie 1](#zadanie-1)
    - [Polecenie](#polecenie)
    - [Wykonanie](#wykonanie)
  - [Zadanie 2](#zadanie-2)
    - [Polecenie](#polecenie-1)
    - [Wykonanie](#wykonanie-1)
  - [Zadanie 3](#zadanie-3)
    - [Polecenie](#polecenie-2)
    - [Wykonanie](#wykonanie-2)
    - [Wyniki](#wyniki)
  - [Zadanie 4](#zadanie-4)
    - [Polecenie](#polecenie-3)
    - [Wykonanie](#wykonanie-3)
    - [Wyniki](#wyniki-1)
# Całkowanie Numeryczne
## Zadanie 1

### Polecenie 

Znaleźć dokładną wartość całki (całkując ręcznie).

### Wykonanie

Wyliczono wartości całek:
* dla `x^2`, całką jest `1/3x^3`, w granicach od `0` do `1` jej wartością jest `1/3`
* dla `1/x^(1/2)`, całką jest `2x^(1/2)`, w granicach od `0` do `1` jej wartością jest `2`

## Zadanie 2

### Polecenie 

Napisać program obliczającą całkę metodą prostokątów. Program powinien mieć następujące parametry:
* `float a` - początek przedziału
* `float b` - koniec przedziału
* `int n` - ilość podprzedziałów, na które dzielimy przedział (a,b)

### Wykonanie

Napisano poniższe funkcje:

```c
float rectangle_integration_xpow2(float a, float b, int n)
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

float rectangle_integration_xsquareroot(float a, float b, int n)
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
```

## Zadanie 3

### Polecenie 

Zbadac, przy uzyciu programu z poprzedniego punktu, jak zmienia sie blad calkowania wraz ze wzrostem liczby podprzedzialow. Kiedy blad jest mniejszy niz 1e-3, 1e-4, 1e-5 i 1e-6?

### Wykonanie

Funkcje z zadania nr 2 wykorzystano w poniższym programie:

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float rectangle_integration_xpow2(float a, float b, int n)
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

float rectangle_integration_xsquareroot(float a, float b, int n)
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

int find_n(float (*f)(float a, float b, int n), float target, float error, int n_increment)
{
    for (int n = 1;; n = n + n_increment)
    {
        float value = f(0, 1, n);
        if (fabs(value - target) < error)
            return n;
    }
}

int main()
{
    const float threshold3 = 1e-3;
    const float threshold4 = 1e-4;
    const float threshold5 = 1e-5;
    const float threshold6 = 1e-6;

    // The value of integration for x^2 from 0 to 1
    const float xpow2_target = 0.33333333f;
    // The value of integration for 1/x^(1/2) from 0 to 1
    const float onebysqrtx_target = 2.0f;

    // x^2
    printf("x^2, less than 1e-3 error for n = %d\n", find_n(rectangle_integration_xpow2, xpow2_target, threshold3, 1));
    printf("x^2, less than 1e-4 error for n = %d\n", find_n(rectangle_integration_xpow2, xpow2_target, threshold4, 1));
    printf("x^2, less than 1e-5 error for n = %d\n", find_n(rectangle_integration_xpow2, xpow2_target, threshold5, 1));
    printf("x^2, less than 1e-6 error for n = %d\n", find_n(rectangle_integration_xpow2, xpow2_target, threshold6, 1));

    // 1/x^(1/2)
    printf("1/x^(1/2), less than 1e-3 error for n = %d\n", find_n(rectangle_integration_xsquareroot, onebysqrtx_target, threshold3, 100));
    printf("1/x^(1/2), less than 1e-4 error for n = %d\n", find_n(rectangle_integration_xsquareroot, onebysqrtx_target, threshold4, 100));
    printf("1/x^(1/2), less than 1e-5 error for n = %d\n", find_n(rectangle_integration_xsquareroot, onebysqrtx_target, threshold5, 100));
    printf("1/x^(1/2), less than 1e-6 error for n = %d\n", find_n(rectangle_integration_xsquareroot, onebysqrtx_target, threshold6, 100));
    return 0;
}
```

### Wyniki

Strumień wyjściowy programu daje odpowiedź na zadane pytania:

```c
x^2, less than 1e-3 error for n = 10
x^2, less than 1e-4 error for n = 29
x^2, less than 1e-5 error for n = 92
x^2, less than 1e-6 error for n = 280

1/x^(1/2), less than 1e-3 error for n = 266301
1/x^(1/2), less than 1e-4 error for n = 541201
1/x^(1/2), less than 1e-5 error for n = 578201
1/x^(1/2), less than 1e-6 error for n = 667701
```

## Zadanie 4

### Polecenie

Obliczyć wartość całki korzystając z funkcji gsl_integration_qag metodą GSL_INTEG_GAUSS15 dla zadanych dokładności takich jak w p. 3. Sprawdzić, ile przedziałów (intervals) potrzebuje ta procedura aby osiągnąc zadaną dokładność (1e-3, 1e-4, 1e-5 i 1e-6). Porownac, ile przedzialow potrzebuje metoda prostokatow do osiagniecia podobnej dokladnosci. Patrz przykład w dokumentacji GSL.

### Wykonanie

Program z zadania nr 3 rozszerzono o wymaganą funkcjonalność:

```c
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
```

### Wyniki

Strumień wyjściowy programu daje odpowiedź na zadane pytania:

```c
custom integration | x^2 | max error: 0.001000, value found: 0.332500, value expected: 0.333333, n: 10
custom integration | x^2 | max error: 0.000100, value found: 0.333234, value expected: 0.333333, n: 29
custom integration | x^2 | max error: 0.000010, value found: 0.333324, value expected: 0.333333, n: 92
custom integration | x^2 | max error: 0.000001, value found: 0.333332, value expected: 0.333333, n: 280
custom integration | 1 / sqrt(x) | max error: 0.001000, value found: 1.999002, value expected: 2.000000, n: 266301
custom integration | 1 / sqrt(x) | max error: 0.000100, value found: 1.999904, value expected: 2.000000, n: 541201
custom integration | 1 / sqrt(x) | max error: 0.000010, value found: 1.999997, value expected: 2.000000, n: 578201
custom integration | 1 / sqrt(x) | max error: 0.000001, value found: 2.000000, value expected: 2.000000, n: 667701
gsl integration | x^2 | max error: 0.001000, value found: 0.333333, n: 1
gsl integration | x^2 | max error: 0.000100, value found: 0.333333, n: 1
gsl integration | x^2 | max error: 0.000010, value found: 0.333333, n: 1
gsl integration | x^2 | max error: 0.000001, value found: 0.333333, n: 1
gsl integration | 1 / sqrt(x) | max error: 0.001000, value found: 1.999911, n: 19
gsl integration | 1 / sqrt(x) | max error: 0.000100, value found: 1.999992, n: 26
gsl integration | 1 / sqrt(x) | max error: 0.000010, value found: 1.999999, n: 33
gsl integration | 1 / sqrt(x) | max error: 0.000001, value found: 2.000000, n: 39
```

Upraszczając odpowiedź:

* Dla funkcji `x^2` i błędu `1e-3`, nasza metoda wymaga 10 kroków, natomiast metoda gsl 1 krok
* Dla funkcji `x^2` i błędu `1e-4`, nasza metoda wymaga 29 kroków, natomiast metoda gsl 1 krok
* Dla funkcji `x^2` i błędu `1e-5`, nasza metoda wymaga 92 kroków, natomiast metoda gsl 1 krok
* Dla funkcji `x^2` i błędu `1e-6`, nasza metoda wymaga 280 kroków, natomiast metoda gsl 1 krok

* Dla funkcji `1 / sqrt(x)` i błędu `1e-3`, nasza metoda wymaga 266301 kroków, natomiast metoda gsl 19 kroków
* Dla funkcji `1 / sqrt(x)` i błędu `1e-4`, nasza metoda wymaga 541201 kroków, natomiast metoda gsl 26 kroków
* Dla funkcji `1 / sqrt(x)` i błędu `1e-5`, nasza metoda wymaga 578201 kroków, natomiast metoda gsl 33 kroki
* Dla funkcji `1 / sqrt(x)` i błędu `1e-6`, nasza metoda wymaga 667701 kroków, natomiast metoda gsl 39 kroków