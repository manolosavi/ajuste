//
//  montante.cpp
//  ajuste
//
//  Created by manolo on 11/5/14.
//  Copyright (c) 2014 manolo. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

class Point {
public:
	Point(int a, int b){i=a;j=b;};
	int i;
	int j;
};

//vector< vector<double> > a;

void multiplica(vector< vector<double> > a, Point p, Point f, int piv) {
	if (p.i < f.i) {
		a[f.i][f.j] = (a[p.i][p.j]*a[f.i][f.j] - a[p.i][f.j]*a[f.i][p.i]) / piv;
	} else {
		a[f.i][f.j] = (a[f.i][p.j]*a[p.i][f.j] - a[f.i][f.j]*a[p.i][p.i]) / (-piv);
	}
}

bool compare(vector< vector<double> > a, int x, int y) {
	vector<double> d;
	for (int i=0; i<a.size(); i++) {
		if (a[x][i] != a[y][i]) {
			return false;
		}
		if (a[x][i]/a[y][i] != 0) {
			d.push_back(a[x][i]/a[y][i]);
		}
	}
	for (int i=0; i<d.size(); i++) {
		if (d[0] != d[i]) {
			return false;
		}
	}
	return true;
}

void solve(vector< vector<double> > &a, int numVariables, vector<double> &r) {
	int pivAct, pivAnt = 1;
	
	for (int i=0; i<numVariables; i++) {
		pivAct = a[i][i];
		
		//			cambia renglones
		if (pivAct == 0) {
			for (int x=i; x<numVariables; x++) {
				if (a[x][i] != 0) {
					pivAct = a[x][i];
					a[i].swap(a[x]);
					break;
				}
			}
		}
		
		//			hace nueva iteracion
		for (int x=0; x<numVariables; x++) {
			if (x!=i) {
				for (int y=i+1; y<=numVariables; y++) {
					multiplica(a, Point(i,i), Point(x,y), pivAnt);
				}
			}
		}
		
		//			hace ceros
		for (int x=0; x<numVariables; x++) {
			for (int y=0; y<=i; y++) {
				if (x==y) {
					a[x][x] = a[i][i];
				} else {
					a[x][y] = 0;
				}
			}
		}
		pivAnt = pivAct;
	}
	
	for (int i=0; i<numVariables; i++) {
		r.push_back(a[i][numVariables]/a[i][i]);
	}
}