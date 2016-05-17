#' Make SQL inserts from data.frame
#'
#' Function produces sql inserts from given dataset
#'
#' @param data \code{data.frame} used to generate SQL inserts
#' @param table_name target table.
#' @export
#' @examples
#' make_inserts(mtcars)
make_inserts <- function(data, table_name = NULL) {

  if(is.null(table_name)) {
    table_name = deparse(substitute(data))
  } else if(length(table_name) != 1L) {
    stop("Wrong vector size of table_name.")
  }

  column_names <- names(data)
  column_types <- sapply(data, function(x) class(x)[1L])

  # pivot data
  df_tm <- matrix(as.character(t(data)),
                  nrow = ncol(data),
                  ncol = nrow(data))

  .Call('sqlinserts_makeInserts', PACKAGE = 'sqlinserts',
        df = df_tm,
        dfName = table_name,
        colNames = column_names,
        colTypes = column_types)
}

