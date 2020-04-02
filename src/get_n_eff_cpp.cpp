#include <Rcpp.h>
using namespace Rcpp;

//' Compute the effective population size
//'
//' Computes \code{n_eff}, the effective population size experienced by an
//' individual.
//' @param z numeric vector, the trait values of all individuals in the
//' community.
//' @param comp_width numeric `>= 0`. Width of the competition kernel.
//' @details `n_eff` sums the competitive effects an individual receives from
//' every individual in the community, including the individual itself. It is
//' called effective population size because it is the size of the population
//' that is relevant for competition.
//' @name get_n_eff_cpp
//' @author Théo Pannetier
//' @export

// [[Rcpp::export]]
std::vector<double> get_n_eff_cpp(std::vector<double> z, double comp_width) {

  std::vector<double> n_eff;

  int i_max = z.size();
  int j_max = z.size();

  for(int i = 0; i < i_max; ++i) {
    double n_eff_i = 0;
    for(int j = 0; j < j_max; ++j) {
      n_eff_i += exp(- pow(z[i] - z[j], 2.0) / (2 * pow(comp_width, 2.0)));
    }
    n_eff.push_back(n_eff_i);
  }

  return n_eff;
}