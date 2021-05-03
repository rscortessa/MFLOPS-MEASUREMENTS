#ifndef _TRANSPUESTAS_H_
#define _TRANSPUESTAS_H_
#include <Eigen/Dense>
#include <armadillo>
#include <vector>
void transpuesta_directa(std::vector<double> & A);
void transpuesta_eigen(Eigen::MatrixXd & A);
void transpuesta_armadillo(arma::Mat<double> & A);
void transpuesta_blocking(std::vector<double> & A, std::vector<double>&ABT, int P);
#endif
