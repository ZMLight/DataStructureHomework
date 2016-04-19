#include <iostream>
using namespace std;

int main()
{
    int clockArray[9],record[9];
    int movesOfClock[9][9] = {{3,3,0,3,3,0,0,0,0},{3,3,3,0,0,0,0,0,0},
                             {0,3,3,0,3,3,0,0,0},{3,0,0,3,0,0,3,0,0},
                             {0,3,0,3,3,3,0,3,0},{0,0,3,0,0,3,0,0,3},
                             {0,0,0,3,3,0,3,3,0},{0,0,0,0,0,0,3,3,3},
                             {0,0,0,0,3,3,0,3,3}};
    int totalMoves
    for(int i = 0; i < 9; i++)
        cin >> clockArray[i];

    for(record[0] = 0; record[0] < 4; record[0]++)
    {
        for(record[1] = 0; record[1] < 4; record[1]++)
        {
            for(record[2] = 0; record[2] < 4; record[2]++)
            {
                for(record[3] = 0; record[3] < 4; record[3]++)
                {
                    for(record[4] = 0; record[4] < 4; record[4]++)
                    {
                        for(record[5] = 0; record[5] < 4; record[5]++)
                        {
                            for(record[6] = 0; record[6] < 4; record[6]++)
                            {
                                for(record[7] = 0; record[7] < 4; record[7]++)
                                {
                                    for(record[8] = 0; record[8] < 4; record[8]++)
                                    {
                                        bool flag = true;
                                        for(int i = 0; i < 9; i++)
                                        {
                                            int t = clockArray[i];
                                            for(int j = 0; j < 9; j++)
                                            {
                                                t += movesOfClock[j][i] * record[j];
                                            }
                                            t = t % 12;
                                            if(t != 0)
                                            {
                                                flag=false;
                                                break;
                                            }
                                        }
                                        if(flag)
                                        {
                                            for(int i = 0;i < 9; i++)
                                            {
                                                while(record[i] > 0)
                                                {
                                                    cout << (i+1) << ' ';
                                                    record[i] --;
                                                }
                                            }
                                            return 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}
