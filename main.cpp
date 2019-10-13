#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
using namespace std;

//Struct type for each node of the AVL tree
typedef struct AVLnodestruct {
    int info;
    int variacion;
    //defining two child
    struct AVLnodestruct *subnodo[2];
} AVLnodeobject,*BinaryTree;//AVLnodeobject data type

//Right Rotating
void rotateright(AVLnodeobject **nodo) {
    
    int izq = 0;
    int der = 1;
    int signo = 1;
    if((*nodo)->subnodo[izq] == NULL){  //terminate program if there is no required child
        exit(1);
    }
    if((*nodo)->subnodo[izq] != NULL) {
        AVLnodeobject* left = (*nodo)->subnodo[izq];
        int u = (*nodo)->variacion * signo;
        int v = left->variacion * signo;
        int nu;
        int nv;
        //update depth
        if(v >= 0) {
            if (u - 1 - v >= 0) {
                nv = v - 1;
            }
            else {
                nv = u - 2;
            }
            nu = u - 1 - v;
        }
        else {
            if (u - 1 >= 0) {
                nv = v - 1;
            }
            else {
                nv = u + v - 2;
            }
            nu = u - 1;
        }
        (*nodo)->variacion = nu * signo;
        left->variacion = nv * signo;
        //do the rotation
        (*nodo)->subnodo[izq] = (*nodo)->subnodo[izq]->subnodo[der];
        left->subnodo[der] = *nodo;
        *nodo = left;
    }
}

//Left Rotating
void rotateleft(AVLnodeobject **nodo) {

    int izq = 1;
    int der = 0;
    int signo = -1;
    if((*nodo)->subnodo[izq] == NULL){
        //Finish program if there is no required child
        exit(1);
    }
    if((*nodo)->subnodo[izq] != NULL) {
        AVLnodeobject* left = (*nodo)->subnodo[izq];
        int x = (*nodo)->variacion* signo;
        int y = left->variacion * signo;
        int mx;
        int my;
        
        //UpdatING depth
        if(y >= 0) {
            if (x - 1 - y >= 0) {
                my = y - 1;
            }
            else {
                my = x - 2;
            }
            mx = x - 1 - y;
        }
        else {
            if (x - 1 >= 0) {
                my = y - 1;
            }
            else {
                my = x + y - 2;
            }
            mx = x - 1;
        }
        (*nodo)->variacion = mx * signo;
        left->variacion = my * signo;
        //do the rotation
        (*nodo)->subnodo[izq] = (*nodo)->subnodo[izq]->subnodo[der];
        left->subnodo[der] = *nodo;
        *nodo = left;
    }
}
//Changing depth after adding a node
int add(AVLnodeobject **nodo, int info) {
    if(*nodo == NULL) {
        
        //add new node
        *nodo = new AVLnodeobject();
        if(*nodo == NULL){
            exit(1);
        }
        if(*nodo != NULL) {
            //initialize the node without child
            (*nodo)->info = info;
            (*nodo)->variacion = 0;
            (*nodo)->subnodo[0] = NULL;
            (*nodo)->subnodo[1] = NULL;
        }
        return *nodo != NULL;
        
    }
    else {
        int l, triang, triangsenal;
        
        if(info == (*nodo)->info) {
            //if value == current data
            return 0;
            
        }
        //the current node is not the node searched
        else {
            
            //Deciding right or left
            if (info < (*nodo)->info) {
                //if smaller  go left
                l = 0;
                triangsenal = 1;
            }
            else {
                //if bigger  go right
                l = 1;
                triangsenal = -1;
            }
            triang = add(&(*nodo)->subnodo[l], info);
        }
         //if there are changes
        if (triang != 0) {
           
            int tmpvariacion = (*nodo)->variacion;
            int rotating = 0;
            int rotatingizq;
            int restasigno;
            int RightorLeftspin;
            (*nodo)->variacion = (*nodo)->variacion + triang * triangsenal;
            
            // right rotation
            if ((*nodo)->variacion > 1) {
                
                rotating = 1;
                rotatingizq = 0;
                restasigno = 1;
                RightorLeftspin = 1;
            }
            //left rotation
            else if((*nodo)->variacion < -1) {
                
                rotating = 1;
                rotatingizq = 1;
                restasigno = -1;
                RightorLeftspin = 0;
            }
            if (rotating) {
                int childsubstr = (*nodo)->subnodo[rotatingizq]->variacion;
                //Rotating
                if((*nodo)->subnodo[rotatingizq]->variacion * restasigno < 0) {
                    //Child first
                    if(RightorLeftspin==0){
                        rotateright(&(*nodo)->subnodo[rotatingizq]);
                    }
                    else{
                        rotateleft(&(*nodo)->subnodo[rotatingizq]);
                    }
                }
                //current node
                if(RightorLeftspin==0){
                    rotateleft(nodo);
                }
                else{
                    rotateright(nodo);
                }
                if(triang < 0 && childsubstr != 0){
                    return -1;
                }
                else{
                    return 0;
                }
            }
            //return new depth
            if (triang > 0 && tmpvariacion == 0) {
                return 1;
            }
            else if (triang < 0 && tmpvariacion != 0) {
                return -1;
            }
            else {
                return 0;
            }
        } else {
            return 0;
        }
    }
}

