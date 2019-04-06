#include "Matrix.h"
#include "Exception.h"
#define ZERO 0.0001

MyMatrix::MyMatrix()
{
}

int MyMatrix::row()
{
	return this->data.size();
}

MyVector & MyMatrix::operator[](int index)
{
	return this->data[index];
}

std::ostream& operator<<(std::ostream& os, MyMatrix& m) {
	for (int i = 0; i < m.row(); i++)
	{
		for (int j = 0; j < m.col(); j++)
		{
			os << m[i][j] << " ";
		}
		os << std::endl;
	}
	return os;
};

int MyMatrix::col()
{
	return this->data[0].dimension();
}

MyMatrix add(MyMatrix a, MyMatrix b)
{
	if (a.col() != b.col() || a.row() != b.row())
		throw Exceptions(dimension);

	MyMatrix m;
	for (int i = 0; i < a.row(); i++)
	{
		MyVector v;
		for (int j = 0; j < a.col(); j++)
		{
			v.data.push_back(a[i][j] + b[i][j]);
		}
		m.data.push_back(v);
	}
	return m;
}

MyMatrix sub(MyMatrix a, MyMatrix b)
{
	if (a.col() != b.col() || a.row() != b.row())
		throw Exceptions(dimension);

	MyMatrix m;
	for (int i = 0; i < a.row(); i++)
	{
		MyVector v;
		for (int j = 0; j < a.col(); j++)
		{
			v.data.push_back(a[i][j] - b[i][j]);
		}
		m.data.push_back(v);
	}
	return m;
}

MyMatrix mul(MyMatrix a, MyMatrix b)
{
	MyMatrix m;
	if (a.col() != b.row())
	{
		throw Exceptions(dimension);
	}
	else
		for (int i = 0; i < a.row(); i++)
		{
			MyVector v;
			for (int j = 0; j < b.col(); j++)
			{
				v.data.push_back(0);
				for (int k = 0; k < a.col(); k++)
				{
					v[j] += a[i][k] * b[k][j];
				}
			}
			m.data.push_back(v);
		}
	return m;
}

int rank(MyMatrix m)
{
	int r = m.row();
	m = GaussianElimination(m);
	for (int i = 0; i < m.row(); i++)
	{
		if (m[i].isZero() == true) r--;
	}
	return r;
}

MyMatrix GaussianElimination(MyMatrix m)
{
	/* old version
	double zero = 0.001;
	MyVector temp;
	int x = 0, y = 0;
	int i, j;
	while (x < m.row() && y < m.col())
	{
		while (x < m.row() && m[y][x] < zero && m[y][x]>(-zero))
		{
			j = y + 1;
			while (j < m.col() && m[j][x]<zero && m[j][x]>(-zero)) j++;

			if (j >= m.col())
			{
				x++;
				continue;
			}
			temp = m[j];
			m[j] = m[y];
			m[y] = temp;
			break;
		}
		if (x >= m.row())break;
		
		for (i = m.row() - 1; i > x; i--)
		{
			m[y][i] /= m[y][x];
		}
		m[y][x] = 1;
		
		for (j = 0; j < m.col(); j++)
		{
			if (j == y)continue;
			for (i = m.row() - 1; i >= x; i--)
				m[j][i] -= m[y][i] * m[j][x];
		}
		x++; y++;
	}
	return m;
	*/

	MyVector v;
	for (int i = 0; i < m.row(); i++)
	{
		int temp = i;
		while (temp < m.row() && abs(m[temp][i]) < ZERO)temp++;
		
		if (temp == m.row())break;
		
		v = m[i];
		m[i] = m[temp];
		m[temp] = v;

		for (int j = i + 1; j < m.row(); j++)
		{
			double radio = m[j][i] / m[i][i];
			for (int k = 0; k < m.col(); k++)
			{
				m[j][k] -= m[i][k] * radio;
			}
		}

	}
	return m;
}

MyMatrix transpose(MyMatrix m)
{
	MyMatrix t;
	for (int i = 0; i < m.col(); i++)
	{
		MyVector v;
		for (int j = 0; j < m.row(); j++)
		{
			v.data.push_back(m[j][i]);
		}
		t.data.push_back(v);
	}
	return t;
}

