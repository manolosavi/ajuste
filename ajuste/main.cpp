//
//  main.cpp
//  ajuste
//
//  Created by manolo on 11/5/14.
//  Copyright (c) 2014 manolo. All rights reserved.
//

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
	
	double x=0, y=0, wh=0;

if (false) {//debug (usar 10 datos, X polinomios)
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
	xi.push_back(6);
	yi.push_back(3.8);
	xi.push_back(8);
	yi.push_back(3.7);
	xi.push_back(10);
	yi.push_back(4);
	xi.push_back(12);
	yi.push_back(3.9);
	xi.push_back(14);
	yi.push_back(4.3);
	xi.push_back(16);
	yi.push_back(4.2);
	xi.push_back(18);
	yi.push_back(4.2);
	xi.push_back(20);
	yi.push_back(4.4);
	xi.push_back(22);
	yi.push_back(4.5);
	xi.push_back(24);
	yi.push_back(4.5);
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
					temp.push_back(sum(xi, yi, i+j, 0));//suma puras x
				}
			}
			matriz.push_back(temp);//guarda renglon en matriz
		}
		
		for (int a=0; a<matriz.size(); a++) {
			for (int b=0; b<matriz[a].size(); b++) {
				cout << matriz[a][b] << " ";
			}
			cout << endl;
		}
		
		solve(matriz, p+1, coeficientes[p-1]);
//		resuelve la matriz con montante, regresa las respuestas en el vector coeficientes
		
		for (int a=0; a<matriz.size(); a++) {
			for (int b=0; b<matriz[a].size(); b++) {
				cout << matriz[a][b] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
		
		for (int a=0; a<matriz.size(); a++) {//borrar matriz para reusar
			matriz[a].clear();
		}
		matriz.clear();
	}
	
	
	
//	imprime respuestas
	for (int i=0; i<maxPolinomio; i++) {
		cout <<"Polinomio de grado " << i+1 << ":\n";
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
