#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include"../LinkedList/mainList.cpp"
//#include"../Circular/circularMain.cpp"

using namespace std;


class Node{
private:
	string key;
	Node *left;
	Node *right;
	linked *lista;
	int imageH;
	int imageW;
	int pixelH;
	int pixelW;
	int id;
	//hacer mas atributos de lo del archivo config width height
public:
	
	Node(string key, int id, linked* lista, int imageH, int imageW, int pixelH, int pixelW){
		this->key = key;
		right = NULL;
		left = NULL;
		this->id=id;
		this->lista = lista;
		this->imageH = imageH;
		this->imageW = imageW;
		this->pixelH = pixelH;
		this->pixelW = pixelW;
	}
	linked* getLista(){
		return this->lista;
	}
	string getKey(){
		return this->key;
	}
	int getId(){
		return this->id;
	}
	int getImageH(){
		return this->imageH;
	}
	int getImageW(){
		return this->imageW;
	}
	int getPixelH(){
		return this->pixelH;
	}
	int getPixelW(){
		return this->pixelW;
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
	void setLista(linked *lista){
		this->lista = lista;
	}
};


class ABB{
private:
	Node *root;
public:
	vector<string> arrInorder;
	vector<string> arrPreorder;
	vector<string> arrPostorder;
	vector<Node*> arrNodes;
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
	arrNodes.push_back(current);
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
		//recorrer arrrNodes
		/*for(int i = 0;i<arrInorder.size();i++){
			string dato = arrInorder[i];
			cout<<i<<" - "<<dato<<endl;
		}*/
		for(int j = 0;j<arrNodes.size();j++){
			Node *current = arrNodes[j];
			cout<<j+1<<" - "<<current->getKey()<<endl;
			
		}
		
