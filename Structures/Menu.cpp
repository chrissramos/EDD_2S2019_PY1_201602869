#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include"ABB/mainABB.cpp"
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
			line.erase(tam-1);
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
    archivo.open(abrir);
    int varx=0;
    int vary=0;
	while(archivo.good()){
        vector<string>datoM;
        getline(archivo,line,archivo.widen('\n'));
        if(line.size()>1){
            size_t tama = line.size();
            line.erase(tama-1);
            for(auto j : line){
                if(j == ','){
                    datoM.push_back(word2);
                    word2="";
                }else{
                    word2 = word2+j;
                }
            }
            datoM.push_back(word2);
            //cout<<"Tamanio: "<<datoM.size()<<endl;
            for(int o =0;o<datoM.size();o++){
				int r;
				int g;
				int b;
				string palabra;
				vector<string>colores;
			    string enM = datoM[o];
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
		string capa = data[q];
		size_t tam = capa.length();
		capa.erase(tam-1);
		cout<<"enviara capa: "<<capa<<endl;

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
				cout << "filtros.\n";
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
void armarCss(string padre){
	//system("cmd /c cls");
	string contenidoChild;
	linked *lista = imagenSelNode->getLista();
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
	
	//obtener cantidad de pixeles, generar matrix completa recorriendo caps
	
	/*linked *lista = imagenSelNode->getLista();
	matrix *matrizCompleta = new matrix();
	
	for(int i = 0; i< lista->size();i++){
		
		nodeList *nodoLista = lista->getNodo(i+1);
		matrix *matrizcapa = nodoLista->getMatrix();
		
		tree->llenarMatrizC(matrizCompleta,matrizcapa);
	}
*/
	
	for(int j = 0;j<cantDivs;j++){
		html << "<div class = \"pixel\"></div> \n";
		
	}
	html << "</div> \n </body> \n </html>";
	html.close();
	armarCss("");
	//system("cmd /c pause"); 

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
				/*cout<<"Datos iniciales::"<<endl;
					cout<<"datos:::::"<<endl;
					cout<<imagewidht<<endl;
					cout<<imageheight<<endl;
					cout<<pixelwidht<<endl;
					cout<<pixelheight<<endl;*/
				//system("cmd /c pause");
				tree->add(new Node(nombreImagen, correlativo,list,imageheight,imagewidht,pixelheight,pixelwidht));

				correlativo++;
				cout<<"Tamanio lista:"<<list->size()<<endl;
				//limpiar aqui variables, se pueden enviar y limpiar aqui mismo
				
				system("cmd /c pause");
				}
				break;
 
			case '2':
				system("cmd /c cls"); 
				cout << "select.\n";
				//selectImage();
				tree->selectImageIn();
				cout<<"Ingrese el numero de imagen a seleccionar";
				int imgSel;
				cin>>imgSel;
				imagenSelNode = tree->returnImagenSel(imgSel);
				cout<<"Imagen seleccionada es: "<<imagenSelNode->getKey()<<endl;
				/// pedir numero 1 es el primero , y devolver algun parametro de ese arbol
				system("cmd /c pause");
				break;

			case '3':
				system("cmd /c cls"); 
				cout << "filtros.\n";
				system("cmd /c pause");
				break;
 
			case '4':
				system("cmd /c cls"); 
				cout << "manual editing.\n";
				system("cmd /c pause");
				break;
 
			case '5':
				system("cmd /c cls"); 
				cout << "export image.\n";
				exportHtml();
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