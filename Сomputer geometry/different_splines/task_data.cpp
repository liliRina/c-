#include "task_data.h"
#include <QTextStream>

double rotate(vector2d A,vector2d B,vector2d C)
{
  return (B.x-A.x)*(C.y-B.y)-(B.y-A.y)*(C.x-B.x);
}

QPair<QVector<double>, QVector<double>> task_data::lagrange()
{
    int n = points.size();

    QVector<double> out_x;
    QVector<double> out_y;

    double x_min = points[0].x;
    double x_max = points[0].x;

    for (int i=1; i<n; i++)
    {
        if(points[i].x < x_min)
        {
            x_min = points[i].x;
        }
        if(points[i].x > x_max)
        {
            x_max = points[i].x;
        }
    }

    for(int i=0; x_min+i*1<=x_max; i++)
    {
        out_x.push_back(x_min+i*1);
    }

    for (int k=0; k<out_x.size(); k++)
    {
        double x = out_x[k];
        double y = 0;
        for (int i = 0; i<n; i++)
        {
            double l_i = 1;
            for (int j=0; j<n; j++)
            {
                if (i!=j)
                    l_i = l_i * (x - points[j].x)/(points[i].x - points[j].x);
            }
            y = y + points[i].y*l_i;
        }
        out_y.push_back(y);
    }
    return QPair<QVector<double>, QVector<double>>(out_x, out_y);
}

QPair<QVector<double>, QVector<double>> task_data::lagrange_parametrical()
{
    int n = points.size();

    QVector<double> out_x;
    QVector<double> out_y;

    QVector<double> t;
    QVector<double> tt;
    t.push_back(0);

    for(int i=0; i<n-1; i++)
    {
        double a = sqrt(pow(points[i+1].x-points[i].x, 2)+pow(points[i+1].y-points[i].y, 2));
        a = a + t[i];
        t.push_back(a);
    }

    double t_min = 0;
    double t_max = t[n-1];

    for(int i=0; t_min+i*1<=t_max; i++)
    {
        tt.push_back(t_min+i*1);
    }

    for (int k=0; k<tt.size(); k++)
    {
        double t_u = tt[k];
        double x = 0;
        double y = 0;
        for (int i = 0; i<n; i++)
        {
            double l_i_x = 1;
            double l_i_y = 1;
            for (int j=0; j<n; j++)
            {
                if (i!=j)
                {
                    l_i_x = l_i_x * (t_u - t[j])/(t[i] - t[j]);
                    l_i_y = l_i_y * (t_u - t[j])/(t[i] - t[j]);
                }
            }
            x = x + points[i].x*l_i_x;
            y = y + points[i].y*l_i_y;
        }
        out_x.push_back(x);
        out_y.push_back(y);
    }
    return QPair<QVector<double>, QVector<double>>(out_x, out_y);
}

QPair<QVector<double>, QVector<double>> task_data::hermite()
{
    int n = points.size();

    QVector<double> out_x;
    QVector<double> out_y;

    double x_min = points[0].x;
    double x_max = points[0].x;

    for (int i=1; i<n; i++)
    {
        if(points[i].x < x_min)
        {
            x_min = points[i].x;
        }
        if(points[i].x > x_max)
        {
            x_max = points[i].x;
        }
    }

    for(int i=0; x_min+i*1<=x_max; i++)
    {
        out_x.push_back(x_min+i*1);
    }

    QVector<int> P;
    for(int i=0; i<n; i++)
    {
        P.push_back(i);
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if (points[P[j]].x>points[P[j+1]].x)
                std::swap(P[j], P[j+1]);
        }
    }

    QVector<double> m(n);

    for (int i=1; i<n-1; i++)
    {
        m[i] = (((points[P[i+1]].y - points[P[i]].y)/(points[P[i+1]].x - points[P[i]].x))+((points[P[i]].y - points[P[i-1]].y)/(points[P[i]].x - points[P[i-1]].x)))/2;
    }

    m[0] = (points[P[1]].y - points[P[0]].y)/(points[P[1]].x - points[P[0]].x);
    m[n-1] = (points[P[n-1]].y - points[P[n-2]].y)/(points[P[n-1]].x - points[P[n-2]].x);

    for (int i=0; i<out_x.size(); i++)
    {
        int k = 0;
        for(int j = 0; points[P[j]].x<out_x[i]; j++)
        {
            k = j;
        }

        double t = (out_x[i]-points[P[k]].x)/(points[P[k+1]].x-points[P[k]].x);

        double h00 = 2*pow(t,3) - 3*pow(t,2) + 1;
        double h10 = pow(t,3) - 2*pow(t,2) + t;
        double h01 = -2*pow(t,3) +3*pow(t,2);
        double h11 = pow(t,3) - pow(t,2);

        double a = h00*points[P[k]].y + h10*(points[P[k+1]].x - points[P[k]].x)*m[k]+h01*points[P[k+1]].y + h11*(points[P[k+1]].x - points[P[k]].x)*m[k+1];
        out_y.push_back(a);
    }

    return QPair<QVector<double>,QVector<double>>(out_x, out_y);
}

