#include <exception>

using namespace std;

struct invalid_operator_exception : exception {
	const char* what() const throw () { return "invalid operator error!"; }
};
struct invalid_constant_exception : exception {
	const char* what() const throw () { return "invalid constant error!"; }
};
struct undefined_symbol_exception : exception {
	const char* what() const throw () { return "undefined symbol error!"; }
};
struct duplicated_symbol_exception : exception {
	const char* what() const throw () { return "duplicated symbol error!"; }
};