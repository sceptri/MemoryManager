#ifndef COMPLEX_H
#define COMPLEX_H

typedef unsigned long int size_t;

class Complex
{
public:
	Complex(double a, double b) : r (a), c (b) {} //8 bytes
#ifdef USE_MEMORY_MANAGER
	void* operator new(size_t); //8 bytes - it's inline, I'm not sure
	void operator delete(void*);
#endif
private:
	double r; //asi 8
	double c;
};


#endif // COMPLEX_H
