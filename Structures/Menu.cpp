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
		getline(archivo,line,archivo.widen(','));
		//cout<<line<<endl;
		data.push_back(line);
		 
	}
	for(int i = 1; i<data.size();i++){
		string datos = data[i];
		cout<<"dato en arreglo: "<<datos<<"|"<<endl;
	}

	system("cmd /c pause");

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
				//archivoInicial(nombreImagen);
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