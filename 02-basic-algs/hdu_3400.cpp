#include <bits/stdc++.h>

#define eps 1e-4

struct Point {
  double x;
  double y;
} A, B, C, D;

int Ax, Ay, Bx, By;
int Cx, Cy, Dx, Dy;
int P, Q, R;

static inline double dist(const Point &A, const Point &B) { return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2)); }

static inline double time(const Point &X, const Point &Y) { return dist(A, X) / P + dist(X, Y) / R + dist(Y, D) / Q; }

double moveY(const Point &X) {
  Point Y1, Y2;
  Point L, R;
  double time1 = 0.0, time2 = 100.0;

  if (Cx == Dx) {
    L = (Cy < Dy ? C : D);
    R = (Cy > Dy ? C : D);
  } else {
    L = (Cx < Dx ? C : D);
    R = (Cx > Dx ? C : D);
  }

  while (std::abs(time1 - time2) > eps) {
    Y1 = {2.0 * L.x / 3.0 + R.x / 3.0, 2.0 * L.y / 3.0 + R.y / 3.0};
    Y2 = {L.x / 3.0 + 2.0 * R.x / 3.0, L.y / 3.0 + 2.0 * R.y / 3.0};
    time1 = time(X, Y1);
    time2 = time(X, Y2);
    if (time1 > time2)
      L = Y1;
    else
      R = Y2;
  }

  return time1;
}

double moveX() {
  Point X1, X2;
  Point L, R;
  double time1 = 0.0, time2 = 100.0;

  if (Ax == Bx) {
    L = (Ay < By ? A : B);
    R = (Ay > By ? A : B);
  } else {
    L = (Ax < Bx ? A : B);
    R = (Ax > Bx ? A : B);
  }

  while (std::abs(time1 - time2) > eps) {
    X1 = {2.0 * L.x / 3.0 + R.x / 3.0, 2.0 * L.y / 3.0 + R.y / 3.0};
    X2 = {L.x / 3.0 + 2.0 * R.x / 3.0, L.y / 3.0 + 2.0 * R.y / 3.0};
    time1 = moveY(X1);
    time2 = moveY(X2);
    if (time1 > time2)
      L = X1;
    else
      R = X2;
  }

  return time1;
}

int main() {
  int testNum;
  std::cin >> testNum;

  while ((testNum--) != 0) {
    std::cin >> Ax >> Ay >> Bx >> By;
    std::cin >> Cx >> Cy >> Dx >> Dy;
    std::cin >> P >> Q >> R;

    A = {static_cast<double>(Ax), static_cast<double>(Ay)};
    B = {static_cast<double>(Bx), static_cast<double>(By)};
    C = {static_cast<double>(Cx), static_cast<double>(Cy)};
    D = {static_cast<double>(Dx), static_cast<double>(Dy)};

    printf("%.2f\n", moveX());
  }
  return 0;
}