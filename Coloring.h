#pragma once
typedef int index;
class Coloring
{
public:
	int n, m;
	int turn;
	int W[26][26];
	int vcolor[26];
	Coloring();
	~Coloring();
	void m_coloring(index i);
	bool promising(index i);
};

