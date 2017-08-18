#' @export
get_common_types <- function(common_types_file = system.file("classes.yml",
                                                             package = "RSSC")) {
  yaml::yaml.load_file(common_types_file)
}


findpkg <- function() {
  if (.Platform$OS.type == "windows") {
    Sys.setenv("PATH" = paste(Sys.getenv("PATH"),
                              "C:\\SAM\\sam-sdk-2017-1-17-r4\\win64", sep = ';'))
  }
}

.onLoad <- function(libname, pkgname) {
  # common types
  if ("RSSC_common_types" %in% search()) detach(RSSC_common_types)
  common_types <- get_common_types()
  for (i in 1:length(common_types)) {
    for (j in 1:length(common_types[[i]])) {
      common_types[[i]][[j]]$default <- eval(parse(text = common_types[[i]][[j]]$default))
    }
  }

  RSSC_common_types <- list2env(common_types)
  attach(RSSC_common_types)
  rm(i, j)
}
