#include <stdio.h>

template<class T>
class HasPtr;

template<class T>
class U_Ptr {
private:
	T *ptr;
	int use;
friend class HasPtr<T>;
public:
	U_Ptr(T *p) : ptr(p), use(1) {
		printf("u_ptr constructor called\n");
	}

	~U_Ptr() {
		printf("u_ptr destructor called\n");
		delete ptr;
	}
};

template<class T>
class HasPtr {
public:
	HasPtr(T *p) : ptr(new U_Ptr<T>(p)), data(0) {
		printf("hasptr constructor called\n");
	}

	HasPtr(const HasPtr &origin) : ptr(origin.ptr), data(origin.data) {
		printf("hasptr copy constructor called\n");
		ptr->use++;
	}

	HasPtr& operator = (const HasPtr &origin) {
		printf("hasptr operator = called\n");
		origin.ptr->use++;
		if (--ptr->use == 0) {
			delete ptr;
		}
		ptr = origin.ptr;
		data = origin.data;
		return *this;
	}

	~HasPtr() {
		printf("hasptr destructor called\n");
		--ptr->use;
		if (0 == ptr->use) {
			delete ptr;
		}
	}

	T get_ptr_val() const {
		return *ptr->ptr;
	}
	void set_ptr_val(T p) {
		*ptr->ptr = p;
	}

	T* get_ptr() const {
		return ptr->ptr;
	}
private:
	U_Ptr<T> *ptr;
	int data;
};

int main() {
	int *p = new int(42);
	HasPtr<int> *hpa = new HasPtr<int>(p);
	HasPtr<int> *hpb = new HasPtr<int>(*hpa);
	HasPtr<int> *hpc = new HasPtr<int>(*hpb);
	HasPtr<int> hpd = *hpa;
	HasPtr<int> hpe = hpd;
	hpe = hpd;

	printf("%d %d\n", hpa->get_ptr_val(), hpb->get_ptr_val());	
	hpc->set_ptr_val(10000);
	printf("%d %d\n", hpa->get_ptr_val(), hpb->get_ptr_val());	
	hpd.set_ptr_val(10);
	printf("%d %d\n", hpa->get_ptr_val(), hpb->get_ptr_val());	
	delete hpa;
	delete hpb;
	delete hpc;
	
	printf("%d\n", hpd.get_ptr_val());
	return 0;
}
