#include <iostream>
#include <Ctime>
using namespace std;
#define N 10
//           ��  ��   ��   ��
int a[4] = { 1,  -1,  0,   0 };
int b[4] = { 0,   0,  1,  -1 };

clock_t nTimeStart;      //��ʱ��ʼ
clock_t nTimeStop;       //��ʱ����


class ResultList {
public:
	int _result[N][N];
	ResultList *_next;
};


class Cell{
public:
	Cell() {}
	~Cell() {}
	int InitState;//0~4��ʾ��ɫ���֣�5��ʾ��ɫcell��9��ʾ��ɫcell��
	bool IsBulb;//��cell�����˵�
	int IsLighten;
	bool CannotBeBulb;//��cell���ܷŵ�
private:

};



class Matrix{
public:
//������
	Matrix();
	~Matrix() {}
	bool SureFill();//������λ��ȷ���ܷ�bulb�ķ�bulb������bulb��Ҫ�������еĶ�Ū��; ��ȷ��CannotBeBulb��Ҳ������
	void RecordUnsureRegion();//��¼��ǰδȷ������
	void PutBulb(int i, int j);
	void RemoveBulb(int i, int j);
	int SurroundLightNumber(int i, int j);
	void SaveAndDisplay();
	void DisplayCurrentStatus();
	bool IsWhiteSuccess();
	bool IsBlackSuccesss();
	void AkariDFS(int i,int j);
	void Case0DFS(int i, int j);
	void Case1DFS(int i, int j);
	void Case2DFS(int i, int j);
	void Case3DFS(int i, int j);
	void WhiteDFS(int i, int j);

//������
	Cell cell[N+2][N+2];
	int m1;
	int m2;
	int n1;
	int n2;
	ResultList ResultHead;

private:
	
};

Matrix::Matrix()
{
	int i,j;
	m1 = 1;//������ǰ��δȷ������
	m2 = N;
	n1 = 1;
	n2 = N;
	ResultHead._next = NULL;
	for (i = 0; i < N + 2; i++)	{
		for (j = 0; j < N + 2; j++)
		{
			/*�Ǳ߽�cell��Ϊ��ɫ�����Ǳ߽��ȡ����*/
			if (i == 0 || i == N + 1 || j == 0 || j == N + 1)
				cell[i][j].InitState = 5;
			else	scanf(" %d", &cell[i][j].InitState);
			/*��ÿ��cell������δ������δ���õ�*/
			cell[i][j].IsLighten = 0;
			cell[i][j].IsBulb = false;
			/*��0~4��"5"����CannotBeBulbΪ��*/
			if (cell[i][j].InitState <= 5)
				cell[i][j].CannotBeBulb = true;
			else cell[i][j].CannotBeBulb = false;
			}
		}
	
	for (i = 0; i<N + 2; i++)	{
		for (j = 0; j < N + 2; j++)
		{
			/*��4��Χ���е������,����bulb��Ҫ���������ж�Ū��;*/
			if (cell[i][j].InitState == 4 ) {
				PutBulb(i - 1, j);
				PutBulb(i + 1, j);
				PutBulb(i, j - 1);
				PutBulb(i, j + 1);
			}

			/*��0��Χ����CannotBeBulbΪ��*/
			if (cell[i][j].InitState == 0) {
				cell[i - 1][j].CannotBeBulb = true;
				cell[i + 1][j].CannotBeBulb = true;
				cell[i][j - 1].CannotBeBulb = true;
				cell[i][j + 1].CannotBeBulb = true;
		}
		}
	}
}

