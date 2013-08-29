#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Person {
	char name[10];
	int age;
	int worth;
};

const int MAX_PERSONS = 100010;
Person person[MAX_PERSONS];
Person person1[MAX_PERSONS];
int N, K;

int cmpAge(const void *a, const void *b) {
	Person p1 = *(Person*)a;
	Person p2 = *(Person*)b;
	return p1.age - p2.age;
}

int cmp(const void *a, const void *b) {
	Person p1 = *(Person*)a;
	Person p2 = *(Person*)b;
	if (p2.worth != p1.worth)
		return p2.worth - p1.worth;
	if (p1.age != p2.age)	
		return p1.age - p2.age;
	return strcmp(p1.name, p2.name); }

void dumpPerson1() {
	for (int i = 0; i < N; i++) {
		printf("%s %d %d\n", person1[i].name, person1[i].age, 
				person1[i].worth);
	}
}

int main() {
	while (scanf("%d %d", &N, &K) != -1) {
		for (int i = 0; i < N; i++) {
			scanf("%s %d %d", person[i].name, &person[i].age, &person[i].worth);
			person1[i] = person[i];
		}
		qsort(person1, N, sizeof(Person), cmpAge);
		printf("after sort by age: \n\n");
		dumpPerson1();

		printf("after sort by requirements: \n\n");
		qsort(person1, N, sizeof(Person), cmp);
		dumpPerson1();
	}
	return 0;
}
