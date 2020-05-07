
#include <memory.h>
#include <random>
#include <stdlib.h>
#include "strategy.h"

mt19937 rand_generator(time(NULL));

vector<xpair> strgy1(vector<ROW> &m)
{
	/* compatible with non-square matrix.*/
	vector<xpair> seq;
	int row_size = m.size();
	int col_size = m[0].size();

	int *mark = new int[row_size];
	memset(mark, 0, row_size * sizeof(int));
	xpair p;
	for (unsigned col = 1; col <= col_size; ++col) 
	{
		unsigned r = 0;
		while (((r < row_size) && (!m[r][col_size - col])) || (mark[r] == 1))
		{
			++r;
		}
		if (r >= row_size)
		{
			continue;
		}
		else
		{
			mark[r] = 1;
		}

		for (unsigned i = 0; i < row_size; ++i)
		{
			if (m[i][col_size - col] && (i != r)) 
			{
				m[i] ^= m[r];
				p.dst = i;
				p.src = r;
				p.flag = false;
				seq.push_back(p);
			}
		}
	}
	delete[] mark;
	return seq;
}

vector<xpair> strgy2(vector<ROW> &m)
{
	vector<ROW> trans_m;
	get_trans_matrix(trans_m, m);
	vector<xpair> seq = strgy1(trans_m);
	for(int i = 0; i < seq.size(); i++)
	{
		seq[i].flag = true;
	}
	get_trans_matrix(m, trans_m);

	int tab[SIZE] = {0};
	build_table(m, tab);//get TABLE
	vector<xpair> final_seq = update_seq_str(seq, tab);
	return final_seq;
}

vector<xpair> strgy3(vector<ROW> &m)
{
	vector<xpair> tmp_seq;
	while(get_ones(m) != m.size())
	{
		vector<xpair> base_oper;
		base_oper.clear();
		int value = 0;

		int Reduced_Row = select_oper(m, base_oper, value, 0);

		vector<ROW> trans_m;
		get_trans_matrix(trans_m,m);

		int Reduced_Col = select_oper(trans_m, base_oper, Reduced_Row, 1);
		if (base_oper.size() >= 1)
			{
				int rand_num = rand_generator() % base_oper.size();
			
				if (!base_oper[rand_num].flag)
				{
					m[base_oper[rand_num].dst] ^= m[base_oper[rand_num].src];
					tmp_seq.push_back(base_oper[rand_num]);
				}
	
				else if (base_oper[rand_num].flag)
				{   
					vector<ROW> trans_tmp_m;
					get_trans_matrix(trans_tmp_m, m);
					trans_tmp_m[base_oper[rand_num].dst] ^= trans_tmp_m[base_oper[rand_num].src];
					get_trans_matrix(m, trans_tmp_m);
					tmp_seq.push_back(base_oper[rand_num]);
				}
			}
			else 
			{
				break;
			}
	}
    
	if (get_ones(m) != m.size())
	{ 
	    // int rnd = rand()%2;
		int rnd = rand_generator() % 2;
		if(rnd == 0)
		{
			vector<xpair> seq_2(strgy1(m));
			tmp_seq.insert(tmp_seq.end(), seq_2.begin(), seq_2.end());
		}
		else if(rnd == 1)
		{
			vector<xpair> seq_2(strgy2(m));
			tmp_seq.insert(tmp_seq.end(), seq_2.begin(), seq_2.end());
		}
	}
	
	int tab[SIZE] = {0};
	build_table(m, tab);
	vector<xpair> final_seq = update_seq_str(tmp_seq, tab);
	return final_seq;
}


int select_oper(vector<ROW> m, vector<xpair> &max_seq, int no_reduced, int opr_type)
{
	int no_before = 0;
	int no_after = 0;
	xpair new_ele;

	for (int i = 0; i < m.size(); i++)
	{
		vector<ROW> tmp_m(m);
		for (int j = 0; j < m.size(); j++)
		{
			if (i != j)
			{
				no_before = tmp_m[j].count();
				tmp_m[j] ^= tmp_m[i];
				no_after = tmp_m[j].count();
				if((no_before - no_after) > 0)
				{
					if (no_reduced < (no_before - no_after))
					{
						no_reduced = no_before - no_after;
						max_seq.clear();
						new_ele.src = i;
						new_ele.dst = j;
						if(opr_type == 0)
						{
							new_ele.flag = false;
						}
						else if(opr_type == 1)
						{
							new_ele.flag = true;
						}
						max_seq.push_back(new_ele);
					}

					else if (no_reduced == (no_before - no_after))
					{
						new_ele.src = i;
						new_ele.dst = j;
						if(opr_type == 0)
						{
							new_ele.flag = false;
						}
						else if(opr_type == 1)
						{
							new_ele.flag = true;
						}
						max_seq.push_back(new_ele);
					}
				}
			}
		}
	}
    return no_reduced;
}


int get_ones(vector<ROW> m)
{
	int s = 0;
	for(int i = 0; i < m.size(); i++)
		s += m[i].count();
	return s;
}

void get_trans_matrix(vector<ROW> &trans_m, vector<ROW> m)
{   
	trans_m.clear();
	for(int i = 0; i < m.size(); i++)
	{  
		bitset<SIZE> tmp(0);
		for (int j = 0; j < m.size(); j++)
		{
		tmp[m[0].size() - 1 - j] = m[j][m[0].size() - i - 1];
		}
		trans_m.push_back(tmp);
	}
}

void build_table(vector<ROW> m, int tab[SIZE])
{
	int ind = 0;
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m.size(); j++)
		{
			if (m[i].test(j))
			{
				ind = m.size() - 1 - j;
				break;
			}
		}
		tab[ind] = i;
	}
}

vector<xpair> update_seq_str(vector<xpair> seq, int tab[SIZE])
{	
	vector<xpair> tmp_seq;
	for(int i = 0; i < seq.size(); i++)
	{	
		if(!seq[i].flag)
		{
			tmp_seq.push_back(seq[i]);
		}
	}

	for(int i = seq.size() - 1; i >= 0; i--)
	{	

		if(seq[i].flag)
		{	
			xpair new_ele;
			new_ele.src = tab[seq[i].dst];
			new_ele.dst = tab[seq[i].src];
			new_ele.flag = false;
			tmp_seq.push_back(new_ele);
		}
	}
	return tmp_seq;
}