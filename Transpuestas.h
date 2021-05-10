#ifndef _TRANSPUESTAS_H_
#define _TRANSPUESTAS_H_
#include <Eigen/Dense>
#include <armadillo>
#include <vector>
void transpuesta_directa(const std::vector<double> & A,  std::vector<double> & AT);
void transpuesta_eigen(const Eigen::MatrixXd & A, Eigen::MatrixXd & AT);
void transpuesta_armadillo(const arma::Mat<double> & A,  arma::Mat<double> & AT);
void transpuesta_blocking(const std::vector<double> & A, std::vector<double>&AT, int P);
#endif