//Changing depth after deleting a node
int borrar(AVLnodeobject **nodo, int info) {
    if(*nodo == NULL) {
        
        return 0;
    }
    else {
        int l, triang, triangsenal;
        AVLnodeobject *nextNodo;
        if(info == (*nodo)->info) {
      
            if((*nodo)->subnodo[1] == NULL) {
                
                nextNodo = (*nodo)->subnodo[0];
                delete(*nodo);
                *nodo = nextNodo;
                return -1;
            }
            else if((*nodo)->subnodo[0] == NULL) {
                
                nextNodo = (*nodo)->subnodo[1];
                delete(*nodo);
                *nodo = nextNodo;
                return -1;
            }
            else{
                //Child right and left
                for (nextNodo = (*nodo)->subnodo[0]; nextNodo->subnodo[1] != NULL; nextNodo = nextNodo->subnodo[1]);
                (*nodo)->info = nextNodo->info;
                l = 0;
                triangsenal = 1;
                triang = borrar(&(*nodo)->subnodo[l], nextNodo->info);
            }
            
        }
        else {
           
            if (info < (*nodo)->info) {
                l = 0;
                triangsenal = 1;
            }
            else {
            
                l = 1;
                triangsenal = -1;
            }
            triang = borrar(&(*nodo)->subnodo[l], info);
        }
        if (triang != 0) {
            
            int tmpvariacion = (*nodo)->variacion;
            int rotating = 0;
            int rotatingizq;
            int restasigno;
            int RightorLeftspin;
            (*nodo)->variacion = (*nodo)->variacion + triang * triangsenal;
            if ((*nodo)->variacion > 1) {
             
                rotating = 1;
                rotatingizq = 0;
                restasigno = 1;
                RightorLeftspin = 1;//
            }
            else if((*nodo)->variacion < -1) {
           
                rotating = 1;
                rotatingizq = 1;
                restasigno = -1;
                RightorLeftspin = 0;
            }
            if (rotating) {
                int childsubstr = (*nodo)->subnodo[rotatingizq]->variacion;
           
                if((*nodo)->subnodo[rotatingizq]->variacion * restasigno < 0) {
                   
                    if(RightorLeftspin==0){
                        rotateright(&(*nodo)->subnodo[rotatingizq]);
                    }
                    else{
                        rotateleft(&(*nodo)->subnodo[rotatingizq]);
                    }
                }
             
                if(RightorLeftspin==0){
                    rotateleft(nodo);
                }
                else{
                    rotateright(nodo);
                }
                if(triang < 0 && childsubstr != 0){
                    return -1;
                }
                else{
                    return 0;
                }
            }
 
            if (triang > 0 && tmpvariacion == 0) {
                return 1;
            }
            else if (triang < 0 && tmpvariacion != 0) {
                return -1;
            }
            else {
                return 0;
            }
        } else {
            return 0;
        }
    }
}

//Printing postorder traversal
bool printPost(const AVLnodeobject *nodo)
{
    if (nodo){
        printPost(nodo->subnodo[0]);
        
        printPost(nodo->subnodo[1]);
        
        printf("%d ", nodo->info);
        
    }
    return true;
}
//Printing inorder traversal
bool printIn(const AVLnodeobject *nodo)
{
    if (nodo){
        printIn(nodo->subnodo[0]);
        
        printf("%d ", nodo->info);
        
        printIn(nodo->subnodo[1]);
        
    }
    return true;
}

//Printing preorder traversal
bool printPre(const AVLnodeobject *nodo)
{
    if (nodo){
        
        printf("%d ", nodo->info);
        
        printPre(nodo->subnodo[0]);
        
        printPre(nodo->subnodo[1]);
        
    }
    return true;
}

int main(void) {
    
    //Capturing one line and put in vectors
    string collecting;
    getline( std::cin, collecting );
    istringstream processit ( collecting );
    vector<string> linea( ( istream_iterator<string>( processit ) ), istream_iterator<string>() );
    
    //Starting node
    AVLnodeobject *raiz = NULL;
    
    int i=0;
    int len = (int)linea.size();
    while (i < len ){
        string each = linea[i];
        if(each == "IN"){
            if(raiz == NULL){
                cout << "EMPTY" << endl;
                return 0;
            }
            printIn(raiz);
            cout << endl;
        }
        else if (each == "POST"){
            if(raiz == NULL){
                cout << "EMPTY" << endl;
                return 0;
            }
            printPost(raiz);
            cout << endl;
        }
        else if(each == "PRE"){
            if(raiz == NULL){
                cout << "EMPTY" << endl;
                return 0;
            }
            printPre(raiz);
            cout << endl;
        }
        else{
            char first = each[0];
       
            if(first == 'A'){
              
                int inf = 0;
                each.erase(0,1);
                stringstream robeach(each);
                robeach >> inf;
                add(&raiz, inf);
                
            }
            else{
              
                int inf = 0;
                each.erase(0,1);
                stringstream robeach(each);
                robeach >> inf;
                borrar(&raiz, inf);
            }
        }
        i++;
    }
    return 0;
}