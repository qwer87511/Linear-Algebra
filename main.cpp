#include "Matrix.h"
#include "Fraction.h"
#include <iostream>
#include <string>
using namespace std;

void run()
{
    Matrix m1(3, 3);
    cin >> m1;
    cout << "m1:" << endl << m1 << endl;
    Matrix m2(3, 3);
    cin >> m1;
    cout << "m2:" << endl << m1 << endl;
    /*Matrix m3(3, 3);
    cin >> m1;
    cout << "m3:" << endl << m1 << endl;
    Matrix m4(3, 4);
    cin >> m1;
    cout << "m4:" << endl << m1 << endl;*/
    cout << "multiple:" << endl;
    cout << m1* m2 << endl;
}

int main()
{
    try {
        run();
    }
    catch (Fraction::ERROR_CODE errorCode)
    {
        switch (errorCode)
        {
            case Fraction::INIT_INT_ERROR:
                cout << "Initilize(int) fail.";
                break;

            case Fraction::INIT_STR_ERROR:
                cout << "Initilize(str) fail.";
                break;

            case Fraction::INVERSE_ERROR:
                cout << "Inverse error: divided by zero";
                break;
        }
    }

    system("pause");
    return 0;
}
/*
1 0 0
0 1 0
0 -1 1
1 0 0
0 1 0
1 0 1
1 0 0
-2 1 0
0 0 1
2 4 -2 2
4 9 -3 8
-2 -3 7 10
*/