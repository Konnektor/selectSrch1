// Consider searchng N numbers stored in array A by first finding the smallest element of A and
// exchanging it with the element in A[0]. Then find the second smallest element, and exchange it
// with A[1]. Continue in this manner for the first N-1 elements of A.
//

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;


int main()
{
	vector<int> A = { 5,8,10,12,4,2,6,1,7,0,11,15,9,3,13,14 };
	int N = A.size(), minVal, minIdx;

	// Output initial sequence
	cout << "Unsorted vector:\n";
	for (int k = 0; k < N; k++) cout << setw(2) << A[k] << " "; 
	cout << "\n\nSorted vector:\n";

	// The program scans array for a minimum value. Each iteration makes array shorter.
	// After minimum has been found, this minimum and the last element before sub-array beginning are exchanged.
	// Perform this operation N-1 times, which will yield full sorting. No need to find minimum N-th time, since there is only one element to find minimum in.
	for (int k = 0; k < N - 1; k++) {		   // Loop to process each element of the given vector																		c1*(n-1)
		minVal = A[k];   					   // Set initial minimum value to the value of k-th vector element being processed											c2*(n-2)
		minIdx = k; 						   // Set minimum value index to the value of k-th vector element index														c3*(n-2)
		
		// Minimum value searching
		// Do not include the currently processed vector element A[k] in minimum search, as it is already included
		// by assigning its value to minVal variable. Thus, begin comparing from element A[k+1] with currently assigned minimum value A[k].
		for (int n = k + 1; n < N; n++) {      // Loop for minimum value searching																						c4*sum(tj)
			if (A[n] < minVal) {			   //																														c5*sum(tj-1)
				minVal = A[n];				   //																														c6*sum(tj-1)
				minIdx = n;					   //																														c7*sum(tj-1)
			}
		}
		// Swap currently processed vector element with minimum value (which is the same, if no smaller value has been found)
		A[minIdx] = A[k];						// Copy current vector element first, since new minimum (and its index) are saved to temporary variable					c8*(n-2)
		A[k] = minVal;				    		// It is safe now to update the currently processed vector element by minimum value found								c9*(n-2)
	}
	// Output sorted sequence
	for (int k = 0; k < N; k++)
		cout << setw(2) << A[k] << " ";
	cout << "\n";

    return 0;
}

// 1. What loop invariant does this algorithm maintain?
// Here loop invariant is sub-array of already sorted numbers. It initially is already sorted (empty array), then during sorting algorithm
// the sub-array A[0] to A[k] remains sorted and the minimum is searched in A[k+1] to A[N-1].
// Finally, at the end of the algorithm execution, the full array is sorted.

// 2. Why does it need to run only for the first N-1 elements rather than for all N elements?
// The last search of minimum is trivial and at the end, the final element of vector, i.e. A[N-1] contains maximum value of entire vector.

// 3. Give the best-case and the worst-case running times of selection sort in O-notation.
// Determine general computational complexity by adding up together computation time multiplied by computational costs:
//		c1*(n-1) + (c2 + c3 + c8 + c9)*(n - 2) + c4*sum(tn) + (c5 + c6 + c7)*sum(tn-1)
//		Thus, sum(tj)   = n*(n+1)/2 - 1			(note, that summation begins from j = 2)
//			  sum(tj-1) = (n-1)*n/2 - 1
//
// Then, after simplification:
//		(c1 + c2 + c3 + c8 + c9)*(n - 1) - (c2 + c3 + c8 + c9) + c4*n*(n + 1)/2 - c4 + (c5 + c6 + c7)*(n - 1)*n/2 - (c5 + c6 + c7)
//		(c4 + c5 + c6 + c7)/2*n^2 + (c1 + c2 + c3 + c4/2 - c5/2 - c6/2 - c7/2 + c8 + c9)*(n - 1) - (c2 + c3 - c4 - c5 - c6 - c7 + c8 + c9)		==> an^2 + bn + c (quadratic function)
//
// Regardless of initial order of the elements, the minimum search is always performed and it takes the same time, independently on the order of vector elements.
// Thus, the selection sorting algorithm yields O(n^2) in all cases (worst, best, average).