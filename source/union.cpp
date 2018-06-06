#include "union.h"

Union::Union(){

}

Union::~Union(){

}

void Union::unionOperation ( std::vector<ushort> &Arr, int A, int B ){
	ushort TEMP = Arr[ A ];
	for(int i = 0; i < Arr.size();i++)
	    {
	    if(Arr[ i ] == TEMP)
	    Arr[ i ] = Arr[ B ]; 
	    }
}