//Funciones de multiplicación
#include<armadillo>
#include <Eigen/Dense>
#include <vector>

void multiplicacion_directa(std::vector<double> & A,std::vector<double> & B,std::vector<double> & C, int N);
void multiplicacion_eigen(const Eigen::MatrixXd & A, const Eigen::MatrixXd & B, const Eigen::MatrixXd & C);
void multplicacion_armadillo(arma::Mat<double> & A,arma::Mat<double>& B,arma::Mat<double> & C);
void multiplicacion_blocking(const std::vector<double> a,const std::vector<double> b,std::vector<double> &c,int Nb);

