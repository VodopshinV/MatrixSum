#include<iostream>
#include<exception>
#include<vector>
using namespace std;

class Matrix
{
public:
	Matrix()
	{
		num_rows = 0;
		num_cols = 0;
	}

	Matrix(int new_rows, int new_cols)
	{
		Reset(new_rows, new_cols);
	}

	void Reset(int new_rows,int new_cols)
	{
		if (new_rows < 0 || new_cols < 0)
		{
			throw out_of_range("out of range");
		}
		
		if (new_rows == 0 || new_cols == 0)
		{
			new_rows = new_cols = 0;
		}

		num_rows = new_rows;
		num_cols = new_cols;
		elements.assign(new_rows, vector<int>(new_cols));
	}

	int At(int row, int col) const
	{
		return elements.at(row).at(col);
	}

	int& At(int row, int col)
	{
		return elements.at(row).at(col);
	}

	int GetNumRows() const
	{
		return num_rows;
	}

	int GetNumColumns()const
	{
		return num_cols;
	}

private:
	int num_rows;
	int num_cols;
	vector<vector<int>> elements;
};

istream& operator>>(istream& in, Matrix& matrix)
{
	int rows_num, cols_num;
	in >> rows_num>>cols_num;

	matrix.Reset(rows_num,cols_num);

	for (int i = 0; i < rows_num; i++)
	{
		for (int j = 0; j < cols_num; j++)
		{
			in >> matrix.At(i, j);
		}
	}
	return in;
};

ostream& operator<<(ostream& out, const Matrix& matrix)
{
	out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;

	for (int i = 0; i < matrix.GetNumRows(); i++)
	{
		for (int j = 0; j < matrix.GetNumColumns(); j++)
		{
			if (j > 0)
			{
				out << " ";
			}
			out<<matrix.At(i,j);
		}
		out << endl;
	}
	return out;
}

bool operator==(const Matrix& lhs, const Matrix& rhs)
{
	if (lhs.GetNumColumns() != rhs.GetNumColumns() || lhs.GetNumRows() != rhs.GetNumRows())
	{
		return false;
	}

	for (int i = 0; i < lhs.GetNumRows(); i++)
	{
		for (int j = 0; j < lhs.GetNumColumns(); j++)
		{
			if (lhs.At(i, j) != rhs.At(i, j))
			{
				return false;
			}
		}
	}

	return true;
}

Matrix operator+(const Matrix& lhs,const Matrix& rhs)
{
	if (lhs.GetNumColumns() != rhs.GetNumColumns() || lhs.GetNumRows() != rhs.GetNumRows())
	{
		throw invalid_argument("invalid argument");
	}
	
	Matrix result_matrix(lhs.GetNumRows(),lhs.GetNumColumns());

	for (int i = 0; i < lhs.GetNumRows(); i++)
	{
		for (int j = 0; j < lhs.GetNumColumns(); j++)
		{
			result_matrix.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
		}
	}

	return result_matrix;
}

int main() {
	Matrix one;
	Matrix two;

	cin >> one >> two;
	cout << one + two << endl;

	return 0;
}