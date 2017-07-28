#include <Rcpp.h>
#include "sscapi.h"
using namespace Rcpp;


//  --with-keep.source
// This is a simple example of exporting a C++ function to R. You can
// source this function into an R session using the Rcpp::sourceCpp
// function (or via the Source button on the editor toolbar). Learn
// more about Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//   http://gallery.rcpp.org/
//

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

//'@export
// [[Rcpp::export]]
int R_ssc_module_create(std::string x) {
  ssc_module_t module = ssc_module_create(x);
  if ( module == NULL )
  {
      Rcout << "error: could not create module " << x;
      ssc_data_free(
  }
}
