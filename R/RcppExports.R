# This file was generated by Rcpp::compileAttributes
# Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

makeInserts <- function(df, dfName, colNames, colTypes) {
    .Call('sqlinserts_makeInserts', PACKAGE = 'sqlinserts',
          df, dfName, colNames, colTypes)
}

