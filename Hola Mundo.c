#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#define MAX_TAM 32 
#define Max 12

/*#include "Producto.h"
#include "DLL.h" 
#include "Stock.h" */

//----------------------------------------------------------------------
//  Producto
//----------------------------------------------------------------------

/*#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#define MAX_TAM 32*/

/**
 * @struct Producto tipo de dato abstracto
*/
typedef struct
{
   int bar_code;
   float precio;
   char nombre[MAX_TAM];
   // ... quizás más campos 
} Producto;

//----------------------------------------------------------------------
//  DLL.h
//----------------------------------------------------------------------

/*#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#define MAX_TAM 32
#define Max 12*/

 /** 
  * @struct Tipo de dato abstracto llamado Nodo 
 */
typedef struct Node
{
   Producto item; 
   size_t cantidad; 

   struct Node* prev; 
   struct Node* next; 
} Node;

typedef Node* NodePtr;
/** 
  * @struct Tipo de dato abstracto llamado DLL(Lista Doblemente Enlazada).
 */
typedef struct
{
   NodePtr first; 
   NodePtr last;  
   NodePtr cursor;
   size_t len;
} DLL;

/**
 * @brief Crea una Lista Doblemente Enlazada.
 * @return referencia al tipo de dato abstracto DLL.
 */
DLL* DLL_New();

/**
 * @brief Destruye una Lista Doblemente Enlazada.
 * @param this referencia a un tipo de dato abstracto DLL.
 */
void DLL_Delete( DLL** this );

/**
 * @brief Inserta un nodo del lado derecho.
 * @param this referencia a un tipo de dato abstracto DLL.
 * @param p referencia a un objeto tipo Producto.
 * @param cant referencia a las unidades del Producto.
 */
void DLL_InsertBack( DLL* this, Producto* p, size_t cant );

/**
 * @brief Inserta un nodo del lado izquierdo.
 * @param this referencia a un tipo de dato abstracto DLL.
 * @param p referencia a un objeto tipo Producto.
 * @param cant referencia a las unidades del Producto.
 */
void DLL_InsertFront( DLL* this, Producto* p, size_t cant );

/**
 * @brief Extrae un nodo del lado izquierdo.
 * @param this referencia a un tipo de dato abstracto DLL.
 * @return un objeto tipo Producto.
 */
Producto DLL_RemoveFront( DLL* this );

/**
 * @brief Extrae un nodo del lado derecho.
 * @param this referencia a un tipo de dato abstracto DLL.
 * @return un objeto tipo Producto.
 */
Producto DLL_RemoveBack( DLL* this );

/**
 * @brief Extrae el nodo que apunta cursor.
 * @param this referencia a un tipo de dato abstracto DLL.
 * @return true si se completo con exito.
 */
bool DLL_Remove( DLL* this );

/**
 * @brief Indica la cantidad de productos.
 * @param this referencia a un tipo de dato abstracto DLL.
 * @return cantidad de producto dentro de DLL.
 */
size_t DLL_Len( DLL* this );

/**
 * @brief Indica si DLL esta vacia.
 * @param this referencia a un tipo de dato abstracto DLL.
 * @return true o false dependiendo el caso.
 */
bool DLL_IsEmpty( DLL* this );

/**
 * @brief Busca una igualdad en la lista y posiciona a cursor donde la encontró.
 * @param this referencia a un tipo de dato abstracto DLL.
 * @param bar_code referencia a un tipo entero.
 * @return true o false dependiendo el caso.
 */
bool DLL_Search( DLL* this, int bar_code );

/**
 * @brief Regresa el producto al que apunta cursor.
 * @param this referencia a un tipo de dato abstracto DLL.
 * @return el tipo Producto al que apunta cursor.
 */
Producto DLL_Peek( DLL* this );

//----------------------------------------------------------------------
//  DLL.c
//----------------------------------------------------------------------

/*#include "Producto.h"
#include "DLL.h"*/

