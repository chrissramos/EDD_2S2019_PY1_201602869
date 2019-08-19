#include <iostream>
using namespace std;

/**class node*/
class node{
public:
  int data;
  node *right;
  node *left;
  node *up;
  node *down;
  node(int data){
      this->data = data;
      right = NULL;
      left = NULL;
      down = NULL;
      up = NULL;
  }
};
/**class matrix*/
class matrix{
public:
  node *head;
  matrix(){
    node *temp = new node(0);
    head = temp;
  }
  void add(int value, int x, int y){
    //1 crear cabeceras, x header
    addXHeader(x);
    addYHeader(y);
    node *new_node = new node(value);
    add_x(new_node,x);
    add_y(new_node,y);

    //insert node
  }
  void add_x(node *newNode, int x){
    node *temp = head;
    while(temp->data!= x){
      temp = temp->right;
    }
    if(temp->down == NULL){
      temp->down = newNode;
      newNode->up = temp;
    }

  }
  void add_y(node *newNode, int y){
    node *temp = head;
    while(temp->data!= y){
      temp = temp->down;
    }
    if(temp->right == NULL){
      temp->right = newNode;
      newNode->left = temp;
    }
  }
  void addXHeader(int x){
    if(head->right == NULL){
      node *temp = new node(x);
      head->right = temp;
      temp->left = head;
    }else{
      node *temp = head;
      while(temp->right!= NULL && temp->right->data< x){
        temp = temp->right;
      }
      if(temp->right ==NULL){
        node *newNode = new node(x);
        temp->right = newNode;
        newNode->left = temp;
      }else if(temp->right != NULL && temp->right ->data != x ){
        node *newTemp = new node(x);
        node *der = temp->right;
        temp->right = newTemp;
        newTemp ->left = temp;
        newTemp ->right = der;
        der->left = newTemp;

      }
    }
  }
  void addYHeader(int y){
    if(head->down == NULL){
      node *temp = new node(y);
      head->down = temp;
      temp->up = head;
    }else{
      node * temp2 = head;
      while(temp2->down!= NULL && temp2->down->data<y){
        temp2 = temp2->down;
      }
      if(temp2->down==NULL){
        node *newTemp2 = new node(y);
        temp2->down = newTemp2;
        newTemp2->up = temp2;
      }else if(temp2->down!= NULL && temp2->down->data != y){
        node *newTemp = new node(y);
        node *der = temp2->down;
        temp2->down = newTemp;
        newTemp->up = temp2;
        newTemp->down = der;
        der->up = newTemp;
      }
    }

  }
  void printHeaders(){
      printXHeader();
      printYHeader();
  }
  void printXHeader(){
      node *temp = head;
      while (temp->right != NULL) {
        cout<<temp->data;
        cout<<"->";
        temp = temp->right;
      }
      cout<<temp->data;
      cout<<"\n";

  }
  void printYHeader(){
    node *temp = head->down;
    while (temp->down != NULL) {
      cout<<temp->data;
      cout<<"\n";
      temp = temp->down;
    }
    cout<<temp->data;
    cout<<"\n";
  }
void printNodesX(){
  node *temp = head->right;
  while(temp->right!= NULL){
    cout<<temp->data;
    cout<<"->";
    if(temp->down!=NULL){
      cout<<temp->down->data;
    }
    cout<<"\n";
    temp = temp->right;
  }
  cout<<temp->data;
  cout<<"->";
  if(temp->down!=NULL){
    cout<<temp->down->data;
  }
  cout<<"\n";
}
void printNodesY(){
  node *temp = head->down;
  while(temp->down!= NULL){
    cout<<temp->data;
    cout<<"->";
    if(temp->right!=NULL){
      cout<<temp->right->data;
    }
    cout<<"\n";
    temp = temp->down;
  }
  cout<<temp->data;
  cout<<"->";
  if(temp->right!=NULL){
    cout<<temp->right->data;
  }
  cout<<"\n";
}
};
int main() {
  /* code */
  matrix *sm = new matrix;
  sm->add(10,2,2);
  sm->add(12,5,1);
  sm->add(14,3,4);
  sm->add(22,5,6);
  sm->add(18,7,8);
  sm->add(7,4,5);
  sm->add(17,9,4);
  sm->add(47,6,3);

  sm->printHeaders();
  cout<<"\n";
  sm->printNodesX();
  cout<<"\n";
  sm->printNodesY();
  //node *temp = new node(1);
  //cout<<temp->data;

 return 0;
}
