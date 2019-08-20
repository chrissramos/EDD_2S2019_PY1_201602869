#include <iostream>
#include <fstream>
using namespace std;

/**class node*/
class node{
public:
  int data;
  int y;
  int x;
  node *right;
  node *left;
  node *up;
  node *down;
  node(int data, int x, int y){
      this->data = data;
      this->x = x;
      this->y = y;
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
    node *temp = new node(0,0,0);
    head = temp;
  }
  void add(int value, int x, int y){
    //1 crear cabeceras, x header
    addXHeader(x);
    addYHeader(y);
    node *new_node = new node(value,x,y);
    add_x(new_node,x, y);
    //add_y(new_node,x,y);

    //insert node
  }
  void add_x(node *newNode, int x, int y){
    node *temp = head;
    while(temp->data!= x){
      temp = temp->right;
    }
    /*
    while(temp->down!=NULL){
      cout<<"Tiene nodo "<<temp->data<<"->"<<temp->down->data<<" Posicion Y: "<<temp->down->y;
      temp = temp->down;

    }*/
    
    if(temp->down == NULL){
      cout<<"se unira: "<<temp->data<<"->"<<newNode->data<<"\n";
      temp->down = newNode;
      newNode->up = temp;
    }else{
      while(temp->down!= NULL && temp->down->y<newNode->y){
        
        temp = temp->down;
      }
      cout<<"salio porque y del temp = "<<temp->data<<" es menor a la y de:"<<newNode->data<<"\n";
      if(temp->down == NULL){
        temp->down = newNode;
        newNode->up = temp;
        cout<<"SE UNIOO: "<<temp->data<<"->"<<newNode->data<<"\n";
      }else{
        node *aux = temp->down;
        temp->down = newNode;
        newNode->up = temp;
        newNode->down = aux;
        aux->up = newNode;

        cout<<"SE UNIOO: "<<temp->data<<"->"<<newNode->data<<"->"<<aux->data<<"\n";
      }
      //temp->down = newNode;
      //newNode->up = temp;
      cout<<"salio porque y del temp = "<<temp->data<<" es menor a la y de:"<<newNode->data<<"\n";

    }
    

  }
  void add_y(node *newNode, int x, int y){
    node *temp = head;
    while(temp->data!= y){
      temp = temp->down;
    }
    while(temp->right!=NULL){
      cout<<"Tiene nodo "<<temp->data<<"->"<<temp->right->data;
      temp = temp->right;
    }
    if(temp->right == NULL){
       cout<<"se unira: "<<temp->data<<"->"<<newNode->data<<"\n";
      temp->right = newNode;
      newNode->left = temp;
    }
  }
  void addXHeader(int x){
    if(head->right == NULL){
      node *temp = new node(x,x,0);
      head->right = temp;
      temp->left = head;
    }else{
      node *temp = head;
      while(temp->right!= NULL && temp->right->data< x){
        temp = temp->right;
      }
      if(temp->right ==NULL){
        node *newNode = new node(x,x,0);
        temp->right = newNode;
        newNode->left = temp;
      }else if(temp->right != NULL && temp->right ->data != x ){
        node *newTemp = new node(x,x,0);
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
      node *temp = new node(y,0,y);
      head->down = temp;
      temp->up = head;
    }else{
      node * temp2 = head;
      while(temp2->down!= NULL && temp2->down->data<y){
        temp2 = temp2->down;
      }
      if(temp2->down==NULL){
        node *newTemp2 = new node(y,0,y);
        temp2->down = newTemp2;
        newTemp2->up = temp2;
      }else if(temp2->down!= NULL && temp2->down->data != y){
        node *newTemp = new node(y,0,y);
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
  node *aux = temp->right;
  /*while(temp->down!= NULL){
    cout<<temp->data;
    cout<<"->";
    temp = temp->down;
  }
  cout<<temp->data;
  */
  while(temp->right!=NULL){
    aux = temp;
    while(aux->down!= NULL){
      cout<<aux->data;
      cout<<"->";
      aux = aux->down;
    }
    cout<<aux->data;
    cout<<"\n";
    temp = temp->right;
  }
  while(temp->down!=NULL){
    cout<<temp->data;
    cout<<"->";
    temp = temp->down;
  }
  cout<<temp->data;
  /* while(temp->right!= NULL){
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
*/


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

void graphMatrix(){
  string contenidoDot = "digraph G {\"A\" -> \"B\"  }";  
  string titulo = "demo2.dot";
   ofstream fs(titulo.c_str());
   fs << contenidoDot << endl;
   fs.close();
   system("cmd /c dot -Tpng demo2.dot -o demo_dot.png");
   system("cmd /c demo_dot.png");
  cout<<contenidoDot;
}

};
int main() {
  /* code */
  matrix *sm = new matrix;
  sm->add(10,2,2);
  sm->add(22,5,1);
  sm->add(14,3,4);
  sm->add(12,5,6);
  
  //sm->add(7,4,5);
  sm->add(17,9,4);
  sm->add(18,9,2);
  sm->add(3,9,3);
  sm->add(47,6,3);
  sm->add(99,3,6);
  sm->add(7,4,5);
  //sm->graphMatrix();
  //sm->printHeaders();
  cout<<"\n";
  sm->printNodesX();
  cout<<"\n";
  //sm->printNodesY();

 return 0;
}