static NodePtr New_node( Producto* p, size_t cant )
{
    NodePtr n = ( NodePtr )malloc( sizeof( Node ) );
    
    if( n ){
        n->cantidad = cant;
        n->item.bar_code = p->bar_code;
        n->item.precio = p->precio;
        strcpy( n->item.nombre, p->nombre );
        n->next = NULL;
        n->prev = NULL;
    }
    return n;
}

static void reset( DLL* this )
{
    this->first = this->last = this->cursor = NULL;
    this->len = 0;
}

DLL* DLL_New()
{
    DLL*  list = ( DLL* )malloc( sizeof( DLL) );
    if( list ){
        reset( list );
    }
    return list;
}

void DLL_Delete( DLL** this )
{
    if( *this ){
        DLL* list = *this;
        while( DLL_Len( list ) != 0 ){
            NodePtr next = list->first->next;
            free( list->first );
            list->first = next;
            --list->len;
        }
        free( list );
        *this = NULL;
    }
}

void DLL_InsertBack( DLL* this, Producto* p, size_t cant )
{
    assert( this );
    
    NodePtr n = New_node( p , cant );
    if( n ){
        if( DLL_IsEmpty( this ) == false ){
            this->last->next = n;
            n->prev = this->last;
            this->last = n;
        }else{
            this->first = this->last = n;
        }
        ++this->len;
    }
}

void DLL_InsertFront( DLL* this, Producto* p, size_t cant )
{
    assert( this );
    
    NodePtr n = New_node( p , cant );
    if( n ){
        if( DLL_IsEmpty( this ) == false ){
            this->first->prev = n;
            n->next = this->first;
            this->first = n;
        }else{
            this->first = this->last = n;
        }
        ++this->len;
    }
}

Producto DLL_RemoveFront( DLL* this )
{
    assert( this );
    Producto p;
    if( !DLL_IsEmpty( this ) ){
        
        p.bar_code = this->first->item.bar_code;
        p.precio = this->first->item.precio;
        strcpy( p.nombre, this->first->item.nombre );
        
        NodePtr tmp = this->first->next;
        free( this->first );
        this->first = tmp;

        if( NULL != this->first ){
            this->first->prev = NULL;
            --this->len;
        }else{
            reset( this );
        }
    }
    return p;
}

Producto DLL_RemoveBack( DLL* this )
{
    assert( this );
    Producto p;
    if( !DLL_IsEmpty( this ) ){
        
        p.bar_code = this->last->item.bar_code;
        p.precio = this->last->item.precio;
        strcpy( p.nombre, this->last->item.nombre );
        
        NodePtr tmp = this->last->prev;
        free( this->last );
        this->last = tmp;

        if( NULL != this->last ){
            this->last->next = NULL;
            --this->len;
        }else{
            reset( this );
        }
    }
    return p;
}
// Quitar el nodo que apunte cursor
bool DLL_Remove( DLL* this )
{
    assert( this );
     
    bool done = false;
     
    if( !DLL_IsEmpty( this ) && NULL != this->cursor ){
        done = true;
         
        if(this->cursor==this->first){
            DLL_RemoveFront( this );
        }else if( this->cursor == this->last ){
            DLL_RemoveBack( this );
        }else{
            NodePtr left = this->cursor->prev;
            NodePtr rigth = this->cursor->next;
            free( this->cursor );
         
            if( left == NULL && rigth == NULL ){
                reset( this );
            }else{
                this->cursor = left;
                this->cursor->next = rigth;
                rigth->prev = this->cursor;
                --this->len;
            }
        }
        
    }
    return done;
}

size_t DLL_Len( DLL* this )
{
    return this->len;
}

bool DLL_IsEmpty( DLL* this )
{
    assert( this );
    return this->first == NULL;
}

bool DLL_Search( DLL* this, int bar_code )
{
    assert( this );
    bool found = false;
    
    for( NodePtr it = this->first; it != NULL && found == false; it = it->next ){
        if( bar_code == it->item.bar_code ){
            this->cursor = it;
            found = true;
        }
    }
    return found;
}

