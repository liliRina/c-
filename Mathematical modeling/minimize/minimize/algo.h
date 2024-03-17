#ifndef ALGO_H
#define ALGO_H
#include <random>
#include <ctime>
#include <iostream>
#include <QVector>
#include <cmath>
#include <set>

class algo
{
private:
    int size_=50;
    int size_best=9;
    std::vector<double> Vx;
    std::vector<double> Vy;
    std::vector<double> best_x;
    std::vector<double> best_y;
    std::vector<double> best_x_neib;
    std::vector<double> best_y_neib;
    float T_min=1;
    float T_max=4000;
    float T;
    int counter;
    float acurracy=0.01;
    int N_neib=5;
    float worst=-10000000;
    int index_dead=size_;
public:
    double bestx=0;
    double besty=0;
    double best=1000000000;
    double a=-5, b=5, c=-5, d=5;
    QVector<double> x;
    QVector<double> y;
    algo();
    int swarn();
    int inertia_swarn();
    int fire_swarn();
    int neighbourhood();
    int with_dead();
    int genetic();
    void mutation(int ind);
    void cross();
    std::set <int> graveyard;
    void sort_();

    double func(double a, double b);
};

#endif // ALGO_H
