# matrix-0.0.3
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

bool input(std::ifstream & file,
	float ** & result_elements,
	unsigned int & result_rows,
	unsigned int & result_columns)
{
	unsigned int rows = 0;
	unsigned int columns = 0;
	char symbol;
	float ** elements = nullptr;

	bool success = true;

	string line;
	if (getline(file, line)) {
		istringstream sstream(line);
		if (sstream >> rows && sstream >> symbol && symbol == ',' && sstream >> columns && sstream.eof()) {
			elements = new float *[rows];
			for (unsigned int i = 0; i < rows && success; i++) {
				elements[i] = new float[columns];
				string line;
				if (getline(file, line)) {
					istringstream sstream(line);
					for (unsigned j = 0; j < columns; j++) {
						sstream >> elements[i][j];
						if (!sstream) {
							success = false;
							break;
						}
					}

					success &= sstream.eof();
				}
				else {
					success = false;
				}
			}
		}
		else {
			success = false;
		}
	}

	if (success) {
		result_elements = elements;
		result_rows = rows;
		result_columns = columns;
	}
	

	return success;
}

bool add(float ** lhs_elements,
	unsigned int lhs_rows,
	unsigned int lhs_columns,
	float ** rhs_elements,
	unsigned int rhs_rows,
	unsigned int rhs_columns,
	float ** & result_elements,
	unsigned int & result_rows,
	unsigned int & result_columns) {

	bool success = true;
	float ** elements = new float *[rhs_rows];
	for (int i = 0; i < rhs_rows; i++) {
		elements[i] = new float[rhs_columns];
	}

	result_elements = new float *[rhs_rows];
	for (int i = 0; i < rhs_rows; i++) {
		result_elements[i] = new float[rhs_columns];
	}

	if (lhs_rows == rhs_rows && lhs_columns == rhs_columns) {
		for (int i = 0; i < rhs_rows; i++) {
			for (int j = 0; j < rhs_columns; j++) {
				elements[i][j] = lhs_elements[i][j] + rhs_elements[i][j];
			}
		}
		result_elements = elements;
		result_rows = lhs_rows;
		result_columns = lhs_columns;

	}
	else success = false;
	return success;
}

bool sub(float ** lhs_elements,
	unsigned int lhs_rows,
	unsigned int lhs_columns,
	float ** rhs_elements,
	unsigned int rhs_rows,
	unsigned int rhs_columns,
	float ** & result_elements,
	unsigned int & result_rows,
	unsigned int & result_columns) {

	bool success = true;
	float ** elements = new float *[rhs_rows];
	for (int i = 0; i < rhs_rows; i++) {
		elements[i] = new float[rhs_columns];
	}

	result_elements = new float *[rhs_rows];
	for (int i = 0; i < rhs_rows; i++) {
		result_elements[i] = new float[rhs_columns];
	}

	if (lhs_rows == rhs_rows && lhs_columns == rhs_columns) {
		for (int i = 0; i < rhs_rows; i++) {
			for (int j = 0; j < rhs_columns; j++) {
				elements[i][j] = lhs_elements[i][j] - rhs_elements[i][j];
			}
		}
		result_elements = elements;
		result_rows = lhs_rows;
		result_columns = lhs_columns;

	}
	else success = false;
	return success;
}

bool multiply(float ** lhs_elements,
	unsigned int lhs_rows,
	unsigned int lhs_columns,
	float ** rhs_elements,
	unsigned int rhs_rows,
	unsigned int rhs_columns,
	float ** & result_elements,
	unsigned int & result_rows,
	unsigned int & result_columns) {

	bool success = true;
	float ** elements = new float *[rhs_rows];
	for (int i = 0; i < rhs_rows; i++) {
		elements[i] = new float[lhs_columns];
	}

	if (lhs_columns == rhs_rows) {
		int n = lhs_columns;
		result_elements = new float *[n];
		for (int i = 0; i < n; i++) {
			result_elements[i] = new float[n];
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				elements[i][j] = 0;
				for (int k = 0; k < n; k++)
					elements[i][j] += lhs_elements[i][k] * rhs_elements[k][j];
			}
		}
		result_elements = elements;
		result_rows = rhs_rows;
		result_columns = lhs_columns;

	}
	else success = false;
	return success;
}

bool transpose(float ** lhs_elements,
	unsigned int lhs_rows,
	unsigned int lhs_columns,
	float ** & result_elements,
	unsigned int & result_rows,
	unsigned int & result_columns) {

	bool success = true;
	result_rows = lhs_columns;
	result_columns = lhs_rows;

	result_elements = new float *[result_rows];
	for (int i = 0; i < result_rows; i++) {
		result_elements[i] = new float[result_columns];
	}

	for (int i = 0; i < result_rows; i++) {
		for (int j = 0; j < result_columns; j++) {
			result_elements[i][j] = lhs_elements[j][i];
		}
	}

	return success;
}

void destroy(float ** elements,
	unsigned int rows)
{
	for (unsigned int i = 0; i < rows; ++i) {
		delete[] elements[i];
	}
	delete[] elements;
}


