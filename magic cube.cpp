#include <iostream>
#include <cstdio>

using namespace std;

#include "defs.h"
#include "magic cube.h"

void showOut(int steps, int way);
Cube* CreatCube(void);
bool AICube(Cube* pCube, int faceNum);

int main()
{
	Cube* pCube=CreatCube();
	
	int i=0,j;

	while (!pCube->Sorted())
	{

		while (!pCube->Sorted())
		{
			if (!AICube(pCube, i))
			{
				cout << "AI falled at " << double(pCube->Score(i))/double(FULLSCORE) << endl;
				break;
			}

		}

		i = (i+2)%5;

		cout << "Changing dealing face to " << i << "......" << endl;
	}

	cout << "Target done!" << endl;

	delete pCube;

	return 0;
}

Cube* CreatCube(void)
{
	cout << "Please input the six faces' colour:" << endl;
	cout << "(Enter 'B', 'G', 'W', 'Y', 'R' or 'P')" << endl;

	int i,j,k;
	colour clr[6][3][3];

	char temp;

REENTER:
	for (i=0; i<6; i++)
	{
		for (j=0; j<3; j++)
		{
			for (k=0; k<3; k++)
			{
				cin >> temp;

				switch (temp)
				{
				case 'B':
					clr[i][j][k] = Blue;
					break;
				case 'G':
					clr[i][j][k] = Green;
					break;
				case 'W':
					clr[i][j][k] = White;
					break;
				case 'Y':
					clr[i][j][k] = Yellow;
					break;
				case 'R':
					clr[i][j][k] = Red;
					break;
				case 'P':
					clr[i][j][k] = Purple;
					break;
				default:
					cout << "Meaningless input!" << endl;
					cout << "Please enter all the colours again:" << endl;
					goto REENTER;
					break;
				}
			}
		}
	}

	return new Cube(clr);
}

