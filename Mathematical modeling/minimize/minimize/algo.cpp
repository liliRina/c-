#include "algo.h"
#include <cmath>
#include <iostream>
algo::algo() : x(size_), y(size_), Vx(size_),
    Vy(size_), best_x(size_), best_y(size_), best_x_neib(size_, best), best_y_neib(size_, best)
{
    T=T_max;
    counter=0;
    std::uniform_real_distribution<double> for_x(a, b);
    std::uniform_real_distribution<double> for_y(c, d);
    std::uniform_real_distribution<double> for_v(0, 0.3);
    std::time_t result = std::time(nullptr);
    std::mt19937 gen(result);
    for (int i=0; i<size_; i++)
    {
        x[i]=for_x(gen);
        y[i]=for_y(gen);
        best_x[i]=x[i];
        best_y[i]=y[i];
        if (func(x[i], y[i]) < best)
        {
            bestx=x[i];
            besty=y[i];
            best=func(x[i], y[i]);
        }
        for (int j=i; j<size_ && j-i<N_neib; j++)
        {
            if (func(best_x_neib[j], best_y_neib[j])>func(x[i], y[i]))
            {
                best_x_neib[j]=x[i];
                best_y_neib[j]=y[i];
            }
        }
        Vx[i]=for_v(gen);
        Vy[i]=for_v(gen);
    }
}

int algo::fire_swarn()
{
    std::uniform_real_distribution<double> dist(0, 1);
    std::uniform_real_distribution<double> dist_minus(-1, 1);
    std::time_t result = std::time(nullptr);
    std::mt19937 gen(result);

    float nu_x=0.1;
    float nu_y=0.1;
    float teta_x;
    float teta_y;
    float x_new;
    float y_new;
    float probability;
    float delta_E;
    float value;
    int minus;
    std::cout<<T<<std::endl;
    std::cout<<"here"<<std::endl;
    for (int i=0; i<size_ && T>=T_min; i++)
    {
        teta_x=dist_minus(gen);
        teta_y=dist_minus(gen);
        minus=teta_y/abs(teta_y);
        teta_y=minus*sqrt(1-teta_x*teta_x);
        x_new=x[i]+teta_x*nu_x;
        y_new=y[i]+teta_y*nu_y;
        delta_E=func(x_new, y_new)-func(x[i], y[i]);
        if (delta_E<=0)
        {
            x[i]=x_new;
            y[i]=y_new;
        }
        else
        {
            probability=exp(-delta_E/T);
            value=dist(gen);
            if (value <= probability)
            {
                x[i]=x_new;
                y[i]=y_new;
            }
        }
        if (best>func(x[i], y[i]))
        {
            bestx=x[i];
            besty=y[i];
            best=func(x[i], y[i]);
        }
    }
    std::cout<<bestx<<" "<<besty<<std::endl;
    counter++;
    T=T_max/(1+counter);
    if (T<=T_min)
    {
        std::cout<<"func: "<<best<<std::endl;
        std::cout<<"coord the best: "<<bestx<<" "<<besty<<std::endl;
        return 1;
    }
    return 0;
}

int algo::swarn()
{
    std::uniform_real_distribution<double> dist(0, 0.5);
    std::time_t result = std::time(nullptr);
    std::mt19937 gen(result);

    double gx=bestx;
    double gy=besty;
    double rp=dist(gen);
    double rg=dist(gen);
    double c1 = 1.49445; // когнитивная весовая доля
    double c2 = 1.49445;
    for (int i=0; i<size_; i++)
    {
        rp=dist(gen);
        rg=dist(gen);
        Vx[i]=Vx[i]+c1*rp*(best_x[i]-x[i])+c2*rg*(gx-x[i]);
        Vy[i]=Vy[i]+c1*rp*(best_y[i]-y[i])+c2*rg*(gy-y[i]);

        x[i]=std::min(x[i]+Vx[i], b);
        x[i]=std::max(x[i], a);
        y[i]=std::min(y[i]+Vy[i], d);
        y[i]=std::max(y[i], c);
        if (func(x[i], y[i]) < func(best_x[i], best_y[i]))
        {
            best_x[i]=x[i];
            best_y[i]=y[i];
        }
        if (func(x[i], y[i]) < best)
        {
            bestx=x[i];
            besty=y[i];
            if (best-func(x[i], y[i])<acurracy)
            {
                best=func(x[i], y[i]);
                std::cout<<"func: "<<best<<std::endl;
                std::cout<<"coord the best: "<<bestx<<" "<<besty<<std::endl;
                return 1;
            }
            best=func(x[i], y[i]);
        }
    }
    std::cout<<best<<std::endl;
    return 0;
}