QPair<QVector<double>, QVector<double>> task_data::hermite_parametrical()
{
    int n = points.size();

    QVector<double> out_x;
    QVector<double> out_y;

    QVector<double> mx(n);
    QVector<double> my(n);

    QVector<double> t;
    QVector<double> tt;
    t.push_back(0);

    for(int i=0; i<n-1; i++)
    {
        double a = sqrt(pow(points[i+1].x-points[i].x, 2)+pow(points[i+1].y-points[i].y, 2));
        a = a + t[i];
        t.push_back(a);
    }

    double t_min = 0;
    double t_max = t[n-1];

    for(int i=0; t_min+i*1<=t_max; i++)
    {
        tt.push_back(t_min+i*1);
    }

    for (int i=1; i<n-1; i++)
    {
        mx[i] = (((points[i+1].x - points[i].x)/(t[i+1] - t[i]))+((points[i].x - points[i-1].x)/(t[i] - t[i-1])))/2;
        my[i] = (((points[i+1].y - points[i].y)/(t[i+1] - t[i]))+((points[i].y - points[i-1].y)/(t[i] - t[i-1])))/2;
    }

    mx[0] = (points[1].x - points[0].x)/(t[1] - t[0]);
    mx[n-1] = (points[n-1].x - points[n-2].x)/(t[n-1] - t[n-2]);
    my[0] = (points[1].y - points[0].y)/(t[1] - t[0]);
    my[n-1] = (points[n-1].y - points[n-2].y)/(t[n-1] - t[n-2]);

    for (int i=0; i<tt.size(); i++)
    {
        int k = 0;
        for(int j = 0; t[j]<tt[i]; j++)
        {
            k = j;
        }

        double tx = (tt[i]-t[k])/(t[k+1]-t[k]);

        double h00 = 2*pow(tx,3) - 3*pow(tx,2) + 1;
        double h10 = pow(tx,3) - 2*pow(tx,2) + tx;
        double h01 = -2*pow(tx,3) +3*pow(tx,2);
        double h11 = pow(tx,3) - pow(tx,2);

        double ax = h00*points[k].x + h10*(t[k+1] - t[k])*mx[k]+h01*points[k+1].x + h11*(t[k+1] - t[k])*mx[k+1];
        double ay = h00*points[k].y + h10*(t[k+1] - t[k])*my[k]+h01*points[k+1].y + h11*(t[k+1] - t[k])*my[k+1];
        out_x.push_back(ax);
        out_y.push_back(ay);
    }

    return QPair<QVector<double>,QVector<double>>(out_x, out_y);
}

QVector<double> task_data::tridiagonal_matrix_algorithm(QVector<double> a, QVector<double> b, QVector<double> c, QVector<double> d)
{
    int k = b.size();
    QVector<double> x(k);
    if (k>1)
    {
        QVector<double> c_s(k-1);
        c_s[0] = c[0]/b[0];
        for (int i = 1; i < k-1; i++)
        {
            c_s[i]=c[i]/(b[i]-a[i]*c_s[i-1]);
        }
        QVector<double> d_s(k);
        d_s[0]=d[0]/b[0];
        for (int i = 1; i < k; i++)
        {
            d_s[i]=(d[i]-a[i]*d_s[i-1])/(b[i]-a[i]*c_s[i-1]);
        }
        //QVector<double> x(k);
        x[k-1] = d_s[k-1];
        for(int i = k-2; i>=0; i--)
        {
            x[i]=d_s[i] - c_s[i]*x[i+1];
        }
    }
    else {
        x[0]=d[0]/b[0];
    }
    return x;
}

