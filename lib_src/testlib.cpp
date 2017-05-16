
#include "testlib.h"

namespace testlib {

int Fibonacci(int n)
{
	int prev = 1;
	int curr = 1;
	int next = 1;
	for( int i = 3; i <= n; ++i )
	{
		next = prev + curr;
		prev = curr;
		curr = next;
	}
	return next;
}

} // namespace