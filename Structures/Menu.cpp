#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include"ABB/mainABB.cpp"
#include"Circular/circularMain.cpp"
//#include"Matrix/main.cpp"
//#include"LinkedList/mainList.cpp"

using namespace std;
ABB *tree = new ABB();
int correlativo = 1;
int imagewidht;
int imageheight;
int pixelwidht;
int pixelheight;
linked *listaSeleccionada;
Node *imagenSelNode;
linkedCircular *listaCircular;//cada vez que seleccione una imagen, hay que inicializarza a new


void entrarConfig(string nombre, string padre){
	//cout<<"entrooo:" << nombre<<endl;
	vector<string> data;
    vector<string> datocomas;
	string abrir = padre+"/"+nombre;
	//system("cmd /c cls");
	//cout<<"abrira: "<<abrir<<endl; 
	//system("cmd /c pause");
    ifstream archivo;
    string line;
	archivo.open(abrir);
	while(archivo.good()){
		getline(archivo,line,archivo.widen('\n'));
		if(line.size()>1){
			size_t tam = line.length();
			string cad = line.substr(tam-1);
			cout<<"Dato ULTIMA de:"<<line<<" es: "<<cad<<endl;
			if(cad=="\n"){
				line.erase(tam-1);
			}
			//line.erase(tam-1);
			data.push_back(line);
		}
	}
	for(int i =0;i<data.size();i++){
        
        string datoEnConfig = data[i];
        //cout<<"dato: "<<i<<" "<<datoEnConfig<<"findato"<<endl;
        //ahora por comas
        string word = "";
        for(auto x : datoEnConfig){
            if(x == ','){
                datocomas.push_back(word);
                word="";
            }else{
                word = word+x;
            }
        }
        datocomas.push_back(word);
    }
	string imagew = datocomas[3];
    string imageh= datocomas[5];
    string pixelw= datocomas[7];
    string pixelh= datocomas[9];
	imagewidht = stoi(imagew);
    imageheight = stoi(imageh);
    pixelwidht = stoi(pixelw);
    pixelheight = stoi(pixelh);
	/*
	cout<<"datos:::::"<<endl;
	cout<<imagewidht<<endl;
    cout<<imageheight<<endl;
    cout<<pixelwidht<<endl;
    cout<<pixelheight<<endl;
	system("cmd /c pause");
	*/
}
void obtenerConfig(string linea, string padre){
	vector<string> config;
	string word="";
	for(auto x : linea){
        if(x == ','){
            //cout<<word<<endl;
            config.push_back(word);
            word="";
        }
        else{
            word = word +x;
        }
    }
	config.push_back(word);
	string configdato = config[1];
	size_t tam = configdato.length();
	configdato.erase(tam-1);
	entrarConfig(configdato, padre);
}
void entrarCapa(string capa, string padre, matrix *m, linked* lista){
	//matrix *m = new matrix;
	vector<string> config;
    vector<string> data;
    //vector<string>datoM;
    string contenido;
    ifstream archivo;
    int contador = 0;
	string line;
    string abrir;
    int numCapa;
    string word="";
    string word2="";
	for(auto x : capa){
        if(x == ','){
            //cout<<word<<endl;
            config.push_back(word);
            word="";
        }
        else{
            word = word +x;
        }
    }
	config.push_back(word);
	//en capa[0] esta el numero de capa
	//en capa[1] esta capa.csv
    string dato = config[1];
    abrir = padre+"/"+dato;
	//cout<<"\n abrira: "<<abrir<<endl;
    archivo.open(abrir);
    int varx=0;
    int vary=0;
	while(archivo.good()){
        vector<string>datoM;
        getline(archivo,line,archivo.widen('\n'));
        if(line.size()>1){
            size_t tama = line.size();
            line.erase(tama-1);
			//cout<<"Info en linea: "<<line<<endl;
            for(auto j : line){
                if(j == ','){
                    datoM.push_back(word2);
					//cout<<"Metio1: "<<word2<<endl;
                    word2="";
                }else{
                    word2 = word2+j;
                }
            }
            datoM.push_back(word2);
			//cout<<"Metio: "<<word2<<endl;
			word2= "";
            //cout<<"Tamanio: "<<datoM.size()<<endl;
            for(int o =0;o<datoM.size();o++){
				int r;
				int g;
				int b;
				string palabra;
				vector<string>colores;
			    string enM = datoM[o];
				//cout<<"DATO ENC "<<enM<<endl;
				if(enM.size()>4){
                    for(auto l:enM){
                        if(l=='-'){
                            colores.push_back(palabra);
                            palabra="";
                        }else{
                            palabra=palabra+l;
                        }
                    }
                    colores.push_back(palabra);
                    //cout<<"Tamanio de colores:"<<colores.size()<<endl;
                    r = stoi(colores[0]);
                    g = stoi(colores[1]);
                    b = stoi(colores[2]);
                    //cout<<"Colores: "<<r<<","<<g<<","<<b<<" en:"<<o+1<<","<<vary+1<<endl;
					m->add(o+1,vary+1,r,g,b);
					
                }
				
                //cout<<"Dato en indice:"<<o<<": "<<r<<","<<g<<","<<b<<"*"<<" X="<<o<<" Y="<<vary<<endl;

            }
            vary++;
            ///cout<<line<<"*"<<endl;
        }
       line = "";
    }
	//cout<<"Vamos a insertar en la lista"<<endl;
	//config[0] tiene el numero de capa
	string numCapa2 = config[0];
	//cout<<"Termino lectura :v"; 
	//system("cmd /c pause");
	lista->add(new nodeList(stoi(numCapa2),m));
	//aqui hacer la carpeta para guardarlo
	//string consola = "cmd /c mkdir ";
	//consola+= padre + "Reports";
	//system(consola.c_str());
	//m->graphMatrix(padre, numCapa2);
	//
}
void archivoInicial(string nombre, linked *lista){
	vector<string> data;
    string contenido;
    ifstream archivo;
    int contador = 0;
	string line;
	string abrir = nombre+"/"+nombre+".csv";
	archivo.open(abrir);
	while (archivo.good())
	{	
		getline(archivo,line,archivo.widen('\n'));
		//cout<<line<<"*"<<endl;
		if(line.size()>1){
			data.push_back(line);
		}
	}	
	string config = data[1];
	//cout<<"Se enviara: "<<config<<endl;
	obtenerConfig(config,nombre);
	
	// en data[2] en adelante son puras capas
	for(int q =2;q<data.size();q++){
		//cout<<"Entro a FOR INICIAL"<<endl;
		
		string capa = data[q];
		
		size_t tam = capa.length();
		string cad = capa.substr(tam-1);
		//cout<<"LETRA ULTIMA de:"<<capa<<" es: "<<cad<<endl;
		if(cad!="v"){
			capa.erase(tam-1);
		}
		
		//cout<<"enviara capa: "<<capa<<endl;

		//system("cmd /c pause");
		
		//matriz hacerla aqui pero llenarla en el siguiente metodo
		// por el nodo, el numero de capa que se obtiene hasta el sig metodo
		matrix *ma = new matrix();
		entrarCapa(capa,nombre, ma, lista);
		//ma->graphMatrix(nombre, capa);
	}

	
	/*string capa = data[2];
	size_t tam = capa.length();
	capa.erase(tam-1);
	cout<<"enviara capa: "<<capa<<endl;
	system("cmd /c pause");
	//matriz hacerla aqui pero llenarla en el siguiente metodo
	// por el nodo, el numero de capa que se obtiene hasta el sig metodo
	matrix *ma = new matrix();
	entrarCapa(capa,nombre, ma, lista);
	ma->graphMatrix(nombre, capa);
	*/
	//system("cmd /c pause");


	//armarCss(nombre);
}
void menuABB(){
	bool bandera=false;
    char tecla;
	string nombreImagen="";
    do{
        system("cmd /c cls"); 
        cin.clear();
        cout << "---------------------  TRAVERSAL REPORT  -------------------------" << endl;
        cout << "-----------" << endl << endl;
        cout << "\t1 .- Inorder Traversal" << endl;
        cout << "\t2 .- Postorder Traversal" << endl;
        cout << "\t3 .- Preorder Traversal" << endl;
        cout << "\t4 .- Back Menu" << endl << endl;
        cout << "Elije una opcion: ";
        cin >> tecla;
        switch(tecla)
		{
			case '1':
				//system("cmd /c cls"); 
				cout << "inorder:\n";
				tree->inorder();
				tree->graphInorder();
				//system("cmd /c pause");
				break;
 
			case '2':
				system("cmd /c cls"); 
				cout << "postorder.\n";
				tree->postorder();
				tree->graphPostorder();
				break;
 
			case '3':
				system("cmd /c cls"); 
				cout << "preorder.\n";
				tree->preorder();
				tree->graphPreorder();
				break;
 
            case '4':
				bandera = true;
				break;
             
			default:
				system("cmd /c cls"); 
				cout << "Opcion no valida.\a\n";
				
				break;
		}
    }while(bandera!=true);
}