int algo::inertia_swarn()
{
    std::uniform_real_distribution<double> dist(0, 0.5);
    std::time_t result = std::time(nullptr);
    std::mt19937 gen(result);

    double gx=bestx;
    double gy=besty;
    double rp=dist(gen);
    double rg=dist(gen);
    double w = 0.729; // весовая доля инерции
    double c1 = 1.49445; // когнитивная весовая доля
    double c2 = 1.49445;
    for (int i=0; i<size_; i++)
    {
        rp=dist(gen);
        rg=dist(gen);
        Vx[i]=w*Vx[i]+c1*rp*(best_x[i]-x[i])+c2*rg*(gx-x[i]);
        Vy[i]=w*Vy[i]+c1*rp*(best_y[i]-y[i])+c2*rg*(gy-y[i]);

        x[i]=std::min(x[i]+Vx[i], b);
        x[i]=std::max(x[i], a);
        y[i]=std::min(y[i]+Vy[i], d);
        y[i]=std::max(y[i], c);
        if (func(x[i], y[i]) < func(best_x[i], best_y[i]))
        {
            best_x[i]=x[i];
            best_y[i]=y[i];
        }
        if (func(x[i], y[i]) < best)
        {
            bestx=x[i];
            besty=y[i];
            if (best-func(x[i], y[i])<acurracy)
            {
                best=func(x[i], y[i]);
                std::cout<<"func: "<<best<<std::endl;
                std::cout<<"coord the best: "<<bestx<<" "<<besty<<std::endl;
                return 1;
            }
            best=func(x[i], y[i]);
        }
    }
    std::cout<<best<<std::endl;
    return 0;
}

int algo::neighbourhood()
{
    std::uniform_real_distribution<double> dist(0, 0.5);
    std::time_t result = std::time(nullptr);
    std::mt19937 gen(result);

    double rp=dist(gen);
    double rg=dist(gen);
    double c1 = 1.49445; // когнитивная весовая доля
    double c2 = 1.49445;
    for (int i=0; i<size_; i++)
    {
        rp=dist(gen);
        rg=dist(gen);
        Vx[i]=Vx[i]+c1*rp*(best_x[i]-x[i])+c2*rg*(std::max(best_x_neib[i],best_x_neib[i+N_neib-1])-x[i]);
        Vy[i]=Vy[i]+c1*rp*(best_y[i]-y[i])+c2*rg*(std::max(best_y_neib[i],best_y_neib[i+N_neib-1])-y[i]);

        x[i]=std::min(x[i]+Vx[i], b);
        x[i]=std::max(x[i], a);
        y[i]=std::min(y[i]+Vy[i], d);
        y[i]=std::max(y[i], c);
        if (func(x[i], y[i]) < func(best_x[i], best_y[i]))
        {
            best_x[i]=x[i];
            best_y[i]=y[i];
        }
        if (func(x[i], y[i]) < best)
        {
            bestx=x[i];
            besty=y[i];
            if (best-func(x[i], y[i])<acurracy)
            {
                best=func(x[i], y[i]);
                std::cout<<"func: "<<best<<std::endl;
                std::cout<<"coord the best: "<<bestx<<" "<<besty<<std::endl;
                return 1;
            }
            best=func(x[i], y[i]);
        }
        for (int j=i; j<size_ && j-i<N_neib; j++)
        {
            if (func(best_x_neib[j], best_y_neib[j])>func(x[i], y[i]))
            {
                best_x_neib[j]=x[i];
                best_y_neib[j]=y[i];
            }
        }
    }
    std::cout<<best_x_neib[0]<<std::endl;
    std::cout<<best<<std::endl;
    return 0;
}

