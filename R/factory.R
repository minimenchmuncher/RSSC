#' @export
instantiate_class <- function(object, cls) {
  common_type <- get(cls, 'RSSC_common_types')
  # ensure that the object contains elements only in the prototype class
  if (any(!(names(object) %in% names(common_type)))) {
    wrong_names <- names(object)[!(names(object) %in% names(common_type))]
    stop(sprintf("attributes of input object are not contained in prototype:\n%s",
                 paste(wrong_names, collapse = ",")))
  }
  # need just elements that are required (require == TRUE)
  common_type_notnull <- common_type[which(unlist(lapply(1:length(common_type),
                                function(i) !is.null(common_type[[i]]$require))))]
  common_type_reqd <- common_type_notnull[which(unlist(lapply(1:length(common_type_notnull),
                                function(i) common_type_notnull[[i]]$require == TRUE)))]
  # ensure that required elements are in the inputs
  if (any(!(names(common_type_reqd) %in% names(object)))) {
  missing_names <- names(common_type_reqd)[!(names(common_type_reqd) %in% names(object))]
    stop(sprintf("required attributes are not contained in object: \n%s",
                 paste(missing_names, collapse = ",")))
  }
  Xc <- modifyList(lapply(common_type_reqd, `[[`, 'default'), object)

  Xc_attrs <- common_type[names(Xc)]
  Xc_classes <- lapply(Xc_attrs, `[[`, 'type')

  invisible(lapply(1:length(Xc),
                   function(i) if (!(inherits(Xc[[i]], Xc_classes[[i]]))) {
                     stop(sprintf("attribute %s is class %s, should be %s", names(Xc[i]), class(Xc[[i]]), Xc_classes[[i]]))
                   }))
  class(Xc) <- cls
  Xc
}
