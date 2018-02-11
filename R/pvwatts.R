#' PVWatts v.5
#'
#' @title PVWatts (Version 5)
#' @rdname pvwattsv5
#' @export pvwattsv5
pvwattsv5 <- function(x, ...) {
  UseMethod("pvwattsv5", x)
}

#' @rdname pvwattsv5
#' @export
pvwattsv5.pvwattsv5_obj <- function(x, ...) {
  class(x) <- "list"
  rcpp_pvwattsv5(x)
}

#' @rdname pvwattsv5
#' @export
pvwattsv5.list <- function(x, ...) {
  rcpp_pvwattsv5(x)
}

#' @rdname pvwattsv5
#' @export
pvwattsv5.character <- function(x, ...) {
  stop("not yet working")
}

#' @rdname pvwattsv5
#' @export
pvwattsv5.default <- function(x, ...) {
  stop("that input was not valid")
}
