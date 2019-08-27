#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include"ABB/mainABB.cpp"
using namespace std;
ABB *tree = new ABB();
int correlativo = 1;
int imagewidht;
int imageheight;
int pixelwidht;
int pixelheight;
void armarCss(string padre){
	//system("cmd /c cls");
	cout<<"image w: "<<imagewidht<<endl;
    cout<<"image h: "<<imageheight<<endl;
    cout<<"pixel w: "<<pixelwidht<<endl;
    cout<<"pixel h: "<<pixelheight<<endl;
	system("cmd /c pause");
}
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
void archivoInicial(string nombre){
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
		//cout<<line<<endl;
		if(line.size()>1){
			data.push_back(line);
		}
	}
	string config = data[1];
	//cout<<"Se enviara: "<<config<<endl;
	obtenerConfig(config,nombre);

	//system("cmd /c pause");

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
				archivoInicial(nombreImagen);
				//armarCss(nombreImagen);
				tree->add(new Node(nombreImagen, correlativo));
				correlativo++;
				system("cmd /c pause");
				}
				break;
 
			case '2':
				system("cmd /c cls"); 
				cout << "select.\n";
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