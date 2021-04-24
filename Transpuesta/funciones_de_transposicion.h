//Funciones de transposición
#include <Eigen/Dense>
#include <armadillo>
#include <vector>
void transpuesta_directa(std::vector<double> & A, int N);
void transpuesta_eigen(const Eigen::MatrixXd & A);
void transpuesta_armadillo(arma::Mat<double> & A);
double TRBlock(std::vector<double> & A, std::vector<double>&ABT, const int N, int P);