//������λ��ȷ���ܷ�bulb�ķ�bulb������bulb��Ҫ�������еĶ�Ū��;
bool Matrix::SureFill()
{
	int i,j;
	bool MatrixThisFill = false;//����Matrix�����û�з���ơ�false��ʾû��
	for(i=m1;i<=m2;i++)	{
			for(j=n1;j<=n2;j++)	{		
			// 3
				if (cell[i][j].InitState == 3 && SurroundLightNumber(i,j) != 3) {
					/*��3��Χ���Ǹ���bulb�׿ո��趨ΪCannotBeBulb;*/
					if (SurroundLightNumber(i, j) == 3) {
						if (cell[i - 1][j].CannotBeBulb == false)
							cell[i - 1][j].CannotBeBulb = true;
						if (cell[i + 1][j].CannotBeBulb == false)
							cell[i + 1][j].CannotBeBulb = true;
						if (cell[i][j - 1].CannotBeBulb == false)
							cell[i][j - 1].CannotBeBulb = true;
						if (cell[i][j + 1].CannotBeBulb == false)
							cell[i][j + 1].CannotBeBulb = true;
					}
					/*��3��Χ����bulb��䣬����bulb���������;*/
					if (SurroundLightNumber(i, j) != 3) {
						if (cell[i - 1][j].IsLighten > 0 || cell[i - 1][j].CannotBeBulb == true)
						{
							cell[i + 1][j].IsBulb = true;
							PutBulb(i + 1, j);
							cell[i][j - 1].IsBulb = true;
							PutBulb(i, j - 1);
							cell[i][j + 1].IsBulb = true;
							PutBulb(i, j + 1);
							MatrixThisFill = true;
						}
						if (cell[i + 1][j].IsLighten > 0 || cell[i + 1][j].CannotBeBulb == true)
						{
							cell[i - 1][j].IsBulb = true;
							PutBulb(i - 1, j);
							cell[i][j - 1].IsBulb = true;
							PutBulb(i, j - 1);
							cell[i][j + 1].IsBulb = true;
							PutBulb(i, j + 1);
							MatrixThisFill = true;
						}
						if (cell[i][j - 1].IsLighten > 0 || cell[i][j - 1].CannotBeBulb == true)
						{
							cell[i - 1][j].IsBulb = true;
							PutBulb(i - 1, j);
							cell[i + 1][j].IsBulb = true;
							PutBulb(i + 1, j);
							cell[i][j + 1].IsBulb = true;
							PutBulb(i, j + 1);
							MatrixThisFill = true;
						}
						if (cell[i][j + 1].IsLighten > 0 || cell[i][j + 1].CannotBeBulb == true)
						{
							cell[i - 1][j].IsBulb = true;
							PutBulb(i - 1, j);
							cell[i + 1][j].IsBulb = true;
							PutBulb(i + 1, j);
							cell[i][j - 1].IsBulb = true;
							PutBulb(i, j - 1);
							MatrixThisFill = true;
						}

					}
				}
			// 2	
				if (cell[i][j].InitState == 2 && SurroundLightNumber(i, j) != 2) {
					/*��2��Χ������������bulb�׿ո��趨ΪCannotBeBulb;*/
					if (SurroundLightNumber(i, j) == 2) {
						if (cell[i - 1][j].CannotBeBulb == false)
							cell[i - 1][j].CannotBeBulb = true;
						if (cell[i + 1][j].CannotBeBulb == false)
							cell[i + 1][j].CannotBeBulb = true;
						if (cell[i][j - 1].CannotBeBulb == false)
							cell[i][j - 1].CannotBeBulb = true;
						if (cell[i][j + 1].CannotBeBulb == false)
							cell[i][j + 1].CannotBeBulb = true;
					}
					/*��2��Χ���е�����䣬����bulb��Ҫ���������ж�Ū��;*/
					if (SurroundLightNumber(i, j) != 2) {
						if ((cell[i - 1][j].CannotBeBulb == true || cell[i - 1][j].IsLighten > 0) && (cell[i + 1][j].CannotBeBulb == true || cell[i + 1][j].IsLighten > 0))
						{
							cell[i][j - 1].IsBulb = true;
							PutBulb(i, j - 1);
							cell[i][j + 1].IsBulb = true;
							PutBulb(i, j + 1);
							MatrixThisFill = true;
						}
						if ((cell[i - 1][j].CannotBeBulb == true || cell[i - 1][j].IsLighten > 0) && (cell[i][j - 1].CannotBeBulb == true || cell[i][j - 1].IsLighten > 0))
						{
							cell[i + 1][j].IsBulb = true;
							PutBulb(i + 1, j);
							cell[i][j + 1].IsBulb = true;
							PutBulb(i, j + 1);
							MatrixThisFill = true;
						}
						if ((cell[i - 1][j].CannotBeBulb == true || cell[i - 1][j].IsLighten > 0) && (cell[i][j + 1].CannotBeBulb == true || cell[i][j + 1].IsLighten > 0))
						{
							cell[i + 1][j].IsBulb = true;
							PutBulb(i + 1, j);
							cell[i][j - 1].IsBulb = true;
							PutBulb(i, j - 1);
							MatrixThisFill = true;
						}
						if ((cell[i][j + 1].CannotBeBulb == true || cell[i][j + 1].IsLighten > 0) && (cell[i][j - 1].CannotBeBulb == true || cell[i][j - 1].IsLighten > 0))
						{
							cell[i + 1][j].IsBulb = true;
							PutBulb(i + 1, j);
							cell[i - 1][j].IsBulb = true;
							PutBulb(i - 1, j);
							MatrixThisFill = true;
						}
						if ((cell[i][j + 1].CannotBeBulb == true || cell[i][j + 1].IsLighten > 0) && (cell[i + 1][j].CannotBeBulb == true || cell[i + 1][j].IsLighten > 0))
						{
							cell[i - 1][j].IsBulb = true;
							PutBulb(i - 1, j);
							cell[i][j - 1].IsBulb = true;
							PutBulb(i, j - 1);
							MatrixThisFill = true;
						}
						if ((cell[i + 1][j].CannotBeBulb == true || cell[i + 1][j].IsLighten > 0) && (cell[i][j - 1].CannotBeBulb == true || cell[i][j - 1].IsLighten > 0))
						{
							cell[i - 1][j].IsBulb = true;
							PutBulb(i - 1, j);
							cell[i][j + 1].IsBulb = true;
							PutBulb(i, j + 1);
							MatrixThisFill = true;
						}
					}
				}
			// 1
				if (cell[i][j].InitState == 1 && SurroundLightNumber(i, j) != 1) {
					/*��1��Χ����������bulb�׿ո��趨ΪCannotBeBulb;*/
					if (SurroundLightNumber(i, j) == 1) {
						if (cell[i - 1][j].CannotBeBulb == false)
							cell[i - 1][j].CannotBeBulb = true;
						if (cell[i + 1][j].CannotBeBulb == false)
							cell[i + 1][j].CannotBeBulb = true;
						if (cell[i][j - 1].CannotBeBulb == false)
							cell[i][j - 1].CannotBeBulb = true;
						if (cell[i][j + 1].CannotBeBulb == false)
							cell[i][j + 1].CannotBeBulb = true;
					}
					/*��1��Χ���е�����䣬����bulb��Ҫ�������еĶ�Ū��;*/
					if (SurroundLightNumber(i, j) != 1) {
						if ((cell[i - 1][j].CannotBeBulb == true || cell[i - 1][j].IsLighten > 0) && (cell[i + 1][j].CannotBeBulb == true || cell[i + 1][j].IsLighten > 0) && (cell[i][j - 1].InitState <= 5 || cell[i][j - 1].IsLighten > 0))
						{
							cell[i][j + 1].IsBulb = true;
							PutBulb(i, j + 1);
							MatrixThisFill = true;
						}
						if ((cell[i - 1][j].CannotBeBulb == true || cell[i - 1][j].IsLighten > 0) && (cell[i + 1][j].CannotBeBulb == true || cell[i + 1][j].IsLighten > 0) && (cell[i][j + 1].InitState <= 5 || cell[i][j + 1].IsLighten > 0))
						{
							cell[i][j - 1].IsBulb = true;
							PutBulb(i, j - 1);
							MatrixThisFill = true;
						}
						if ((cell[i][j + 1].CannotBeBulb == true || cell[i][j + 1].IsLighten > 0) && (cell[i + 1][j].CannotBeBulb == true || cell[i + 1][j].IsLighten > 0) && (cell[i][j - 1].InitState <= 5 || cell[i][j - 1].IsLighten > 0))
						{
							cell[i - 1][j].IsBulb = true;
							PutBulb(i - 1, j);
							MatrixThisFill = true;
						}
						if ((cell[i - 1][j].CannotBeBulb == true || cell[i - 1][j].IsLighten > 0) && (cell[i][j + 1].CannotBeBulb == true || cell[i][j + 1].IsLighten > 0) && (cell[i][j - 1].InitState <= 5 || cell[i][j - 1].IsLighten > 0))
						{
							cell[i + 1][j].IsBulb = true;
							PutBulb(i + 1, j);
							MatrixThisFill = true;
						}
					}
				}
			}
	}
	return MatrixThisFill;
}

