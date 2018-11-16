/***********************************************************************************
 * Author:                 Max Huang
 * 
 * Description:            A program that solves (and shows the stops for) linear
 *                         Diophantine equations (ax + by = n) where:
 *                           i) a, b, n are integers
 *                          ii) 0 < a, b, n < 1000
 *                         iii) a > b
 *
 * Known bugs:             None
 * 
 * History (YYYY/MM/DD):   2018/11/09:
 *                          - Initial creation
 *                         2018/11/16
 *                          - Fixed error with simplifiable equations
 ***********************************************************************************/

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

struct GCDLog {

    // FORMAT: a = b(c) + d
    // FORMAT: d = a - b(c)
    int a, b, c, d;
};

GCDLog make_gcdLog(int a, int b, int c, int d) {

    GCDLog l;
    l.a = a; l.b = b; l.c = c; l.d = d;
    return l;
}

int gcd(int a, int b) {

    if (a % b == 0) {
        return b;
    }

    return gcd(b, a % b);
}

void createLog(vector <GCDLog> &gcdLog, int a, int b) {

    // push back log for euclidean algorithm, print log item
    gcdLog.push_back(make_gcdLog(a, a / b, b, a % b));
    printf("%d = %d - %d(%d)\n", a % b, a, a / b, b);

    if (a % b == 0 || a % b == 1) {
        return;
    }

    createLog(gcdLog, b, a % b);
}

void solveDiophantine(vector <GCDLog> gcdLog, int n) {

    // set initial answer values based on the latest gcdLog
    // FORMAT: 1 = a(b) + c(d)
    int a = 1;
    int b = gcdLog[gcdLog.size() - 1].a;
    int c = gcdLog[gcdLog.size() - 1].b;
    int d = gcdLog[gcdLog.size() - 1].c;

    // loop through all elements of the log, start = second lastest, end = earliest
    // we start with the second latest log beause we preloaded a, b, c, d with the latest log
    for (int i = gcdLog.size() - 2; i >= 0; i--) {

        GCDLog prev = gcdLog[i];

        // print current step
        printf("1 = %d(%d) - %d(%d)\n", a, b, c, d);

        if (prev.d == b) {
            
            // replace left side with previous log
            // calculate new a, b, c, d values
            printf("1 = %d[%d - %d(%d)] - %d(%d)\n", a, prev.a, prev.b, prev.c, c, d);
            a = a;
            b = prev.a;
            c = c + a * prev.b;
            d = d;
        }
        else {
            
            // replace right side with previous log
            // calculate new a, b, c, d values
            printf("1 = %d(%d) - %d[%d - %d(%d)]\n", a, b, c, prev.a, prev.b, prev.c);
            a = a + c * prev.b;
            b = b;
            c = c;
            d = prev.a;
        }
    }

    // print last step
    printf("1 = %d(%d) - %d(%d)\n", a, b, c, d);

    // print answer
    cout << endl;
    cout << "Answer" << endl;
    if (n != 1) {
        // if n != 1, there is an extra step
        printf("%d(%d)(%d) - %d(%d)(%d) = %d\n", b, a, n, d, c, n, n);
        printf("%d(%d) - %d(%d) = %d\n", b, a * n, d, c * n, n);
    }
    else {
        printf("%d(%d) - %d(%d) = 1\n", a, b, c, d);
    }
}

int main() {

    vector <GCDLog> gcdLog;
    int a, b, n;

    cout << "--------------------------------------------------------------------" << endl;
    cout << "| LINEAR DIOPHANTINE EQUATION SOLVER                               |" << endl;
    cout << "| Solve for ax + by = n where:                                     |" << endl;
    cout << "|   i) a, b, n are integers                                        |" << endl;
    cout << "|  ii) 0 < a, b, n < 1000                                          |" << endl;
    cout << "| iii) a > b                                                       |" << endl;
    cout << "--------------------------------------------------------------------" << endl;

    cout << endl;
    cout << "Input a value for a:\n => ";

    // input a, return error on invalid input
    if (!(cin >> a) || a <= 0 || a >= 1000) {
        cout << "Invalid input" << endl;
        return 0;
    }

    cout << "Input a value for b:\n => ";

    // input b, return error on invalid input
    if (!(cin >> b) || b <= 0 || b >= a) {
        cout << "Invalid input" << endl;
        return 0;
    }

    cout << "Input a value for n:\n => ";

    // input n, return error on invalid input
    if (!(cin >> n) || n <= 0 || n >= 1000) {
        cout << "Invalid input" << endl;
        return 0;
    }

    cout << "--------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "SOLUTION FOR " << a << "x + " << b << "y = " << n << endl;

    if (gcd(a, b) != gcd(gcd(a, b), n)) {

        cout << "No solution" << endl;

        // wait after program finishes
        getchar();
        getchar();
        return 0;
    }

    // use Euclidean algorithm to determine whether or not the equation can be solved
    // log the steps taken
    // input max(a, b) as the first coefficient, input min(a, b) as the second coefficient
    cout << endl;
    cout << "Using Euclidean algorithm" << endl;
    createLog(gcdLog, a, b);

    // solve Diophantine equation
    cout << endl;
    cout << "Reversing Euclidean algorithm" << endl;
    solveDiophantine(gcdLog, n);

    // wait after program finishes
    getchar();
    getchar();

    return 0;
}