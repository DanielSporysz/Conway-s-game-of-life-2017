#include "points.h"
#include <stdlib.h>

static int realloc_pts_failed (points_t * pts, int size)
{
  return ((pts->x = realloc (pts->x, size * sizeof *pts->x)) == NULL)
    || ((pts->y = realloc (pts->y, size * sizeof *pts->y)) == NULL);
}
void free_points( points_t pts){
    free( pts.x );
    free( pts.y );
}

int read_points_failed(FILE * inf, points_t * pts)
{
  int size;
  double x, y;

  if (pts->n == 0) {
    pts->x = malloc (100 * sizeof *pts->x);
    if (pts->x == NULL)
      return 1;

    pts->y = malloc (100 * sizeof *pts->y);
    if (pts->y == NULL) {
      free (pts->x);
      return 1;
    }
    size = 100;
  } else
    size = pts->n;

  while (fscanf (inf, "%lf %lf", &x, &y) == 2) {
    pts->x[pts->n] = x;
    pts->y[pts->n] = y;
    pts->n++;
    if (!feof (inf) && pts->n == size) {
      if (realloc_pts_failed (pts, 2 * size))
        return 1;
      else
        size *= 2;
    }
  }

  if (pts->n != size)
    if (realloc_pts_failed (pts, pts->n))
      return 1;

  return 0;
}

double points_min_x(points_t *points) {
    int i;
    double v = 1e66;
    for (i = 0; i < points->n; i++) {
        if (points->x[i] < v)
            v = points->x[i];
    }
    return v;
}

double points_max_x(points_t *points) {
    int i;
    double v = -1e66;
    for (i = 0; i < points->n; i++) {
        if (points->x[i] > v)
            v = points->x[i];
    }
    return v;
}

points_t * points_linspace(double a, double b, int n) {
    int i;
    points_t * points = (points_t*) malloc(sizeof(points_t));
    if (points != NULL) {
        points->n = n;
        double h = (b - a) / n;
        points->x = (double*) malloc(n * sizeof(double));
        if (points->x == NULL) {
            free(points);
            printf("Błąd podczas alokacji pamięci dla wektora współrzędnych x punktów o rozmiarze %d w funkcji 'points_linspace'", n);
            return NULL;
        }

        points->y = (double*) malloc(n * sizeof(double));
        if (points->y == NULL) {
            free(points->x);
            free(points);
            printf("Błąd podczas alokacji pamięci dla wektora współrzędnych x punktów o rozmiarze %d w funkcji 'points_linspace'", n);
            return NULL;
        }

        for (i=0; i<n; i++) {
            points->x[i] = a + i*h;
        }

    } else {
        printf("Błąd podczas alokacji pamięci dla struktury danych punktów o rozmiarze %d w funkcji 'points_linspace'", n);
        return NULL;
    }

    return points;
}