void Matrix::PutBulb(int i, int j)	
{
	int k;
	cell[i][j].IsBulb = true;
	for (k = i - 1; cell[k][j].InitState == 9 ; k--)
		cell[k][j].IsLighten++;
	for (k = i + 1; cell[k][j].InitState == 9;  k++)
		cell[k][j].IsLighten++;
	for (k = j - 1; cell[i][k].InitState == 9 ; k--)
		cell[i][k].IsLighten++;
	for (k = j + 1; cell[i][k].InitState == 9 ; k++)
		cell[i][k].IsLighten++;

}

void Matrix::RemoveBulb(int i, int j)
{
	int k;
	cell[i][j].IsBulb = false;
	for (k = i - 1; cell[k][j].InitState == 9 ; k--)
		cell[k][j].IsLighten--;
	for (k = i + 1; cell[k][j].InitState == 9 ; k++)
		cell[k][j].IsLighten--;
	for (k = j - 1; cell[i][k].InitState == 9 ; k--)
		cell[i][k].IsLighten--;
	for (k = j + 1; cell[i][k].InitState == 9 ; k++)
		cell[i][k].IsLighten--;

}

//��¼��ǰδȷ������(�ڵ�����亯���󣬿��������������δȷ������)
void Matrix::RecordUnsureRegion()
{
	int i,j;
	bool found = false;
	for(i=m1;i<=m2;i++)//ȷ����ǰ��m1
	{
		for(j=n1;j<=n2;j++)
		{
			if(cell[i][j].InitState==9 && cell[i][j].IsLighten==0 && cell[i][j].IsBulb ==false)
			{
				m1 = i;
				found = true;	break;
			}
		}
		if(found) break;
	}
	found = false;
	for(i=m2;i>=m1;i--)//ȷ����ǰ��m2
	{
		for(j=n1;j<=n2;j++)
		{
			if (cell[i][j].InitState == 9 && cell[i][j].IsLighten==0 && cell[i][j].IsBulb == false)
			{
				m2 = i;
				found = true;	break;
			}
		}
		if(found) break;
	}
	found = false;
	for(j=n1;j<=n2;j++)//ȷ����ǰ��n1
	{
		for(i=m1;i<=m2;i++)
		{
			if (cell[i][j].InitState == 9 && cell[i][j].IsLighten==0 && cell[i][j].IsBulb == false)
			{
				n1 = j;
				found = true;	break;
			}
		}
		if(found) break;
	}
	found = false;
	for(j=n2;j>=n1;j--)//ȷ����ǰ��n2
	{
		for(i=m1;i<=m2;i++)
		{
			if (cell[i][j].InitState == 9 && cell[i][j].IsLighten==0 && cell[i][j].IsBulb == false)
			{
				n2 = j;
				found = true;	break;
			}
		}
		if(found) break;
	}
}

