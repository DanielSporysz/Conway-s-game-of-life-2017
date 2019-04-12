//
// Created by szmurlor on 25.01.17.
//

#include "splines.h"
#include "./gaus/matrix.h"

spline_t * alloc_spl(int nb) {
    spline_t * spl = (spline_t*) malloc(sizeof(spline_t));
    if (spl != NULL) {
        spl->nbase = nb;
        spl->c = (double *) malloc(nb * sizeof(double));
        if (spl->c == NULL) {
            printf("Błąd alokacji pamięci dla współczynników funkcji sklejanych.\n");
            free(spl);
            return NULL;
        }

        spl->x = (double *) malloc(nb * sizeof(double));
        if (spl->x == NULL) {
            printf("Błąd alokacji pamięci dla współrzędnych bazowych funkcji sklejanych.\n");
            free(spl->c);
            free(spl);
            return NULL;
        }
    }

    return spl;
}

void free_spline(spline_t * spl) {
    free(spl->x);
    free(spl->c);
    free(spl);
}


double _fi(double x, double *hx, double h) {
    double h3 = h * h * h;

    if ((x < hx[0]) || (x > hx[4]))
        return 0;
    else if (x >= hx[0] && x <= hx[1])
        return 1 / h3 * (x - hx[0]) * (x - hx[0]) * (x - hx[0]);
    else if (x > hx[1] && x <= hx[2])
        return 1 / h3 * (h3 + 3 * h * h * (x - hx[1]) +
                         3 * h * (x - hx[1]) * (x - hx[1]) - 3 * (x -
                                                                  hx[1]) * (x -
                                                                            hx[1])
                                                             * (x - hx[1]));
    else if (x > hx[2] && x <= hx[3])
        return 1 / h3 * (h3 + 3 * h * h * (hx[3] - x) +
                         3 * h * (hx[3] - x) * (hx[3] - x) - 3 * (hx[3] -
                                                                  x) * (hx[3] -
                                                                        x) *
                                                             (hx[3] - x));
    else	/* if (x > hx[3]) && (x <= hx[4]) */
        return 1 / h3 * (hx[4] - x) * (hx[4] - x) * (hx[4] - x);

}

/*
 * Zwraca wartość funkcji bazowej fi(x) : n - liczba funkcji a,b - granice przedzialu aproksymacji i
 * - numer funkcji x - wspolrzedna dla ktorej obliczana jest wartosc funkcji
 */
double fi_ab (double a, double b, int nb, int i, double x)
{
    double h = (b - a) / (nb - 1);
    int hi[5] = { i - 2, i - 1, i, i + 1, i + 2 };
    double hx[5];
    int j;

    for (j = 0; j < 5; j++)
        hx[j] = a + h * hi[j];

    return _fi(x, hx, h);
}


/*
 * Zwraca wartość funkcji bazowej fi(x) : x - wspolrzędna środkowa funkcji bazowej dla ktorej obliczana jest wartosc funkcji,
 * h - długość przedziału,
 */
double fi_xih (double xi, double h, double x)
{
    double h3 = h * h * h;
    int hi[5] = { -2, -1, 0, 1, 2 };
    double hx[5];
    int j;

    for (j = 0; j < 5; j++)
        hx[j] = xi + h * hi[j];

    return _fi(x, hx, h);
}

spline_t * splines_approximate(points_t * pts, int nb)
{
    spline_t * spl;
    matrix_t *eqs = NULL;
    double *x = pts->x;
    double *y = pts->y;
    double a = x[0];
    double b = x[pts->n - 1];
    int i, j, k;
    double h;

    if (nb < 4) {
        printf("Program do prawidłowego działania wymaga co najmniej 4 funkcji bazowych. Podano wartość: %d\n", nb);
        return NULL;
    }
    if (nb > pts->n) {
        printf("Liczba funkcji bazowych powinna być mniejsza lub równa liczbie punktów. Podano: nbase=%d, size(x)=%d\n", nb, pts->n);
        return NULL;
    }

    /* W poniższym fragmencie kodu rozszerzam przedział funkcji sklejanych w stosunku
     * do oryginalnego zakresu współrzędnych x o +h i -h z obydwu stron. */
#define SPLINES_EXTEND_INTERVAL
#ifdef SPLINES_EXTEND_INTERVAL
    h = (b - a) / (nb - 3);
    a=a-h;
    b=b+h;
#else
    h = (b - a) / (nb - 1);
#endif


    eqs = make_matrix (nb, nb + 1);

    for (j = 0; j < nb; j++) {
        for (i = 0; i < nb; i++)
            for (k = 0; k < pts->n; k++)
                add_to_entry_matrix(eqs, j, i, fi_ab(a, b, nb, i, x[k]) * fi_ab(a, b, nb, j, x[k]));

        for (k = 0; k < pts->n; k++)
            add_to_entry_matrix (eqs, j, nb, y[k] * fi_ab (a, b, nb, j, x[k]));
    }

    if (piv_ge_solver(eqs))
    {
        printf("Błąd podczas rozwiązywania układu równań metodą elimiacji Gaussa\n");
        return NULL;
    }

    if ((spl = alloc_spl(nb)) != NULL)
    {
        for (i = 0; i < spl->nbase; i++)
        {
            spl->c[i] = get_entry_matrix(eqs, i, nb);
            spl->x[i] = a + h * i;
        }
    }

    free( eqs->e );
    free( eqs );

    return spl;
}


double splines_eval(spline_t * spline, double x) {
    int i;
    double y = 0;
    double h = spline->x[1] - spline->x[0];

    for (i = 0; i < spline->nbase; i++) {
        y += spline->c[i] * fi_xih( spline->x[i], h, x);
    }

    return y;
}

