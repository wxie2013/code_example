struct base {
	base() {;}
	float a;
	int b;
	void print1() {cout<<"a: "<<a<<" b: "<<b<<endl;}
};

struct dau1: base {
	dau1() {base();} 
	//dau1() {;}  // don't see any difference this way
	int c;;
	void print() {cout<<"c: "<<c<<endl;}
};

void struct_inherit()
{
	dau1* t1 = new dau1;
	t1->a = 1.0;
	t1->b = 2;
	t1->c = 3;
	t1->print();
	t1->print1();
}
