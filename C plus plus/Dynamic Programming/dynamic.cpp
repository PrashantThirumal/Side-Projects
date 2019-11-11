/*
* Written by Prashant Thirumal
* I wanted to check the time difference when using dynamic programming
*/

#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

// Initialize our clock
clock_t t, t1;
double time_taken, time_taken1;

// Computing the nth term of the Fibonacci sequence using recursion
int recursion(int n) {
  if (n <= 1) {
    return n;
  }
  int nth_value = recursion(n-1) + recursion(n-2);
  return nth_value;
}

// Computing the nth term of the Fibonacci sequence using dynamic programming
int dynam(int n){
  // Declare vector to store the Fibonnaci terms
  vector<int> dynamic(n+2);

  // 0th and 1st number of the series are 0 and 1
  dynamic[0] = 0;
  dynamic[1] = 1;

  for (int i = 2; i <= n; i++)
  {
      // Add the previous 2 numbers in the series and store it
      dynamic[i] = dynamic[i-1] + dynamic[i-2];
  }
  return dynamic[n];
}

int main() {
  // Set n = 40 if not recursion takes too long or dumps the core on me
  int n = 40;
  t = clock();
  int nth_term = dynam(n);
  t = clock() - t;
  time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
  
  cout << "Dynamic programming computed: " << nth_term << endl;
  cout << "Time taken for nth term via dynamic programming (in seconds): " << time_taken << endl;

  t1 = clock();
  int xth_term = recursion(n);
  t1 = clock() - t1;
  double time_taken1 = ((double)t1)/CLOCKS_PER_SEC; // in seconds

  cout << "Recursion computed: " << xth_term << endl;
  cout << "Time taken for nth term via recurion (in seconds): " << time_taken1 << endl;

  return 0;
}
