#include <Eigen/Dense>
void multiplicacion_eigen(const Eigen::MatrixXd & A, const Eigen::MatrixXd & B, const Eigen::MatrixXd & C)
{
  C=2.0*A*B;
}
