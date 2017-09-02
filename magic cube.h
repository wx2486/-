#include "iostream"

using namespace std;

enum colour{Blue,Green,White,Yellow,Red,Purple};      // 枚举颜色

// 重要的类，存储魔方的一个状态
class Cube                                       
{
public:
	Cube(colour sur[6][3][3])
	{
		int i,j,k;
		for (i=0; i<6; i++)
		{
			for (j=0; j<3; j++)
			{
				for (k=0; k<3; k++)
				surface[i][j][k] = sur[i][j][k];
			}
		}

		freshFace = -1;
	}

private:
	colour surface[6][3][3];     //front: 0; back: 1; left: 2; right: 3; top: 4; bottom: 5;
public:
	int freshFace;              // 上次转动的面

public:
	void Turn(int faceNum, int direct);  // 转动模拟函数
	int Score(int faceNum);              // 估分函数
	bool Sorted()
	{
		int i, j, k;
		for (i=0; i<6; i++)
		{
			for (j=0; j<3; j++)
			{
				for (k=0; k<3; k++)
					if (surface[i][j][k]!=surface[i][1][1])
						return false;
			}
		}

		return true;
	}
	void ShowFace()                         // 当前状态显示
	{
		int i,j,k;
		for (i=0; i<6; i++)
		{
			for (j=0; j<3; j++)
			{
				for (k=0; k<3; k++)
					cout << surface[i][j][k];
			}
			cout << endl;
		}

		cout << endl;
		cout << endl;
		cout << endl;
	}
};

void Cube::Turn(int faceNum, int direct)
{
	int i,j;
	colour *f[3][3], *sur[4][3];

	for (i=0; i<3; i++)
	{
		for (j=0; j<3; j++)
			f[i][j] = &surface[faceNum][i][j];
	}

	switch (faceNum)
	{
	case 0:
		for (i=0; i<3; i++)
		{
			sur[0][i] = &surface[4][2][i];
			sur[1][i] = &surface[3][i][0];
			sur[2][i] = &surface[5][0][2-i];
			sur[3][i] = &surface[2][2-i][2];
		}		
		break;
	case 1:
		for (i=0; i<3; i++)
		{
			sur[0][i] = &surface[4][0][2-i];
			sur[1][i] = &surface[2][i][0];
			sur[2][i] = &surface[5][2][i];
			sur[3][i] = &surface[3][2-i][2];
		}
		break;
	case 2:	
		for (i=0; i<3; i++)
		{
			sur[0][i] = &surface[4][i][0];
			sur[1][i] = &surface[0][i][0];
			sur[2][i] = &surface[5][i][0];
			sur[3][i] = &surface[1][2-i][2];
		}
		break;
	case 3:	
		for (i=0; i<3; i++)
		{
			sur[0][i] = &surface[4][2-i][2];
			sur[1][i] = &surface[1][i][0];
			sur[2][i] = &surface[5][2-i][2];
			sur[3][i] = &surface[0][2-i][2];
		}
		break;
	case 4:	
		for (i=0; i<3; i++)
		{
			sur[0][i] = &surface[1][0][2-i];
			sur[1][i] = &surface[3][0][2-i];
			sur[2][i] = &surface[0][0][2-i];
			sur[3][i] = &surface[2][0][2-i];
		}
		break;
	case 5:	
		for (i=0; i<3; i++)
		{
			sur[0][i] = &surface[0][2][i];
			sur[1][i] = &surface[3][2][i];
			sur[2][i] = &surface[1][2][i];
			sur[3][i] = &surface[2][2][i];
		}
		break;
	default:
		break;
	}

	if (direct==0)
	{
		colour t;
		t = *f[0][0], *f[0][0] = *f[0][2], *f[0][2] = *f[2][2], *f[2][2] = *f[2][0], *f[2][0] = t;
		t = *f[0][1], *f[0][1] = *f[1][2], *f[1][2] = *f[2][1], *f[2][1] = *f[1][0], *f[1][0] = t;

		for (i=0; i<3; i++)
			t = *sur[0][i], *sur[0][i] = *sur[1][i], *sur[1][i] = *sur[2][i], *sur[2][i] = *sur[3][i], *sur[3][i] = t;
	}
	else if (direct==2)
	{
		colour t;
		t = *f[2][0], *f[2][0] = *f[2][2], *f[2][2] = *f[0][2], *f[0][2] = *f[0][0], *f[0][0] = t;
		t = *f[1][0], *f[1][0] = *f[2][1], *f[2][1] = *f[1][2], *f[1][2] = *f[0][1], *f[0][1] = t;

		for (i=0; i<3; i++)
			t = *sur[3][i], *sur[3][i] = *sur[2][i], *sur[2][i] = *sur[1][i], *sur[1][i] = *sur[0][i], *sur[0][i] = t;
	}
	else if (direct==1)
	{
		colour t;
		t = *f[0][0], *f[0][0] = *f[2][2], *f[2][2] = t;
		t = *f[0][1], *f[0][1] = *f[2][1], *f[2][1] = t;
		t = *f[0][2], *f[0][2] = *f[2][0], *f[2][0] = t;
		t = *f[1][2], *f[1][2] = *f[1][0], *f[1][0] = t;

		for (i=0; i<3; i++)
		{
			t = *sur[0][i], *sur[0][i] = *sur[2][i], *sur[2][i] = t;
			t = *sur[1][i], *sur[1][i] = *sur[3][i], *sur[3][i] = t;
		}
	}

	freshFace = faceNum;
}

