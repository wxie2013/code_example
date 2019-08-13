//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

const int n_child= 2;

using namespace std;
class Node
{
    public:
        int id;
        int level; //.. level in the tree
        vector<Node *> child; 

    public:
        Node():id{0}, level{0} {;}
        void init(int N, int);
        int get_level() const {return level;}
        void set_level(int in_level) {level = in_level;}
};

//.. add values and nodes to a tree
void Node::init(int N, int in_level)
{//. use recursion

    id = N;
    level = in_level++;

    if(N!=0) {
        for(int i = 0; i<n_child; i++) {
            Node *node = new Node;
            child.push_back(node);
        }

        //in_level += 1; //.. add one level up for the child 
        for(int i = 0; i<child.size(); i++) {
            child[i]->init(N-1, in_level);
        }
    }
}

// number of nodes in the tree
int size(Node* node)
{
    int tmp =0;
    for(int i = 0; i<node->child.size(); i++) {
        tmp += size(node->child[i]);
    }
    tmp +=1;

    return tmp;
}

//.. find the maximum depth of a tree
int maxLevel(Node* node)
{
    int max_level = 0;
    for(int i = 0; i<node->child.size(); i++) {
        int tmp = maxLevel(node->child[i]);
        if(max_level < tmp)
            max_level = tmp;
    }

    return max_level+1;
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
            cout << p->id << "(level: "<<p->get_level()<<") "; 
            //cout << p << "(level: "<<p->get_level()<<") "; //.. can print address for debugging to see if it's changed..
   
            // Enqueue all children of the dequeued item 
            for (int i=0; i<p->child.size(); i++) 
                q.push(p->child[i]); 
            n--; 
        } 
   
        cout << endl; // Print new line between two levels 
    } 
} 

//.. if t1 or any of its decendants is equal to t0 or any of its decendant
int in_existing_root(Node **ptr_t0,  Node **ptr_t1)
{//.. use recusion. 
 //using pointer of pointer to keep the changes occurs in the function outside the function when function call is finished

    int found = -1;

    if(!(*ptr_t0) || !(*ptr_t1)) {
        cout<<" !!! t0 or t1 is NULL"<<endl;
        return 0;
    }

    if((*ptr_t0)->id == (*ptr_t1)->id) {

        int original_level = (*ptr_t0)->get_level();
        *ptr_t0 = *ptr_t1;

        (*ptr_t0)->set_level(original_level); //.. same node in 2 trees can have different level

        return std::min((*ptr_t0)->get_level(), (*ptr_t1)->get_level()) ;
    }

    Node **n0 = 0;
    Node **n1 = 0;
    for(int i = 0; i < (*ptr_t0)->child.size()+1; i++) {
        for(int m = 0; m < (*ptr_t1)->child.size()+1; m++) {

            //.. already check if t0->id==t1->id. do it again will cause core dump
            if(i==(*ptr_t0)->child.size()  && m==(*ptr_t1)->child.size()) 
                continue;

            if(i==(*ptr_t0)->child.size())
                n0 = &(*ptr_t0);
            else
                n0 = &(*ptr_t0)->child[i];

            if(m==(*ptr_t1)->child.size())
                n1 = &(*ptr_t1);
            else
                n1 = &(*ptr_t1)->child[m];

            found = in_existing_root(n0, n1);

            // one can return here but it will only allow changes in one node. 
            // if there can be more than one nodes common between the two trees, comment the following out
            // if(found)
            //    return true;
        }
    }

    return found;
}
//This is an alternative, without manuallty changing the level
//int in_existing_root(Node **ptr_t0,  Node **ptr_t1)
//{//.. use recusion.
// //using pointer of pointer to keep the changes occurs in the function outside the function when function call is finished
//
//    int found = -1;
//    static bool top = false;
//
//    if(!(*ptr_t0) || !(*ptr_t1)) {
//        cout<<" !!! t0 or t1 is NULL"<<endl;
//        return found;
//    }
//
//    if((*ptr_t0)->id == (*ptr_t1)->id) {
//
//        if((*ptr_t0)->get_level() ==0 || (*ptr_t1)->get_level() ==0)
//            top = true;
//
//        *ptr_t0 = *ptr_t1;
//
//        found = 1;
//
//        return found;
//    }
//
//    Node **n0 = 0;
//    Node **n1 = 0;
//    for(int i = 0; i < (*ptr_t0)->child.size()+1; i++) {
//        for(int m = 0; m < (*ptr_t1)->child.size()+1; m++) {
//
//            //.. already check if t0->id==t1->id. do it again will cause core dump
//            if(i==(*ptr_t0)->child.size()  && m==(*ptr_t1)->child.size())
//                continue;
//
//            if(i==(*ptr_t0)->child.size())
//                n0 = &(*ptr_t0);
//            else
//                n0 = &(*ptr_t0)->child[i];
//
//            if(m==(*ptr_t1)->child.size())
//                n1 = &(*ptr_t1);
//            else
//                n1 = &(*ptr_t1)->child[m];
//
//            found += in_existing_root(n0, n1);
//            cout<<"found: "<<found<<endl;
//
//            // one can return here but it will only allow changes in one node.
//            // if there can be more than one nodes common between the two trees, comment the following out
//            // if(found)
//            //    return true;
//        }
//    }
//
//    if(top)
//        found =1;
//
//    return found;
//}

//
int main()
{
    Node *s = new Node;
    s->init(2, 0);
    cout<<"size: "<<size(s)<<endl;
    cout<<"max level: "<<maxLevel(s)<<endl;

    Node *t = new Node;
    t->init(4, 0);
    cout<<"size: "<<size(t)<<endl;
    cout<<"max level: "<<maxLevel(t)<<endl;

    Node *a = new Node;
    a->init(2, 0);
    cout<<"size: "<<size(a)<<endl;
    cout<<"max level: "<<maxLevel(a)<<endl;

    cout<<" ==============================================================   "<<endl;
    // when s->id == a->id, the adress of a is changed to the address of s
    cout<<" !!! before the change ...."<<endl;
    cout<<" .. address of tree s .."<<endl;
    print(s);
    cout<<" .. address of tree a .."<<endl;
    print(a);
    
    int result = in_existing_root(&a, &s);
    cout<<"!! result: "<<result<<endl;


    cout<<" !!! after the change ...."<<endl;
    cout<<" .. address of tree s .."<<endl;
    print(s);
    cout<<" .. address of tree a .."<<endl;
    print(a);

    cout<<" ==============================================================   "<<endl;
    // when a child of s is equal to a, the address of the child does not change
    cout<<" !!! before the change ...."<<endl;
    cout<<" .. address of tree t .."<<endl;
    print(t);
    cout<<" .. address of tree a .."<<endl;
    print(a);
    
    result = in_existing_root(&a, &t);
    cout<<"!! result: "<<result<<endl;

    cout<<" !!! after the change ...."<<endl;
    cout<<" .. address of tree t .."<<endl;
    print(t);
    cout<<" .. address of tree a .."<<endl;
    print(a);
}
