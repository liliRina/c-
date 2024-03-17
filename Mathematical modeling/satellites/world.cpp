#include "world.h"

world::world(QObject *parent)
    : QObject{parent}
{
    create_world();
    std::cout<<object.size()<<std::endl;
}
void world::addObject(worldObject *obj)
{
    if(!this->vector_objects.contains(obj))
    {
        this->vector_objects.push_back(obj);
    }
}
std::vector <double> world::world_Update(int time) // а в чём время-то измеряется?
{
    int x, y, z;
    for(int i = 1; i < this->object.size(); i++)// не баг, а фича: только с 1 работает
    {
        //std::cout<<satellites[i-1].PositionEci(time).Position().m_x<<std::endl;
        object[i][0]=satellites[i-1].PositionEci(time).Position().m_x;
        object[i][1]=satellites[i-1].PositionEci(time).Position().m_y;
        object[i][2]=satellites[i-1].PositionEci(time).Position().m_z;
    }
   // std::cout<<satellites[0].PositionEci(time).Position().m_x<<std::endl;
   // std::cout<<object[1][0]<<" "<<object[1][1]<<" "<<object[1][2]<<std::endl;
    return {object[1][0], object[1][1], object[1][2]};
}

void world::create_world()
{
    QVector <std::string> strlist;
    QVector <cOrbit> satellites_temp;
    cVector temp_coord;
    cVector temp_vel;
    std::string str;
    std::string TLE_file_name;
    TLE_file_name = "C:/Users/Sharlotte/Desktop/trouble2/oneweb.txt";
    const char *cstr = TLE_file_name.c_str();
    QFile file(cstr);
    if(!file.open(QIODevice::ReadOnly| QIODevice :: Text))
    {
        std::cout<<"No such file exists."<<std::endl;
    }
    else
    {
        QTextStream in(&file);
        while(!in.atEnd()) // Считали строки нашего файла со спутниками
        {
            QString qstring_str = in.readLine(1000);
            str = qstring_str.toStdString();
            strlist.push_back(str);
        }
    }
    double x, y, z, V_x, V_y, V_z;
    for(int i=0; i<strlist.length(); i = i+3)
    {
        satellites_temp.push_back(cOrbit(cTle(strlist[i], strlist[i+1], strlist[i+2])));
        satellites.push_back(cOrbit(cTle(strlist[i], strlist[i+1], strlist[i+2])));

    }
    for (int i=0; i<satellites.size(); i++)
    {
        temp_coord = satellites_temp[i].PositionEci(0).Position();
        x = temp_coord.m_x;                                    //Вычленил оттуда координаты и скорости отдельно для каждой проекции
        y = temp_coord.m_y;
        z = temp_coord.m_z;
        object.push_back({x, y, z});
    }
    satellites_temp.clear();
    file.close();
}
