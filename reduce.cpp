#include "reduce.h"
#include <pthread.h>
#include <cstdlib>

// #define THREAD_NUM 2


vector<ROW> get_reduced_matrix(vector<xpair> seq, vector<ROW> m)
{
	vector<ROW> tmp_m(m);
	for(int i = 0; i < seq.size(); i++)
		tmp_m[seq[i].dst] ^= tmp_m[seq[i].src];
	return tmp_m;
}


vector<ROW> get_identity()
{
	vector<ROW> m;
	ROW tmp(0);
	for(int i = 0; i < SIZE; i++)
	{
		m.push_back(tmp);
		m[i][SIZE - 1 - i] = 1;
	}
	return m;
}

bool exchange(xpair a, xpair b)
{
	if(a.dst == b.dst)
		return true;
	if(a.src == b.src)
		return true;
	if((a.src != b.dst) && (a.dst != b.src))
		return true;
	return false;
}

int** get_table(vector<xpair> seq, int ** table, int osize, int nsize)
{
	if(table != NULL)
	{
		for(int i = 0; i < osize; i++)
			delete[] table[i];
		delete[] table;
	}
	table = new int*[nsize];
	for(int i = 0; i < nsize; i++)
		table[i] = new int[nsize];

	int s = seq.size();
	for(int i = 0; i < s; i++)
	{
		table[i][i] = 1;
		for(int j = i + 1; j < s; j++)
		{
			if(exchange(seq[i], seq[j]))
				table[i][j] = 1;
			else
			{
				for(int k = j; k < s; k++)
					table[i][k] = 0;
				break;
			}
		}
		for(int j = i - 1; j >= 0; j--)
		{
			if(exchange(seq[i], seq[j]))
				table[i][j] = 1;
			else
			{
				for(int k = j; k >= 0; k--)
					table[i][k] = 0;
				break;
			}
		}
	}
	return table;
}

void delete_table(int** table, int size)
{
	if(table != NULL)
	{
		for(int i = 0; i < size; i++)
			delete[] table[i];
		delete[] table;
	}
}

bool exchange_set(vector<xpair> seq, int start, int end, xpair p)
{
	if(start <= end)
	{
		for(int i = start; i <= end; i++)
		{
			if(!exchange(p, seq[i]))
				return false;
		}
	}
	else
	{
		for(int i = start; i >= end; i--)
		{
			if(!exchange(p, seq[i]))
				return false;
		}
	}
	return true;
}


bool reduce0(vector<xpair> &seq, int** table)
{
	int s = seq.size();
	int index;

	for(int i = 0; i < s; i++)
	{
		for(int j = i + 1; j < s; j++)
		{
			if((table[i][j - 1] == 0) && (table[j][i + 1] == 0))
				break;
			if(seq[i].src != seq[j].src)
				continue;
			for(int k = j + 1; k < s; k++)
			{
				if((table[k][j + 1] == 0) && (table[j][k-1] == 0))
					break;
				if(seq[k].dst != seq[i].dst)
				{
					if (seq[k].dst != seq[j].dst)
						continue;
					else
					{
						if(seq[k].src != seq[i].dst)
							continue;
					}
				}
				else
				{
					if(seq[k].src != seq[j].dst)
						continue;
				}
				if((table[i][j - 1]) && table[k][j + 1])
					index = j - 1;//fixpoint = j;
				else if(table[j][i + 1] && table[k][j + 1] && exchange_set(seq, j - 1, i + 1, seq[k]))
					index = i; //fixpoint = i;
				else if(table[i][j - 1] && table[j][k - 1] && exchange_set(seq, j + 1, k - 1, seq[i]))
					index = k - 2; //fixpoint = k;
				else
					continue;
				xpair tmp1, tmp2;
				tmp1 = seq[k];
				tmp2.src = seq[i].src;
				tmp2.dst = seq[k].src;
				seq.erase(seq.begin() + k);
				seq.erase(seq.begin() + j);
				seq.erase(seq.begin() + i);
				seq.insert(seq.begin() + index, tmp1);
				seq.insert(seq.begin() + index + 1, tmp2);
				return true;
			}
		}
	}
	return false;
}

