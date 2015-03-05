/**
 * @file station.h
 * @brief 
 *
 * @author Marlier Maxime <marlier.maxime@gmail.com>
 *
 **/

#ifndef STATION		
#define STATION	

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class station    
{
private:
    string name;
    vector<station*> connected;

public:
    station();

};

#endif
