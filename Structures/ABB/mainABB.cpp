#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


class Node{
private:
	string key;
	Node *left;
	Node *right;
public:
	
	Node(string key){
		this->key = key;
		right = NULL;
		left = NULL;
	}

	string getKey(){
		return this->key;
	}

	Node* getLeft(){
		return this->left;
	}

	Node* getRight(){
		return this->right;
	}

	//setters
	void setKey(int key){
		this->key = key;
	}

	void setLeft(Node *left){
		this->left = left;
	}

	void setRight(Node *right){
		this->right = right;
	}
};


class ABB{
private:
	Node *root;
public:
	vector<string> arrInorder;
	vector<string> arrPreorder;
	vector<string> arrPostorder;
	
	ABB(){
		root = NULL;
	}	

void add(Node *temp){
	if(root == NULL){
		root = temp;
	}else{
		recursive_add(root,temp);
	}
}

void recursive_add(Node *current, Node *temp){
	if(temp->getKey() < current->getKey()){//insert izq
		if(current->getLeft() != NULL){
			recursive_add(current->getLeft(),temp);
		}else{
			current->setLeft(temp);
		}

	}else if(temp->getKey() > current->getKey()){//insert derecha
		if(current->getRight() != NULL){
			recursive_add(current->getRight(),temp);
		}else{
			current->setRight(temp);
		}
	}else{
		// aqui es cuando es igual el key, o sea error 
	}
}


void preorder(){ // raiz izq der
	recursive_preorder(root);
}
void recursive_preorder(Node* current){
	//imprimr el valor de la raiz
	cout <<current->getKey();
	cout <<"->";
	arrPreorder.push_back(current->getKey());
	//llamar recursivamente al sub arbol izq
	if (current->getLeft() != NULL)
	{
		recursive_preorder(current->getLeft());
	}
	//llamar recursivamente al sub arbol der 
	if (current->getRight() != NULL)
	{
		recursive_preorder(current->getRight());
	}

}
void postorder(){ // izq derecha raiz
	recursive_postorder(root);
}
void recursive_postorder(Node* current){
	//llamar recursivamente al sub arbol izq
	if (current->getLeft() != NULL)
	{
		recursive_postorder(current->getLeft());
	}
	
	//llamar recursivamente al sub arbol der 
	if (current->getRight() != NULL)
	{
		recursive_postorder(current->getRight());
	}
	//imprimr el valor de la raiz
	cout <<current->getKey();
	cout <<"->";
	arrPostorder.push_back(current->getKey());
}
void inorder(){
	recursive_inorder(root);
}
void recursive_inorder(Node* current){//izq raiz der 

	//llamar recursivamente al sub arbol izq
	if (current->getLeft() != NULL)
	{
		recursive_inorder(current->getLeft());
	}
	//imprimr el valor de la raiz
	cout <<current->getKey();
	arrInorder.push_back(current->getKey());
	cout <<"->";
	//llamar recursivamente al sub arbol der 
	if (current->getRight() != NULL)
	{
		recursive_inorder(current->getRight());
	}
}

void graphInorder(){
	string titulo = "ABBInorder.dot";
	string contenido = "digraph G { \n rankdir=LR;\n node [shape = record, style=filled, fillcolor=seashell2];\n";
	string indice;
	for(auto x =0 ; x< arrInorder.size()-1;x++){
		string dato = arrInorder[x];
		contenido+= dato + "->";
	}
	string dato2 = arrInorder[arrInorder.size()-1];
	contenido+=dato2;
	contenido+="}";
	ofstream fs(titulo.c_str());
    fs << contenido << endl;
    fs.close();
	system("cmd /c dot -Tpng ABBInorder.dot -o ABBInorder.png");
       // system("cmd /c ls");
    system("cmd /c ABBInorder.png");
}
void graphPreorder(){
	string titulo = "ABBPreorder.dot";
	string contenido = "digraph G { \n rankdir=LR;\n node [shape = record, style=filled, fillcolor=seashell2];\n";
	string indice;
	for(auto x =0 ; x< arrPreorder.size()-1;x++){
		string dato = arrPreorder[x];
		contenido+= dato + "->";
	}
	string dato2 = arrPreorder[arrPreorder.size()-1];
	contenido+=dato2;
	contenido+="}";
	ofstream fs(titulo.c_str());
    fs << contenido << endl;
    fs.close();
	system("cmd /c dot -Tpng ABBPreorder.dot -o ABBPreorder.png");
       // system("cmd /c ls");
    system("cmd /c ABBPreorder.png");
}
void graphPostorder(){
	string titulo = "ABBPostorder.dot";
	string contenido = "digraph G { \n rankdir=LR;\n node [shape = record, style=filled, fillcolor=seashell2];\n";
	string indice;
	for(auto x =0 ; x< arrPostorder.size()-1;x++){
		string dato = arrPostorder[x];
		contenido+= dato + "->";
	}
	string dato2 = arrPostorder[arrPostorder.size()-1];
	contenido+=dato2;
	contenido+="}";
	ofstream fs(titulo.c_str());
    fs << contenido << endl;
    fs.close();
	system("cmd /c dot -Tpng ABBPostorder.dot -o ABBPostorder.png");
       // system("cmd /c ls");
    system("cmd /c ABBPostorder.png");
	//cout<<contenido;
}
void graph(){
	string titulo = "aBinario.dot";
    string contenido = "digraph G { \n rankdir=TB;\n node [shape = record, style=filled, fillcolor=seashell2];\n";
	contenido+= contenidoDot(root);
	contenido+="}";
	//cout<<contenido;
	ofstream fs(titulo.c_str());
    fs << contenido << endl;
    fs.close();
	system("cmd /c dot -Tpng aBinario.dot -o aBinario.png");
       // system("cmd /c ls");
    system("cmd /c aBinario.png");
}

string contenidoDot(Node* current){
	string contenido ="";
	if(current!=NULL){
		contenido+=current->getKey();
		contenido+="\n";
		string hojaI = contenidoDot(current->getLeft());
		if(hojaI!=""){
			contenido+=current->getKey()+"->"+hojaI;
		}
		string hojaD = contenidoDot(current->getRight());
		if(hojaD!=""){
			contenido+=current->getKey()+"->"+hojaD; 
		}
	}
	return contenido;
}

};
/*
int main(){
	ABB *tree = new ABB();
	tree->add(new Node("Mario1"));
	tree->add(new Node("Pikachu"));
	tree->add(new Node("Boo"));
	tree->add(new Node("Geoff"));
	tree->add(new Node("Mario2"));
	tree->add(new Node("Mushroom"));

	
	
	tree->postorder();//de menor a mayor, ordenados 
	cout<<"\n";
	//tree->preorder();
	cout<<"\n";
	tree->graphPostorder();
	//tree->postorder();
	
	cout<<"\n";
	//tree->graph();


}*/