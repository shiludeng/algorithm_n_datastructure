#include <stdio.h>
#include <string.h>

class A {
	public:
		void f() {
			printf("f\n");
		}
		void f() const {
			printf("const f\n");
		}
};

int main() {
	A a;
	a.f();

	A const b;
	b.f();
}
