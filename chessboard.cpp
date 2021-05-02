#include <iostream>
#include <stdexcept>
#include <iomanip>
using namespace std;

class ChessBoardArray
{
protected:
	int* data;
	int the_base;
	unsigned the_size;
	unsigned loc(int i, int j)const throw(out_of_range) {
		int di = i - the_base, dj = j - the_base;
		if (di < 0 || di >= the_size || dj < 0 || dj >= the_size || (i + j) % 2 == 1)
			throw out_of_range("invalid index");
		return (di * the_size + dj) / 2;
	}
	class Row
	{
	public:
		Row(ChessBoardArray& a, int i)
			:array(a), row(i) {}
		int& operator [](int i) const {
			return array.select(row, i);
		}

	private:
		ChessBoardArray& array;
		int row;
	};
	class ConstRow
	{
	public:
		ConstRow(const ChessBoardArray& a, int i)
			:array(a), row(i) {}
		const int operator [](int i) const {
			return array.select(row, i);
		}
	private:
		const ChessBoardArray& array;
		int row;
	};

public:
	ChessBoardArray(unsigned size =0, unsigned base =0): data(new int[(size*size+1)/2]),the_size(size),the_base(base){}
	ChessBoardArray(const ChessBoardArray& a)
		:data(new int[(a.the_size * a.the_size + 1) / 2]), the_size(a.the_size), the_base(a.the_base) {
		for (unsigned i = 0; i < (the_size * the_size + 1) / 2; ++i)
			data[i] = a.data[i];
	}
	~ChessBoardArray() { delete [] data; }

	ChessBoardArray& operator =(const ChessBoardArray& a) {
		delete[] data;
		the_base = a.the_base;
		the_size = a.the_size;
		data = new int[(the_size * the_size + 1) / 2];
		for (unsigned i = 0; i < ((the_size * the_size + 1) / 2); ++i) {
			data[i] = a.data[i];
		}
		return *this;
	}

	int& select(int i, int j) {
		return data[loc(i, j)];
	}
	int select(int i, int j) const {
		return data[loc(i, j)];
	}
	const Row operator [] (int i) {
		return Row(*this, i);
	}
	const ConstRow operator [] (int i) const {
		return ConstRow(*this, i);
	}
	/*
	friend ostream& operator << (ostream& out, const ChessBoardArray& a) {
		for (int line = 0; line < a.the_size; ++line) {
			for (int sthlh = 0; sthlh < a.the_size; ++sthlh) {
				cout << setw(4);
				if ((line + sthlh) % 2 == 0)
					cout << a.select(line + a.the_base, sthlh + a.the_base);
				else cout << 0;
			}
			cout << endl;
		}
		return out;
	}
	*/
	
	friend ostream& operator <<(ostream& out, const ChessBoardArray& a) {
		int j = 0;
		for (unsigned i = 0; i < (a.the_size * a.the_size); ++i) {
			if (i % a.the_size == 0 && i != 0) out << endl;
			out << setw(4);
			if (i % 2 == 1) {
				out << 0;
				continue;
			}
			else {
				out <<a.data[j];
				j++;
			}
		}
		return out;
	}
	

};

/*
int main()
{
	ChessBoardArray a(4, 1); // size 4x4, rows and columns numbered from 1
	a[3][1] = 42;
	a[4][4] = 17;
	try { a[2][1] = 7; }
	catch (out_of_range& e) { cout << "a[2][1] is black" << endl; }
	try { cout << a[1][2] << endl; }
	catch (out_of_range& e) { cout << "and so is a[1][2]" << endl; }
	cout << a;

    
}
*/
