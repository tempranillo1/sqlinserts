#include <Rcpp.h>
#include <string>
using namespace Rcpp;

void removeLastTwoChars(std::string* str) {

  *str = (*str).substr(0, (*str).size() - 2);
}

// [[Rcpp::export]]
CharacterVector makeInserts(CharacterMatrix df,
                            CharacterVector dfName,
                            CharacterVector colNames) {

  std::string sqlinsert = "INSERT INTO " + as<std::string>(dfName) + "\n(";

  for(int i = 0; i < colNames.length(); i++) {

    sqlinsert += as<std::string>(colNames(i)) + ", ";
  }
  removeLastTwoChars(&sqlinsert);
  sqlinsert += ")\n";

  sqlinsert += "VALUES\n";
  // rows
  for(int i = 0; i < df.ncol(); i++){
    // cols
    sqlinsert += "(";
    for(int j = 0; j <  df.nrow(); j++){
       // (j, i) - df has been pivoted
       sqlinsert += as<std::string>(as<CharacterVector>(df(j, i))) + ", ";
    }
    removeLastTwoChars(&sqlinsert);
    sqlinsert += ")\n";
  }
  removeLastTwoChars(&sqlinsert);
  sqlinsert += ")\n";

  return(sqlinsert);
}


/*** R
make_inserts(iris) %>% cat()
*/
