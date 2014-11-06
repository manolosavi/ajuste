//
//  main.cpp
//  ajuste
//
//  Created by manolo on 11/5/14.
//  Copyright (c) 2014 manolo. All rights reserved.
//

#include <math.h>
#include "montante.cpp"

//regresa la sumatoria que se guarda en la matriz
double sum(vector<double> x, vector<double> y, int powX, int powY) {
	double total = 0;
	
	if (powY > 0) {//incluye y's
		for (int i=0; i<x.size(); i++) {
			total += pow(x[i], powX) * pow(y[i], powY);
		}
	} else {//ignora y's
		for (int i=0; i<x.size(); i++) {
			total += pow(x[i], powX);
		}
	}
	
	return total;
}

int main() {
	int numDatos, maxPolinomio;
	vector<double> xi, yi;
	vector< vector<double> > matriz, coeficientes;
	bool error = false;
	
	cout << "Cual es el numero de datos a ajustar?\n";
	cin >> numDatos;
	
	do {
		if (error) {
			cout << "No se puede ajustar a un polinomio mayor al numero de datos, vuelva a intentar.\n";
		}
		cout << "Cual es el maximo polinomio a ajustar?\n";
		cin >> maxPolinomio;
		error = (maxPolinomio > numDatos);
	} while (error);
	
	int x=0, y=0, wh=0;

if (false) {//debug (usar 4 datos, X polinomios)
//	leer xi, yi
	for (int i=0; i<numDatos; i++) {
		do {
			if (error) {
				cout << "El valor de x = " << x <<" ya fue agregado previamente, intente otro valor.\n";
				error = false;
			}
			cout << "Cual es el valor de x" << i+1 << "?\n";
			cin >> x;
			while (wh < xi.size()) {
				if (x == xi[wh]) {
					error = true;
				}
				wh++;
			}
			wh=0;
			if (!error) {
				cout << "Cual es el valor de y en x = " << x << "?\n";
				cin >> y;
				xi.push_back(x);
				yi.push_back(y);
			}
		} while (error);
	}
}//debug----
	xi.push_back(-1);
	yi.push_back(3);
	xi.push_back(0);
	yi.push_back(-4);
	xi.push_back(1);
	yi.push_back(1);
	xi.push_back(2);
	yi.push_back(3);
	//debug----
	
	
	for (int i=0; i<maxPolinomio; i++) {//inicializa los vectores
		coeficientes.push_back(vector<double>());
	}
	
	for (int p=1; p<=maxPolinomio; p++) {//polinomios
		
		for (int i=0; i<=p; i++) {//renglon
			vector<double> temp;//temporalmente guardar renglon
			for (int j=0; j<=p+1; j++) {//columna
				if (j == p+1) {
					temp.push_back(sum(xi, yi, i, 1));//suma x's * y
				} else {
					temp.push_back(sum(xi, yi, i+j, 0));// suma puras x
				}
			}
			matriz.push_back(temp);//guarda renglon en matriz
		}
		
		solve(matriz, p+1, coeficientes[p-1]);
//		resuelve la matriz con montante, regresa las respuestas en el vector coeficientes
		
		for (int a=0; a<matriz.size(); a++) {
				cout << coeficientes[p-1][a] << endl;
		}
		
		for (int a=0; a<matriz.size(); a++) {//borrar matriz para reusar
			matriz[a].clear();
		}
		matriz.clear();
	}
	
	
	
//	imprime respuestas
	for (int i=0; i<maxPolinomio; i++) {
		cout <<"Polinomio de grado " << i << ":\n";
		for (int j=0; j<=i; j++) {
			if (coeficientes[i][j] > 0) {
				cout << "+";
			}
			cout << coeficientes[i][j] << "x^" << j << " ";
		}
		cout << endl;
	}
    return 0;
}
