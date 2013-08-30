#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

struct Person {
	char name[10];
	int age;
	int worth;

	bool operator >(const Person &person) const {
		if (person.worth != worth)
			return worth > person.worth;
		if (person.age != age)
			return age < person.age;
		return strcmp(name, person.name) < 0;
	}

	bool operator <(const Person &person) const {
		return !(*this > person);
	}
};

const int MAX_PERSONS = 100010;
const int MAX_AGE = 210;
Person person[MAX_PERSONS];
int N, K;
int minAge, maxAge;
int age_lower_bound[MAX_AGE];
int age_upper_bound[MAX_AGE];
int tmpIndex[MAX_PERSONS];
vector<vector<vector<int> > > res;

int cmpAge(const void *a, const void *b) {
	Person p1 = *(Person*)a;
	Person p2 = *(Person*)b;
	return p1.age - p2.age;
}

int cmp(const void *a, const void *b) {
	Person p1 = person[*(int*)a];
	Person p2 = person[*(int*)b];
	if (p2.worth != p1.worth)
		return p2.worth - p1.worth;
	if (p1.age != p2.age)	
		return p1.age - p2.age;
	return strcmp(p1.name, p2.name); 
}

int search_lower_bound(int age, int left, int right) {
	while (left < right - 1) {
		int mid = (left + right) / 2;
		int midValue = person[mid].age;
		if (midValue >= age) {
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}
	if (person[left].age >= age)
		return left;
	if (person[right].age < age)
		return right + 1;
	return right;
}

int search_upper_bound(int age, int left, int right) {
	while (left < right - 1) {
		int mid = (left + right) / 2;
		int midValue = person[mid].age;
		if (midValue <= age) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	if (person[right].age <= age)
		return right;
	if (person[left].age > age)
		return left - 1;
	return left;
}

void calcBounds() {
	for (int i = 0; i <= 200; i++) {
		age_lower_bound[i] = search_lower_bound(i, 0, N - 1);
		age_upper_bound[i] = search_upper_bound(i, 0, N - 1);
	}
}

void calcOne(int age, vector<int> &res) {
	int t = 0;
	for (int i = age_lower_bound[age]; i <= age_upper_bound[age]; i++) {
		tmpIndex[t++] = i;
	}
	qsort(tmpIndex, t, sizeof(int), cmp);
	for (int i = 0; i < t && i < 100; i++) {
		res.push_back(tmpIndex[i]);
	}
}

void merge_sort(const vector<int> &pre, const vector<int> &latter, vector<int> &res) {
	int i = 0, j = 0, t = 0;
	int preSize = pre.size();
	int latterSize = latter.size();
	while (i < preSize && j < latterSize) {
		if (person[pre[i]] < person[latter[j]]) {
			res.push_back(latter[j++]);
			t++;
		} else {
			res.push_back(pre[i++]);
			t++;
		}
		if (t >= 100) {
			return;
		}
	}
	if (i < preSize) {
		for (; i < preSize; i++) {
			res.push_back(pre[i]);
			t++;
			if (t >= 100)
				return;
		}
	}

	if (j < latterSize) {
		for (; j < latterSize; j++) {
			res.push_back(latter[j]);
			t++;
			if (t >= 100)
				return;
		}
	}
}

/**

12 4
Zoe_Bill 35 2333
Bob_Volk 24 5888
Anny_Cin 95 999999
Williams 30 -22
Cindy 76 76000
Alice 18 88888
Joe_Mike 32 3222
Michael 5 300000
Rosemary 40 5888
Dobby 24 5888
Billy 24 5888
Nobody 5 0
4 15 45
4 30 35
4 5 95
1 45 50

*/
int main() {
	while (scanf("%d %d", &N, &K) != -1) {
		res.clear();
		res.resize(210);
		for (int i = 1; i <= 200; i++) {
			res[i].resize(210);
		}
		minAge = 210;
		maxAge = -1;

		for (int i = 0; i < N; i++) {
			scanf("%s %d %d", person[i].name, &person[i].age, &person[i].worth);
			if (minAge > person[i].age)
				minAge = person[i].age;
			if (maxAge < person[i].age)
				maxAge = person[i].age;
		}

		qsort(person, N, sizeof(Person), cmpAge);
		calcBounds();
		for (int i = 1; i <= 200; i++) {
			calcOne(i, res[i][i]);
		}
		for (int i = 1; i < 200; i++) {
			for (int j = i + 1; j <= 200; j++) {
				merge_sort(res[i][j - 1], res[j][j], res[i][j]);
			}
		}

		int m, amin, amax;
		for (int i = 1; i <= K; i++) {
			scanf("%d %d %d", &m, &amin, &amax);
			if (amin < minAge)
				amin = minAge;
			if (amax > maxAge)
				amax = maxAge;

			printf("Case #%d:\n", i);
			if (amax < amin) {
				printf("None\n");
			} else {
				vector<int> v = res[amin][amax];
				if (v.size() == 0)
					printf("None\n");
				else {
					for (int j = 0; j < v.size() && j < m; j++) {
						printf("%s %d %d\n", person[v[j]].name, person[v[j]].age, 
								person[v[j]].worth);
					}
				}
			}
		}
	}
	return 0;
}