bool reverse(float ** lhs_elements,
	unsigned int lhs_rows,
	unsigned int lhs_columns,
	float ** & result_elements,
	unsigned int & result_rows,
	unsigned int & result_columns) {

	bool success = true;

	result_elements = new float *[lhs_rows];
	for (int i = 0; i < lhs_rows; i++) {
		result_elements[i] = new float[lhs_rows];
	}

	if (lhs_rows == lhs_columns) {
		unsigned int n = lhs_rows;
		float temp;
		float **elements = new float *[n];
		for (unsigned int i = 0; i < n; i++) {
			elements[i] = new float[n];
		}

		for (unsigned int i = 0; i < n; i++) {
			for (unsigned int j = 0; j < n; j++) {
				elements[i][j] = 0;
				if (i == j) {
					elements[i][j] = 1;
				}
			}
		}
		for (unsigned int k = 0; k < n; k++) {
			temp = lhs_elements[k][k];
			for (unsigned int j = 0; j < n; j++) {
				lhs_elements[k][j] /= temp;
				elements[k][j] /= temp;
			}
			for (unsigned int i = k + 1; i < n; i++) {
				temp = lhs_elements[i][k];
				for (unsigned int j = 0; j < n; j++) {
					lhs_elements[i][j] -= lhs_elements[k][j] * temp;
					elements[i][j] -= elements[k][j] * temp;
				}
			}
		}
		for (int k = n - 1; k > 0; k--) {
			for (int i = k - 1; i >= 0; i--) {
				temp = lhs_elements[i][k];
				for (unsigned int j = 0; j < n; j++) {
					lhs_elements[i][j] -= lhs_elements[k][j] * temp;
					elements[i][j] -= elements[k][j] * temp;
				}
			}
		}
		result_elements = elements;
		result_columns = n;
		result_rows = n;
	}
	else success = false;

	return success;
}

double determ(float ** lhs_elements, unsigned int rows)
{
	unsigned int n = rows;
	int i, j;
	double det = 0;
	float ** matr;
	if (n == 1) {
		det = lhs_elements[0][0];
	}
	else if (n == 2) {
		det = lhs_elements[0][0] * lhs_elements[1][1] - lhs_elements[0][1] * lhs_elements[1][0];
	}
	else
	{
		matr = new float*[n - 1];
		for (i = 0; i < n; ++i)
		{
			for (j = 0; j < n - 1; ++j)
			{
				if (j < i)
					matr[j] = lhs_elements[j];
				else
					matr[j] = lhs_elements[j + 1];
			}
			det += pow((double)-1, (i + j))*determ(matr, n - 1) * lhs_elements[i][n - 1];
		}
		delete[] matr;
	}
	return det;
}

auto output(std::ostream & stream,
	float ** elements,
	unsigned int rows,
	unsigned int columns)->std::ostream & {
	cout << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			stream << elements[i][j] << ' ';
		}
		stream << endl;
	}
	return stream;
}

int main()
{
	float ** matrix1;
	unsigned int rows1, columns1;
	string line;
	string filename1, filename2;
	
	char oper;
	if (getline(cin, line)) {
		istringstream stream(line);
		if (stream >> filename1 && stream >> oper) {
			if (stream >> filename2) {
				ifstream file1(filename1);
				ifstream file2(filename2);

				if (input(file1, matrix1, rows1, columns1)) {
					float ** matrix2;
					unsigned int rows2, columns2;
					float ** result;
					unsigned int rows3, columns3;

					switch (oper) {
					case '+':
						if (input(file2, matrix2, rows2, columns2) &&
							add(matrix1, rows1, columns1, matrix2, rows2, columns2, result, rows3, columns3)) {
							output(cout, result, rows3, columns3);
							destroy(matrix2, rows2);
							destroy(result, rows3);
						}
						else cout << "An error has occured while reading input data";

						break;

					case '-':
						if (input(file2, matrix2, rows2, columns2) &&
							sub(matrix1, rows1, columns1, matrix2, rows2, columns2, result, rows3, columns3)) {
							output(cout, result, rows3, columns3);
							destroy(matrix2, rows2);
							destroy(result, rows3);
						}
						else cout << "An error has occured while reading input data";

						break;

					case '*':
						if (input(file2, matrix2, rows2, columns2) &&
							multiply(matrix1, rows1, columns1, matrix2, rows2, columns2, result, rows3, columns3)) {
							output(cout, result, rows3, columns3);
							destroy(matrix2, rows2);
							destroy(result, rows3);
						}
						else cout << "An error has occured while reading input data";

						break;
					}
					destroy(matrix1, rows1);


				}
				else cout << "An error has occured while reading input data";
			}
			else {
				ifstream file1(filename1);

				if (input(file1, matrix1, rows1, columns1)) {
					float ** result;
					unsigned int rows3, columns3;
					switch (oper) {
					case 'T':
						if (transpose(matrix1, rows1, columns1, result, rows3, columns3)) {
							output(cout, result, rows3, columns3);
							destroy(result, rows3);
						}
						break;

					case 'R':
						double det = determ(matrix1, rows1);
						if (reverse(matrix1, rows1, columns1, result, rows3, columns3) && det != 0) {
							output(cout, result, rows3, columns3);
							destroy(result, rows3);
						}
						else cout << "There is no reverse matrix";
						break;
					}
					destroy(matrix1, rows1);

				}
				else cout << "An error has occured while reading input data";
			}
		}
		else cout << "An error has occured while reading input data";
	}
	else cout << "An error has occured while reading input data";

	cin.get();
	cin.get();
	return 0;
}