Producto DLL_Peek( DLL* this )
{
    assert( this );
    return this->cursor->item;
}

//----------------------------------------------------------------------
//  Stock.h
//----------------------------------------------------------------------

/*#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#define MAX_TAM 32
#define Max 12*/

/**
 * @struct Stock tipo de dato abstracto llamada, Stock es mas corto que inventario.
*/
typedef struct
{
   DLL* list; 
} Stock; 

/**
 * @brief Crea un Inventario( Stock ).
 * @return una referencia al tipo de dato abstracto Stock.
 */
Stock* Stock_New();

/**
 * @brief Destruye un Inventario( Stock ).
 * @param this referencia a un tipo de dato abstracto Stock.
 */
void Stock_Delete( Stock** this );

/**
 * @brief Agrega un nuevo producto, lee y guarda su cantidad.
 * @param this referencia a un tipo de dato abstracto Stock.
 * @param p referencia a un tipo de dato abstracto Producto.
 * @param cant referencia a un tipo entero sin signo.
 */
void Stock_add( Stock* this, Producto* p, size_t cant );

/**
 * @brief Retira un Producto del Inventario.
 * @param this referencia a un tipo de dato abstracto Stock.
 * @param p referencia a un tipo de dato abstracto Producto.
 */
void Stock_remove( Stock* this, Producto* p );

/**
 * @brief Busca un producto apartir de bar_code.
 * @param this referencia a un tipo de dato abstracto Stock.
 * @param bar_code referencia a un tipo entero.
 * @return true o false dependiendo de la situacion
 */
bool Stock_search_by_bar_code( Stock* this, int bar_code );

/**  
 * @brief Imprime los datos del producto que apunte cursor.
 * @param this referencia a un tipo de dato abstracto Stock.
 */
void Stock_get( Stock* this );

/**
 * @brief Imprimir todos los productos dentro del inventario.
 * @param this referencia a un tipo de dato abstracto Stock.
 */
void Stock_report( Stock* this );

//----------------------------------------------------------------------
//  Stock.c
//----------------------------------------------------------------------

/*#include "Producto.h"
#include "DLL.h"
#include "Stock.h"*/

Stock* Stock_New()
{
    Stock* Inventario = ( Stock* )malloc( sizeof( Stock ) );
    if( Inventario ){
        Inventario->list = DLL_New();
    }
    return Inventario;
}

void Stock_Delete( Stock** this )
{
    assert( *this );
    if( *this ){
        Stock* n = *this;
        DLL_Delete( &n->list );
        free( n );
        *this = NULL;
    }
}

void Stock_add( Stock* this, Producto* p, size_t cant )
{
   if( DLL_Search( this->list, p->bar_code ) == false ){
        DLL_InsertBack( this->list, p, cant );//DLL_InsertFront( this->list, p, cant );
    } else {
        this->list->cursor->cantidad += cant;
    }
}

void Stock_remove( Stock* this, Producto* p )
{
   if( DLL_Search( this->list, p->bar_code ) != false ){
        if(DLL_Remove( this->list ) == true ){
            printf("\nSe elimino con exito");
        }else{
            printf("\nNo se pudo Eliminar");
        }
        
    }else{
        printf("\n!!No se encontro El producto deseado.");
    } 
}

bool Stock_search_by_bar_code( Stock* this, int bar_code )
{
   return DLL_Search( this->list, bar_code );
}

void Stock_get( Stock* this )
{
    Producto p = DLL_Peek( this->list );
    printf("\n\n===================\nNombre del Producto: ");
    
    for( size_t i = 0; i < 12 ; ++i ){
       printf("%c", p.nombre[ i ] );
    }
    printf("\nCodigo de Barras: %u\nPrecio: %0.2f\nUnidades: %ld\n", p.bar_code, p.precio, this->list->cursor->cantidad);
}

