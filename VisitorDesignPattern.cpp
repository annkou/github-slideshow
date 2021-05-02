//VISITOR DESIGN PATTERN 
template <typename T>
class Visitor 
{
public:
	Visitor ();
	virtual ~Visitor() {}
	virtual void visit(T& x) = 0;
	virtual bool finished() const { return false; }
private:

};
template <typename T>
class Visitable
{
public:
	Visitable();
	~Visitable();
	virtual void accept(Visitor<T>& visitor) = 0;

private:

};
class AddingVisitor: public Visitor<int> 
{
public:
	AddingVisitor(): sum(0){}
	int getSum() const { return sum; }
	void visit(int& x) override { sum += x; }
private:
	int sum;
};

// mesa sti lista sto public part katw katw 
void accept(Visitor<T>& visitor) override {
	for (node* p = the_front; p != nullptr; p = p->next) {
		if (visitor.finished()) return;
		visitor.visit(p->data);
	}
}
template <typename T>
class PrintingVisitor: public Visitor<T> 
{
public:
	void visit(T& x) override { cout << x << endl; }
private:

};
class PZsearchingVisitor: public Visitor <int>
{
public:
	PZsearchingVisitor : found(false) {}
	void visit(int& x) override {
		if (17 <= x && x <= 42) { found = true; value = x; }
	}
	bool finished() const override { return found; }
	bool getFound() const { return found; }
	int getValue() const { return value; }
private:
	bool found;
	int value;
};