bool AICube(Cube* pCube, int faceNum)           //deepth = 6;
{
	static steps=0;

	colour init[6][3][3] = {Blue};
	Cube *pi = new Cube(init), *pj = new Cube(init), *pk = new Cube(init), *pl = new Cube(init),
		*pm = new Cube(init), *pn = new Cube(init), *pa = new Cube(init), *pb = new Cube(init),
		*pc = new Cube(init);

	int i,j,k,l,m,n,a,b,c;

	int maxScore=pCube->Score(faceNum);
	int maxI=-1,maxJ=-1,maxK=-1, maxL=-1, maxM=-1, maxN=-1, maxA=-1, maxB = -1, maxC = -1;

	int score;
	for (i=0; i<18; i++)
	{
		//cout << "Dealing with the " << i << "th way......" << endl;

		if (i/3==pCube->freshFace)
			continue;

		*pi = *pCube;

		pi->Turn(i/3, i%3);

		score = pi->Score(faceNum);
		if (score>maxScore)
		{
			maxScore = score;
			maxI = i, maxJ = -1, maxK = -1, maxL = -1, maxM = -1, maxN = -1, maxA = -1;
		}
		else if (score < maxScore * limrate[0])
			continue;



		for (j=0; j<18; j++)
		{
			if (j/3==i/3)
				continue;

			*pj = *pi;

			pj->Turn(j/3, j%3);

			score = pj->Score(faceNum);
			if (score>maxScore)
			{
				maxScore = score;
				maxI = i, maxJ = j, maxK = -1, maxL = -1, maxM = -1, maxN = -1, maxA = -1;
			}
			else if (score < maxScore * limrate[1])
				continue;





			for (k=0; k<18; k++)
			{
				if (k/3==j/3)
					continue;

				*pk = *pj;

				pk->Turn(k/3, k%3);

				score = pk->Score(faceNum);
				if (score>maxScore)
				{
					maxScore = score;
					maxI = i, maxJ = j, maxK = k, maxL = -1, maxM = -1, maxN = -1, maxA = -1;
				}
				else if (score < maxScore * limrate[2])
					continue;




				for (l=0; l<18; l++)
				{
					if (l/3==k/3)
						continue;

					*pl = *pk;

					pl->Turn(l/3, l%3);

					score = pl->Score(faceNum);
					if (score>maxScore)
					{
						maxScore = score;
						maxI = i, maxJ = j, maxK = k, maxL = l, maxM = -1, maxN = -1, maxA = -1;
					}
					else if (score < maxScore * limrate[3])
						continue;





					for (m=0; m<18; m++)
					{
						if (m/3==l/3)
							continue;

						*pm = *pl;

						pm->Turn(m/3, m%3);
	
						score = pm->Score(faceNum);
						if (score>maxScore)
						{
							maxScore = score;
							maxI = i, maxJ = j, maxK = k, maxL = l, maxM = m, maxN = -1, maxA = -1;
						}
						else if (score < maxScore * limrate[4])
							continue;





						if (SEARCHDEEPTH>=6)
						{
						for (n=0; n<18; n++)
						{
							if (n/3==m/3)
								continue;

							*pn = *pm;

							pn->Turn(n/3, n%3);
	
							score = pn->Score(faceNum);
							if (score>maxScore)
							{
								maxScore = score;
								maxI = i, maxJ = j, maxK = k, maxL = l, maxM = m, maxN = n, maxA = -1;
								//goto GETOUT;
							}
							else if (score < maxScore * limrate[5])
								continue;




							if (SEARCHDEEPTH>=7)
							{
							for (a=0; a<18; a++)
							{
								if (a/3==n/3)
									continue;

								*pa = *pn;

								pa->Turn(a/3, a%3);
		
								score = pa->Score(faceNum);
								if (score>maxScore)
								{
									maxScore = score;
									maxI = i, maxJ = j, maxK = k, maxL = l, maxM = m, maxN = n, maxA = a;
									//goto GETOUT;
								}
								else if (score < maxScore * limrate[6])
									continue;

								for (b=0; b<18; b++)
								{
									if (b/3==a/3)
										continue;

									*pb = *pa;

									pb->Turn(b/3, b%3);
			
									score = pb->Score(faceNum);
									if (score>maxScore)
									{
										maxScore = score;
										maxI = i, maxJ = j, maxK = k, maxL = l, maxM = m, maxN = n, maxA = a, maxB = b;
										//goto GETOUT;
									}
									else if (score < maxScore * limrate[7])
										continue;
									
									for (c=0; c<18; c++)
									{
										if (c/3==c/3)
											continue;

										*pc = *pb;

										pc->Turn(c/3, c%3);
				
										score = pc->Score(faceNum);
										if (score>maxScore)
										{
											maxScore = score;
											maxI = i, maxJ = j, maxK = k, maxL = l, maxM = m, maxN = n, maxA = a, maxB = b, maxC = c;
											//goto GETOUT;
										}
										//else if (score < maxScore * limrate[8])
										//	continue;
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
	}

GETOUT:
	delete pi; delete pj; delete pk; delete pl; delete pm; delete pn; delete pa; delete pb; delete pc;

	if (maxI>=0 && !DEBUG)
	{
		cout << "Next ready:" << endl;
		getchar();
		cout << endl;
	}

	if (maxI<0)
		return false;
	else
	{
		pCube->Turn(maxI/3, maxI%3);
		steps++;
		showOut(steps, maxI);
	}

	if (maxJ>=0)
	{
		pCube->Turn(maxJ/3, maxJ%3);
		steps++;
		showOut(steps, maxJ);
	}

	if (maxK>=0)
	{
		pCube->Turn(maxK/3, maxK%3);
		steps++;
		showOut(steps, maxK);
	}

	if (maxL>=0)
	{
		pCube->Turn(maxL/3, maxL%3);
		steps++;
		showOut(steps, maxL);
	}

	if (maxM>=0)
	{
		pCube->Turn(maxM/3, maxM%3);
		steps++;
		showOut(steps, maxM);
	}

	if (maxN>=0)
	{
		pCube->Turn(maxN/3, maxN%3);
		steps++;
		showOut(steps, maxN);
	}

	if (maxA>=0)
	{
		pCube->Turn(maxA/3, maxA%3);
		steps++;
		showOut(steps, maxA);
	}

	if (maxB>=0)
	{
		pCube->Turn(maxB/3, maxB%3);
		steps++;
		showOut(steps, maxB);
	}
	
	if (maxC>=0)
	{
		pCube->Turn(maxC/3, maxC%3);
		steps++;
		showOut(steps, maxC);
	}

	cout << endl;
	cout << double(maxScore)/double(FULLSCORE) << endl;
	cout << endl;

	pCube->ShowFace();


	return true;
}

void showOut(int steps, int way)
{
	cout << "step: " << steps << "     ";
	switch (way/3)
	{
	case 0:
		cout << "Blue  ";
		break;
	case 1:
		cout << "Green ";
		break;
	case 2:
		cout << "White ";
		break;
	case 3:
		cout << "Yellow";
		break;
	case 4:
		cout << "Red   ";
		break;
	case 5:
		cout << "Purple";
		break;
	default:
		break;
	}

	switch (way%3)
	{
	case 0:
		cout << "   <-";
		break;
	case 1:
		cout << "  <--->";
		break;
	case 2:
		cout << "   ->";
		break;
	default:
		break;
	}

	cout << endl;
}