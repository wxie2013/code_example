//Pointers: A pointer is a variable that holds memory address of another variable. A pointer needs to be dereferenced with * operator to access the memory location it points to.
//References : A reference variable is an alias, that is, another name for an already existing variable. A reference, like a pointer is also implemented by storing the address of an object.  A reference can be thought of as a constant pointer (not to be confused with a pointer to a constant value!) with automatic indirection, i.e the compiler will apply the * operator for you.

/*
int i = 3;

// A pointer to variable i (or stores address of i)
int *ptr = &i;

// A reference (or alias) for i.
int &ref = i;
*/


/*
Initalisation: A pointer can be initalised in this way:
 int a = 10;
  int *p = &a;
         OR
     int *p;
   p = &a;
we can declare and initalise pointer at same step or in multiple line.

While in refrences,

int a=10;
int &p=a;  //it is correct
   but
int &p;
 p=a;    // it is incorrect as we should declare and initialise references at single step.

*/

/*
Reassignment: A pointer can be re-assigned. This property is useful for implementation of data structures like linked list, tree, etc. See the following examples:
int a = 5;
int b = 6;
int *p;
p =  &a;
p = &b;

On the other hand, a reference cannot be re-assigned, and must be assigned at initialization.
int a = 5;
int b = 6;
int &p = a;
int &p = b;  //At this line it will show error as "multiple declaration is not allowed".

However it is valid statement,
int &q=p;

Memory Address: A pointer has its own memory address and size on the stack whereas a reference shares the same memory address (with the original variable) but also takes up some space on the stack.
NOTE However if we want true address of reference, then it can be found out in turbo IDE by writting the following statement,

   int &p = a;
   cout << &(&p);


NULL value: Pointer can be assigned NULL directly, whereas reference cannot. The constraints associated with references (no NULL, no reassignment) ensure that the underlying operations do not run into exception situation.

Indirection: You can have pointers to pointers offering extra levels of indirection. Whereas references only offer one level of indirection.I.e, In Pointers,
int a = 10;
int *p;
int **q;  //it is valid.
p = &a;
q = &p;

Whereas in refrences,

int &p = a;
int &&q = p; //it is reference to reference, so it is an error.

When to use What

The performances are exactly the same, as references are implemented internally as pointers. But still you can keep some points in your mind to decide when to use what :

Use references
In function parameters and return types.
Use pointers:
Use pointers if  pointer arithmetic or passing NULL-pointer is needed. For example for arrays (Note that array access is implemented using pointer arithmetic).
To implement data structures like linked list, tree, etc and their algorithms because to point different cell,we have to use the concept of pointers.
For Example,
In Pointers

int arr[] = {10,20,30};
int &p = arr[0];
int i;
for(i = 0; i<3 ; i++)
{
cout << p << endl;
p++;  //here it will increament arr[0]++
}


Output:

10
20
30
NOTE: Here pointer will be ahead of base address

Now take same code in Reference

int arr[] = {10,20,30};
int &p = arr[0];
int i;
for(i = 0; i<3 ; i++)
{
cout << p << endl;
p++;  //here it will increament arr[0]++
}
Output:

10
11
12

*/
