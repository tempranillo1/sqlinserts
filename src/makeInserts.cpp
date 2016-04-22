#include <Rcpp.h>
#include <string>
using namespace Rcpp;


// [[Rcpp::export]]
CharacterVector makeInserts(CharacterMatrix df,
                            CharacterVector dfName,
                            CharacterVector colNames) {

  std::string output = "INSERT INTO " + as<std::string>(dfName) + "\n(";

  for(int i = 0; i < colNames.length(); i++) {

    output += as<std::string>(colNames(i)) + ", ";
  }
  //remove last two chars ", "
  output = output.substr(0, output.size() - 2) + ")\n";

  output += "VALUES\n";
  // rows
  for(int i = 0; i < df.ncol(); i++){

    // cols
    output += "(";
    for(int j = 0; j <  df.nrow(); j++){
       // (j, i) - df has been pivoted
       output += as<std::string>(as<CharacterVector>(df(j, i))) + ", ";
    }
    //remove last two chars ", "
    output = output.substr(0, output.size() - 2) + ")\n";
  }
  //remove last two chars ", "
  output = output.substr(0, output.size() - 2) + ")\n";

  return(output);
}


/*** R
make_inserts(iris) %>% cat()
*/
