#include <unistd.h>
#include <cstdlib>
#include <iostream>
int main(){
	sleep(1);
	int* p = nullptr;
	*p = 42; // segmentation fault
}
