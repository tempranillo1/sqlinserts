#include <Rcpp.h>
#include <string>
using namespace Rcpp;

void removeLastTwoChars(std::string* str) {

  *str = (*str).substr(0, (*str).size() - 2);
}

// [[Rcpp::export]]
CharacterVector makeInserts(CharacterMatrix df,
                            CharacterVector dfName,
                            CharacterVector colNames,
                            CharacterVector colTypes) {

  CharacterVector quoteMarks(colTypes.length());
  CharacterVector currentCell;
  std::string currentQuoteMark;
  std::string sqlinsert = "INSERT INTO " + as<std::string>(dfName) + "\n(";


  for(int i = 0; i < colTypes.length(); i++) {

    sqlinsert += as<std::string>(colNames(i)) + ", ";
    if(colTypes[i] == "numeric" ||
       colTypes[i] == "integer") {
      quoteMarks[i] = "";
    } else {
      quoteMarks[i] = "'";
    }

  }
  removeLastTwoChars(&sqlinsert);
  sqlinsert += ")\n";

  sqlinsert += "VALUES\n";

  //VALUES:

  // rows
  for(int i = 0; i < df.ncol(); i++){
    // cols
    sqlinsert += "(";
    for(int j = 0; j < df.nrow(); j++){

       // (j, i) - df has been pivoted
       currentCell = as<CharacterVector>(df(j, i));

       if(any(is_na(currentCell))) {
         sqlinsert += "NULL, ";
       } else {
         currentQuoteMark = as<std::string>(quoteMarks[j]);
         sqlinsert += currentQuoteMark + as<std::string>(currentCell) + currentQuoteMark + ", ";
       }

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