int Cube::Score(int faceNum)
{
	int i,j,k;

	int square=0;

	int same[6]={0};

#define CORNER 2
#define MIDDLE 3

	if (surface[0][0][1]==0 && surface[4][2][1]==4)
	{
		square+=MIDDLE;
		same[0]++, same[4]++;
	}
	if (surface[0][1][2]==0 && surface[3][1][0]==3)
	{
		square+=MIDDLE;
		same[0]++, same[3]++;
	}
	if (surface[0][2][1]==0 && surface[5][0][1]==5)
	{
		square+=MIDDLE;
		same[0]++, same[5]++;
	}
	if (surface[0][1][0]==0 && surface[2][1][2]==2)
	{
		square+=MIDDLE;
		same[0]++, same[2]++;
	}



	if (surface[2][0][1]==2 && surface[4][1][0]==4)
	{
		square+=MIDDLE;
		same[2]++, same[4]++;
	}
	if (surface[4][1][2]==4 && surface[3][0][1]==3)
	{
		square+=MIDDLE;
		same[4]++, same[3]++;
	}
	if (surface[3][2][1]==3 && surface[5][1][2]==5)
	{
		square+=MIDDLE;
		same[3]++, same[5]++;
	}
	if (surface[5][1][0]==5 && surface[2][2][1]==2)
	{
		square+=MIDDLE;
		same[5]++, same[2]++;
	}




	if (surface[4][0][1]==4 && surface[1][0][1]==1)
	{
		square+=MIDDLE;
		same[4]++, same[1]++;
	}
	if (surface[3][1][2]==3 && surface[1][1][0]==1)
	{
		square+=MIDDLE;
		same[3]++, same[1]++;
	}
	if (surface[5][2][1]==5 && surface[1][2][1]==1)
	{
		square+=MIDDLE;
		same[5]++, same[1]++;
	}
	if (surface[2][1][0]==2 && surface[1][1][2]==1)
	{
		square+=MIDDLE;
		same[2]++, same[1]++;
	}



	if (surface[0][0][0]==0 && surface[2][0][2]==2 && surface[4][2][0]==4)
	{
		square+=CORNER;
		same[0]++, same[2]++, same[4]++;
	}
	if (surface[0][0][2]==0 && surface[3][0][0]==3 && surface[4][2][2]==4)
	{
		square+=CORNER;
		same[0]++, same[3]++, same[4]++;
	}
	if (surface[0][2][2]==0 && surface[3][2][0]==3 && surface[5][0][2]==5)
	{
		square+=CORNER;
		same[0]++, same[3]++, same[5]++;
	}
	if (surface[0][2][0]==0 && surface[2][2][2]==2 && surface[5][0][0]==5)
	{
		square+=CORNER;
		same[0]++, same[2]++, same[5]++;
	}
	if (surface[4][0][0]==4 && surface[1][0][2]==1 && surface[2][0][0]==2)
	{
		square+=CORNER;
		same[4]++, same[1]++, same[2]++;
	}
	if (surface[4][0][2]==4 && surface[1][0][0]==1 && surface[3][0][2]==3)
	{
		square+=CORNER;
		same[4]++, same[1]++, same[3]++;
	}
	if (surface[2][2][0]==2 && surface[5][2][0]==5 && surface[1][2][2]==1)
	{
		square+=CORNER;
		same[2]++, same[5]++, same[1]++;
	}
	if (surface[3][2][2]==3 && surface[5][2][2]==5 && surface[1][2][0]==1)
	{
		square+=CORNER;
		same[3]++, same[5]++, same[1]++;
	}



	int faceScore=0;

	for (i=0; i<6; i++)
		faceScore += same[i] + same[i]*(i==faceNum)*5;

	


	return square*25+faceScore*10;
}
