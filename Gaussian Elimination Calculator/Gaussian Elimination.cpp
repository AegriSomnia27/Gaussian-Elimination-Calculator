#include <iostream>
using namespace std;

double** createMatrix(int n);
void initializeMatrix(double** m, int n);
void reduceToEchelonForm(double** m, int n);
double* computeMatrix(double** m, int n);
void showResults(double* m, int n);
void bubbleSort(double** m1, int n);
void order(double** d1, double** d2);
void showEchelonMatrixForm(double** m, int n);
void freeMemory(double**, int n);
void freeMemory(double*, int n);

int main() {
	int unknownVariablesNumber = 0;
	double** matrix;
	double* answerVector;

	cout << "Enter the number of unknown variables: ";
	cin >> unknownVariablesNumber;
	matrix = createMatrix(unknownVariablesNumber);

	cout << "Enter the coefficients and the constant terms of the matrix: " << endl;
	initializeMatrix(matrix, unknownVariablesNumber);

	reduceToEchelonForm(matrix, unknownVariablesNumber);
	answerVector = computeMatrix(matrix, unknownVariablesNumber);
	showResults(answerVector, unknownVariablesNumber);
	freeMemory(matrix, unknownVariablesNumber);
	freeMemory(answerVector, unknownVariablesNumber);

	return 0;
}

double** createMatrix(int unknownVariablesNumber) {
	double** matrix = new double* [unknownVariablesNumber];
	for (int i = 0; i < unknownVariablesNumber; i++) {
		matrix[i] = new double[unknownVariablesNumber + 1];
	}
	return matrix;
}

void initializeMatrix(double** matrix, int unknownVariablesNumber) {
	double coefficient = 0;
	for (int i = 0; i < unknownVariablesNumber; i++) {
		for (int j = 0; j < unknownVariablesNumber + 1; j++) {
			if (j < unknownVariablesNumber) {
				cout << "a[" << i << "][" << j << "] = ";
				cin >> coefficient;
				matrix[i][j] = coefficient;
			}
			else if (j < unknownVariablesNumber + 1) {
				cout << "b[" << i << "] = ";
				cin >> coefficient;
				matrix[i][j] = coefficient;
			}
		}
	}
}

void reduceToEchelonForm(double** matrix, int unknownVariablesNumber) {
	double matrixPivotElement;
	bubbleSort(matrix, unknownVariablesNumber);
	for (int j = 0; j < unknownVariablesNumber; j++) {
		for (int i = j + 1; i < unknownVariablesNumber; i++) {
			matrixPivotElement = matrix[i][j] / matrix[j][j];
			for (int k = j; k < unknownVariablesNumber; k++) {
				matrix[i][k] -= matrixPivotElement * matrix[j][k];
			}
			matrix[i][unknownVariablesNumber] -= matrixPivotElement * matrix[j][unknownVariablesNumber];
		}
	}
	showEchelonMatrixForm(matrix, unknownVariablesNumber);
	cout << endl << endl;
}

double* computeMatrix(double** matrix, int unknownVariablesNumber) {
	double totalSystemSum = 0;
	double vectorAndMatrixElementMultiplyingResult;
	double* answerVector = new double[unknownVariablesNumber];
	for (int i = 0; i < unknownVariablesNumber; i++) {
		answerVector[i] = 1;
	}

	for (int i = unknownVariablesNumber - 1; i >= 0; i--) {
		totalSystemSum = 0;
		for (int j = i + 1; j < unknownVariablesNumber; j++) {
			vectorAndMatrixElementMultiplyingResult = matrix[i][j] * answerVector[j];
			totalSystemSum += vectorAndMatrixElementMultiplyingResult;
		}
		answerVector[i] = (matrix[i][unknownVariablesNumber] - totalSystemSum) / matrix[i][i];
	}

	return answerVector;
}

void bubbleSort(double** matrix, int unknownVariablesNumber) {
	for (int i = 0; i < unknownVariablesNumber - 1; i++) {
		for (int j = i + 1; j < unknownVariablesNumber; j++) {
			order(matrix + i, matrix + j);
		}
	}
}

void order(double** dblNumb1, double** dblNumb2) {
	if (**dblNumb1 < **dblNumb2) {
		double* temp = *dblNumb1;
		*dblNumb1 = *dblNumb2;
		*dblNumb2 = temp;
	}
}

void showResults(double* answerVector, int unknownVariablesNumber) {
	for (int i = 0; i < unknownVariablesNumber; i++) {
		cout << "x[" << i << "] = " << *(answerVector + i) << endl;
	}
	cout << endl;
}

void showEchelonMatrixForm(double** matrix, int unknownVariablesNumber) {
	cout << endl;
	for (int i = 0; i < unknownVariablesNumber; i++) {
		for (int j = 0; j < unknownVariablesNumber + 1; j++) {
			cout << "a[" << i << "][" << j << "] = " << matrix[i][j] << "   ";
		}
		cout << endl;
	}
}

void freeMemory(double** matrix, int unknownVariablesNumber) {
	for (int i = 0; i < unknownVariablesNumber; i++) {
		delete[] matrix[i];
		cout << "matrix row [" << i << "] has been deleted" << endl;
	}
	delete[] matrix;
	cout << "matrix has been deleted" << endl << endl;
}

void freeMemory(double* vector, int unknownVariablesNumber) {
	delete[] vector;
	cout << "Answer vector has been deleted";
}