// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// pvwattstest
NumericVector pvwattstest(CharacterVector filename);
RcppExport SEXP _RSSC_pvwattstest(SEXP filenameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type filename(filenameSEXP);
    rcpp_result_gen = Rcpp::wrap(pvwattstest(filename));
    return rcpp_result_gen;
END_RCPP
}
// R_ssc_version
int R_ssc_version();
RcppExport SEXP _RSSC_R_ssc_version() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(R_ssc_version());
    return rcpp_result_gen;
END_RCPP
}
// R_ssc_build_info
std::string R_ssc_build_info();
RcppExport SEXP _RSSC_R_ssc_build_info() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(R_ssc_build_info());
    return rcpp_result_gen;
END_RCPP
}
// dataiotest_num
NumericVector dataiotest_num(NumericVector x);
RcppExport SEXP _RSSC_dataiotest_num(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(dataiotest_num(x));
    return rcpp_result_gen;
END_RCPP
}
// dataiotest_char
CharacterVector dataiotest_char(CharacterVector x);
RcppExport SEXP _RSSC_dataiotest_char(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(dataiotest_char(x));
    return rcpp_result_gen;
END_RCPP
}
// dataiotest_log
LogicalVector dataiotest_log(LogicalVector x);
RcppExport SEXP _RSSC_dataiotest_log(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< LogicalVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(dataiotest_log(x));
    return rcpp_result_gen;
END_RCPP
}
// dataiotest_nv
NumericVector dataiotest_nv(NumericVector x);
RcppExport SEXP _RSSC_dataiotest_nv(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(dataiotest_nv(x));
    return rcpp_result_gen;
END_RCPP
}
// dataiotest_nummat
NumericMatrix dataiotest_nummat(NumericMatrix x);
RcppExport SEXP _RSSC_dataiotest_nummat(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(dataiotest_nummat(x));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_RSSC_pvwattstest", (DL_FUNC) &_RSSC_pvwattstest, 1},
    {"_RSSC_R_ssc_version", (DL_FUNC) &_RSSC_R_ssc_version, 0},
    {"_RSSC_R_ssc_build_info", (DL_FUNC) &_RSSC_R_ssc_build_info, 0},
    {"_RSSC_dataiotest_num", (DL_FUNC) &_RSSC_dataiotest_num, 1},
    {"_RSSC_dataiotest_char", (DL_FUNC) &_RSSC_dataiotest_char, 1},
    {"_RSSC_dataiotest_log", (DL_FUNC) &_RSSC_dataiotest_log, 1},
    {"_RSSC_dataiotest_nv", (DL_FUNC) &_RSSC_dataiotest_nv, 1},
    {"_RSSC_dataiotest_nummat", (DL_FUNC) &_RSSC_dataiotest_nummat, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_RSSC(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
