#include <stdio.h>

class A {
public: 
	virtual void f() {
		printf("A:f\n");
	}
};

class B {
public: 
	virtual void f() {
		printf("B:f\n");
	}
};

class C : public A, public B {
public: 
	virtual void f() {
		printf("C:f\n");
	}
};

class A1 : public A {
public: 
	void f() {
		printf("A1:f\n");
	}
};

int main() {
	C c;
	c.f();
	c.A::f();
	c.B::f();

	A *a = new C();
	a->f();
	a->A::f();
//	a->B::f(); // compile error!!!

	C c1;
	A &a1 = c1;
	a1.f();
}
