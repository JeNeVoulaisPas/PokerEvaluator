//
// Created by paulo on 06/01/2025.
//

#ifndef MERSENNE_TWISTER_H
#define MERSENNE_TWISTER_H

#include <vector>

void init_genrand(unsigned long s);


void init_by_array(unsigned long init_key[], int key_length);


unsigned long genrand_int32(void);


long genrand_int31(void);


double genrand_real1(void);


double genrand_real2(void);


double genrand_real3(void);


double genrand_res53(void);

void random_shuffle(std::vector<int>&);

#endif //MERSENNE_TWISTER_H
