
#include <iostream>
using namespace std;

class Polynomial
{
protected:
	class Term {
	public:

		int exponent;
		int  coefficient;
		Term* next;
		Term(int exp, int coeff, Term* n) :exponent(exp), coefficient(coeff), next(n) {}
		friend class Polynomial;
};
	Term* front;
public:
	Polynomial() : front(nullptr) {}
	Polynomial(const Polynomial& p) : front(nullptr) { copy(p); }

	~Polynomial() { purge(); }
	Polynomial& operator =(const Polynomial& p) {
		clear(); copy(p); return *this;
	}
	void clear() {
		purge();
		front = nullptr;
	}
	void remove(int exp) {// afairesi stoixeiou
		Term* prev = nullptr;
		Term* p = front;
		if (front == nullptr) return;
		else {
			
			if (exp == front->exponent) {
				front = front->next;
				delete p;
			}
			else {
				for (p = front; (p->next != nullptr && p->exponent!=exp); p = p->next) {
					prev = p;
					
				}
				if (p->exponent == exp) {
					prev->next = p->next;
					delete p;

				}
				else return;
			}
		}
	}
	void addTerm(int expon, int coeff) {
		if (expon < 0 || coeff == 0) return;
		if (front == nullptr) {
			Term* newTerm = new Term(expon, coeff, nullptr);
			front = newTerm;
			return;
		}
		else if (expon > front->exponent) {
			Term* newTerm = new Term(expon, coeff, nullptr);
			newTerm->next = front;
			front = newTerm;
			return;
		}
		else if (expon == front->exponent) {
			front->coefficient = front->coefficient + coeff;
			if (front->coefficient == 0) remove(front->exponent);
			return;
		}
		else {
			Term* p = front;
			while (p->next != nullptr) {
				if (expon == p->exponent) {
					p->coefficient = p->coefficient + coeff;
					if (p->coefficient == 0) remove(p->exponent);
					return;
				}
				else if (expon > p->next->exponent) {
					Term* newTerm = new Term(expon, coeff, nullptr);
					newTerm->next = p->next;
					p->next = newTerm;
					return;
				}
				p = p->next;
			}
			if (expon == p->exponent) {
				p->coefficient = p->coefficient + coeff;
				if (p->coefficient == 0) remove(p->exponent);
				return;
			}
			else {
				Term* newTerm = new Term(expon, coeff, nullptr);
				p->next = newTerm;
				return;
			}
			return;
		}
	}
	double evaluate(double x) {
		Term* list = front;
		double sum = 0;
		for (list = front; list != nullptr; list = list->next) {
			double value = 1;
			if (list->exponent == 0) value = 1;
			else {
				for (int i = 0; i < list->exponent; ++i)
					value *= x;
			}
			sum += value * (list->coefficient);

		}
		return sum;
	}
	friend Polynomial operator + (const Polynomial& p, const Polynomial& q) {
		Polynomial newlist;
		Polynomial::Term* temp1 = p.front;
		Polynomial::Term* temp2 = q.front;
		while (!(temp1 == nullptr && temp2 == nullptr)) {
			if (temp1 == nullptr && temp2 != nullptr) {
				newlist.addTerm(temp2->exponent, temp2->coefficient);
				temp2 = temp2->next;
				continue;
			}
			else if (temp1 != nullptr && temp2 == nullptr) {
				newlist.addTerm(temp1->exponent, temp1->coefficient);
				temp1 = temp1->next;
				continue;
			}
			else if (temp1->exponent == temp2->exponent) {
				newlist.addTerm(temp1->exponent, temp1->coefficient + temp2->coefficient);
				temp1 = temp1->next;
				temp2 = temp2->next;
				continue;
			}
			else if (temp1->exponent > temp2->exponent) {
				newlist.addTerm(temp1->exponent, temp1->coefficient);
				temp1 = temp1->next;
				continue;
			}
			else if (temp1->exponent < temp2->exponent) {
				newlist.addTerm(temp2->exponent, temp2->coefficient);
				temp2 = temp2->next;
				continue;
			}
		}
		return newlist;
	}
	friend Polynomial operator * (const Polynomial& p, const Polynomial& q) {
		Polynomial r;
		for (Term* i = p.front; i != nullptr; i = i->next) {
			for (Term* j = q.front; j != nullptr; j = j->next) {
				r.addTerm(i->exponent + j->exponent, i->coefficient * j->coefficient);
			}
		}
		return r;
	}
	friend ostream& operator << (ostream& out, const Polynomial& p) {
		if (p.front == nullptr) {
			out << "0";
			return out;
		}
		for (Polynomial::Term* i = p.front; i != nullptr; i = i->next) {
			if (i == p.front) {
				if (i->exponent == 0) {
					if (i->coefficient < 0) out << "- " << -(i->coefficient);
					else if (i->coefficient > 0) out << i->coefficient;
				}
				else if (i->exponent == 1) {
					if (i->coefficient < 0) {
						if (i->coefficient == -1) out << "- " << "x";
						else  out << "- " << -(i->coefficient) << "x";
					}
					else if (i->coefficient > 0) {
						if (i->coefficient == 1) out << "x";
						else out << i->coefficient << "x";
					}
				}
				else if (i->exponent > 1) {
					if (i->coefficient < 0) {
						if (i->coefficient == -1) out << "- " << "x^" << i->exponent;
						else out << "- " << -(i->coefficient) << "x^" << i->exponent;
					}
					else if (i->coefficient > 0) {
						if (i->coefficient == 1) out << "x^" << i->exponent;
						else out << i->coefficient << "x^" << i->exponent;
					}
				}
			}
			else {
				if (i->exponent == 0) {
					if (i->coefficient < 0) out << " - " << -(i->coefficient);
					else if (i->coefficient > 0) out << " + " << i->coefficient;
				}
				else if (i->exponent == 1) {
					if (i->coefficient < 0) {
						if (i->coefficient == -1) out << " - " << "x";
						else out << " - " << -(i->coefficient) << "x";
					}
					else if (i->coefficient > 0) {
						if (i->coefficient == 1) out << " + " << "x";
						else out << " + " << i->coefficient << "x";
					}
				}
				else if (i->exponent > 1) {
					if (i->coefficient < 0) {
						if (i->coefficient == -1) out << " - " << "x^" << i->exponent;
						else out << " - " << -(i->coefficient) << "x^" << i->exponent;
					}
					else if (i->coefficient > 0) {
						if (i->coefficient == 1) out << " + " << "x^" << i->exponent;
						else out << " + " << i->coefficient << "x^" << i->exponent;
					}
				}
			}
		}
		//out<<"\n";  
		return out;
	}


private:
	void copy(const Polynomial& p) {
		for (Term* q = p.front; q != nullptr; q = q->next)
			addTerm(q->exponent, q->coefficient);
	}
	void purge() {
		Term* p = front;
		while (p != nullptr) {
			Term* q = p;
			p = p->next;
			delete q;
		}
	}
};


/*
int main()
{
	Polynomial p; // 0
	p.addTerm(1, 3); // 3x
	p.addTerm(2, 1); // x^2
	p.addTerm(0, -1); // -1
	Polynomial q(p); // x^2 + 3x - 1
	q.addTerm(1, -3); // -3x
	cout << "P(x) = " << p << endl;
	cout << "P(1) = " << p.evaluate(1) << endl;
	cout << "Q(x) = " << q << endl;
	cout << "Q(1) = " << q.evaluate(1) << endl;
	cout << "(P + Q)(x) = " << p + q << endl;
	cout << "(P * Q)(x) = " << p * q << endl;

}
*/