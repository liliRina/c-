#include "task_data.h"
#include <iostream>
#include <vector>
#include <iostream>
void task_data :: schitaim_ch()
{
    int n=chki[chki.size()-1].size();
    chki.resize(chki.size()+1);
    chki[chki.size()-1].push_back(1);
    for (int i=0; i<n-1; i++)
    {
        chki[chki.size()-1].push_back(chki[chki.size()-2][i]+chki[chki.size()-2][i+1]);
        std::cout<<chki.size()-1<<std::endl;
    }
    chki.back().push_back(1);
}
