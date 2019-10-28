// class derived from cp264 implementations
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>

#include "data.h"
Data* copy_data(Data* d){
	return copy_process(d);
}
