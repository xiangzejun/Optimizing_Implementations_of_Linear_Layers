#include "strategy.h"
#include "matrix.h"
#include "reduce.h"
#include <fstream>
#include <sys/time.h>

void print_seq(vector<ROW> m, vector<ROW> tmp_m, vector<xpair> seq);
int main()
{
	int counter = 100000;
	struct timeval start;
	struct timeval end;
	gettimeofday(&start, NULL);

	int num = 0;
	cout<<FILENAME<<endl;
	// while((num++) < 1)
	// srand(time(0));
	while(true)
	{
		vector<ROW> m = get_matrix();


		vector<xpair> seq = reduce(m);

		vector<ROW> tmp_m = get_reduced_matrix(seq, m);

		cout << "minimal = " << counter << "   current = " << seq.size() << endl << endl;

		if(seq.size() < counter)
		{
			counter = seq.size();
			print_seq(m, tmp_m, seq);
		}
	}

	gettimeofday(&end, NULL);
	float time  = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	time /= 1000000;
	cout << "Time used = " << time << endl;

	return 0;
}

void print_seq(vector<ROW> m, vector<ROW> tmp_m, vector<xpair> seq)
{
	ofstream f;
	f.open(FILENAME);
	f << "Original Matrix:" << endl;
	for(int i = 0; i < m.size(); i++)
		f << m[i] << endl;
	f << endl << endl;
	f << "Reduced Matrix:" << endl;
	for(int i = 0; i < tmp_m.size(); i++)
		f << tmp_m[i] << endl;
	f << endl << endl;


	f << "Xor Count = " << seq.size() << endl;
	
	int tab[SIZE] = {0};
	for(int i = 0; i < tmp_m.size(); i++)
		{
			for(int j = 0; j < tmp_m.size(); j++)
			{
				if(tmp_m[i].test(tmp_m.size() - 1 - j))
				{
					tab[i] = j;
					break;
				}
			}
		}

	for(int i = seq.size() - 1; i >= 0; i--)
		{//f << seq[i].dst << " <- " << seq[i].src << endl;
			f<<"x["<<tab[seq[i].dst]<<"] = x["<<tab[seq[i].dst]<<"] ^ x["<<tab[seq[i].src]<<"]";
		    tmp_m[seq[i].dst] ^= tmp_m[seq[i].src];
		  	bool flag = false;
		    for(int j = 0; j < m.size(); j++)
		    {
				if(tmp_m[seq[i].dst] == m[j])
				{
					flag = true;
					f<<"    y["<<j<<"]"<<endl;
					break;
				}
			}
			
			if(!flag)
			{
				f<<endl;
			}
		}
		f.close();
}