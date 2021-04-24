#include <armadillo>
void multplicacion_armadillo(arma::Mat<double> & A,arma::Mat<double>& B,arma::Mat<double> & C)
{
  C=2.0*A*B;
  
}
