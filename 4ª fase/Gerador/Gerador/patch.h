#pragma once

#include <vector>

using namespace std;

class Patch {
	vector<int> indices;
public:
	Patch();
	vector<int> getPatch() { return indices; }
	void adicionaIndice(int);
	virtual ~Patch();
};