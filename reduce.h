#ifndef REDUCE_H
#define REDUCE_H

#include "strategy.h"
#include "matrix.h"

vector<xpair> reduce(vector<ROW> m);

bool reduce0(vector<xpair> &seq, int** table);
int reduce_step(vector<xpair> &seq);
int** get_table(vector<xpair> seq, int ** table, int osize, int nsize);

int get_ones(vector<ROW> m);


vector<ROW> get_reduced_matrix(vector<xpair> seq, vector<ROW> m);




#endif