		inorderFlag = true;
	}else{
		/*for(int i = 0;i<arrInorder.size();i++){
			string dato = arrInorder[i];
			cout<<i<<" - "<<dato<<endl;
		}*/
		for(int j = 0;j<arrNodes.size();j++){
			Node *current = arrNodes[j];
			cout<<j+1<<" - "<<current->getKey()<<endl;
		}
	}
	
}
Node* returnImagenSel(int numImagen){
	//linked *lista;
	for(int i = 0;i<arrNodes.size();i++){
		Node *current = arrNodes[i];
		if(current->getId() == numImagen){
			
			return current;
		}
	}
}
void mostarCapasImagen(int numImagen){
	for (int i = 0; i < arrNodes.size(); i++)
	{
		Node *current = arrNodes[i];
		if(current->getId() == numImagen){
			int numCapaG;
			linked *lista = current->getLista();
			
			cout<<"Desea graficar 1 capa o todas las capas?"<<endl;
			cout<<"1....Una capa. \n 2....Toda la imagen."<<endl;
			cout<<"Opcion: ";
			int opcionCapaToda;
			cin>>opcionCapaToda;
			if(opcionCapaToda == 1){
				cout<<"Esta imagen tiene: "<<lista->size()<<" capas"<<endl;
				cout<<"Ingrese el numero de capa que desea graficar: ";
				cin>>numCapaG;
				//verificar si se paso del numero de capas				
				nodeList *nodoLista= lista->getNodo(numCapaG);
				
				matrix *matriz = nodoLista->getMatrix();
				cout<<"Se obtubo: "<<nodoLista->getKey()<<endl;
				if(matriz->head == NULL){
					cout<<"matriz vacia"<<endl;
				}else
				{
					cout<<"dato matriz: "<<matriz->head->color<<endl;
					if(matriz->head->right == NULL){
						cout<<"no tiene derecha"<<endl;
					}else
					{
						cout<<"dato derecha"<<matriz->head->right<<endl;
					}
					
				}
				
				//cout<<"dato: "<<matriz->head->right->down->color<<endl;

				//matriz->graphMatrix(" ", " ");
			}else if(opcionCapaToda == 2){
				//aqui juntar las capas en 1 sola y graficar
				matrix *matrizCompleta = new matrix();
				for(int t=0;t<lista->size();t++){
					nodeList *nodoCapa = lista->getNodo(t+1);
					matrix *matrizCapa = nodoCapa->getMatrix();
					matrizCapa->graphMatrix("","");
					//llenarMatrizC(matrizCompleta, matrizCapa);
				}
				//matrizCompleta->graphMatrix(" "," ");
				// no se donde guardar matriz completa
				//system("cmd /c pause");
			}else{
				cout<<"opcion invalida";
			}
		}
	}
}
void capasLinear(int numImagen){
	linked *lista = new linked();
	for(int i = 0 ; i<arrNodes.size();i++){
		Node *current = arrNodes[i];
		if(current->getId() == numImagen){
			int numCapaG;
			linked *lista = current->getLista();
			cout<<"this image has: "<<lista->size()<<" layers, being 1 the first layer."<<endl;
			cout<<"Enter the layer number you want to graph: ";
			cin>>numCapaG;
			nodeList *nodoLista= lista->getNodo(numCapaG);
			matrix *matriz = nodoLista->getMatrix();
			cout<<"-------------------------------------------------";
			cout<<"1 - Rows \n 2 - Columns";
			cout<<"\n";
			cout<<"Enter the option number"<<endl;
			int opcion;
			cin>>opcion;
			if(opcion == 1){
				// filas
				linealFilas(matriz);
			}else if(opcion == 2){
				//columns
				linealColumnas(matriz);
			}else
			{
				cout<<"Invalid Option.";
			}
			
			
			
		}
	}
}
void linealFilas(matrix* matriz){
	string titulo = "ABBInorder.dot";
	string contenido = "digraph G { \n rankdir=LR;\n node [shape = record, style=filled, fillcolor=seashell2];\n";
	string indice;
	node *temp = matriz->head;
	int contador2 =1;
	while(temp->down!=NULL){
		node *aux = temp->down->right;
		while(aux->right!=NULL){
			contenido+= to_string(contador2)+"[label = \"" + "("+ to_string(aux->x) + ","+ to_string(aux->y)+")"+ to_string(aux->r)  + "-"+ to_string(aux->g) + "-" + to_string(aux->b) + " \"] \n"; 
			contenido+=to_string(contador2)+ "->" + to_string(contador2+1) + "\n";
			cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<" 	numero:"<<contador2<<endl;
			contador2++;
			aux = aux->right;
			if(aux->right == NULL){
				cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<" 	numero:"<<contador2<<endl;
				
				contenido+= to_string(contador2)+"[label = \"" + "("+ to_string(aux->x) + ","+ to_string(aux->y)+")"+ to_string(aux->r)  + "-"+ to_string(aux->g) + "-" + to_string(aux->b) + " \"] \n";   
				contenido+=to_string(contador2)+ "->" + to_string(contador2+1) + "\n";
				contador2++;
			}
		}
		temp = temp->down;
	}


	/*for(auto x =0 ; x< arrInorder.size()-1;x++){
		string dato = arrInorder[x];
		contenido+= dato + "->";
	}
	string dato2 = arrInorder[arrInorder.size()-1];
	contenido+=dato2;*/
	contenido+="}";
	ofstream fs(titulo.c_str());
    fs << contenido << endl;
    fs.close();
	system("cmd /c dot -Tpng ABBInorder.dot -o ABBInorder.png");
       // system("cmd /c ls");
    system("cmd /c ABBInorder.png");

}
void linealColumnas(matrix* matriz){
	string titulo = "ABBInorder.dot";
	string contenido = "digraph G { \n rankdir=LR;\n node [shape = record, style=filled, fillcolor=seashell2];\n";
	string indice;
	node *temp = matriz->head;
	int contador2 =1;
	while(temp->right!=NULL){
		node *aux = temp->right->down;
		while(aux->down!=NULL){
			contenido+= to_string(contador2)+"[label = \"" + "("+ to_string(aux->x) + ","+ to_string(aux->y)+")"+ to_string(aux->r)  + "-"+ to_string(aux->g) + "-" + to_string(aux->b) + " \"] \n"; 
			contenido+=to_string(contador2)+ "->" + to_string(contador2+1) + "\n";
			cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<" 	numero:"<<contador2<<endl;
			contador2++;
			aux = aux->down;
			if(aux->down == NULL){
				cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<" 	numero:"<<contador2<<endl;
				
				contenido+= to_string(contador2)+"[label = \"" + "("+ to_string(aux->x) + ","+ to_string(aux->y)+")"+ to_string(aux->r)  + "-"+ to_string(aux->g) + "-" + to_string(aux->b) + " \"] \n";   
				contenido+=to_string(contador2)+ "->" + to_string(contador2+1) + "\n";
				contador2++;
			}
		}
		
		temp = temp->right;
		if(temp->right == NULL){
			temp = temp->down;
			if(temp->down == NULL){
				cout<<"Estamos en: X:"<<temp->x<<","<<temp->y<<" 	numero:"<<contador2<<endl;
				contenido+= to_string(contador2)+"[label = \"" + "("+ to_string(temp->x) + ","+ to_string(temp->y)+")"+ to_string(temp->r)  + "-"+ to_string(temp->g) + "-" + to_string(temp->b) + " \"] \n";   
				contenido+=to_string(contador2)+ "->" + to_string(contador2+1) + "\n";
				contador2++;
			}else{
				while(temp->down!=NULL){
				cout<<"Estamos en: X:"<<temp->x<<","<<temp->y<<" 	numero:"<<contador2<<endl;
				contenido+= to_string(contador2)+"[label = \"" + "("+ to_string(temp->x) + ","+ to_string(temp->y)+")"+ to_string(temp->r)  + "-"+ to_string(temp->g) + "-" + to_string(temp->b) + " \"] \n";   
				contenido+=to_string(contador2)+ "->" + to_string(contador2+1) + "\n";
				contador2++;
				temp=temp->down;
				}
			}
			

		}
	}


	/*for(auto x =0 ; x< arrInorder.size()-1;x++){
		string dato = arrInorder[x];
		contenido+= dato + "->";
	}
	string dato2 = arrInorder[arrInorder.size()-1];
	contenido+=dato2;*/
	contenido+="}";
	ofstream fs(titulo.c_str());
    fs << contenido << endl;
    fs.close();
	system("cmd /c dot -Tpng ABBInorder.dot -o ABBInorder.png");
       // system("cmd /c ls");
    system("cmd /c ABBInorder.png");
}
void llenarMatrizC(matrix* matrizCompleta, matrix* matrizhijo){
	node *temp = matrizhijo->head->right;
	//cout<<"primero: "<<temp->down->x<<","<<temp->down->y<<endl;
	while (temp->right!=NULL){
		node *aux = temp->down;
		if(aux->down == NULL){
			//insertar aqui
			matrizCompleta->add(aux->x,aux->y,aux->r,aux->g,aux->b);
			//cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<"  tiene color: "<< aux->color<<endl;
		}
		while (aux->down!=NULL)
		{
			//insertar aqui
			matrizCompleta->add(aux->x,aux->y,aux->r,aux->g,aux->b);
			//cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<"  tiene color: "<< aux->color<<endl;
			aux = aux->down;
			if (aux->down == NULL)
			{
				//insertar aqui
				matrizCompleta->add(aux->x,aux->y,aux->r,aux->g,aux->b);
				//cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<"  tiene color: "<< aux->color<<endl;
			}
			
		}		
		temp = temp->right;
		if (temp->right == NULL)
		{
			node *aux2 = temp->down;
			while (aux2->down!=NULL)
			{
				//insertar aqui
				matrizCompleta->add(aux2->x,aux2->y,aux2->r,aux2->g,aux2->b);
				//cout<<"Estamos en: X:"<<aux2->x<<","<<aux2->y<<"  tiene color: "<< aux2->color<<endl;
				aux2 = aux2->down;
				if (aux2->down == NULL)
				{
					//insertar aqui
					matrizCompleta->add(aux2->x,aux2->y,aux2->r,aux2->g,aux2->b);
					//cout<<"Estamos en: X:"<<aux2->x<<","<<aux2->y<<"  tiene color: "<< aux2->color<<endl;
				}
			}
			
		}
	}
	cout<<"\n Termino UNA MATRIZ"<<endl;

}
int contarNodos(matrix* matrizCompleta){
	int contador = 0;
	node *temp = matrizCompleta->head->right;
		while (temp->right!=NULL){
			node *aux = temp->down;
			if(aux->down == NULL){
				//insertar aqui
				contador++;
				//matrizCompleta->add(aux->x,aux->y,aux->r,aux->g,aux->b);
				//cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<"  tiene color: "<< aux->color<<endl;
			}
			while (aux->down!=NULL)
			{
				//insertar aqui
				contador++;
				//matrizCompleta->add(aux->x,aux->y,aux->r,aux->g,aux->b);
				//cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<"  tiene color: "<< aux->color<<endl;
				aux = aux->down;
				if (aux->down == NULL)
				{
					//insertar aqui
					contador++;
					//matrizCompleta->add(aux->x,aux->y,aux->r,aux->g,aux->b);
					//cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<"  tiene color: "<< aux->color<<endl;
				}
				
			}		
			temp = temp->right;
			if (temp->right == NULL)
			{
				node *aux2 = temp->down;
				while (aux2->down!=NULL)
				{
					//insertar aqui
					contador++;
					//matrizCompleta->add(aux2->x,aux2->y,aux2->r,aux2->g,aux2->b);
					//cout<<"Estamos en: X:"<<aux2->x<<","<<aux2->y<<"  tiene color: "<< aux2->color<<endl;
					aux2 = aux2->down;
					if (aux2->down == NULL)
					{
						//insertar aqui
						contador++;
						//matrizCompleta->add(aux2->x,aux2->y,aux2->r,aux2->g,aux2->b);
						//cout<<"Estamos en: X:"<<aux2->x<<","<<aux2->y<<"  tiene color: "<< aux2->color<<endl;
					}
				}
				
			}
	}

	//cout<<"Cantidad de nodos: "<<contador<<endl;
	return contador;
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
		contenido = "nodo"+ to_string(current->getId())+ "[ label= \"" + to_string(current->getId()) + current->getKey() + "\"];\n";

	}else{
		contenido = "nodo"+ to_string(current->getId())+ "[ label= \" <C0>|" + to_string(current->getId())+ current->getKey() + "|<C1> \"];\n";
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