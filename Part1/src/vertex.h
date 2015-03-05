/**
 * @file station.h
 * @brief 
 *
 * @author Marlier Maxime <marlier.maxime@gmail.com>
 *
 **/

#ifndef VERTEX		
#define VERTEX	

#include <vector>
#include <string>
#include <algorithm>

using namespace std;


class vertex    
{

struct connection
{
	vertex * node;
	int weight;
};

private:
    // string name;
	// vector < vertex * > connected;
	vector < connection > connected;
	bool check;

	int indice;

public:
    vertex();
    vertex(int i);
    void add_connection(vertex * con, int weight);
    void add_connection(vertex * con);
    int is_connected(vertex * con);

	int getId();


    void setCheck(bool state);
    bool isChecked();

    vertex* nextCon();
    vertex* nextCon_reverse();


};



#endif
