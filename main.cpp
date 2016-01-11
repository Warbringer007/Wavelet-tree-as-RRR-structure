#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdint.h>
#include <sys/time.h>
#include "rrr_struct.h"
#include "wavelet_tree.h"

using namespace std;

int main(int argc , char *argv[]) {
    struct timeval start_time, end_time;
    long us;
    uint32_t result = 0;
    //Load arguments
    string fileName = argv[1];
    char rankSelect = argv[2][0];
    char letter = argv[3][0];
    int number = atoi(argv[4]);
    gettimeofday(&start_time,NULL);
    //Create Wavelet tree
    Wavelet_tree wt=Wavelet_tree(fileName);
    gettimeofday(&end_time,NULL);
    us = (long)((1000000 * end_time.tv_sec + end_time.tv_usec) -
                    (1000000 * start_time.tv_sec + start_time.tv_usec));
    cout << us <<" mikrosekundi priprema struktura" << endl;
    if ( rankSelect == 'R') {
        gettimeofday(&start_time,NULL);
        result = wt.Rank(letter,number);
        gettimeofday(&end_time,NULL);
        cout << "Rank: " << letter << "," << number << " = " << result << endl;
    }
    else if ( rankSelect == 'S') {
        gettimeofday(&start_time,NULL);
        result = wt.Select(letter,number);
        gettimeofday(&end_time,NULL);
        cout << "Select: " << letter << "," << number << " = " << result << endl;
    }
    us = (long)((1000000 * end_time.tv_sec + end_time.tv_usec) -
                    (1000000 * start_time.tv_sec + start_time.tv_usec));
    cout << us << " mikrosekundi obavljanje operacije" <<endl;
    return 0;
}
