#include <iostream>
#include"../Matrix/main.cpp"
using namespace std;

class nodeList{
    private:
    int key;
    matrix *matriz;
    nodeList *next;
    public:
    nodeList(int key, matrix* matriz){
        this->key = key;
        this->matriz = matriz;
        next = NULL;
    }
    int getKey(){
		return this->key;
	}
    matrix* getMatrix(){
        return this->matriz;
    }
    nodeList* getNext(){
        return this->next;
    }
    void setMatrix(matrix *matriz){
        this->matriz = matriz;
    }
    void setKey(int key){
        this->key = key;
    }
    void setNext(nodeList *next){
        this->next = next;
    }
    

};
class linked{
    private:
    nodeList *head;
    public:
    linked(){
        head = NULL;
    }
    void add(nodeList* nodo){
        if(head == NULL){
            head = nodo;
        }else{
            nodeList *temp;
            temp = head;
            while (temp->getNext()!=NULL)
            {
                temp = temp->getNext();
            }
            if(temp->getNext()==NULL){
                temp->setNext(nodo);
            }else{
                cout<<"No se pudo insertar"<<endl;
            }

            
        }
    }
    void imprimir(){
        nodeList *temp;
        temp = head;
        while (temp->getNext()!=NULL)
        {
            cout<<temp->getKey()<<endl;
            temp = temp->getNext();
        }
        cout<<temp->getKey();
        
    }
    int size(){
        nodeList *temp;
        int contador = 0;
        temp = head;
        while(temp->getNext()!=NULL){
            contador++;
            temp = temp->getNext();
        }
        if(temp->getNext()==NULL){
            contador++;
        }
        return contador;
    }
    nodeList* getNodo(int pos){
        if(pos == 1){
            return head;
        }else
        {
            int contador = 1;
            nodeList *temp = head;
            while (temp->getNext()!=NULL)
            {
                if(contador==pos){
                    return temp;
                }else{
                    contador++;  
                    temp = temp->getNext(); 
                }
                if(temp->getNext()==NULL && contador == pos){
                    return temp;
                }
            }
            
        }
        
    }
};
/*
int main(){
    linked *lista = new linked();
    lista->add(new nodeList(1));
    lista->add(new nodeList(2));
    lista->add(new nodeList(3));
    lista->add(new nodeList(4));
    lista->add(new nodeList(5));
    lista->imprimir();
    
    return 0;
}*/