void menuReports(){
	bool bandera=false;
    char tecla;
	string nombreImagen="";
    do{
        system("cmd /c cls"); 
        cin.clear();
        cout << "---------------------  REPORTS MENU  -------------------------" << endl;
        cout << "-----------" << endl << endl;
        cout << "\t1 .- IMPORTED IMAGES REPORT" << endl;
        cout << "\t2 .- IMAGE LAYER REPORT" << endl;
        cout << "\t3 .- LINEAR MATRIX REPORT" << endl;
        cout << "\t4 .- TRAVERSAL REPORT" << endl;
        cout << "\t5 .- FILTERS REPORT" << endl;
        cout << "\t6 .- Back Menu" << endl << endl;
        cout << "Elije una opcion: ";
        cin >> tecla;
        switch(tecla)
		{
			case '1':
				//system("cmd /c cls"); 
				cout << "Arbol binario:\n";
				tree->graph();
				system("cmd /c pause");
				break;
 
			case '2':
				system("cmd /c cls"); 
				cout << "select.\n";
				tree->selectImageIn();
				cout<<"Ingrese el numero de imagen: ";
				int numimagen;
				cin>>numimagen;
				tree->mostarCapasImagen(numimagen);
				system("cmd /c pause");
				break;
 
			case '3':
				system("cmd /c cls"); 
				cout << "LINEAR MATRIX REPORT.\n";
				tree->selectImageIn();
				cout<<"Ingrese el numero de imagen: ";
				int numimagen2;
				cin>>numimagen2;
				tree->capasLinear(numimagen2);
				system("cmd /c pause");
				break;
 
			case '4':
				system("cmd /c cls"); 
				//sub menu inorder preorder postorder
				menuABB();
				//system("cmd /c pause");
				break;
 
			case '5':
				system("cmd /c cls"); 
				cout << "export image.\n";
				system("cmd /c pause");
				break;
            case '6':
				bandera = true;
				break;
             
			default:
				system("cmd /c cls"); 
				cout << "Opcion no valida.\a\n";
				
				break;
		}
    }while(bandera!=true);
}
void selectImage(){
	//system("cmd /c cls"); 
	tree->selectImageIn();
	system("cmd /c pause"); 
}
string decToHexa(int n){
	if(n < 10){
        //cout<<"entro cero"<<endl;
        return "0"+to_string(n);
        
    }
		string color;
		// char array to store hexadecimal number 
		char hexaDeciNum[100]; 
		
		// counter for hexadecimal number array 
		int i = 0; 
		while(n!=0) 
		{    
			// temporary variable to store remainder 
			int temp  = 0; 
			
			// storing remainder in temp variable. 
			temp = n % 16; 
			
			// check if temp < 10 
			if(temp < 10) 
			{ 
				hexaDeciNum[i] = temp + 48; 
				i++; 
			} 
			else
			{ 
				hexaDeciNum[i] = temp + 55; 
				i++; 
			} 
			
			n = n/16; 
		} 
		
		// printing hexadecimal number array in reverse order 
		for(int j=i-1; j>=0; j--){ 
			//cout << hexaDeciNum[j];
			color.push_back(hexaDeciNum[j]);
			
		}
		return color;

	   
    
} 
string llenarCss(matrix* matriz){
	string contenido =" ";

	vector<string> prueba;
	node *temp = matriz->head;
	int contador = 1;
	while(temp->down!=NULL){
		node *aux = temp->down->right;
		while (aux->right!=NULL){
			//cout<<"estamos en x,y: "<<aux->x<<","<<aux->y<<"	"<<contador<<endl;
			contenido+= ".pixel:nth-child("+ to_string(((aux->y -1)*imagenSelNode->getImageW())+ aux->x) + "){ background: #" + decToHexa(aux->r) +decToHexa(aux->g)+decToHexa(aux->b) + "}\n";
			contador++;
			aux = aux->right;
			if(aux->right==NULL){
				//cout<<"estamos en x,y: "<<aux->x<<","<<aux->y<<"	"<<contador<<endl;
				contenido+= ".pixel:nth-child("+ to_string(((aux->y -1)*imagenSelNode->getImageW())+ aux->x) + "){ background: #" + decToHexa(aux->r) +decToHexa(aux->g)+decToHexa(aux->b) +"}\n";
				contador++;
			}
		}
		
		temp = temp->down;
	}
	return contenido;
}
void armarCss(string padre, linked* lista ){
	//system("cmd /c cls");
	string contenidoChild;
	//linked *lista = imagenSelNode->getLista();
	matrix *matrizCompleta = new matrix();
	for(int i = 0; i< lista->size();i++){
		//cout<<"entro  a for indiceL "<<i<<endl;
		//system("cmd /c pause"); 
		nodeList *nodoLista = lista->getNodo(i+1);
		matrix *matrizcapa = nodoLista->getMatrix();
		contenidoChild += llenarCss(matrizcapa);
		//tree->llenarMatrizC(matrizCompleta,matrizcapa);
	}
	//string contenidoChild = llenarCss(matrizCompleta);
	system("cmd /c pause"); 
	int cantidadN;
	int canvasW = imagenSelNode->getImageW() * imagenSelNode->getPixelW();
	int canvasH = imagenSelNode->getImageH() * imagenSelNode->getPixelH();
	cout<<"Valores w y h"<<canvasW<<" y "<<canvasH<<endl;
	system("cmd /c pause"); 
	ofstream css;
	string nombre = imagenSelNode->getKey();
	css.open("Exports/"+nombre+".css");
	css << "body{background: #333333; \n  height: 100vh;\n display: flex;  \n justify-content: center;\n align-items: center; \n  }\n"; 
	css << ".canvas{\n width: " + to_string( canvasW) + "px; \n height: " +to_string( canvasH) + "px; \n } \n";
	css << ".pixel{\n width: " + to_string( imagenSelNode->getPixelW()) + "px; \n height: " +to_string( imagenSelNode->getPixelH()) + "px; \n";
	css << "float: left; \n";
	css << "box-shadow: 0px 0px 1px #fff;";
	css << "}\n";
	//css << llamar a metodo de los child
	css<< contenidoChild;
	css.close();

	//system("cmd /c pause");
}
void exportHtml(){
	int cantidadN =0;
	ofstream html;
	string nombre = imagenSelNode->getKey();
	int cantDivs = imagenSelNode->getImageW() * imagenSelNode->getImageH();
	html.open("Exports/"+nombre+".html");
	html << "<!DOCTYPE html><html> \n <head> <link rel=\"stylesheet\" href=\"" + nombre +".css \" >\n" ;
	html << "</head> \n <body> \n <div class=\" canvas \"> \n";
	for(int j = 0;j<cantDivs;j++){
		html << "<div class = \"pixel\"></div> \n";
		
	}
	html << "</div> \n </body> \n </html>";
	html.close();
	armarCss("",imagenSelNode->getLista());
	//system("cmd /c pause"); 

}

