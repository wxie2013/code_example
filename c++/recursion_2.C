#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>

const int n_child= 2;

using namespace std;
class Node
{
    public:
        int id;
        vector<Node *> child; 

    public:
        Node():id{0} {;}
        void init(int n_gen, int N);
        void print();


        //
};

//
void Node::init(int n_gen, int N)
{//. use recursion

    id=N;

    if(n_gen!=0) {
        for(int i = 0; i<n_child; i++) {
            Node *node = new Node;
            child.push_back(node);
        }

        for(int i = 0; i<child.size(); i++) {
            child[i]->init(n_gen-1, N-1);
        }
    }

}


//
void Node::print()
{//. use recursion. printout hard to understand
    if(child.size()) {
        cout<<"parent: "<<id<<" size: "<<child.size()<<endl;
        for(int i = 0; i<child.size(); i++) {
            cout<<" child: "<<i<<" "<<child[i]->id<<" ";
        }
        cout<<endl;

        for(int i = 0; i<child.size(); i++) {
            child[i]->print();
        }
    }
}

//
void print(Node * root) 
{//. no recursion. print out easy to understand 

    if (root==NULL) 
        return; 
   
    // Standard level order traversal code 
    // using queue 
    queue<Node *> q;  // Create a queue 
    q.push(root); // Enqueue root  
    while (!q.empty()) 
    { 
        int n = q.size(); 
  
        // If this node has children 
        while (n > 0) 
        { 
            // Dequeue an item from queue and print it 
            Node * p = q.front(); 
            q.pop(); 
            cout << p->id << " "; 
   
            // Enqueue all children of the dequeued item 
            for (int i=0; i<p->child.size(); i++) 
                q.push(p->child[i]); 
            n--; 
        } 
   
        cout << endl; // Print new line between two levels 
    } 
} 

//.. if t1 or any of its decendants is equal to t0 or any of its decendant
bool in_existing_root(Node *t0,  Node *t1)
{//.. use recusion
    bool found = false;

    if(!t0 || !t1) {
        cout<<" !!! t0 or t1 is NULL"<<endl;
        return false;
    }

    if(t0->id == t1->id) 
        return true;

    Node *n0 = 0;
    Node *n1 = 0;
    for(int i = 0; i < t0->child.size()+1; i++) {
        for(int m = 0; m < t1->child.size()+1; m++) {

            if(i==t0->child.size())
                n0 = t0;
            else
                n0 = t0->child[i];

            if(m==t1->child.size())
                n1 = t1;
            else
                n1 = t1->child[m];


            //.. already check if t0->id==t1->id. do it again will cause core dump
            if(i==t0->child.size()  && m==t1->child.size()) 
                continue;

            found |= in_existing_root(n0, n1);

            if(found) 
                return true;
        }
    }


    return found;
}


//
int main()
{
    Node t;
    t.init(3, 12);

    vector<Node *> PG;
    for(int i = 10; i<11; i++) {
        Node *a = new Node;
        a->init(3, i);

        PG.push_back(a);
    }
    
    if(in_existing_root(PG[0], &t))
        cout<<" ...find it ..."<<endl;
    else 
        cout<<" ..Nope ..."<<endl;

    print(&t);
    for(int i = 0; i<PG.size(); i++) {
        print(PG[i]);
    }
}
