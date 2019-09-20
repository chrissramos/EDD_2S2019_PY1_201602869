#include<iostream>
//#include"../LinkedList/mainList.cpp"
using namespace std;


class nodeCircular{
    public:
    string filtro;
    
    linked *lista;
    nodeCircular *siguiente;
    nodeCircular *anterior;
    nodeCircular(string filtro, linked* lista){
        this->filtro = filtro;
        this->lista = lista;
        siguiente = NULL;
        anterior = NULL;
        
    }
    string getFiltro(){
        return this->filtro;
    }
    linked* getLista(){
        return this->lista;
    }
    nodeCircular* getSiguiente(){
        return this->siguiente;
    }
    nodeCircular* getAnterior(){
        return this->anterior;
    }
    void setFiltro(string filtro){
        this->filtro = filtro;
    }
    void setLista(linked *lista){
        this->lista = lista;
    }
    void setSiguiente(nodeCircular *siguiente){
        this->siguiente = siguiente;
    }
    void setAnterior(nodeCircular *anterior){
        this->anterior = anterior;
    }
};
class linkedCircular{
    
    
    public:
    nodeCircular *head;
    linkedCircular(){
        head=NULL;
    }
    void add(nodeCircular *nodo){
        if(head == NULL){
            head = nodo;
            head->setSiguiente(nodo);
            head->setAnterior(nodo);
        }else{
            nodeCircular *temp;
            temp = head;
            while(temp->getSiguiente()!= head){
                temp= temp->getSiguiente();
            }
            temp->setSiguiente(nodo);
            nodo->setSiguiente(head);
            nodo->setAnterior(temp);
            head->setAnterior(nodo);
        }
    }
    nodeCircular* getHead(){
        return this->head;
    }
    void graph(){
        string titulo = "Circular.dot";
        string enlaces = "";
        string ranks = "{rank = same ";
        string contenido = "digraph G {\n node [shape = record, style=filled, fillcolor=seashell2];\n";
        int contador = 0;
        nodeCircular *temp = head;
        while(temp->getSiguiente()!=head){
            //cout<<temp->getFiltro()<<to_string(contador)<<endl;
            contenido+=to_string(contador) + "[label= \"" + temp->getFiltro() + "\"]\n";
            enlaces+=to_string(contador)+"-> ";
            ranks += to_string(contador) + " ";
            contador++;
            temp = temp->getSiguiente();
        }
        //cout<<temp->getFiltro()<<to_string(contador)<<endl;
        contenido+=to_string(contador) + "[label= \"" + temp->getFiltro() + "\"]\n";
        enlaces+=to_string(contador) + "-> 0";
        ranks += to_string(contador);
        
        enlaces+= "[dir = both]";
        ranks+="}";
        contenido+= "\n" + enlaces + "\n"+ranks;

        contenido+="\n}";
        cout<<contenido;

        ofstream fs(titulo.c_str());
        fs << contenido << endl;
        fs.close();
        system("cmd /c dot -Tpng Circular.dot -o Circular.png");
        // system("cmd /c ls");
        system("cmd /c Circular.png");
    }
    string mostarFiltros(){
        string filtros ="";
        if(head!=NULL){
            nodeCircular *temp = head;
            while(temp->getSiguiente()!=head){

            }

        }
        return filtros;
    }
    nodeCircular* getNodo(int pos){
        if(pos == 1){
            return head;
        }else{
            int contador = 1;
            nodeCircular *temp = head;
            while(temp->getSiguiente()!=head){
                if(contador == pos){
                    return temp;
                }else{
                    contador++;
                    temp = temp->getSiguiente();
                }
                if(temp->getSiguiente()==head &&contador == pos){
                    return temp;
                }
            }
        }
    }
};/*
int main(){
    linkedCircular *lista = new linkedCircular();
    matrix *m = new matrix();
    lista->add(new nodeCircular("GrayScale", m));
    lista->add(new nodeCircular("Negative", m));
    lista->add(new nodeCircular("MirrowY", m));
    lista->add(new nodeCircular("MirrowX", m));
    lista->graph();
    return 0;
}*/