int Matrix::SurroundLightNumber(int i,int j){
	int count=0;
	if (cell[i - 1][j].IsBulb) count++;
	if (cell[i + 1][j].IsBulb) count++;
	if (cell[i][j - 1].IsBulb) count++;
	if (cell[i][j + 1].IsBulb) count++;

	return count;

}

void Matrix::AkariDFS(int x, int y) {
	int i=x, j=y;
	for (; i <m2+1; i++) 
	{
		for (; j <n2+1; j++)
		{
			if(cell[i][j].InitState>0 &&cell[i][j].InitState<4)
			{ 
				switch (cell[i][j].InitState - SurroundLightNumber(i, j)) {
					case 0:
						Case0DFS(i, j); break;
					case 1:
						Case1DFS(i,j); break;
					case 2: 
						Case2DFS(i,j); break;
					case 3:
						Case3DFS(i,j); break;
				}
			}
		}
		j = n1;
	}
	if (IsBlackSuccesss())
	{ 
		WhiteDFS(m1, n1); 	
	}
}

void Matrix::Case0DFS(int i, int j) {
	int k;
	for (k = 0; k < 4;k++){
		if (cell[i + a[k]][j + b[k]].InitState == 9 && cell[i + a[k]][j + b[k]].IsBulb == false)
			cell[i + a[k]][j + b[k]].CannotBeBulb = true;
	}
	AkariDFS(i, j + 1);
	for (k = 0; k < 4; k++) {
		if (cell[i + a[k]][j + b[k]].InitState == 9 && cell[i + a[k]][j + b[k]].IsBulb == false)
			cell[i + a[k]][j + b[k]].CannotBeBulb = false;
	}
}