bool reduce1(vector<xpair> &seq, int** table)
{
	int s = seq.size();
	int index;

	for(int i = 0; i < s; i++)
	{
		for(int j = i + 1; j < s; j++)
		{
			if((table[i][j - 1] == 0) && (table[j][i + 1] == 0))
				break;
			if((seq[i].src != seq[j].dst) && (seq[i].dst != seq[j].dst))
				continue;
			for(int k = j + 1; k < s; k++)
			{
				if((table[k][j + 1] == 0) && (table[j][k-1] == 0))
					break;
				if(seq[k].src != seq[j].src)
					continue;
				else
				{
					if(seq[j].dst == seq[i].dst)
					{
						if(seq[k].dst != seq[i].src)
							continue;
					}
					if(seq[j].dst == seq[i].src)
					{
						if(seq[k].dst != seq[i].dst)
							continue;
					}
				}
				if((table[i][j - 1]) && table[k][j + 1])
					index = j - 1;//fixpoint = j;
				else if(table[j][i + 1] && table[k][j + 1] && exchange_set(seq, j - 1, i + 1, seq[k]))
					index = i; //fixpoint = i;
				else if(table[i][j - 1] && table[j][k - 1] && exchange_set(seq, j + 1, k - 1, seq[i]))
					index = k - 2; //fixpoint = k;
				else
					continue;
				xpair tmp1, tmp2;
				tmp1.src = seq[j].src;
				tmp1.dst = seq[i].src;
				tmp2 = seq[i];
				seq.erase(seq.begin() + k);
				seq.erase(seq.begin() + j);
				seq.erase(seq.begin() + i);
				seq.insert(seq.begin() + index, tmp1);
				seq.insert(seq.begin() + index + 1, tmp2);
				return true;
			}
		}
	}
	return false;
}

bool reduce2(vector<xpair> &seq, int** table)
{
	int s = seq.size();
	int index;

	for(int i = 0; i < s; i++)
	{
		for(int j = i + 1; j < s; j++)
		{
			if((table[i][j - 1] == 0) && (table[j][i + 1] == 0))
				break;
			if((seq[j].src != seq[i].dst) && (seq[j].dst != seq[i].dst))
				continue;
			for(int k = j + 1; k < s; k++)
			{
				if((table[k][j + 1] == 0) && (table[j][k-1] == 0))
					break;
				if(seq[k].src != seq[i].src)
					continue;
				else
				{
					if(seq[j].src == seq[i].dst)
					{
						if(seq[k].dst != seq[j].dst)
							continue;
					}
					if(seq[j].dst == seq[i].dst)
					{
						if(seq[k].dst != seq[j].src)
							continue;
					}
				}
				if((table[i][j - 1]) && table[k][j + 1])
					index = j - 1;//fixpoint = j;
				else if(table[j][i + 1] && table[k][j + 1] && exchange_set(seq, j - 1, i + 1, seq[k]))
					index = i; //fixpoint = i;
				else if(table[i][j - 1] && table[j][k - 1] && exchange_set(seq, j + 1, k - 1, seq[i]))
					index = k - 2; //fixpoint = k;
				else
					continue;
				xpair tmp1, tmp2;
				tmp1.dst = seq[k].dst;
				tmp2.dst = seq[i].dst;
				if(seq[j].src == seq[i].dst)
				{
					tmp1.src = seq[j].src;
					tmp2.src = seq[i].src;
				}
				else
				{
					tmp1.src = seq[i].src;
					tmp2.src = seq[j].src;
				}
				seq.erase(seq.begin() + k);
				seq.erase(seq.begin() + j);
				seq.erase(seq.begin() + i);
				seq.insert(seq.begin() + index, tmp1);
				seq.insert(seq.begin() + index + 1, tmp2);
				return true;
			}
		}
	}
	return false;
}

bool reduce3(vector<xpair> &seq, int** table)
{
	int s = seq.size();
	int index;

	for(int i = 0; i < s; i++)
	{
		for(int j = i + 1; j < s; j++)
		{
			if((table[i][j - 1] == 0) && (table[j][i + 1] == 0))
				break;
			if(seq[j].dst != seq[i].src)
				continue;
			if(seq[j].src != seq[i].dst)
				continue;
			if(table[i][j - 1])
				index = j - 1;
			else
				index = i;
			xpair tmp = seq[j];
			seq.erase(seq.begin() + j);
			seq.erase(seq.begin() + i);
			seq.insert(seq.begin() + index, tmp);
			int mask = seq[index].dst ^ seq[index].src;
			for(int k = index + 1; k < s; k++)
			{
				if((seq[k].dst == seq[index].dst) || (seq[k].dst == seq[index].src))
					seq[k].dst ^= mask;
				if((seq[k].src == seq[index].dst) || (seq[k].src == seq[index].src))
					seq[k].src ^= mask;
			}
			return true;
		}
	}
	return false;
}


