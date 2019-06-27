//Joseph Harrison 2019
//compute roots of polynomials
//using the Aberth Method

#include <iostream>
#include <complex>

using namespace std;

//compute p(x) given array of p(x) coefficients and order
complex<double> polynomial(complex<double> x, complex<double> * coeffs, int order)
{
	complex<double> result;
	for (int i = 0; i <= order; i++)
	{
		result += coeffs[i] * pow(x, i);
	}
	return result;
}

void compute_offsets(complex<double> * z, complex<double> * coeffs, complex<double> * w, int order)
{
	//coefficients of derivative polynomial
	complex<double> dercoeffs[order];
	for (int i = 1; i <= order; i++)
	{
		dercoeffs[i - 1] = coeffs[i] * (complex<double>)i;
	}	

	complex<double> ratio, total;
	for (int i = 0; i < order; i++)
	{
		ratio = polynomial(z[i], coeffs, order) / polynomial(z[i], dercoeffs, order - 1);
		total = 0;
		for (int j = 0; j < order; j++)
		{
			if (i == j)
			{
				continue;
			}
			else
			{
				total += (complex<double> (1, 0)) / (z[i] - z[j]);
			}
		}
		w[i] = ratio / ((complex<double> (1, 0)) - ratio * total);
	}
}

int main(int argc, char ** argv)
{
	int order;
	
	cout << "polynomial order: ";
	cin >> order;

	//get polynomial coefficients from user
	double realpart, imagpart;
	complex<double> coeffs[order + 1];
	for (int i = 0; i <= order; i++){
		cout << "x^" << i << " term:\n"
		     << "real part: ";
		cin >> realpart;
		cout << "imag part: ";
		cin >> imagpart;
		coeffs[i] = complex<double> (realpart, imagpart);
	}

	//create heuristic set of roots, z
	complex<double> z[order];
	//create offset set, w
	complex<double> w[order];

	//set elements of sets
	for (int i = 1; i <= order; i++)
	{
		//roots cannot be the same initially
		//as this would result in division by 0
		z[i - 1] = complex<double> (i, i + 1);
		w[i - 1] = complex<double> (i + 1, i);
	}

	int iterations;
	cout << "iterations: ";
	cin >> iterations;

	for (int i = 0; i < iterations; i++)
	{
		compute_offsets(z, coeffs, w, order);
	
		//apply offsets
		for (int j = 0; j < order; j++)
		{
			z[j] -= w[j];
		}
	}

	//output result roots
	cout << "roots: " << endl;
	for (int i = 0; i < order; i++)
	{
		cout << real(z[i]) << " + " 
		     << imag(z[i]) << "i" << endl;
	}
    
	return 0;
}

