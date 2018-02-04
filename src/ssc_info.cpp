#include <Rcpp.h>
#include "sscapi.h"
using namespace Rcpp;


//'@export
// [[Rcpp::export]]
int R_ssc_version() {
  int version = ssc_version();
  return version;
}


// apparently, this works fine keeping as a string - R must be able to do that
// conversion itself.
//'@export
// [[Rcpp::export]]
std::string R_ssc_build_info() {
  const char *build = ssc_build_info();
  std::string build_s(build);
  //String build_S = Rcpp::as<Rcpp::String>(build_s);
  return build_s;
}