double Determinants(MyMatrix m)
{
	/* TLE
	double d = 0;
	if (m.col() != m.row())
	{
		//error
	}
	else if (m.col() == 2)
	{
		return m[0][0] * m[1][1] - m[0][1] * m[1][0];
	}
	else
	{
		for (int i = 0; i < m.row(); i++)
		{
			MyMatrix temp;
			for (int j = 1; j < m.col(); j++)
			{
				MyVector v;
				for (int k = 0; k < m.row(); k++)
				{
					if (k != i) v.data.push_back(m[j][k]);
				}
				temp.data.push_back(v);
			}
			d += m[0][i] * Determinants(temp) * pow(-1,i);
		}
	}
	return d;
	*/

	double d = 1;
	if (m.row() != m.col())
	{
		throw Exceptions(rowNotEqualCol);
	}
	else if (m.row() == 2)
	{
		return m[0][0] * m[1][1] - m[0][1] * m[1][0];
	}
	else
	{
		m = GaussianElimination(m);
		for (int i = 0; i < m.row(); i++)
		{
			d *= m[i][i];
		}
	}
	return d;
}

//The matrix do not push c column and r row.
MyMatrix subMatrix(MyMatrix m, int c, int r)
{
	MyMatrix s;
	for (int i = 0; i < m.row(); i++)
	{
		MyVector v;
		for (int j = 0; j < m.col(); j++)
		{
			if (j != r)v.data.push_back(m[i][j]);
		}
		if (i != c) s.data.push_back(v);
	}
	return s;
}

MyMatrix Adjoint(MyMatrix m)
{
	MyMatrix adj;
	for (int i = 0; i < m.row(); i++)
	{
		MyVector v;
		for (int j = 0; j < m.col(); j++)
		{
			v.data.push_back(pow(-1, j + i) * Determinants(subMatrix(m, j, i)));
		}
		adj.data.push_back(v);
	}
	return adj;
}

MyMatrix Inverse(MyMatrix m)	//some error number and TLE when size too large
{
	MyMatrix inv;
	double d = Determinants(m);
	if (d == 0)
	{
		throw Exceptions(noInverse);
	}
	else
	{
		inv = Adjoint(m);
		d = 1 / d;
		for (int i = 0; i < inv.row(); i++)
		{
			for (int j = 0; j < inv.col(); j++)
			{
				inv[i][j] *= d;
			}
		}
	}
	return inv;
}

MyMatrix SolveLinearSystem(MyMatrix a, MyMatrix b)	//TLE when size too large.
{
	if (a.row() != b.row() || b.col() != 1)
	{
		throw Exceptions(dimension);
	}

	MyMatrix inv = Inverse(a);
	MyMatrix ans = mul(inv,b);
	return ans;
}

MyMatrix LeastSquare(MyMatrix x, MyMatrix y)	//TLE when size too large.
{
	MyMatrix tx = transpose(x);
	MyMatrix s = mul(tx, x);
	return mul(mul(Inverse(s), tx), y);
}

void FindEigen(MyMatrix m, MyMatrix& eigenVector, MyMatrix& eigenValue)
{
	if (m.col() == 2 && m.row() == 2)
	{
		
	}
	else if (m.col() == 3 && m.row() == 3)
	{

	}
	else
	{
		//???
	}
}

void PowerMethod(MyMatrix m, MyMatrix& eigenVector, MyMatrix& eigenValue)
{
	if (m.col() != m.row())
	{
		throw Exceptions(dimension);
	}
	MyMatrix guess;
	double error;
	for (int i = 0; i < m.row(); i++)
	{
		MyVector v;
		v.data.push_back(1);
		guess.data.push_back(v);
	}

	do
	{
		MyMatrix newGuess = mul(m, guess);

		error = guess[1][0] / guess[0][0] - newGuess[1][0] / newGuess[0][0];
		guess = newGuess;
	} while (abs(error) > ZERO);

	for (int i = 1; i < guess.row(); i++)
	{
		guess[i][0] /= guess[0][0];
	}
	guess[0][0] = 1;

	eigenVector = mul(transpose(mul(m, guess)), guess);
	eigenValue = mul(transpose(guess), guess);
	eigenValue[0][0] = eigenVector[0][0] / eigenValue[0][0];
	eigenVector = guess;
}