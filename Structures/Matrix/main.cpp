#include <iostream>
#include <fstream>
using namespace std;

/**class node*/
class node{
public:
  int data;
  string color;
  int r;
  int g;
  int b;
  int y;
  int x;
  string contador;
  node *right;
  node *left;
  node *up;
  node *down;
  node(int x, int y, int r, int g, int b){
      
      //this->data = data;
      this->x = x;
      this->y = y;
      this->r = r;
      this->g = g;
      this->b = b;
      this->color="\"" + to_string(r) + "," + to_string(g) + "," + to_string(b) + "\"";
      this->contador = to_string(x)+to_string(y); 
      
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
    node *temp = new node(0,0,0,0,0);
    head = temp;
  }
  void add(int x, int y, int r, int g, int b){
    //1 crear cabeceras, x header
    addXHeader(x);
    addYHeader(y);
    node *new_node = new node(x,y,r,g,b);
    
    add_x(new_node,x, y);
    add_y(new_node,x,y);

    //insert node
  }
  void add_x(node *newNode, int x, int y){
    node *temp = head;
    while(temp->r!= x){
      temp = temp->right;
    }


    if(temp->down == NULL){
      //cout<<"se unira: "<<temp->data<<"->"<<newNode->data<<"\n";
      temp->down = newNode;
      newNode->up = temp;
    }else{
      while(temp->down!= NULL && temp->down->y<newNode->y){
        
        temp = temp->down;
      }
      //cout<<"salio porque y del temp = "<<temp->data<<" es menor a la y de:"<<newNode->data<<"\n";
      if(temp->down == NULL){
        temp->down = newNode;
        newNode->up = temp;
        //cout<<"SE UNIOO: "<<temp->data<<"->"<<newNode->data<<"\n";
      }else{
        node *aux = temp->down;
        temp->down = newNode;
        newNode->up = temp;
        newNode->down = aux;
        aux->up = newNode;

        //cout<<"SE UNIOO: "<<temp->data<<"->"<<newNode->data<<"->"<<aux->data<<"\n";
      }
      //temp->down = newNode;
      //newNode->up = temp;
      //cout<<"salio porque y del temp = "<<temp->data<<" es menor a la y de:"<<newNode->data<<"\n";

    }
     //finanila aquii

  }
  void add_y(node *newNode, int x, int y){
    node *temp = head;
    while(temp->r!= y){
      temp = temp->down;
    }/*
    while(temp->right!=NULL){
      cout<<"Tiene nodo "<<temp->data<<"->"<<temp->right->data;
      temp = temp->right;
    }*/
    if(temp->right == NULL){
       //cout<<"se unira: "<<temp->data<<"->"<<newNode->data<<"\n";
      temp->right = newNode;
      newNode->left = temp;
    }else{
      while(temp->right!=NULL && temp->right->x<newNode->x){
        temp = temp->right;
      }
      if(temp->right ==NULL){
        temp->right = newNode;
        newNode->left = temp;
      }else{
        node *aux = temp->right;
        temp->right = newNode;
        newNode->left = temp;
        newNode->right = aux;
        aux->left = newNode;
      }
    }
  }
  void addXHeader(int x){
    if(head->right == NULL){
      node *temp = new node(x,0,x,0,0);
      head->right = temp;
      temp->left = head;
    }else{
      node *temp = head;
      while(temp->right!= NULL && temp->right->r< x){
        temp = temp->right;
      }
      if(temp->right ==NULL){
        node *newNode = new node(x,0,x,0,0);
        temp->right = newNode;
        newNode->left = temp;
      }else if(temp->right != NULL && temp->right ->r != x ){
        node *newTemp = new node(x,0,x,0,0);
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
      node *temp = new node(0,y,y,0,0);
      head->down = temp;
      temp->up = head;
    }else{
      node * temp2 = head;
      while(temp2->down!= NULL && temp2->down->r<y){
        temp2 = temp2->down;
      }
      if(temp2->down==NULL){
        node *newTemp2 = new node(0,y,y,0,0);
        temp2->down = newTemp2;
        newTemp2->up = temp2;
      }else if(temp2->down!= NULL && temp2->down->r != y){
        node *newTemp = new node(0,y,y,0,0);
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
        cout<<temp->r;
        cout<<"->";
        temp = temp->right;
      }
      cout<<temp->r;
      cout<<"\n";

  }
  void printYHeader(){
    node *temp = head->down;
    while (temp->down != NULL) {
      cout<<temp->r;
      cout<<"\n";
      temp = temp->down;
    }
    cout<<temp->r;
    cout<<"\n";
  }
void printNodesX(){
  node *temp = head->right;
  node *aux = temp->right;
   while(temp->right!=NULL){
    aux = temp;
    while(aux->down!= NULL){
      cout<<aux->color;
      cout<<"->";
      aux = aux->down;
    }
    cout<<aux->color;
    cout<<"\n";
    temp = temp->right;
  }
  while(temp->down!=NULL){
    cout<<temp->color;
    cout<<"->";
    temp = temp->down;
  }
  cout<<temp->color;


}
void printNodesY(){
 node *temp = head->down;
  node *aux = temp->down;
  node *aux2 = temp->down;
  
  string contenidoY="";
  while(temp->down!=NULL){
    aux = temp;
    //aux2 = temp->right;
    while(aux->right!=NULL){
      
      cout<<aux->color;
      cout<<"->";
      aux = aux->right;
    }
    cout<<aux->color;
    cout<<"\n";
    temp = temp->down;
  }
  while(temp->right!=NULL){
    cout<<temp->color;
    cout<<"->";
    temp = temp->right;
  }
  cout<<temp->color;
}

string graphYNodes(){
  node *temp = head->down;
  node *aux = temp->down;
  node *nod = head->down;
  string contenidoY = "\n";
  string ranksame = "";
  string contenidoTodo="";
  string enlaces="";
 
  while(temp->down!=NULL){
    //contenidoY+="Y";
    ranksame += "{rank = same " + temp->contador + " " ;
    contenidoY +=temp->contador + "[label = " +to_string(temp->r) + "]\n";
    enlaces+= "\n"+temp->contador + "->";
    //contenidoY+="->";
    if(temp->right!=NULL){
      aux = temp->right;
      while(aux->right!=NULL){
        ranksame +=" " + aux->contador + " ";
        contenidoY+= aux->contador + " [label = " +aux->color +" ]\n";
        enlaces+=aux->contador + "->";
        //contenidoY+="->";
        
        aux = aux->right;
      }
      ranksame +=" " + aux->contador + " ";
      contenidoY+= aux->contador + " [label = " +aux->color +" ]\n";
      enlaces+= aux->contador;
      enlaces+=" [dir = both] \n";
    }
    ranksame+="}\n";
    contenidoY +="\n";
    enlaces+=" [dir = both] \n";
    temp = temp->down;
  }
  //contenidoY+="Y";
  ranksame += "{rank = same " + temp->contador + " " ;
  enlaces+= "\n"+ temp->contador + "->";
  contenidoY+=temp->contador + "[label = " +to_string(temp->r) + "]\n";
  //enlaces+= temp->contador + "->";
  //contenidoY+="->";
  if(temp->right!=NULL){
    aux = temp->right;
  }
  while(aux->right!=NULL){
    ranksame += " " + aux->contador + " ";
     contenidoY+= aux->contador + " [label = " +aux->color +" ]\n";
     enlaces+= aux->contador + "->";
     //contenidoY+="->";
      aux = aux->right;
  }
 
  ranksame += " " + aux->contador+ " }";
  contenidoY+= aux->contador + " [label = " +aux->color +" ]\n";
  enlaces+=aux->contador;
  enlaces+=" [dir = both] \n";
  contenidoTodo = ranksame + contenidoY + enlaces;
  //cout<<contenidoTodo;
  return contenidoTodo;
}
string graphXNodes(){
  node *temp = head->right;
  node *aux = temp->right;
  node *nod = head->right;
  string contenidoX="\n";
  string ranksame = "";
  string contenidoTodo="";
  string enlaces="";
  while(temp->right!=NULL){
    ranksame += "{rank = same " + temp->contador + " " ;
    contenidoX+= temp->contador + "[label = " +to_string(temp->r)+" group =" + to_string(temp->x) + "]\n";
    enlaces += "\n"+temp->contador + "->";
    //contenidoX+= "->";
    if(temp->down!=NULL){
      aux = temp->down;
      while(aux->down!=NULL){
        ranksame += " " + aux->contador + " ";
        contenidoX+= aux->contador + " [label = " +aux->color+" group =" + to_string(aux->x) +" ]\n";
        enlaces+=aux->contador + "->";
        //contenidoX+="->";
        aux = aux->down;
      }
      ranksame += " " + aux->contador + " ";
      contenidoX+=  aux->contador + " [label = " +aux->color+" group =" + to_string(aux->x) +" ]\n";
      enlaces+= aux->contador;
      enlaces+=" [dir = both] \n";
    }
    ranksame+="}\n";
    contenidoX +="\n";
    //enlaces+=" [dir = both] \n";
    temp = temp->right;
  }
  //contenidoX+="X";
  ranksame += "{rank = same " + temp->contador + " " ;
  enlaces+= "\n"+ temp->contador + "->";
  contenidoX+=temp->contador + "[label = " +to_string(temp->r)+" group =" + to_string(temp->x) + "]\n";
  //contenidoX+="->";
  if(temp->down!=NULL){
    aux = temp->down;
  }
  while(aux->down!=NULL){
    ranksame += " " + aux->contador + " ";
     contenidoX+=aux->contador + " [label = " +aux->color+" group =" + to_string(aux->x) +" ]\n";
     enlaces+=aux->contador + "->";
     //contenidoX+="->";
      aux = aux->down;
  }
  ranksame +=  " " + aux->contador+ " }";
  contenidoX+= aux->contador + " [label = " +aux->color+" group =" + to_string(aux->x) +" ]\n";
  enlaces+=aux->contador;
  enlaces+=" [dir = both] \n";
  contenidoTodo = contenidoX + enlaces;
  //cout<<enlaces;
  //cout<<contenidoTodo;
  return contenidoTodo;
}
void graphMatrix(string padre, string numCapa){
  string contenidoDot = "digraph G { \n node [shape=record];\n";  
  //string titulo = padre+"Capa"+numCapa+".dot";
  string titulo = "demo2.dot";
  string ranksame="{rank = same " + head->contador +" ";
  string encabezados = "";
  string enlacesX="\n";
  string enlacesY="\n";
  node *temp = head;
  //ahora encabezados en Y
  //ranksame += "{rank = same ";
  temp = head->down;
  encabezados+="\n";
  encabezados+=head->contador + "[label = 0 group =0]";
  enlacesX+= head->contador + "->";
    while (temp->down != NULL) {
      encabezados+="\n";
      encabezados += temp->contador + "[label =" + to_string(temp->r) +" group = 0]";
 
      enlacesX += temp->contador + "->";
      
      temp = temp->down;
    }
    encabezados += temp->contador + "[label =" + to_string(temp->r) +" group = 0]";
    enlacesX+= temp->contador;
    enlacesX+= " [dir = both] \n";


  // imprimir encabezados x
  encabezados+="\n";
  
    temp = head->right;
      encabezados+=head->contador + "[label = 0 group = 0]";
      enlacesY+= head->contador + "->";
     
      while (temp->right != NULL) {
        encabezados+="\n";
        
        encabezados += temp->contador + "[label =" + to_string(temp->r) +" group =" + to_string(temp->x) +"]";
        ranksame += temp->contador + " ";
        
        enlacesY += temp->contador + "->";
        
        temp = temp->right;
      }
     encabezados+="\n";
      ranksame += temp->contador + " ";
      encabezados += temp->contador + "[label =" + to_string(temp->r) +" group =" + to_string(temp->x)+"]";
      enlacesY += temp->contador ;
      enlacesY +=" [dir = both] \n";
      //cout<<temp->data;
      cout<<"\n";



  // fin encabezados x  
  ranksame += "}";
  
    cout<<"\n";
  //HACER TODOS LOS RANKSAMES
  //nodos de Y 
  
  contenidoDot+= ranksame;
  

  contenidoDot+= encabezados + enlacesX + enlacesY;
  contenidoDot+= graphYNodes();
  
  contenidoDot+= graphXNodes();
  contenidoDot+= "}";
   ofstream fs(titulo.c_str());
   fs << contenidoDot << endl;
   fs.close();
   system("cmd /c dot -Tpng demo2.dot -o demo_dot.png");
   system("cmd /c demo_dot.png");
  //padre+"Capa"+numCapa+".dot";
   //cout<<"ENLACES Y"<<"\n"<<enlacesY<<"\n";
  //cout<<"enlaces X:\n"<<enlacesX<<"\n\n"<<enlacesY;
  //cout<<contenidoDot;
}
void modificarNodo(int x, int y, int r, int g, int b){
    node *temp = head->right;
  while(temp->x!=x && temp->right!=NULL){
    temp = temp->right;
  }
  if(temp->x == x){
    //cout<<"encontro coordenada X y es:"<<temp->x<<"\n";
    while(temp->y!=y && temp->down!=NULL){
      temp = temp->down;
    }
    if(temp->y == y){
     // cout<<"encontro coordenada Y y es: "<<temp->y<<"\n";
    }
    cout<<"coordenadas encontradas: "<<temp->x<<","<<temp->y<<" y su contenido es: "<<temp->color<<"\n";
    temp->r = r;
    temp->g = g;
    temp->b = b;
    temp->color = "\"" + to_string(r) + "," + to_string(g) + "," + to_string(b) + "\"";
   // cout<<"Nodo arriba: "<<temp->up->color<<"\n";
    /*if(temp->down!=NULL){
      cout<<"Nodo abajo: "<<temp->down->color<<"\n";
    }else if(temp->right!=NULL){
      cout<<"Nodo derecha: "<<temp->right->color<<"\n";
    }else if(temp->left!=NULL){
      cout<<"Nodo izquierda: "<<temp->left->color<<"\n";
    }*/
  }else{
    cout<<"no se encontro coordenada";
  }
}
void findNode(int x, int y){
  node *temp = head->right;
  while(temp->x!=x && temp->right!=NULL){
    temp = temp->right;
  }
  if(temp->x == x){
    cout<<"encontro coordenada X y es:"<<temp->x<<"\n";
    while(temp->y!=y && temp->down!=NULL){
      temp = temp->down;
    }
    if(temp->y == y){
      cout<<"encontro coordenada Y y es: "<<temp->y<<"\n";
    }
    cout<<"coordenadas encontradas: "<<temp->x<<","<<temp->y<<" y su contenido es: "<<temp->color<<"\n";
    cout<<"Nodo arriba: "<<temp->up->color<<"\n";
    if(temp->down!=NULL){
      cout<<"Nodo abajo: "<<temp->down->color<<"\n";
    }else if(temp->right!=NULL){
      cout<<"Nodo derecha: "<<temp->right->color<<"\n";
    }else if(temp->left!=NULL){
      cout<<"Nodo izquierda: "<<temp->left->color<<"\n";
    }
  }else{
    cout<<"no se encontro coordenada";
  }
}
};/*
int main() {
  
  matrix *matriz = new matrix;
  matriz->add(15,10,1,1,1);
  matriz->add(3,6,2,2,2);
  matriz->add(5,2,3,3,3);
  matriz->add(2,2,4,4,4);
   matriz->add(15,2,5,5,5);
   matriz->add(2,3,6,6,6);
  
  matriz->add(16,11,7,7,7);
  matriz->add(4,1,8,8,8);
  matriz->add(1,1,9,9,9);
  
  
  matriz->add(15,1,10,10,10);
 //matriz->findNode(15,1);
  

 // matriz->graphXNodes();
  //matriz->printHeaders();
  cout<<"\n";
  matriz->graphMatrix();
  //matriz->printNodesX();
  //matriz->printNodesY();

  //sm->graphMatrix();
  
 // sm->printNodesX();
 
  //sm->printNodesY();

  //cout<<"graficandooo \n";
 // sm->graphXNodes();
 // sm->graphMatrix();
 return 0;
}*/
