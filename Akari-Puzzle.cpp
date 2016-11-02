#include <iostream>
#include <Ctime>
using namespace std;
#define N 10
//           ↓  ↑   →   ←
int a[4] = { 1,  -1,  0,   0 };
int b[4] = { 0,   0,  1,  -1 };

clock_t nTimeStart;      //计时开始
clock_t nTimeStop;       //计时结束


class ResultList {
public:
	int _result[N][N];
	ResultList *_next;
};


class Cell{
public:
	Cell() {}
	~Cell() {}
	int InitState;//0~4表示黑色数字；5表示黑色cell；9表示白色cell；
	bool IsBulb;//该cell放置了灯
	int IsLighten;
	bool CannotBeBulb;//该cell不能放灯
private:

};



class Matrix{
public:
//函数域
	Matrix();
	~Matrix() {}
	bool SureFill();//把所有位置确定能放bulb的放bulb，放了bulb需要点亮行列的都弄好; 把确定CannotBeBulb的也设置下
	void RecordUnsureRegion();//记录当前未确定区域
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

//数据域
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
	m1 = 1;//给出当前的未确定区域
	m2 = N;
	n1 = 1;
	n2 = N;
	ResultHead._next = NULL;
	for (i = 0; i < N + 2; i++)	{
		for (j = 0; j < N + 2; j++)
		{
			/*是边界cell设为黑色，不是边界读取输入*/
			if (i == 0 || i == N + 1 || j == 0 || j == N + 1)
				cell[i][j].InitState = 5;
			else	scanf(" %d", &cell[i][j].InitState);
			/*对每个cell都设置未点亮、未放置灯*/
			cell[i][j].IsLighten = 0;
			cell[i][j].IsBulb = false;
			/*对0~4和"5"设置CannotBeBulb为真*/
			if (cell[i][j].InitState <= 5)
				cell[i][j].CannotBeBulb = true;
			else cell[i][j].CannotBeBulb = false;
			}
		}
	
	for (i = 0; i<N + 2; i++)	{
		for (j = 0; j < N + 2; j++)
		{
			/*对4周围进行灯泡填充,放了bulb需要点亮的行列都弄好;*/
			if (cell[i][j].InitState == 4 ) {
				PutBulb(i - 1, j);
				PutBulb(i + 1, j);
				PutBulb(i, j - 1);
				PutBulb(i, j + 1);
			}

			/*对0周围设置CannotBeBulb为真*/
			if (cell[i][j].InitState == 0) {
				cell[i - 1][j].CannotBeBulb = true;
				cell[i + 1][j].CannotBeBulb = true;
				cell[i][j - 1].CannotBeBulb = true;
				cell[i][j + 1].CannotBeBulb = true;
		}
		}
	}
}

//把所有位置确定能放bulb的放bulb，放了bulb需要点亮行列的都弄好;
bool Matrix::SureFill()
{
	int i,j;
	bool MatrixThisFill = false;//整个Matrix这次有没有放入灯。false表示没有
	for(i=m1;i<=m2;i++)	{
			for(j=n1;j<=n2;j++)	{		
			// 3
				if (cell[i][j].InitState == 3 && SurroundLightNumber(i,j) != 3) {
					/*对3周围的那个非bulb白空格，设定为CannotBeBulb;*/
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
					/*对3周围进行bulb填充，放了bulb后点亮行列;*/
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
					/*对2周围的那两个个非bulb白空格，设定为CannotBeBulb;*/
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
					/*对2周围进行灯泡填充，放了bulb需要点亮的行列都弄好;*/
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
					/*对1周围的那三个非bulb白空格，设定为CannotBeBulb;*/
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
					/*对1周围进行灯泡填充，放了bulb需要点亮行列的都弄好;*/
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

//记录当前未确定区域(在调用填充函数后，可用这个函数更新未确定区域)
void Matrix::RecordUnsureRegion()
{
	int i,j;
	bool found = false;
	for(i=m1;i<=m2;i++)//确定当前的m1
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
	for(i=m2;i>=m1;i--)//确定当前的m2
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
	for(j=n1;j<=n2;j++)//确定当前的n1
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
	for(j=n2;j>=n1;j--)//确定当前的n2
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
		cout <<"耗时：" << (double)(nTimeStop - nTimeStart)  << "ms" << endl;
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
		cout << endl<<"**********显示答案如下**********"<<endl;
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

//为了调试
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

	//开始计时
	nTimeStart = clock();

 	while (matrix.SureFill() == true);
	matrix.RecordUnsureRegion();

	//递归
	matrix.AkariDFS(matrix.m1,matrix.n1);
	return 0;
}