//
//  main.cpp
//  ajuste
//
//  Created by manolo on 11/5/14.
//  Copyright (c) 2014 manolo. All rights reserved.
//

#include "montante.cpp"

//regresa la sumatoria que se guarda en la matriz
long double sum(vector<long double> x, vector<long double> y, int powX, int powY) {
	long double total = 0;
	
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

long double f(vector<long double> coeficientes, long double x) {
	long double r = 0;
	
	for (int i=0; i<coeficientes.size(); i++) {
		r += coeficientes[i]*pow(x, i);
	}
	
	return r;
}

int main() {
	int numDatos, maxPolinomio;
	vector<long double> xi, yi, q;
	vector< vector<long double> > matriz, coeficientes;
	bool error = false;
	
	cout << "Cual es el numero de datos a ajustar?\n";
	cin >> numDatos;
	
	do {
		if (error) {
			cout << "El polinomio a ajustar debe ser menor al numero de datos, vuelva a intentar.\n";
		}
		cout << "Cual es el maximo polinomio a ajustar?\n";
		cin >> maxPolinomio;
		error = (maxPolinomio >= numDatos);
	} while (error);
	
	long double x=0, y=0, wh=0;
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
	
	for (int i=0; i<maxPolinomio; i++) {//inicializa los vectores
		coeficientes.push_back(vector<long double>());
		q.push_back(0);
	}
	
	for (int p=1; p<=maxPolinomio; p++) {//polinomios
		
		for (int i=0; i<=p; i++) {//renglon
			vector<long double> temp;//temporalmente guardar renglon
			for (int j=0; j<=p+1; j++) {//columna
				if (j == p+1) {
					temp.push_back(sum(xi, yi, i, 1));//suma x's * y
				} else {
					temp.push_back(sum(xi, yi, i+j, 0));//suma puras x
				}
			}
			matriz.push_back(temp);//guarda renglon en matriz
		}
		
		solve(matriz, p+1, coeficientes[p-1]);
//		resuelve la matriz con montante, regresa las respuestas en el vector coeficientes
		
		for (int a=0; a<matriz.size(); a++) {//borrar matriz para reusar
			matriz[a].clear();
		}
		matriz.clear();
	}
	
	
	
//	imprime respuestas
	for (int i=0; i<maxPolinomio; i++) {
		cout << "Polinomio de grado " << i+1 << ":\n";
		for (int j=0; j<=i+1; j++) {
			if (coeficientes[i][j] > 0) {
				cout << "+";
			}
			cout << coeficientes[i][j] << "x^" << j << " ";
		}
		cout << endl << endl;
	}
	
	for (int i=0; i<maxPolinomio; i++) {
		long double temp = 0;
		for (int j=0; j<numDatos; j++) {
			temp += pow(f(coeficientes[i], xi[j])-yi[j], 2);
		}
		q[i] = temp;
	}
	
	int min = 0;
	long double mini = q[0];
	for (int i=0; i<maxPolinomio; i++) {
		if (q[i] < q[min]) {
			min = i;
			mini = q[i];
		}
	}
	
	cout << "La mejor aproximacion es con el polinomio de grado " << min+1 << ", con una Q de " << q[min] << ".\n";
	
    return 0;
}