void Matrix::Case1DFS(int i, int j) {
	int k,m;
	for (k = 0; k < 4; k++) 
	{
		if (cell[i + a[k]][j + b[k]].InitState == 9 && cell[i + a[k]][j + b[k]].IsBulb == false && cell[i + a[k]][j + b[k]].IsLighten==0&& cell[i + a[k]][j + b[k]].CannotBeBulb==false)
		{
			PutBulb(i + a[k], j + b[k]);
			for ( m = 0; m < 4 ; m++)
			{
				if (cell[i + a[m]][j + b[m]].InitState == 9 && cell[i + a[m]][j + b[m]].IsBulb == false)
					cell[i + a[m]][j + b[m]].CannotBeBulb = true;
			}
			AkariDFS(i, j + 1);
			for (m = 0; m < 4; m++)
			{
				if (cell[i + a[m]][j + b[m]].InitState == 9 && cell[i + a[m]][j + b[m]].IsBulb == false)
					cell[i + a[m]][j + b[m]].CannotBeBulb = false;
			}
			RemoveBulb(i + a[k], j + b[k]);
		}
	}
}

void Matrix::Case2DFS(int i, int j) {
	int k,t,m;
	for (k = 0; k < 4; k++)
	{
		if (cell[i + a[k]][j + b[k]].InitState == 9 && cell[i + a[k]][j + b[k]].IsBulb == false && cell[i + a[k]][j + b[k]].IsLighten == 0 && cell[i + a[k]][j + b[k]].CannotBeBulb == false)
		{
			PutBulb(i + a[k], j + b[k]);
			for (t = k+1; t < 4; t++)
			{
				if (cell[i + a[t]][j + b[t]].InitState == 9 && cell[i + a[t]][j + b[t]].IsBulb == false && cell[i + a[t]][j + b[t]].IsLighten == 0 && cell[i + a[t]][j + b[t]].CannotBeBulb == false)
				{
					PutBulb(i + a[t], j + b[t]);
					for (m = 0; m < 4; m++)
					{
						if (cell[i + a[m]][j + b[m]].InitState == 9 && cell[i + a[m]][j + b[m]].IsBulb == false)
							cell[i + a[m]][j + b[m]].CannotBeBulb = true;
					}
					AkariDFS(i, j + 1);
					for ( m = 0; m < 4 ; m++)
					{
						if (cell[i + a[m]][j + b[m]].InitState == 9 && cell[i + a[m]][j + b[m]].IsBulb == false)
							cell[i + a[m]][j + b[m]].CannotBeBulb = false;
					}
					RemoveBulb(i + a[t], j + b[t]);
				}
			}
			RemoveBulb(i + a[k], j + b[k]);
		}
	}
}

void Matrix::Case3DFS(int i, int j) {
	int k, t,p, m;
	for (k = 0; k < 4; k++)
	{
		if (cell[i + a[k]][j + b[k]].InitState == 9 && cell[i + a[k]][j + b[k]].IsBulb == false && cell[i + a[k]][j + b[k]].IsLighten == 0 && cell[i + a[k]][j + b[k]].CannotBeBulb == false)
		{
			PutBulb(i + a[k], j + b[k]);
			for (t = k + 1; t < 4; t++)
			{
				if (cell[i + a[t]][j + b[t]].InitState == 9 && cell[i + a[t]][j + b[t]].IsBulb == false && cell[i + a[t]][j + b[t]].IsLighten == 0 && cell[i + a[t]][j + b[t]].CannotBeBulb == false)
				{
					PutBulb(i + a[t], j + b[t]);
					for (p = k + 1; p < 4; t++)
					{
						if (cell[i + a[p]][j + b[p]].InitState == 9 && cell[i + a[p]][j + b[p]].IsBulb == false && cell[i + a[p]][j + b[p]].IsLighten == 0 && cell[i + a[p]][j + b[p]].CannotBeBulb == false)
						{
							PutBulb(i + a[p], j + b[p]);
							for (m = 0; m < 4 ; m++)
							{
								if (cell[i + a[m]][j + b[m]].InitState == 9 && cell[i + a[m]][j + b[m]].IsBulb == false)
									cell[i + a[m]][j + b[m]].CannotBeBulb = true;
							}
							AkariDFS(i, j + 1);
							for (m = 0; m < 4 ; m++)
							{
								if (cell[i + a[m]][j + b[m]].InitState == 9 && cell[i + a[m]][j + b[m]].IsBulb == false)
									cell[i + a[m]][j + b[m]].CannotBeBulb = false;
							}
							RemoveBulb(i + a[p], j + b[p]);
						}
					}
					RemoveBulb(i + a[t], j + b[t]);
				}
			}
			RemoveBulb(i + a[k], j + b[k]);
		}
	}
}