QPair<QVector<double>, QVector<double>> task_data::cubic()
{
    int n = points.size();

    QVector<int> P;
    for(int i=0; i<n; i++)
    {
        P.push_back(i);
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if (points[P[j]].x>points[P[j+1]].x)
                std::swap(P[j], P[j+1]);
        }
    }

    QVector<double> h(n-1);
    QVector<double> md(n-1);
    for (int i = 0; i < n-1; i++)
    {
        h[i] = points[P[i+1]].x - points[P[i]].x;
    }
    for (int i = 0; i<n-1; i++)
    {
        md[i] = (points[P[i+1]].y - points[P[i]].y)/h[i];
    }

    QVector<double> a(n-2);
    QVector<double> b(n-2);
    QVector<double> c(n-2);
    for (int i = 0; i < n-2; i++)
    {
        a[i] = h[i];
        c[i] = h[i+1];
    }
    //a.push_front(0);
    //c.push_back(0);
    for (int i = 0; i < n-2; i++)
    {
        b[i] = 2*(h[i]+h[i+1]);
    }

    QVector<double> d(n-2);
    for(int i=0; i<n-2; i++)
    {
        d[i]=6*(md[i+1]-md[i]);
    }

    QVector<double> m;

    if(n>2)
    {
        m = tridiagonal_matrix_algorithm(a, b, c, d);
    }


    //краевые условия
    m.push_front(0);
    m.push_back(0);

    QVector<double> s3(n-1);
    QVector<double> s2(n-1);
    QVector<double> s1(n-1);
    QVector<double> s0(n-1);
    for (int i = 0; i < n-1; i++)
    {
        s3[i] = (m[i+1] - m[i])/(6*h[i]);
        s2[i] = m[i]/2;
        s1[i] = md[i] - h[i]*(2*m[i] + m[i+1])/6;
        s0[i] = points[P[i]].y;
    }

    QVector<double> out_x;
    QVector<double> out_y;

    double x_min = points[P[0]].x;
    double x_max = points[P[n-1]].x;

    for(int i=0; x_min+i*1<=x_max; i++)
    {
        out_x.push_back(x_min+i*1);
    }

    for (int i=0; i<out_x.size(); i++)
    {
        int k = 0;
        for(int j = 0; points[P[j]].x<out_x[i]; j++)
        {
            k = j;
        }

        double t = out_x[i]-points[P[k]].x;
        double a;
        a = s3[k]*pow(t,3)+s2[k]*pow(t,2)+s1[k]*t+s0[k];

        out_y.push_back(a);
    }

    return QPair<QVector<double>,QVector<double>>(out_x, out_y);
}

QPair<QVector<double>, QVector<double>> task_data::cubic_parametrical()
{
    int n = points.size();

    QVector<double> t;
    QVector<double> tt;
    t.push_back(0);

    for(int i=0; i<n-1; i++)
    {
        double a = sqrt(pow(points[i+1].x-points[i].x, 2)+pow(points[i+1].y-points[i].y, 2));
        a = a + t[i];
        t.push_back(a);
    }

    double t_min = 0;
    double t_max = t[n-1];

    for(int i=0; t_min+i*1<=t_max; i++)
    {
        tt.push_back(t_min+i*1);
    }

    QVector<double> h(n-1);

    QVector<double> mdx(n-1);
    QVector<double> mdy(n-1);

    for (int i = 0; i < n-1; i++)
    {
        h[i] = t[i+1] - t[i];
    }

    for (int i = 0; i<n-1; i++)
    {
        mdx[i] = (points[i+1].x - points[i].x)/h[i];
        mdy[i] = (points[i+1].y - points[i].y)/h[i];
    }

    QVector<double> a(n-2);
    QVector<double> b(n-2);
    QVector<double> c(n-2);
    for (int i = 0; i < n-2; i++)
    {
        a[i] = h[i];
        c[i] = h[i+1];
    }
    //a.push_front(0);
    //c.push_back(0);
    for (int i = 0; i < n-2; i++)
    {
        b[i] = 2*(h[i]+h[i+1]);
    }

    QVector<double> dx(n-2);
    QVector<double> dy(n-2);
    for(int i=0; i<n-2; i++)
    {
        dx[i]=6*(mdx[i+1]-mdx[i]);
        dy[i]=6*(mdy[i+1]-mdy[i]);
    }

    QVector<double> mx;
    QVector<double> my;

    if(n>2)
    {
        mx = tridiagonal_matrix_algorithm(a, b, c, dx);
        my = tridiagonal_matrix_algorithm(a, b, c, dy);
    }

    //краевые условия
    mx.push_front(0);
    mx.push_back(0);
    my.push_front(0);
    my.push_back(0);

    QVector<double> s3x(n-1);
    QVector<double> s2x(n-1);
    QVector<double> s1x(n-1);
    QVector<double> s0x(n-1);

    QVector<double> s3y(n-1);
    QVector<double> s2y(n-1);
    QVector<double> s1y(n-1);
    QVector<double> s0y(n-1);

    for (int i = 0; i < n-1; i++)
    {
        s3x[i] = (mx[i+1] - mx[i])/(6*h[i]);
        s2x[i] = mx[i]/2;
        s1x[i] = mdx[i] - h[i]*(2*mx[i] + mx[i+1])/6;
        s0x[i] = points[i].x;

        s3y[i] = (my[i+1] - my[i])/(6*h[i]);
        s2y[i] = my[i]/2;
        s1y[i] = mdy[i] - h[i]*(2*my[i] + my[i+1])/6;
        s0y[i] = points[i].y;
    }

    QVector<double> out_x;
    QVector<double> out_y;

    for (int i=0; i<tt.size(); i++)
    {
        int k = 0;
        for(int j = 0; t[j]<tt[i]; j++)
        {
            k = j;
        }

        double s = tt[i]-t[k];
        double ax;
        ax = s3x[k]*pow(s,3)+s2x[k]*pow(s,2)+s1x[k]*s+s0x[k];
        double ay;
        ay = s3y[k]*pow(s,3)+s2y[k]*pow(s,2)+s1y[k]*s+s0y[k];

        out_x.push_back(ax);
        out_y.push_back(ay);
    }

    return QPair<QVector<double>,QVector<double>>(out_x, out_y);
}
