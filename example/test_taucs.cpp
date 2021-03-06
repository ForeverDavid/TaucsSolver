#include <taucs_matrix.h>
#include <taucs_solver.h>
#include <iostream>


bool test_symmetry() {
	/*
		10     0    0   -2   -1   -1
		 0    10    0    0   -2    0
		 0     0   15    0    0    0
		-2     0    0   10   -1    0
		-1    -2    0   -1    1    0
		-1     0    0    0    0    6

		b = (-9, 10, 45, 33, −4, 35)T
	*/

	const unsigned int n = 6;
	TaucsMatrix M(n, n, true);
	M.set_coef(0, 0, 10.0);
	M.set_coef(3, 0, -2.0);
	M.set_coef(4, 0, -1.0);
	M.set_coef(5, 0, -1.0);
	M.set_coef(1, 1, 10.0);
	M.set_coef(4, 1, -2.0);
	M.set_coef(2, 2, 15.0);
	M.set_coef(3, 3, 10.0);
	M.set_coef(4, 3, -1.0);
	M.set_coef(4, 4, 1.0);
	M.set_coef(5, 5,  6.0);

	std::vector<double> b(n);
	b[0] = -9;
	b[1] = 10;
	b[2] = 45; 
	b[3] = 33;  
	b[4] = -4;  
	b[5] = 35;

	std::vector<double> x;
	bool success = TaucsSolver::solve_symmetry(M, b, x);
	if (success) {
		std::cout << "output for symmetry test (only one rhs vector): " << std::endl;
		for (unsigned int i=0; i<n; ++i)
			std::cout << x[i] << "  " ;
		std::cout << std::endl;
	}

	//////////////////////////////////////////////////////////////////////////

	// another rhs
	std::vector<double> c(n);
	c[0] = b[0]*2;
	c[1] = b[1]*2;
	c[2] = b[2]*2; 
	c[3] = b[3]*2;  
	c[4] = b[4]*2;  
	c[5] = b[5]*2;

	std::vector<std::vector<double>> B;
	B.push_back(b);
	B.push_back(c);
	std::vector<std::vector<double>> X;
	success = TaucsSolver::solve_symmetry(M, B, X);
	if (success) {
		std::cout << "output for symmetry test (an array of rhs vectors): " << std::endl;
		for (unsigned int i=0; i<X.size(); ++i) {
			for (unsigned int j=0; j<n; ++j) {
				std::cout << X[i][j] << "  " ;
			}
			std::cout << std::endl;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	return success;
}





bool test_non_symmetry() {
	/*
		10     0    0    0    0    0
		 0    10   -3    -1   0    0
		 0     0   15    0    0    0
		-2     0    0   10   -1    0
		-1    -2    0   -5    1   -3
		-1     0    0    0    0    6

		b = (10, 7, 45, 33, −38, 35)T
	*/

	const unsigned int n = 6;
	TaucsMatrix M(n, n, false);
	M.set_coef(0, 0, 10.0);
	M.set_coef(1, 1, 10.0);
	M.set_coef(1, 2, -3.0);
	M.set_coef(1, 3, -1.0);
	M.set_coef(2, 2, 15.0);
	M.set_coef(3, 0, -2.0);
	M.set_coef(3, 3, 10.0);
	M.set_coef(3, 4, -1.0);
	M.set_coef(4, 0, -1.0);
	M.set_coef(4, 1, -2.0);
	M.set_coef(4, 3, -5.0);
	M.set_coef(4, 4,  1.0);
	M.set_coef(4, 5, -3.0);
	M.set_coef(5, 0, -1.0);
	M.set_coef(5, 5,  6.0);

	std::vector<double> b(n);
	b[0] = 10;
	b[1] = 7;
	b[2] = 45; 
	b[3] = 33;  
	b[4] = -38;  
	b[5] = 35;

	std::vector<double> x;
	bool success = TaucsSolver::solve_non_symmetry(M, b, x);
	if (success) {
		std::cout << "output for non-symmetry test (only one rhs vector): " << std::endl;
		for (unsigned int i=0; i<n; ++i)
			std::cout << x[i] << "  " ;
		std::cout << std::endl;
	}

	//////////////////////////////////////////////////////////////////////////

	// another rhs
	std::vector<double> c(n);
	c[0] = b[0]*2;
	c[1] = b[1]*2;
	c[2] = b[2]*2; 
	c[3] = b[3]*2;  
	c[4] = b[4]*2;  
	c[5] = b[5]*2;

	std::vector<std::vector<double>> B;
	B.push_back(b);
	B.push_back(c);
	std::vector<std::vector<double>> X;
	success = TaucsSolver::solve_non_symmetry(M, B, X);
	if (success) {
		std::cout << "output for non-symmetry test (an array of rhs vectors): " << std::endl;
		for (unsigned int i=0; i<X.size(); ++i) {
			for (unsigned int j=0; j<n; ++j) {
				std::cout << X[i][j] << "  " ;
			}
			std::cout << std::endl;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	return success;
}




bool test_linear_least_square() {
	/*
	  10    0    0    0    0   0
	   0   10   -3   -1    0   0
	   0    0   15    0    0   0
	  -2    0    0   10   -1   0
	  -1    0    0   -5    1  -3
	  -1   -2    0    0    0   6
	   0    0    1    0    0  -1
	   2    0    0    0    4   0

	   b = (10, 7, 45, 33, −34, 31, -3, 22)T
	*/


	const int row = 8;
	const int col = 6;

	TaucsMatrix M(row, col, false);
	M.set_coef(0, 0, 10.0);
	M.set_coef(1, 1, 10.0);
	M.set_coef(1, 2, -3.0);
	M.set_coef(1, 3, -1.0);
	M.set_coef(2, 2, 15.0);
	M.set_coef(3, 0, -2.0);
	M.set_coef(3, 3, 10.0);
	M.set_coef(3, 4, -1.0);
	M.set_coef(4, 0, -1.0);
	M.set_coef(4, 3, -5.0);
	M.set_coef(4, 4,  1.0);
	M.set_coef(4, 5, -3.0);
	M.set_coef(5, 0, -1.0);
	M.set_coef(5, 1, -2.0);
	M.set_coef(5, 5,  6.0);
	M.set_coef(6, 2,  1.0);
	M.set_coef(6, 5, -1.0);
	M.set_coef(7, 0,  2.0);
	M.set_coef(7, 4,  4.0);

	std::vector<double> b(row);
	b[0] = 10;
	b[1] = 7;
	b[2] = 45; 
	b[3] = 33;  
	b[4] = -34;  
	b[5] = 31;
	b[6] = -3;
	b[7] = 22;

	std::vector<double> x;
	bool success = TaucsSolver::solve_linear_least_square(M, b, x);
	if (success) {
		std::cout << "output for linear least square test (only one rhs vector): " << std::endl;
		for (unsigned int i=0; i<col; ++i)
			std::cout << x[i] << "  " ;
		std::cout << std::endl;
	}

	//////////////////////////////////////////////////////////////////////////
	
	// another rhs
	std::vector<double> c(row);
	c[0] = b[0]*2;
	c[1] = b[1]*2;
	c[2] = b[2]*2; 
	c[3] = b[3]*2;  
	c[4] = b[4]*2;  
	c[5] = b[5]*2;
	c[6] = b[6]*2;
	c[7] = b[7]*2;

	std::vector<std::vector<double>> B;
	B.push_back(b);
	B.push_back(c);
	std::vector<std::vector<double>> X;
	success = TaucsSolver::solve_linear_least_square(M, B, X);
	if (success) {
		std::cout << "output for linear least square test (an array of rhs vectors): " << std::endl;
		for (unsigned int i=0; i<X.size(); ++i) {
			for (unsigned int j=0; j<col; ++j) {
				std::cout << X[i][j] << "  " ;
			}
			std::cout << std::endl;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	return success;
}



int main(int argc, char* argv[])
{
	//////////////////////////////////////////////////////////////////////////
	bool success = test_symmetry();
	if (success)
		std::cout << "symmetry test succeeded" << std::endl;
	else
		std::cout << "symmetry test failed" << std::endl;

	std::cout << std::endl << std::endl << std::endl;

	//////////////////////////////////////////////////////////////////////////

	success = test_non_symmetry();
	if (success)
		std::cout << "non-symmetry test succeeded" << std::endl;
	else
		std::cout << "non-symmetry test failed" << std::endl;

	std::cout << std::endl << std::endl << std::endl;

	//////////////////////////////////////////////////////////////////////////

	success = test_linear_least_square();
	if (success)
		std::cout << "linear least square test succeeded" << std::endl;
	else
		std::cout << "linear least square test failed" << std::endl;

	std::cout << std::endl << std::endl << std::endl;


	return 0;
}

