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
	int id;
public:
	
	Node(string key, int id){
		this->key = key;
		right = NULL;
		left = NULL;
		this->id=id;
	}

	string getKey(){
		return this->key;
	}
	int getId(){
		return this->id;
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
	void setId(int id){
		this->id = id;
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
	int contadorIn = 1;
	bool inorderFlag;
	bool postorderFlag;
	bool preorderFlag;
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
	if(preorderFlag == false){
		recursive_preorder(root);
		preorderFlag = true;
	}
	
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
	if(postorderFlag == false){
		recursive_postorder(root);
		postorderFlag = true;
	}
	
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
	if(inorderFlag == false){
		recursive_inorder(root);
		inorderFlag = true;
	}
	
	//cout<<" se insertaron datos inorder:"<<arrInorder.size()<<endl;
	//system("cmd /c pause");
}
void recursive_inorder(Node* current){//izq raiz der 

	//llamar recursivamente al sub arbol izq
	if (current->getLeft() != NULL)
	{
		recursive_inorder(current->getLeft());
	}
	//imprimr el valor de la raiz
	//cout <<current->getId()<<current->getKey();
	//cout<<current->getKey();
	contadorIn++;
	arrInorder.push_back(current->getKey());
	//cout <<"\n";
	//llamar recursivamente al sub arbol der 
	if (current->getRight() != NULL)
	{
		recursive_inorder(current->getRight());
	}
}

void selectImageIn(){
	contadorIn = 1;
	//system("cmd /c pause");
	cout<<"------------imageness"<<endl;
	if(inorderFlag == false){
		//cout<<"inorder vacio"<<endl;
		recursive_inorder(root);
		for(int i = 0;i<arrInorder.size();i++){
			string dato = arrInorder[i];
			cout<<i<<" - "<<dato<<endl;
		}
		inorderFlag = true;
	}else{
		for(int i = 0;i<arrInorder.size();i++){
			string dato = arrInorder[i];
			cout<<i<<" - "<<dato<<endl;
		}
	}
	
	
	//system("cmd /c pause");
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
	//contenido+= contenidoDot(root);
	contenido+=contenidoInterno(root);
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
string contenidoInterno(Node* current){
	string contenido ="";
	
	if(current->getLeft()==NULL && current->getRight() == NULL){
		contenido = "nodo"+ to_string(current->getId())+ "[ label= \"" + current->getKey() + "\"];\n";

	}else{
		contenido = "nodo"+ to_string(current->getId())+ "[ label= \" <C0>|" + current->getKey() + "|<C1> \"];\n";
	}
	if(current->getLeft()!=NULL){
		contenido+= contenidoInterno(current->getLeft()) + "nodo"+ to_string(current->getId())+":C0->nodo"+ to_string(current->getLeft()->getId()) + "\n";

	}
	if(current->getRight()!=NULL){
		contenido+= contenidoInterno(current->getRight()) + "nodo"+ to_string(current->getId())+":C1->nodo"+ to_string(current->getRight()->getId()) + "\n";

	}
	
	return contenido;
}
};
/*
int main(){

	int correlativo = 1;
	ABB *tree = new ABB();
	tree->add(new Node("Mario1", correlativo));
	correlativo++;
	tree->add(new Node("Pikachu", correlativo));
	correlativo++;
	tree->add(new Node("Boo",correlativo));
	correlativo++;
	tree->add(new Node("Geoff",correlativo));
	correlativo++;
	tree->add(new Node("Mario2",correlativo));
	correlativo++;
	tree->add(new Node("Mushroom",correlativo));

	
	
	//tree->inorder();//de menor a mayor, ordenados 
	cout<<"\n";
	//tree->preorder();
	cout<<"\n";
	//tree->graphPostorder();
	//tree->postorder();
	
	cout<<"\n";
	tree->graph();


}*/