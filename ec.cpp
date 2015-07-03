/**
   Extraction of scores from easychar review list.
   
   ./a.out review.txt > out.csv

   Open out.csv with Excel

 */
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

int tokenize ( const std::string& str, const std::string& delimiter, std::vector<std::string>& result )
{
        std::string::size_type end;
        std::string line = str;

        for ( ; ; ) {
                end = line.find_first_of ( delimiter );

                if ( line.substr ( 0, end ).length() > 0 ) {
                        result.push_back ( line.substr ( 0, end ) );
                }

                if ( std::string::npos == end ) {
                        break;
                }

                line = line.substr ( end + 1 );
        }

        return result.size();
}
int main ( int argc, char** argv )
{
	// Description of the field that you want to extract.
        std::string checkString ( "WOULD YOU RECOMMEND THIS PAPER TO THE BEST PAPER AWARD" );

        if ( argc < 2 ) {
                std::cerr << "usage: ec file.txt > out.csv" << std::endl;
                return -1;
        }

        std::ifstream fin ( argv[1] );

        if ( !fin ) {
                std::cerr << argv[1] << " does not exist." << std::endl;
                return -2;
        }

        while ( fin ) {
                std::string buffer;
                std::getline ( fin, buffer );
		//paper ID begins with "***********************" 
                if ( buffer.find ( "***********************" ) != std::string::npos ) {
                        std::vector<std::string> result;
                        tokenize ( buffer, "* ", result );
                        std::cout << std::endl;
                        std::cout << result.at ( 1 );

                } else if ( buffer.find ( checkString ) != std::string::npos ) {
                        std::vector<std::string> result;
                        tokenize ( buffer, ":(", result );
                        std::cout <<","<< result.at ( 1 );
                }
        }

        std::cout << std::endl;
        return 0;
}
