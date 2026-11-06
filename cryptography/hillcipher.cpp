// Hill cipher encryption and decryption using A=0, ..., Z=25.
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using Matrix = std::vector<std::vector<int>>;
constexpr int MOD = 26;
const std::string plaintext = "LUCIDMOON";

int mod(int value) {
	value %= MOD;
	return value < 0 ? value + MOD : value;
}

// Cofactor expansion is suitable for the small matrices used as Hill keys.
int determinant(const Matrix& matrix) {
	const int n = static_cast<int>(matrix.size());
	if (n == 1) return mod(matrix[0][0]);

	int result = 0;
	for (int col = 0; col < n; ++col) {
		Matrix minor(n - 1, std::vector<int>(n - 1));
		for (int row = 1; row < n; ++row) {
			int minorCol = 0;
			for (int sourceCol = 0; sourceCol < n; ++sourceCol) {
				if (sourceCol != col) minor[row - 1][minorCol++] = matrix[row][sourceCol];
			}
		}
		result = mod(result + (col % 2 ? -1 : 1) * matrix[0][col] * determinant(minor));
	}
	return result;
}

int modularInverse(int value) {
	for (int candidate = 1; candidate < MOD; ++candidate) {
		if (mod(value * candidate) == 1) return candidate;
	}
	throw std::invalid_argument("Key matrix is not invertible modulo 26");
}

void validateKey(const Matrix& key) {
	if (key.empty()) throw std::invalid_argument("Key matrix cannot be empty");
	for (const auto& row : key) {
		if (row.size() != key.size()) throw std::invalid_argument("Key matrix must be square");
	}
	// The determinant must have a multiplicative inverse modulo 26.
	const int det = determinant(key);
	if (det % 2 == 0 || det % 13 == 0)
		throw std::invalid_argument("Key matrix is not invertible modulo 26");
}

Matrix inverseMatrix(const Matrix& key) {
	validateKey(key);
	const int n = static_cast<int>(key.size());
	const int detInverse = modularInverse(determinant(key));
	Matrix inverse(n, std::vector<int>(n));

	if (n == 1) {
		inverse[0][0] = detInverse;
		return inverse;
	}

	// The inverse is the transposed cofactor matrix times the inverse determinant.
	for (int row = 0; row < n; ++row) {
		for (int col = 0; col < n; ++col) {
			Matrix minor(n - 1, std::vector<int>(n - 1));
			int minorRow = 0;
			for (int sourceRow = 0; sourceRow < n; ++sourceRow) {
				if (sourceRow == col) continue;
				int minorCol = 0;
				for (int sourceCol = 0; sourceCol < n; ++sourceCol) {
					if (sourceCol != row) minor[minorRow][minorCol++] = key[sourceRow][sourceCol];
				}
				++minorRow;
			}
			const int sign = (row + col) % 2 ? -1 : 1;
			inverse[row][col] = mod(detInverse * sign * determinant(minor));
		}
	}
	return inverse;
}

std::string lettersOnly(const std::string& text) {
	std::string result;
	for (unsigned char ch : text) {
		if (ch >= 'a' && ch <= 'z') result += static_cast<char>(ch - 'a' + 'A');
		else if (ch >= 'A' && ch <= 'Z') result += static_cast<char>(ch);
	}
	return result;
}

std::string transform(const std::string& text, const Matrix& matrix, bool pad) {
	validateKey(matrix);
	std::string input = lettersOnly(text);
	const std::size_t blockSize = matrix.size();
	// Encryption pads incomplete blocks with X; decryption preserves that padding.
	if (pad) {
		while (input.size() % blockSize != 0) input += 'X';
	} else if (input.size() % blockSize != 0) {
		throw std::invalid_argument("Ciphertext length must be a multiple of key size");
	}

	std::string output;
	for (std::size_t offset = 0; offset < input.size(); offset += blockSize) {
		for (std::size_t row = 0; row < blockSize; ++row) {
			int value = 0;
			for (std::size_t col = 0; col < blockSize; ++col)
				value += matrix[row][col] * (input[offset + col] - 'A');
			output += static_cast<char>('A' + mod(value));
		}
	}
	return output;
}

std::string encrypt(const std::string& plaintext, const Matrix& key) {
	return transform(plaintext, key, true);
}

std::string decrypt(const std::string& ciphertext, const Matrix& key) {
	return transform(ciphertext, inverseMatrix(key), false);
}

int main() {
	// Example invertible 3x3 key; the result for ACT is POH.
	const Matrix key = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}};
	try {
		const std::string ciphertext = encrypt(plaintext, key);
		std::cout << "Plaintext:  " << plaintext << '\n'
				  << "Ciphertext: " << ciphertext << '\n'
				  << "Decrypted:  " << decrypt(ciphertext, key) << '\n';
	} catch (const std::exception& error) {
		std::cerr << "Error: " << error.what() << '\n';
		return 1;
	}
	return 0;
}
