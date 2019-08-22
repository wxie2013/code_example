//.. similar as recursion_3.C except the node using object instead of pointer to avoid memory issue of the child
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
            child.push_back(new Node);
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
            //cout << p->id << "(level: "<<p->get_level()<<") "; 
            cout << p << "(level: "<<p->get_level()<<") "; //.. can print address for debugging to see if it's changed..
   
            // Enqueue all children of the dequeued item 
            for (int i=0; i<p->child.size(); i++) 
                q.push(p->child[i]); 
            n--; 
        } 
   
        cout << endl; // Print new line between two levels 
    } 
} 

int in_existing_node(int id, Node *&node) 
{//. no recursion. print out easy to understand 

    if (node==NULL) 
        return -1; 
   
    // Standard level order traversal code 
    // using queue 
    queue<Node **> q;  // Create a queue to contain the pointer to a pointer 
    q.push(&node); // store the reference to node

    int level = 0;
    while (!q.empty()) 
    { 
        int n = q.size(); 

        // If this node has children 
        while (n > 0) 
        { 
            // Dequeue an item from queue and print it 
            Node **p = q.front();  //.. pointer to the original pointer
            q.pop(); 

            //
            if(id == (*p)->id) {
                cout<<"id: "<<id<<" (*p)->id: "<<(*p)->id<<endl;
                return level;
            }

            // Enqueue all children of the dequeued item 
            for (int i=0; i<(*p)->child.size(); i++) 
                q.push(&(*p)->child[i]); 
            n--; 
        } 
   
        level++;
    } 

    return -1;
} 

//.. if t1 or any of its decendants is equal to t0 or any of its decendant
bool two_node_overlap (Node *&ptr_t0,  Node *&ptr_t1)
{
    bool matched = false;

    if (ptr_t0==NULL || ptr_t1==NULL) 
        return false; 
   
    // Standard level order traversal code 
    // using queue 
    queue<Node **> q;  // Create a queue 

    q.push(&ptr_t0); // Enqueue root  

    int level = 0;
    while (!q.empty()) 
    { 
        int n = q.size(); 

        // If this node has children 
        while (n > 0) 
        { 
            // Dequeue an item from queue and print it 
            Node ** p = q.front(); //.. it's the original pointer instead of a copy
            q.pop(); 

            //
            int level_ptr_t1 = in_existing_node((*p)->id, ptr_t1);
            cout<<" level_ptr_t1: "<<level_ptr_t1<<endl;
            if(level_ptr_t1 != -1) {
                cout<<"1__: "<<*p<<" "<<ptr_t1<<endl;
                *p = ptr_t1;
                cout<<"2__: "<<*p<<" "<<ptr_t1<<endl;
                matched = true;
                n--;
                continue; //.. no need to proceed to the child of p
            }

            // Enqueue all children of the dequeued item 
            for (int i=0; i<(*p)->child.size(); i++) 
                q.push(&(*p)->child[i]); 
            n--; 
        } 
   
        level++;
    } 

    return matched;
}

// check if the input is already in the node
bool in_the_node(Node* node, int input)
{
    bool found = false;

    cout<<"level: "<<node->get_level()<<endl;
    if(node->id == input) {
        return true;
    }

    for(int i = 0; i < node->child.size(); i++) {
        found = in_the_node(node->child[i], input);

        if(found)
            return true;
    }

    return found;
}

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
    
    int result = two_node_overlap(a, s);
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
    
    result = two_node_overlap(a, t);
    cout<<"!! result: "<<result<<endl;

    cout<<" !!! after the change ...."<<endl;
    cout<<" .. address of tree t .."<<endl;
    print(t);
    cout<<" .. address of tree a .."<<endl;
    print(a);
}