int reduce_step(vector<xpair> &seq)
{
	int** tab = NULL;
	tab = get_table(seq, tab, 0, seq.size());
	int i = 0;
	int NUM = 4;
	int counter = 0;
	while(counter != NUM)
	{
		switch(i)
		{
			case 0:
			{
				if(reduce0(seq, tab))
				{
					// cout << "activate case 0"<<endl;
					tab = get_table(seq, tab, seq.size() + 1, seq.size());
					// i = 0;
					counter = 0;
				}
				else
				{
					i = (i + 1) % NUM;
					counter++;
				}
				break;
			}
			case 1:
			{
				if(reduce1(seq, tab))
				{
					// cout << "activate case 1" << endl;
					tab = get_table(seq, tab, seq.size() + 1, seq.size());
					// i = 1;
					counter = 0;
				}
				else
				{
					i = (i + 1) % NUM;
					counter++;
				}
				break;
			}
			case 2:
			{
				if(reduce2(seq, tab))
				{
					// cout << "activate case 2" <<endl;
					tab = get_table(seq, tab, seq.size() + 1, seq.size());
					counter = 0;
				}
				else
				{
					i = (i + 1) % NUM;
					counter++;
				}
				break;
			}
			case 3:
			{

				if(reduce3(seq, tab))
				{
					// cout << "activate case 3" << endl;
					tab = get_table(seq, tab, seq.size() + 1, seq.size());
					counter = 0;
				}
				else
				{
					// cout << "case 3" << endl;
					i = (i + 1) % NUM;
					counter++;
				}
			}
		}

	}
	delete_table(tab, seq.size());
	return seq.size();
}

void update_seq(vector<xpair> &seq, int tab[SIZE], int start)
{

	for(int i = start; i < seq.size(); i++)
	{
		seq[i].src = tab[seq[i].src];
		seq[i].dst = tab[seq[i].dst];
	}
}

void get_equivalent_seq(vector<xpair> &seq, int gap, int start)
{

	vector<ROW> m;
	bitset<SIZE> tmp;
	for (int i = 0; i < SIZE; i++)
	{
		tmp = 0;
		tmp[SIZE - 1 - i]=1;
		m.push_back(tmp);
	}
	for(int i = start + gap - 1; i >= start; i--)
	{
		m[seq[i].dst] ^= m[seq[i].src];
	}

	vector<xpair> seq_here(strgy3(m));
 	seq.erase(seq.begin() + start, seq.begin() + start + gap);
 	seq.insert(seq.begin() + start, seq_here.begin(), seq_here.end());
 	int tab[SIZE] = {0};
 	build_table(m, tab);
 	update_seq(seq, tab, start + seq_here.size());
}

void* reduce_thread(void *d)
{
	thread_data* data = (thread_data*)d;
	get_equivalent_seq(data->seq, data->gap, data->start);
	data->len = reduce_step(data->seq);
	pthread_exit(NULL);
}

bool check_consistence(vector<xpair> seq)
{
	vector<ROW> m = get_matrix();
	for(int i = 0; i < seq.size(); i++)
		m[seq[i].dst] ^= m[seq[i].src];
	if(get_ones(m) == SIZE)
		return true;
	else
		return false;

}

#if MULTI_THREAD_FLAG
vector<xpair> reduce(vector<ROW> m)
{

	vector<ROW> tmp_m(m);

	vector<xpair> seq = strgy3(m);
	int l = reduce_step(seq);


	int gap = l;
	int start = 0;

	thread_data data[THREAD_NUM];
	bool flag = true;
	while(flag)
	{
		for(int j = 0; j < THREAD_NUM; j++)
		{
			data[j].seq = seq;
			data[j].gap = gap;
			data[j].start = start;
			if((gap != 3) || (start != l - gap))
			{
				if(start == l - gap)
				{
					gap--;
					start = 0;
				}
				else
				{
					start++;
				}
			}
			else
			{
				flag = false;
			}
		}
		int rc;
		pthread_t threads[THREAD_NUM];
		pthread_attr_t attr;
		void* status;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		for(int j = 0; j < THREAD_NUM; j++)
		{

			rc = pthread_create(&threads[j], NULL, reduce_thread, (void *)(data + j));
			if(rc)
			{
				cout << "Error: unable to create thread!" << endl;
				exit(-1);
			}
		}
		// pthread_attr_destroy(&attr);
		for(int j = 0; j < THREAD_NUM; j++)
		{
			rc = pthread_join(threads[j], &status);
			if(rc)
			{
				cout << "Error: unable to join, " << rc << endl;
				exit(-1);
			}
		}
		for(int j = 0; j < THREAD_NUM; j++)
		{
			if(data[j].len < l)
			{
				seq = data[j].seq;
				l = data[j].len;
				gap = l;
				start = 0;
			}
		}
		// cout << "gap = " << gap << endl;
	}
	return seq;
}
#else
vector<xpair> reduce(vector<ROW> m)
{

	vector<ROW> tmp_m(m);

	vector<xpair> seq = strgy3(m);
	int l = reduce_step(seq);

	int t;
	int gap = l + 1;


	while(gap >= 4)
	{
		gap--;
		for(int start = 0; start <= l - gap; start++)
		{
			vector<xpair> t_seq(seq);
			get_equivalent_seq(t_seq, gap, start);

			t = reduce_step(t_seq);

			if(t < l)
			{
				l = t;
				seq = t_seq;
				gap = l + 1;
				break;
			}
		}

	}
	return seq;

}
#endif