void exportFiltro(linked* lista){
	int cantidadN =0;
	ofstream html;
	string nombre = imagenSelNode->getKey();
	int cantDivs = imagenSelNode->getImageW() * imagenSelNode->getImageH();
	html.open("Exports/"+nombre+".html");
	html << "<!DOCTYPE html><html> \n <head> <link rel=\"stylesheet\" href=\"" + nombre +".css \" >\n" ;
	html << "</head> \n <body> \n <div class=\" canvas \"> \n";
	for(int j = 0;j<cantDivs;j++){
		html << "<div class = \"pixel\"></div> \n";
		
	}
	html << "</div> \n </body> \n </html>";
	html.close();
	armarCss("", lista);
}
void llenarMatrizC(linked* listaCapas, matrix* matrizhijo, int key){
	matrix *m = new matrix();
	node *temp = matrizhijo->head->right;
	//cout<<"primero: "<<temp->down->x<<","<<temp->down->y<<endl;
	while (temp->right!=NULL){
		node *aux = temp->down;
		if(aux->down == NULL){
			//insertar aqui
			m->add(aux->x,aux->y,aux->r,aux->g,aux->b);
			//cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<"  tiene color: "<< aux->color<<endl;
		}
		while (aux->down!=NULL)
		{
			//insertar aqui
			m->add(aux->x,aux->y,aux->r,aux->g,aux->b);
			//cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<"  tiene color: "<< aux->color<<endl;
			aux = aux->down;
			if (aux->down == NULL)
			{
				//insertar aqui
				m->add(aux->x,aux->y,aux->r,aux->g,aux->b);
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
				m->add(aux2->x,aux2->y,aux2->r,aux2->g,aux2->b);
				//cout<<"Estamos en: X:"<<aux2->x<<","<<aux2->y<<"  tiene color: "<< aux2->color<<endl;
				aux2 = aux2->down;
				if (aux2->down == NULL)
				{
					//insertar aqui
					m->add(aux2->x,aux2->y,aux2->r,aux2->g,aux2->b);
					//cout<<"Estamos en: X:"<<aux2->x<<","<<aux2->y<<"  tiene color: "<< aux2->color<<endl;
				}
			}
			
		}
	}
	listaCapas->add(new nodeList(key,m));
	cout<<"\n Termino UNA MATRIZ"<<endl;

}
matrix* negativoDos(matrix* matrizH){
	node *temp = matrizH->head;
	cout<<"primero: "<<temp->x<<","<<temp->y<<endl;
	while(temp!=NULL){
		node *aux = temp->right;
		while(aux!=NULL){
			aux->r =255- aux->r;
			aux->g =255- aux->g;
			aux->b =255- aux->b;
			cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<endl;
			aux = aux->right;
			/*if(aux->right == NULL){
				cout<<"RIGHT Estamos en: X:"<<aux->x<<","<<aux->y<<endl;
				aux->r =255- aux->r;
				aux->g =255- aux->g;
				aux->b =255- aux->b;
			}*/
		}
		cout<<"Salto de linea"<<" valores de temp: "<<temp->x<<","<<temp->y<<endl;
		temp = temp->down;	
		/*if(temp->down == NULL){
				cout<<"RIGHTD Estamos en: X:"<<temp->x<<","<<temp->y<<endl;
				//aux->r =255- aux->r;
				//aux->g =255- aux->g;
				//aux->b =255- aux->b;
		}*/
		
	}
	return matrizH;
}
matrix* escalaGrisDos(matrix* matrizH){
	node *temp = matrizH->head;
	//cout<<"primero: "<<temp->x<<","<<temp->y<<endl;
	while(temp!=NULL){
		node *aux = temp->right;
		while(aux!=NULL){
			int suma = (int)(aux->r * 0.3 + aux->g*0.59 + aux->b * 0.11) ;
			aux->r = suma;
			aux->g =suma;
			aux->b =suma;
			//cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<endl;
			aux = aux->right;
			/*if(aux->right == NULL){
				cout<<"RIGHT Estamos en: X:"<<aux->x<<","<<aux->y<<endl;
				aux->r =255- aux->r;
				aux->g =255- aux->g;
				aux->b =255- aux->b;
			}*/
		}
		//cout<<"Salto de linea"<<" valores de temp: "<<temp->x<<","<<temp->y<<endl;
		temp = temp->down;	
		/*if(temp->down == NULL){
				cout<<"RIGHTD Estamos en: X:"<<temp->x<<","<<temp->y<<endl;
				//aux->r =255- aux->r;
				//aux->g =255- aux->g;
				//aux->b =255- aux->b;
		}*/
		
	}
	return matrizH;
}
matrix* negativo(matrix* matrizH){
	
	node *temp = matrizH->head->right;
		while (temp->right!=NULL){
			node *aux = temp->down;
			if(aux->down == NULL){
				//insertar aqui
				aux->r =255- aux->r;
				aux->g =255- aux->g;
				aux->b =255- aux->b;
				aux->color = "\"" + to_string(aux->r) + "," + to_string(aux->g) + "," + to_string(aux->b) + "\"";
				//matrizCompleta->add(aux->x,aux->y,aux->r,aux->g,aux->b);
				cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<"  tiene color: "<< aux->color<<endl;
			}
			while (aux->down!=NULL)
			{
				//insertar aqui
				aux->r =255- aux->r;
				aux->g =255- aux->g;
				aux->b =255- aux->b;
				aux->color = "\"" + to_string(aux->r) + "," + to_string(aux->g) + "," + to_string(aux->b) + "\"";
				//matrizCompleta->add(aux->x,aux->y,aux->r,aux->g,aux->b);
				cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<"  tiene color: "<< aux->color<<endl;
				aux = aux->down;
				if (aux->down == NULL)
				{
					//insertar aqui
					aux->r =255- aux->r;
					aux->g =255- aux->g;
					aux->b =255- aux->b;
					aux->color = "\"" + to_string(aux->r) + "," + to_string(aux->g) + "," + to_string(aux->b) + "\"";
					//matrizCompleta->add(aux->x,aux->y,aux->r,aux->g,aux->b);
					cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<"  tiene color: "<< aux->color<<endl;
				}
				
			}		
			temp = temp->right;
			if (temp->right == NULL)
			{
				node *aux2 = temp->down;
				while (aux2->down!=NULL)
				{
					//insertar aqui
					aux->r =255- aux->r;
					aux->g =255- aux->g;
					aux->b =255- aux->b;
					aux->color = "\"" + to_string(aux->r) + "," + to_string(aux->g) + "," + to_string(aux->b) + "\"";
					//matrizCompleta->add(aux2->x,aux2->y,aux2->r,aux2->g,aux2->b);
					cout<<"Estamos en: X:"<<aux2->x<<","<<aux2->y<<"  tiene color: "<< aux2->color<<endl;
					aux2 = aux2->down;
					if (aux2->down == NULL)
					{
						//insertar aqui
						aux->r =255- aux->r;
						aux->g =255- aux->g;
						aux->b =255- aux->b;
						aux->color = "\"" + to_string(aux->r) + "," + to_string(aux->g) + "," + to_string(aux->b) + "\"";
						//matrizCompleta->add(aux2->x,aux2->y,aux2->r,aux2->g,aux2->b);
						cout<<"Estamos en: X:"<<aux2->x<<","<<aux2->y<<"  tiene color: "<< aux2->color<<endl;
					}
				}
				
			}
	}
	return matrizH;
}
matrix* escalaGris(matrix* matrizH){
	node *temp = matrizH->head->right;
		while (temp->right!=NULL){
			node *aux = temp->down;
			if(aux->down == NULL){
				//insertar aqui
				int suma = (int)(aux->r * 0.3 + aux->g*0.59 + aux->b * 0.11) ;
				aux->r =suma;
				aux->g =suma;
				aux->b =suma;
				aux->color = "\"" + to_string(aux->r) + "," + to_string(aux->g) + "," + to_string(aux->b) + "\"";
				//matrizCompleta->add(aux->x,aux->y,aux->r,aux->g,aux->b);
				//cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<"  tiene color: "<< aux->color<<endl;
			}
			while (aux->down!=NULL)
			{
				//insertar aqui
				int suma = (int)(aux->r * 0.3 + aux->g*0.59 + aux->b * 0.11) ;
				aux->r =suma;
				aux->g =suma;
				aux->b =suma;
				aux->color = "\"" + to_string(aux->r) + "," + to_string(aux->g) + "," + to_string(aux->b) + "\"";
				//matrizCompleta->add(aux->x,aux->y,aux->r,aux->g,aux->b);
				//cout<<"Estamos en: X:"<<aux->x<<","<<aux->y<<"  tiene color: "<< aux->color<<endl;
				aux = aux->down;
				if (aux->down == NULL)
				{
					//insertar aqui
					int suma = (int)(aux->r * 0.3 + aux->g*0.59 + aux->b * 0.11) ;
					aux->r =suma;
					aux->g =suma;
					aux->b =suma;
					aux->color = "\"" + to_string(aux->r) + "," + to_string(aux->g) + "," + to_string(aux->b) + "\"";
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
					int suma = (int)(aux->r * 0.3 + aux->g*0.59 + aux->b * 0.11) ;
					aux->r =suma;
					aux->g =suma;
					aux->b =suma;
					aux->color = "\"" + to_string(aux->r) + "," + to_string(aux->g) + "," + to_string(aux->b) + "\"";
					//matrizCompleta->add(aux2->x,aux2->y,aux2->r,aux2->g,aux2->b);
					//cout<<"Estamos en: X:"<<aux2->x<<","<<aux2->y<<"  tiene color: "<< aux2->color<<endl;
					aux2 = aux2->down;
					if (aux2->down == NULL)
					{
						//insertar aqui
						int suma = (int)(aux->r * 0.3 + aux->g*0.59 + aux->b * 0.11) ;
						aux->r =suma;
						aux->g =suma;
						aux->b =suma;
						aux->color = "\"" + to_string(aux->r) + "," + to_string(aux->g) + "," + to_string(aux->b) + "\"";
						//matrizCompleta->add(aux2->x,aux2->y,aux2->r,aux2->g,aux2->b);
						//cout<<"Estamos en: X:"<<aux2->x<<","<<aux2->y<<"  tiene color: "<< aux2->color<<endl;
					}
				}
				
			}
	}
	return matrizH;
}
void menuPrincipal(){
	
	bool bandera=false;
    char tecla;
	string nombreImagen="";
	
    do{
        system("cmd /c cls"); 
        cin.clear();
        cout << "---------------------  PHOTGEN++  -------------------------" << endl;
        cout << "-----------" << endl << endl;
        cout << "\t1 .- Insert Image" << endl;
        cout << "\t2 .- Select Image" << endl;
        cout << "\t3 .- Apply Filters" << endl;
        cout << "\t4 .- Manual Editing" << endl;
        cout << "\t5 .- Export Image" << endl;
        cout << "\t6 .- Reports" << endl;
        cout << "\t7 .- Salir" << endl << endl;
        cout << "Elije una opcion: ";
        cin >> tecla;
        switch(tecla)
		{
			case '1':{
				//system("cmd /c cls"); 
				cout << "Ingrese el nombre de la imagen:\n";
				cin>>nombreImagen;
				linked *list = new linked();
				archivoInicial(nombreImagen,list);
				cout<<"Datos iniciales::"<<endl;
					cout<<"datos:::::"<<endl;
					cout<<imagewidht<<endl;
					cout<<imageheight<<endl;
					cout<<pixelwidht<<endl;
					cout<<pixelheight<<endl;
				system("cmd /c pause");
				tree->add(new Node(nombreImagen, correlativo,list,imageheight,imagewidht,pixelheight,pixelwidht));

				correlativo++;
				cout<<"Tamanio lista:"<<list->size()<<endl;
				//limpiar aqui variables, se pueden enviar y limpiar aqui mismo
				
				system("cmd /c pause");
				}
				break;
 
			case '2':{
				system("cmd /c cls"); 
				cout << "select.\n";
				//selectImage();
				tree->selectImageIn();
				cout<<"Ingrese el numero de imagen a seleccionar";
				int imgSel;
				cin>>imgSel;
				imagenSelNode = tree->returnImagenSel(imgSel);
				cout<<"Imagen seleccionada es: "<<imagenSelNode->getKey()<<endl;
				listaCircular = new linkedCircular();
				/// pedir numero 1 es el primero , y devolver algun parametro de ese arbol
				//nodeCircular *cabezaC = listaCircular->getHead();
				//listaCircular->head = NULL;
				//cabezaC->setSiguiente(NULL);
				system("cmd /c pause");
				}
				break;

			case '3':{
				system("cmd /c cls"); 
				cout << "filtros.\n";
				//listaCircular = new linkedCircular();
				//hacer copia de la imagen seleccinonada
				Node *copia = imagenSelNode;
				linked *listaCopia = imagenSelNode->getLista();
				cout<<"Lista de Filtros:\n"<<endl;
				cout<<"1 - Negative"<<endl;
				cout<<"2 - GrayScale"<<endl;
				cout<<"3 - Mirrow"<<endl;
				cout<<"4 - Collage"<<endl;
				cout<<"5 - Mosaic\n"<<endl;
				cout<<"Ingrese el numero de filtro a aplicar"<<endl;
				
				int numFiltro = 0;
				cin>>numFiltro;
				system("cmd /c cls"); 
				switch (numFiltro)
				{
				case 1:{//negativo
						Node *copiaNodo = new Node(imagenSelNode->getKey(),imagenSelNode->getId(),imagenSelNode->getLista(),imagenSelNode->getImageH(),imagenSelNode->getImageW(),imagenSelNode->getPixelH(),imagenSelNode->getPixelW());
						//copiando
						linked *listaCopiaNueva = new linked();
						
						for(int x =0; x<imagenSelNode->getLista()->size();x++){
							nodeList* nodolista = imagenSelNode->getLista()->getNodo(x+1);
							llenarMatrizC(listaCopiaNueva,nodolista->getMatrix(), nodolista->getKey());
						}

						cout<<"-------------------Negative-------------\n\n";
						cout<<"1 - Filtro a imagen completa"<<endl;
						cout<<"2 - Filtro a una Capa en especifico "<<endl;
						cout<<"Ingrese la opcion deseada: "<<endl;
						int opcion =0;
						cin>>opcion;
						if(opcion == 1){
							linked *listaCapas = copiaNodo->getLista();
							linked *listaNuevaF = new linked();
							matrix *matrizC = new matrix();
							for (int i = 0; i < listaCopiaNueva->size(); i++)
							{
								
								nodeList *nodoCapa = listaCopiaNueva->getNodo(i+1);
								int key = nodoCapa->getKey();
								matrix *matrizH = nodoCapa->getMatrix();
								matrizH = negativoDos(matrizH);
								nodeList *nodoNuevo = new nodeList(key, matrizH);
								listaNuevaF->add(nodoNuevo);
								//llenarMatrizC(matrizC, matrizH);
								
								//matrizH->graphMatrix("","");
							}
							listaCircular->add(new nodeCircular("Negative", listaNuevaF));
							//listaCircular->graph();

							//verificar valores en listanueva y lsita seleccionada
							nodeList *pruebaLista = listaNuevaF->getNodo(1);
							nodeList *pruebaImagen = imagenSelNode->getLista()->getNodo(1);
							cout<<"probando imagenes"<<endl;
							string color1 =pruebaLista->getMatrix()->head->right->down->color;
							string color2 =pruebaImagen->getMatrix()->head->right->down->color;
							cout<<color1<<" y el otro: "<<color2<<endl;
							system("cmd /c pause");
							//listaCircular->add(new )
						}else if(opcion == 2){

						}else{
							cout<<"Numero invalido"<<endl;
						}
					}	
					break;
				case 2:{//escala grises

					Node *copiaNodo = new Node(imagenSelNode->getKey(),imagenSelNode->getId(),imagenSelNode->getLista(),imagenSelNode->getImageH(),imagenSelNode->getImageW(),imagenSelNode->getPixelH(),imagenSelNode->getPixelW());
						//copiando
						linked *listaCopiaNueva = new linked();
						
						for(int x =0; x<imagenSelNode->getLista()->size();x++){
							nodeList* nodolista = imagenSelNode->getLista()->getNodo(x+1);
							llenarMatrizC(listaCopiaNueva,nodolista->getMatrix(), nodolista->getKey());
						}

						cout<<"-------------------GRAYSCALE-------------\n\n";
						cout<<"1 - Filtro a imagen completa"<<endl;
						cout<<"2 - Filtro a una Capa en especifico "<<endl;
						cout<<"Ingrese la opcion deseada: "<<endl;
						int opcion =0;
						cin>>opcion;
						if(opcion == 1){
							linked *listaCapas = copiaNodo->getLista();
							linked *listaNuevaF = new linked();
							matrix *matrizC = new matrix();
							for (int i = 0; i < listaCopiaNueva->size(); i++)
							{
								
								nodeList *nodoCapa = listaCopiaNueva->getNodo(i+1);
								int key = nodoCapa->getKey();
								matrix *matrizH = nodoCapa->getMatrix();
								matrizH = escalaGrisDos(matrizH);
								nodeList *nodoNuevo = new nodeList(key, matrizH);
								listaNuevaF->add(nodoNuevo);
								//llenarMatrizC(matrizC, matrizH);
								
								//matrizH->graphMatrix("","");
							}
							listaCircular->add(new nodeCircular("GRAYSCALE", listaNuevaF));
							//listaCircular->graph();

							//verificar valores en listanueva y lsita seleccionada
							nodeList *pruebaLista = listaNuevaF->getNodo(1);
							nodeList *pruebaImagen = imagenSelNode->getLista()->getNodo(1);
							cout<<"probando imagenes"<<endl;
							string color1 =pruebaLista->getMatrix()->head->right->down->color;
							string color2 =pruebaImagen->getMatrix()->head->right->down->color;
							cout<<color1<<" y el otro: "<<color2<<endl;
							system("cmd /c pause");
							//listaCircular->add(new )
						}else if(opcion == 2){

						}else{
							cout<<"Numero invalido"<<endl;
						}

					}
					break;
				case 3://mirrow
					//falta sub menu
					break;
				case 4:{//collage
						Node *copiaNodo = new Node(imagenSelNode->getKey(),imagenSelNode->getId(),imagenSelNode->getLista(),imagenSelNode->getImageH(),imagenSelNode->getImageW(),imagenSelNode->getPixelH(),imagenSelNode->getPixelW());
						//copiando
						linked *listaCopiaNueva = new linked();
						
						for(int x =0; x<imagenSelNode->getLista()->size();x++){
							nodeList* nodolista = imagenSelNode->getLista()->getNodo(x+1);
							llenarMatrizC(listaCopiaNueva,nodolista->getMatrix(), nodolista->getKey());
						}

						cout<<"-------------------Collage-------------\n\n";
						cout<<"1 - Filtro a imagen completa"<<endl;
						cout<<"2 - Filtro a una Capa en especifico "<<endl;
						cout<<"Ingrese la opcion deseada: "<<endl;
						int opcion =0;
						cin>>opcion;
						if(opcion == 1){
							linked *listaCapas = copiaNodo->getLista();
							linked *listaNuevaF = new linked();
							matrix *matrizC = new matrix();
							for (int i = 0; i < listaCopiaNueva->size(); i++)
							{
								
								nodeList *nodoCapa = listaCopiaNueva->getNodo(i+1);
								int key = nodoCapa->getKey();
								matrix *matrizH = nodoCapa->getMatrix();
								matrizH = escalaGris(matrizH);
								nodeList *nodoNuevo = new nodeList(key, matrizH);
								listaNuevaF->add(nodoNuevo);
								//llenarMatrizC(matrizC, matrizH);
								
								//matrizH->graphMatrix("","");
							}
							listaCircular->add(new nodeCircular("GRAYSCALE", listaNuevaF));
							//listaCircular->graph();

							//verificar valores en listanueva y lsita seleccionada
							nodeList *pruebaLista = listaNuevaF->getNodo(1);
							nodeList *pruebaImagen = imagenSelNode->getLista()->getNodo(1);
							cout<<"probando imagenes"<<endl;
							string color1 =pruebaLista->getMatrix()->head->right->down->color;
							string color2 =pruebaImagen->getMatrix()->head->right->down->color;
							cout<<color1<<" y el otro: "<<color2<<endl;
							system("cmd /c pause");
							//listaCircular->add(new )
						}else if(opcion == 2){

						}else{
							cout<<"Numero invalido"<<endl;
						}


					}
					break;
				case 5://mosaic
					cout<<"1 - Filtro a imagen completa"<<endl;
					cout<<"2 - Filtro a una Capa en especifico "<<endl;
					cout<<"Ingrese la opcion deseada: "<<endl;
					break;			
				default:
					break;
				}
				system("cmd /c pause");
				}
				break;

			case '4':{
				system("cmd /c cls"); 
				cout << "manual editing.\n";
				cout<<"1-------OG IMAGE"<<endl;
				cout<<"2-------Filters"<<endl;
				int opcion4;
				cin>>opcion4;
				if(opcion4 == 1){
					//imagen original
					int x = 0;
					int y =0;
					int capa =0;
					int r = 0;
					int g = 0;
					int b = 0;
					linked *lista = imagenSelNode->getLista();
					cout<<"Imagen Seleccionada tiene: "<<lista->size()<<" Capas"<<endl;
					cout<<"Ingrese la coordenada en x:"<<endl;
					cin>>x;
					cout<<"Ingrese la coordenada en Y:"<<endl;
					cin>>y;
					cout<<"Ingrese el numero de capa:"<<endl;
					cin>>capa;
					cout<<"Ingrese parametro R"<<endl;
					cin>>r;
					cout<<"Ingrese parametro G:"<<endl;
					cin>>g;
					cout<<"Ingrese parametro B:"<<endl;
					cin>>b;
					nodeList *nodoLista = lista->getNodo(capa);
					//cout<<"Key de la lista: "<<nodoLista->getKey();
					matrix *m = nodoLista->getMatrix();
					m->modificarNodo(x,y,r,g,b);

				}else if(opcion4 == 2){
					//filtros
				}else{
					cout<<"Invalid Number"<<endl;
				}
				
				system("cmd /c pause");
				}
				break;
 
			case '5':
				system("cmd /c cls"); 
				cout << "export image.\n";
				if(listaCircular!=NULL){
					cout<<"Desea exportar la imagen originar o un filtro aplicado?"<<endl;
					cout<<"1---ORIGINAL\n2----Filtro"<<endl;
					int opcion = 0;
					cin>>opcion;
					if(opcion == 1){
						exportHtml();
					}else if(opcion ==2){
						//mostrar filtros
						nodeCircular *circular = listaCircular->getHead();
						exportFiltro(circular->getLista());
					}else{
						cout<<"numero Invalido"<<endl;
					}
				}else{
					exportHtml();
				}
				
				system("cmd /c pause");
				break;
            case '6':
				system("cmd /c cls");
				menuReports(); 
				//cout << "reports.\n";
				//system("cmd /c pause");
				break;
            case '7':
				bandera=true;
				//exit(1);
				break;
 
			default:
				system("cmd /c cls"); 
				cout << "Opcion no valida.\a\n";
				
				break;
		}
    }while(bandera!=true);
}


int main(){
    menuPrincipal();
    return 0;
}