void Stock_report( Stock* this )
{
   assert( this );
    for(NodePtr it = this->list->first; it != NULL ; it = it->next ){
        printf("\n\n=====================");
        printf("\nProducto: ");
        for( size_t i = 0 ; i < Max ; ++i ){
            printf("%c", it->item.nombre[ i ] );   
        }
        printf("\nCodigo de Barras: %d\nPrecio: %0.2f\nUnidades: %ld",it->item.bar_code, it->item.precio, it->cantidad );
    }
    printf("\n\nCuentas con %ld Poductos\n" , DLL_Len( this->list ) );
}

//----------------------------------------------------------------------
//  Programa principal
//----------------------------------------------------------------------
/**
 * @brief Regresa una cantidad valida que no sobrepase las unidades dentro del inventario
 * 
 * @param this Tipo de dato Abstracto Stock
 * 
 * @return Un valor tipo entero sin signo
 */
size_t Cantidad( Stock* this )
{
    int bar_code = 0;
    size_t cant=0;
    printf("\nDigite el codigo del producto que va a Usar ");
    scanf("%i",&bar_code);
    if(Stock_search_by_bar_code( this, bar_code ) == true ){
        Stock_get( this );
        printf("\nintroduzca el numero de unidades del producto seleccionado: ");
        scanf("%lu", &cant);
        if( cant > this->list->cursor->cantidad ){
            printf("\nNumero Invalido");
            cant = 0;
        }else{
            printf("\nNumero Valido");
        }
    }else{
        printf("\nNo se encontro el Producto");
    }
    return cant;
}
/**
 * @brief Regresa una opción válida.
 * 
 * @return Un valor tipo entero.
 */
int Opcion()
{
    int produ = 0;
    while(produ != 1 && produ != 2){
        printf("\nDesea procesar otro producto?\n1)Si\n2)No\nOpcion: ");
        scanf("%i",&produ);        
        if( produ != 1 && produ != 2){
            printf("\nIntrodusca un Numero valido");
        }
    }
    return produ;
}
/**
 * @brief Abastece las unidades de un producto dentro del inventario.
 * 
 * @param this referencia a un tipo de dato abstracto Stock.
 */
void Abastecimiento( Stock* this )
{
    printf("==>Menu ==>Abastecimiento");
    Stock_report( this );
    int option;
    do {
        option = 0;
        size_t canti = Cantidad( this );
        this->list->cursor->cantidad += canti;
        option = Opcion();
        
    }while(option != 2 );
    
}

/**
 * @brief Disminuye las unidades de productos seleccionados y crea un ticket.
 * 
 * @param this referencia a un tipo de dato abstracto Stock. 
 */
void Venta( Stock* this )
{
    printf("==>Menu ==>Vender ");
    Stock_report( this );
    Stock* ticket = Stock_New();
    int produ;
    float total=0;
    do{
        produ = 0;
        size_t cant = Cantidad( this );
        
        if( cant <= this->list->cursor->cantidad ){
            this->list->cursor->cantidad -= cant;
            Producto p;
            p.bar_code = this->list->cursor->item.bar_code;
            p.precio = this->list->cursor->item.precio;
            strcpy(p.nombre ,this->list->cursor->item.nombre );
            Stock_add( ticket, &p , cant );
            total+=(cant*p.precio);
        }else{
            printf("\n Error");
        }
        produ = Opcion();
    }while(produ != 2);
    printf("\n========{ Ticket }========\n");
    Stock_report( ticket );
    printf("\nTotal es :\t%0.2f\n", total );
    Stock_Delete( &ticket );
    
}

/**
 * @brief Agrega nuevos productos al Inventario( Stock ).
 * 
 * @param this referencia a un tipo de dato abstracto Stock
*/
void Agregar( Stock* this )
{
    printf("\n\n==>Menu ==>Agregar ");
    Stock_report( this );
    int opc;
    do{
        opc = 0;
        Producto p;
        p.bar_code = 0;
        p.precio = 0.0;
        char nombre[ MAX_TAM ];
        size_t cantidad;
        printf("\nDigite el Nombre del Producto: ");
        scanf("%s", nombre );
        strcpy( p.nombre , nombre );
        printf("\nDigite el codigo del Producto: ");
        scanf("%i", &p.bar_code );
        printf("\nDigite precio para el Producto: ");
        scanf("%f", &p.precio );
        printf("\nDigite el numero de unidades: ");
        scanf("%lu", &cantidad);
        
        Stock_add( this, &p , cantidad );
        opc = Opcion();
    }while( opc != 2);
}