bool Matrix::IsBlackSuccesss()
{
	int i, j;
	for (i = m1; i < m2+1; i++) 
	{
		for (j = n1; j < n2+1; j++) 
		{
			if (cell[i][j].InitState>0 && cell[i][j].InitState<4)
			{
				if (cell[i][j].InitState != SurroundLightNumber(i, j))
					return false;
			}
		}
	}
	return true;
}

bool Matrix::IsWhiteSuccess()
{
	int i, j, k;
	bool recentfill = false;
	for (i = m1; i <= m2; i++) {
		for (j = n1; j <= n2; j++) {
			if (cell[i][j].InitState == 9)
			{
				if (cell[i][j].IsLighten == false && cell[i][j].IsBulb == false)
					return false;
			}
		}
	}
	return true;
}

void Matrix::WhiteDFS(int x, int y)
{
	int i = x, j = y;
	for (; i < m2 + 1; i++)
	{
		for (; j < n2 + 1; j++)
		{
			if (cell[i][j].InitState == 9 && cell[i][j].CannotBeBulb == false && cell[i][j].IsBulb == false && cell[i][j].IsLighten == 0)
			{
				PutBulb(i, j);
				WhiteDFS(i, j + 1);
				RemoveBulb(i, j);
			}
		}
		j = n1;
	}
	if (IsWhiteSuccess())
	{
		//DisplayCurrentStatus();
		SaveAndDisplay();
		nTimeStop = clock();    //
		cout <<"��ʱ��" << (double)(nTimeStop - nTimeStart)  << "ms" << endl;
		system("pause");
	}
}

void Matrix::SaveAndDisplay()
{
	int i, j;
	//save
	ResultList  *ptr_new = new ResultList;
	ResultList  *ptr = ResultHead._next;
	for (i = 1; i < N+1;i++)
		for (j = 1; j < N + 1; j++)
			ptr_new->_result[i-1][j-1] =	cell[i][j].IsBulb ? 1 : 0;

	ptr_new->_next = NULL;
	while (ptr != NULL) { ptr = ptr->_next; }
	ptr = ptr_new;

	//display
	if (ptr != NULL) {
		cout << endl<<"**********��ʾ������**********"<<endl;
		for (i = 0; i < N;i++)
		{
			for (j = 0; j < N; j++) 
			{
				cout << ptr->_result[i][j]<<' ';
			}
			cout << endl;
		}
		cout << "********************************" << endl;
	}
	else
		cout <<"NO RESULT!" <<endl;
}

//Ϊ�˵���
void Matrix::DisplayCurrentStatus()
{
	int i, j;
	cout << endl<<"*************"<<endl;
	for (i = 1; i < N+1; i++)
	{
		for (j = 1; j < N + 1; j++)
		{
			if (cell[i][j].InitState == 9 && cell[i][j].IsBulb)	
				printf("1 ");
			else if (cell[i][j].InitState == 9 && cell[i][j].CannotBeBulb)	
				printf("x ");
			else
				printf("0 ");		
		}
		cout << endl;
	}
	cout<< "*************" << endl;
}

int  main()
{

	Matrix matrix;

	//��ʼ��ʱ
	nTimeStart = clock();

 	while (matrix.SureFill() == true);
	matrix.RecordUnsureRegion();

	//�ݹ�
	matrix.AkariDFS(matrix.m1,matrix.n1);
	return 0;
}