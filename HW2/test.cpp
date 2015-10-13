#include "3a.h"

using namespace std;

int main()
{
		bigNumTwithMinus<> top("100000");
		bigNumTwithMinus<> bot("99800");
		bigNumTwithMinus<> res = (top-bot);
		cout << res.print() << endl;

	return 0;
}