/**
 * @brief Retira un producto del Inventario.
 * 
 * @param this referencia a un tipo de dato abstracto Stock.
*/
void Eliminar( Stock* this )
{
    printf("\n\n==>Menu ==>Eliminar ");
    int opc;
    do{
        opc = 0;
        Stock_report( this );
        Producto p;
        p.bar_code = 0;
        printf("\nDigite el codigo del Producto que va a Eliminar");
        scanf("%i" , &p.bar_code );
        Stock_remove( this , &p );
        opc = Opcion();
    }while( opc != 2 );

}

/**
 * @brief Agrega productos ya establecidos.
 * 
 * @param this referencia a un tipo de dato abstracto Stock.
*/
void Productos(Stock* this )
{
    Producto p1;
    p1.bar_code = 1234;
    p1.precio = 13.50;
    strcpy( p1.nombre, "Crema_Lala");
    Stock_add( this , &p1, 10 );
    
    Producto p2;
    p2.bar_code = 1334;
    p2.precio = 13.50;
    strcpy( p2.nombre, "Queso_panela");
    Stock_add( this , &p2, 9 );
    
    Producto p3;
    p3.bar_code = 1404;
    p3.precio = 9.50;
    strcpy( p3.nombre, "Sabritas");
    Stock_add( this , &p3, 9 );

    Producto p4;
    p4.bar_code = 2222;
    p4.precio = 24.50;
    strcpy( p4.nombre, "1/4Jamon_EFA");
    Stock_add( this , &p4, 9 );

    Producto p5;
    p5.bar_code = 1567;
    p5.precio = 22.00;
    strcpy( p5.nombre, "Queso_Crema");
    Stock_add( this , &p5, 10 );

    Producto p6;
    p6.bar_code = 3587;
    p6.precio = 38.50;
    strcpy( p6.nombre, "1kHuevoSanJu");
    Stock_add( this , &p6, 10 );

    Producto p7;
    p7.bar_code = 2597;
    p7.precio = 20.00;
    strcpy(p7.nombre, "Salchichas");
    Stock_add( this , &p7, 10 );
}

/**
 * @brief Ofrece opciones y las ejecuta.
 * 
 * @param this referencia a un tipo de dato abstracto Stock.
*/
void Menu(Stock* this )
{
   int opc;
    do{ 
        printf("\n\n\t====={ Cremeria Los Angelos }=====\n ==> Menu");
        printf("\nBienvenido, en que le podemos ayudar ?:\n1.-Existencias\n2.-Abastecer\n3.-Vender Productos\n4.-Nuevo Producto\n5.-Desventurar un Producto\n6.-Salir\nFavor de escribir el numero de la opcion de su Preferencia: ");
        scanf("%d", &opc );
        switch ( opc ){
        case 1:
            //existencias
            Stock_report( this );
            printf("\n");
            break;
        case 2:
            //Aumentar la cantidad de unidades que se tiene
            Abastecimiento( this );
            break;
        case 3:
            //Vende
            Venta( this );
            break;
        case 4:
            Agregar( this );
            //Agrega un nuevo producto
            break;
        case 5:
            //Quita un producto ya existente
            Eliminar( this );
            break;
        default:
            printf("\nGracias Por usar Este Programa");
            break;
        }
    }while(opc != 6 );
}

int main()
{
    Stock* Inventario = Stock_New();// crea al inventario
    Productos( Inventario );
    Menu( Inventario );
  
    Stock_Delete( &Inventario );// destruye al inventario   
}