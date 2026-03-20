#include <Eigen/Core>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <armadillo>

template <class Matrix>
void read_binary(const std::string& filename, Matrix& matrix)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in.is_open())
  {
    typename Matrix::Index rows = 0, cols = 0;
    in.read(reinterpret_cast<char*>(&rows), sizeof(typename Matrix::Index));
    in.read(reinterpret_cast<char*>(&cols), sizeof(typename Matrix::Index));
    matrix.resize(rows, cols);
    in.read(reinterpret_cast<char*>(matrix.data()), rows * cols * static_cast<typename Matrix::Index>(sizeof(typename Matrix::Scalar)));
    in.close();
  }
  else
  {
    std::cout << "Can not open binary matrix file: " << filename << std::endl;
  }
}

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " <matrix_bin_path>" << std::endl;
    return 1;
  }

  const std::string input_path = argv[1];
  Eigen::MatrixXd h_x_;
  read_binary(input_path, h_x_);

  int l1 = -1, l2 = -1, l3 = -1;
  Eigen::internal::queryCacheSizes(l1, l2, l3);
  std::cout << "\t L1d cache: " << l1 / 1024 << " KiB\n"; // Eigen::l1CacheSize()
  std::cout << "\t L2  cache: " << l2 / 1024 << " KiB\n"; // Eigen::l2CacheSize()
  std::cout << "\t L3  cache: " << l3 / 1024 << " KiB\n"; // Eigen::l3CacheSize()

  std::cout << "Eigen: \n";
  Eigen::Matrix<double, 12, 12> HTH = h_x_.transpose() * h_x_;
  double value = HTH(0, 5);
  std::cout << std::fixed << "H[0, 5] = " << std::setprecision(18) << value << std::endl;

  std::cout << "Armadillo: \n";
  arma::mat h_x_armadillo = arma::mat(h_x_.data(), h_x_.rows(), h_x_.cols());
  arma::mat HTH_armadillo = h_x_armadillo.t() * h_x_armadillo;
  double value_armadillo = HTH_armadillo(0, 5);
  std::cout << std::fixed << "H[0, 5] (Armadillo) = " << std::setprecision(18) << value_armadillo << std::endl;
}