int algo::with_dead()
{
    std::uniform_real_distribution<double> dist(0, 0.5);
    std::time_t result = std::time(nullptr);
    std::mt19937 gen(result);

    double gx=bestx;
    double gy=besty;
    double rp=dist(gen);
    double rg=dist(gen);
    double c1 = 1.49445; // когнитивная весовая доля
    double c2 = 1.49445;
    std::cout<<size_<<std::endl;
    for (int i=0; i<size_; i++)
    {
        rp=dist(gen);
        rg=dist(gen);
        Vx[i]=Vx[i]+c1*rp*(best_x[i]-x[i])+c2*rg*(gx-x[i]);
        Vy[i]=Vy[i]+c1*rp*(best_y[i]-y[i])+c2*rg*(gy-y[i]);

        x[i]=std::min(x[i]+Vx[i], b);
        x[i]=std::max(x[i], a);
        y[i]=std::min(y[i]+Vy[i], d);
        y[i]=std::max(y[i], c);
        if (func(x[i], y[i]) < func(best_x[i], best_y[i]))
        {
            best_x[i]=x[i];
            best_y[i]=y[i];
        }
        if (func(x[i], y[i]) < best)
        {
            bestx=x[i];
            besty=y[i];
            if (best-func(x[i], y[i])<acurracy)
            {
                best=func(x[i], y[i]);
                std::cout<<"func: "<<best<<std::endl;
                std::cout<<"coord the best: "<<bestx<<" "<<besty<<std::endl;
                return 1;
            }
            best=func(x[i], y[i]);
        }
    }
    sort_();
    if (size_==0)
    {
        std::cout<<"func: "<<best<<std::endl;
        std::cout<<"coord the best: "<<bestx<<" "<<besty<<std::endl;
        return 1;
    }
    else
    {
        if (func(x[size_-1], y[size_-1])>best+10)
        {
            size_--;
            x.resize(size_);
            y.resize(size_);
        }
    }
    return 0;
}

int algo::genetic()
{
    std::uniform_real_distribution<double> dist(-0.01, 0.01);
    std::time_t result = std::time(nullptr);
    std::mt19937 gen(result);
    sort_();
    int k=size_best;
    for (int i=0; i<size_best; i++)
    {
        for (int j = i + 1; j < size_best; j++)
        {
            x[k] = (x[i] + x[j]) / 2;
            y[k] = (y[i] + y[j]) / 2;
            if (best>func(x[k], y[k]))
            {
                bestx=x[k];
                besty=y[k];
                if (best-func(x[k], y[k])<acurracy)
                {
                    best=func(x[k], y[k]);
                    std::cout<<"func: "<<best<<std::endl;
                    std::cout<<"coord the best: "<<bestx<<" "<<besty<<std::endl;
                    return 1;
                }
                best=func(x[k], y[k]);
            }
            k++;
        }
    }
    for (int i=(int)size_best/2; i<size_best; i++)
    {
        x[i]=dist(gen)+x[i];
        y[i]=dist(gen)+y[i];
        if (func(x[i], y[i]) < best)
        {
            bestx=x[i];
            besty=y[i];
            if (best-func(x[i], y[i])<acurracy)
            {
                best=func(x[i], y[i]);
                std::cout<<"func: "<<best<<std::endl;
                std::cout<<"coord the best: "<<bestx<<" "<<besty<<std::endl;
                return 1;
            }
            best=func(x[i], y[i]);
        }
    }
    size_=size_best*(size_best-1)/2+size_best;
    x.resize(size_best*(size_best-1)/2+size_best);
    y.resize(size_best*(size_best-1)/2+size_best);
    std::cout<<best<<std::endl;
    std::cout<<bestx<<" "<<besty<<std::endl;
    return 0;
}

void algo::sort_()  // сортировка пузырьком
{
    for (int i = 0; i < size_; i++)
    {
        for (int j = i + 1; j < size_; j++)
        {
            if (func(x[j], y[j]) < func(x[i], y[i]))
            {
                double temp = y[i];
                y[i] = y[j];
                y[j] = temp;
                temp = x[i];
                x[i] = x[j];
                x[j] = temp;
                temp = best_x[i];
                best_x[i] = best_x[j];
                best_x[j] = temp;
                temp = best_y[i];
                best_y[i] = best_y[j];
                best_y[j] = temp;
                temp = Vx[i];
                Vx[i] = Vx[j];
                Vx[j] = temp;
                temp = Vy[i];
                Vy[i] = Vy[j];
                Vy[j] = temp;
            }
        }
    }
}
double algo::func(double a, double b) // inline сделать
{
    return 50*sin(46*a)*cos(b+a);
}


//следование за лидером. Выбор коэф c2
// ещё какое-то распределение, например, нормально.
// выбирать лидера из окрестности и за ним топать





