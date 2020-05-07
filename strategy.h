#ifndef STRATEGY_H
#define STRATEGY_H
#include "matrix.h"

vector<xpair> strgy1(vector<ROW> &m);
vector<xpair> strgy2(vector<ROW> &m);
vector<xpair> strgy3(vector<ROW> &m);
int get_ones(vector<ROW> m);
void get_trans_matrix(vector<ROW> &trans_m, vector<ROW> m);


// int select_oper(vector<ROW> m, int &idx_src, int &idx_dst);
int select_oper(vector<ROW> m, vector<xpair> &max_seq, int no_reduced, int opr_type);


void build_table(vector<ROW> m, int tab[SIZE]);
vector<xpair> update_seq_str(vector<xpair> seq, int tab[SIZE]);

#endif
