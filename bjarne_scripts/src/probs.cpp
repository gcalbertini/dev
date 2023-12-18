#include <iostream>
#include <iomanip>	 // for std::quoted
#include <string>	 // for std::string
#include <algorithm> // std::max
#include <climits>	 // for ULLONG_MAX

using std::cout, std::endl, std::cin, std::quoted, std::max;


//NOTE the next step to this is to introduce metaprogramming to offload factorial work
// to the compiler with templates with features intoduced in C++14 and beyond


bool legal_int(char *str)
{
	// while not at end of buffer (null terminator); or may use "" but not standard way
	while (*str != '\0')
	{
		if (!isdigit(*str))
		{
			return false;
		}
		str++;
	}
	return true;
}

unsigned long long factorialPC(const unsigned long long N, const unsigned long long K, int mode)
{
	unsigned long long result = 1ULL;
	if ((N < K) || (N < 0) || (K < 0))
		std::cerr << "Error! Factorial of a negative number doesn't exist.";

	// 0! = 1! = 1
	unsigned long long numerator = std::max(1ULL, N);
	unsigned long long denominator = std::max(1ULL, N - K);

	if (mode == 0)
	{
		// permutation
		if (K == 0ULL)
			return 1ULL;

		for (unsigned long long j = denominator; j <= numerator; ++j)
		{
			// Check for overflow
			if (result > ULLONG_MAX / j)
			{
				std::cerr << "Error! Overflow detected in permutation computation." << std::endl;
				return 0ULL;
			}
			result *= j;
		}
		return result;
	}
	else
	{
		// combination; count up from closest two integers
		// to reduce computation time then divide by smaller divisor
		// NOTE C(N,N) = C(N,0) = 1
		if ((N == K) || (K == 0ULL))
			return 1ULL;

		unsigned long long largerDivisor = std::max(denominator, K);
		unsigned long long smallerDivisor = std::min(denominator, K);

		for (unsigned long long j = numerator; j > largerDivisor; --j)
		{
			if (result > ULLONG_MAX / j)
			{
				std::cerr << "Error! Overflow detected in combination computation." << std::endl;
				return 0ULL;
			}
			result *= j;
		}

		for (unsigned long long i = smallerDivisor; i > 0; --i)
		{
			// Check for overflow
			if (result > ULLONG_MAX / i)
			{
				std::cerr << "Error! Overflow detected in combination computation." << std::endl;
				return 0ULL;
			}
			result /= i;
		}
		return result;
	}
}

int main(int argc, char **argv)
{
	cout << "argc == " << argc << endl;

	if (argc != 4)
	{
		// Handle the case when no command-line argument is provided
		std::cerr << "Incorrect usage: " << argv[0] << " <mode> <N> choose <K>" << std::endl;
		return 1;
	}

	for (int ndx = 0; ndx < argc; ++ndx)
	{
		std::cout << "argv[" << ndx << "] == " << std::quoted(argv[ndx]) << '\n';
	}

	int mode = -1;
	char *n, *k;

	try
	{
		bool isInt1 = legal_int(argv[2]);
		bool isInt2 = legal_int(argv[3]);

		if (!(isInt1 && isInt2))
		{
			throw std::out_of_range("At least one of the integers is not valid!");
		}

		// wont check for limits rn
		unsigned long long N = strtoull(argv[2], &n, 10);
		unsigned long long K = strtoull(argv[3], &k, 10);

		mode = (std::string(argv[1]) == "P") ? 0 : ((std::string(argv[1]) == "C") ? 1 : throw std::invalid_argument("Invalid mode"));

		if (mode == 0)
		{
			unsigned long long value = factorialPC(N, K, 0);
			cout << "Permutation: " << value << endl;
		}
		else if (mode == 1)
		{
			unsigned long long value = factorialPC(N, K, 1);
			cout << "Combination: " << value << endl;
		}
	}
	catch (const std::invalid_argument &e)
	{
		std::cerr << "Error: " << e.what() << " (Argument must be 'P', 'C', or integers)" << std::endl;
		return 1;
	}
	catch (const std::out_of_range &e)
	{
		std::cerr << "Error: " << e.what() << " (Argument out of range)" << std::endl;
		return 1;
	}

	cout << "Used " << argv[1] << " mode for numbers " << argv[2] << " and " << argv[3] << endl;

	return 0;
}