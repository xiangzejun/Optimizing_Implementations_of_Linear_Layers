#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <bitset>
#include <iostream>

using namespace std;

#define MULTI_THREAD_FLAG 1
#define THREAD_NUM 4

//#define STRATEGY 2   // 1 for strategy3-1, 2 for strategy3-2
#define CHOICE 33




#if CHOICE == 1
    #define SIZE 16
    #define FILENAME "FSE_SKOP15_4x4_4.txt"

#elif CHOICE == 2  
    #define SIZE 16
    #define FILENAME "FSE_LimSim16_4x4_4.txt"

#elif CHOICE == 3
    #define SIZE 16
    #define FILENAME "FSE_LiWang16_4x4_4.txt"

#elif CHOICE == 4 
    #define SIZE 16
    #define FILENAME "FSE_LiWang16_4x4_4_2.txt"

#elif CHOICE == 5  
    #define SIZE 16
    #define FILENAME "C_BeiKraLea16_4x4_4.txt"

#elif CHOICE == 6  
    #define SIZE 16
    #define FILENAME "ToSC_SarSye16_4x4_4.txt"

#elif CHOICE == 7  
    #define SIZE 16
    #define FILENAME "ePrint_JeaPeySim_4x4_4.txt"

#elif CHOICE == 8 
    #define SIZE 16
    #define FILENAME "FSE_SKOP15_i_4x4_4.txt"

#elif CHOICE == 9
    #define SIZE 16
    #define FILENAME "FSE_LiWang16_i_4x4_4.txt"

#elif CHOICE == 10
    #define SIZE 16
    #define FILENAME "ToSC_SarSye16_i_4x4_4.txt"

#elif CHOICE == 11
    #define SIZE 16
    #define FILENAME "ePrint_JeaPeySim_i_4x4_4.txt"

#elif CHOICE == 12
    #define SIZE 32
    #define FILENAME "FSE_SKOP15_4x4_8.txt"

#elif CHOICE == 13
    #define SIZE 32
    #define FILENAME "FSE_LiuSim16_4x4_8.txt"

#elif CHOICE == 14
    #define SIZE 32
    #define FILENAME "FSE_LiWang16_4x4_8.txt"

#elif CHOICE == 15
    #define SIZE 32
    #define FILENAME "FSE_LiWang16_4x4_8_2.txt"

#elif CHOICE == 16
    #define SIZE 32
    #define FILENAME "C_BeiKraLea16_4x4_8.txt"

#elif CHOICE == 17
    #define SIZE 32
    #define FILENAME "ToSC_SarSye16_4x4_8.txt"

#elif CHOICE == 18
    #define SIZE 32
    #define FILENAME "ePrint_JeaPeySim_4x4_8.txt"

#elif CHOICE == 19
    #define SIZE 32
    #define FILENAME "FSE_SKOP15_i_4x4_8.txt"

#elif CHOICE == 20
    #define SIZE 32
    #define FILENAME "FSE_LiWang16_i_4x4_8.txt"

#elif CHOICE == 21
    #define SIZE 32
    #define FILENAME "FSE_LiWang16_i_4x4_8_2.txt"

#elif CHOICE == 22
    #define SIZE 32
    #define FILENAME "ToSC_SarSye16_i_4x4_8.txt"

#elif CHOICE == 23
    #define SIZE 32
    #define FILENAME "ePrint_JeaPeySim_i_4x4_8.txt"

#elif CHOICE == 24
    #define SIZE 32
    #define FILENAME "FSE_SKOP15_8x8_4.txt"

#elif CHOICE == 25
    #define SIZE 32
    #define FILENAME "ACISP_SarSye17_8x8_4.txt"

#elif CHOICE == 26
    #define SIZE 32
    #define FILENAME "FSE_SKOP15_i_8x8_4.txt"

#elif CHOICE == 27
    #define SIZE 64
    #define FILENAME "FSE_SKOP15_8x8_8.txt"

#elif CHOICE == 28
    #define SIZE 64
    #define FILENAME "FSE_LiuSim16_8x8_8.txt"

#elif CHOICE == 29
    #define SIZE 64
    #define FILENAME "C_BeiKraLea16_8x8_8.txt"

#elif CHOICE == 30
    #define SIZE 64
    #define FILENAME "ACISP_SarSye17_8x8_8.txt"

#elif CHOICE == 31
    #define SIZE 64
    #define FILENAME "FSE_SKOP15_i_8x8_8.txt"

#elif CHOICE == 32
    #define SIZE 64
    #define FILENAME "ePrint_JeaPeySim_i_8x8_8.txt"

#elif CHOICE == 33
    #define SIZE 32
    #define FILENAME "AES.txt"

#elif CHOICE == 34
    #define SIZE 32
    #define FILENAME "Anubis.txt"

#elif CHOICE == 35
    #define SIZE 32
    #define FILENAME "Clefia_M0.txt"

#elif CHOICE == 36
    #define SIZE 32
    #define FILENAME "Clefia_M1.txt"

#elif CHOICE == 37
    #define SIZE 32
    #define FILENAME "Fox_Mu4.txt"

#elif CHOICE == 38
    #define SIZE 32
    #define FILENAME "Twofish.txt"

#elif CHOICE == 39
    #define SIZE 64
    #define FILENAME "Fox_Mu8.txt"

#elif CHOICE == 40
    #define SIZE 64
    #define FILENAME "Grostl.txt"

#elif CHOICE == 41
    #define SIZE 64
    #define FILENAME "Khazad.txt"

#elif CHOICE == 42
    #define SIZE 64
    #define FILENAME "Whirlpool.txt"

#elif CHOICE == 43
    #define SIZE 16
    #define FILENAME "Joltik.txt"

#elif CHOICE == 44
    #define SIZE 16
    #define FILENAME "SmallScale_AES.txt"

#elif CHOICE == 45
    #define SIZE 32
    #define FILENAME "Whirlwind_M0.txt"

#elif CHOICE == 46
    #define SIZE 32
    #define FILENAME "Whirlwind_M1.txt"

#elif CHOICE == 47
    #define SIZE 32
    #define FILENAME "QARMA128.txt"

#elif CHOICE == 48
    #define SIZE 128
    #define FILENAME "ARIA.txt"

#elif CHOICE == 49
    #define SIZE 16
    #define FILENAME "MIDORI.txt"

#elif CHOICE == 50
    #define SIZE 16
    #define FILENAME "PRINCE_M_0.txt"

#elif CHOICE == 51
    #define SIZE 16
    #define FILENAME "PRINCE_M_1.txt"

#elif CHOICE == 52
    #define SIZE 16
    #define FILENAME "PRIDE_L_0.txt"

#elif CHOICE == 53
    #define SIZE 16
    #define FILENAME "PRIDE_L_1.txt"

#elif CHOICE == 54
    #define SIZE 16
    #define FILENAME "PRIDE_L_2.txt"

#elif CHOICE == 55
    #define SIZE 16
    #define FILENAME "PRIDE_L_3.txt"

#elif CHOICE == 56
    #define SIZE 16
    #define FILENAME "QARMA64.txt"

#elif CHOICE == 57
    #define SIZE 16
    #define FILENAME "SKINNY.txt"

#else
    #define SIZE 16
#endif

typedef bitset<SIZE> ROW;

typedef struct{
    int src;
    int dst;
    bool flag;
}xpair;

typedef struct
{
    vector<xpair> seq;
    int gap;
    int start;
    int len;
}thread_data;

vector<ROW> get_matrix();


#endif
