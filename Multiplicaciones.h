//Funciones de multiplicación
#ifndef _MULTIPLICACIONES_H_
#define _MULTIPLICACIONES_H_
#include<armadillo>
#include <Eigen/Dense>
#include <vector>

void multiplicacion_directa(const std::vector<double> & A,const std::vector<double> & B,std::vector<double> & C);
void multiplicacion_eigen(const Eigen::MatrixXd & A, const Eigen::MatrixXd & B, Eigen::MatrixXd & C);
void multplicacion_armadillo(arma::Mat<double> & A,arma::Mat<double>& B,arma::Mat<double> & C);
void multiplicacion_blocking(const std::vector<double> a,const std::vector<double> b,std::vector<double> &c,int Nb);
#endif
