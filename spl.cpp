#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// class Nodo
// {
//     int clave_Izquierda;
//     int clave_Derecha;
//     int clave;
//     public:
//     Nodo(int a, int b, int c){
//         clave_Izquierda = b;
//         clave_Derecha = c;
//         clave = a;
//     }
//     Nodo(){
//         clave = clave_Derecha = clave_Izquierda = 0;
//     }
// };

int null = -1000000;
int size = 10000;
int nodos = 0;
int spl[10000];
int ramas[10000];


int derecha(int padre)
{
    return padre*2+2;        
}
int izquierda(int padre)
{
    return padre*2+1;
}

void graficar()
{
    FILE* fp = fopen("graph.dot", "w");
    fprintf(fp,"%s","Digraph G{\n randir = LR;\nnode[shape = box]\n");
    for(int i = 0; i < 1000; i++)
    {
        if(ramas[i] != null)
        {
            if(derecha(ramas[i]) < size && izquierda(ramas[i]) < size)
            {                
                if(spl[izquierda(ramas[i])] != null){
                    fprintf(fp,"%d->%d[label =\"iz\"];\n",spl[i],spl[izquierda(ramas[i])]);
                }
                if(spl[derecha(ramas[i])] != null){
                    fprintf(fp,"%d->%d[label =\"dr\"];\n",spl[i],spl[derecha(ramas[i])]);
                }
            }
        }
    }       
    fprintf(fp,"%s","}");
    fclose(fp);
    system("dot -Tpng graph.dot -o graph.png");
}

int rotacion_derecha(int x) 
{  
    int y = ramas[izquierda(ramas[x])]; 
    ramas[izquierda(ramas[x])] = ramas[derecha(y)];  
    ramas[derecha(y)] = x; 
    return y;
}  
  
int rotacion_izquierda(int x)  
{  
    int y = ramas[derecha(ramas[x])];  
    ramas[derecha(ramas[x])] = ramas[izquierda(y)];  
    ramas[izquierda(y)] = x; 
    return y;  
} 

int buscar(int root, int clave)
{ 
    std::cout<<root<<","<<clave<<std::endl;
    int retorno = null;
    if (ramas[root] != null && (spl[ramas[root]] != null || spl[ramas[root]] == clave)){
        return root ;
    }        

    else if (spl[ramas[root]] > clave) 
    {   
        std::cout<<"this code 1"<<std::endl;
        if (spl[ramas[izquierda(ramas[root])]] == null) return root;  
   
        if (spl[ramas[izquierda(ramas[root])]] > clave)  
        {   
            //ramas[izquierda(izquierda(ramas[root]))] = 
            retorno = buscar(izquierda(izquierda(ramas[root])), clave);   
            ramas[root] = rotacion_derecha(root);  
        }  
        else if (spl[ramas[izquierda(ramas[root])]] < clave)  
        {  
            //ramas[derecha(izquierda(ramas[root]))] = 
            retorno = buscar(derecha(izquierda(ramas[root])), clave);  
            if (spl[ramas[derecha(izquierda(ramas[root]))]] != null)
                ramas[izquierda(ramas[root])] = rotacion_izquierda(izquierda(ramas[root]));  
        }  
        if(spl[ramas[izquierda(ramas[root])]] != null)
            ramas[root] = rotacion_derecha(root);  
        return root;
    }  
    else 
    {  
        std::cout<<"this code 2"<<std::endl;
        if (spl[ramas[derecha(ramas[root])]] == null) return root;  
        if (spl[ramas[derecha(ramas[root])]] > clave)  
        {  
            std::cout<<"My code shouldn't enter here"<<std::endl;
            retorno = buscar(izquierda(derecha(ramas[root])), clave);        
            if (spl[ramas[izquierda(derecha(ramas[root]))]] != null)  
                ramas[derecha(ramas[root])] = rotacion_derecha(derecha(ramas[root]));  
        }  
        else if (spl[ramas[derecha(ramas[root])]] < clave) 
        {   
            std::cout<<"My code should enter here"<<std::endl;
            retorno = buscar(derecha(derecha(ramas[root])), clave);  
            ramas[root] = rotacion_izquierda(root);  
        }   
        if(spl[ramas[derecha(ramas[root])]] == null)
            ramas[root] = rotacion_izquierda(root);  
        return root;
    }      
    return retorno;
}

int buscar_1(int clave)
{
    int abuelo = null;
    int padre = null;
    buscar(0, clave);    
}

int insertar(int clave, int root)
{
    int clave_raiz;
    if(ramas[root] == null)
        clave_raiz = spl[root];
    else
        clave_raiz = spl[ramas[root]];
    
    if(clave_raiz == null)
    {
        std::cout<<root<<std::endl;
        nodos++;
        ramas[root] = root;
        spl[root] = clave;
        buscar(0, clave);
    }
    else if(clave > clave_raiz)
    {
        insertar(clave, derecha(ramas[root]));        
    }
    else if(clave < clave_raiz)
    {
        insertar(clave, izquierda(ramas[root]));
    }
    else
        return null;
}

int main()
{
    for(int i = 0; i < size; i++){
        spl[i] = null;
        ramas[i] = null;
    }
    int opcion;
    int menu = 1;
    while(menu){
        std::cout<<"1. Insertar"<<std::endl;
        std::cout<<"2. Graficar"<<std::endl;
        std::cout<<"3. Imprimir arreglos"<<std::endl;
        std::cout<<"4. Salir"<<std::endl;
        std::cin >> opcion;
        switch (opcion)
        {
            case 1:
            {
                std::cout<<"insertar numero"<<std::endl;
                std::cin >> opcion;
                insertar(opcion, 0);
                break;
            }    
            case 2:
                graficar();   
                break;
            case 3:
            {
                for(int i = 0; i < 10; i++)
                    std::cout << ramas[i]<<",";
                std::cout<<std::endl;
                for(int i = 0; i < 10; i++)
                    std::cout << spl[i]<<",";
                std::cout<<std::endl;   
                break;             
            }
            case 4:
                menu = 0;
                break;

        }
    }        
    insertar(0, 0);
    return 0;
}



