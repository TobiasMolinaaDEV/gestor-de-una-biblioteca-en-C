#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <ctype.h>


#define MAX_USUARIOS 100
#define MAX_LONGITUD 50
#define MAX_CANTIDAD_LIBROS 1000


int sleep;
void usuario_validado();
void menu_libros();
void agregar_Libros();
void ver_ListaLibros();
int buscar_Libro();
int editar_Libro();
int borrar_Libro();
void ayuda();
void salirProg();

typedef struct {
    char usuario[MAX_LONGITUD];
    char contrasena[MAX_LONGITUD];
} DatosUsuario;

DatosUsuario usuarios[MAX_USUARIOS];
int numUsuarios = 0;

void cargar_usuarios() {
    FILE *archivo = fopen("usuarios.txt", "r");
    if (archivo == NULL) {
        return;
    }

    while (fscanf(archivo, "%s %s", usuarios[numUsuarios].usuario, usuarios[numUsuarios].contrasena) != EOF) {
        numUsuarios++;
    }

    fclose(archivo);
}

void guardar_usuarios() {
    FILE *archivo = fopen("usuarios.txt", "w");
    for (int i = 0; i < numUsuarios; i++) {
        fprintf(archivo,"%s %s\n" , usuarios[i].usuario, usuarios[i].contrasena);
    }
    fclose(archivo);
}

int usuario_existe(const char *usuario) {
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].usuario, usuario) == 0) {
            return 1;
        }
    }
    return 0;
}

void agregar_usuario() {
    char usuario[MAX_LONGITUD];
    char contrasena[MAX_LONGITUD];

    printf("Introduce el nombre de usuario: ");
    scanf("%s", usuario);

    if (usuario_existe(usuario)) {
        printf("\n// El usuario '%s' ya existe.\n", usuario);
    } else {
        printf("Introduce la contraseña: ");
        scanf("%s", contrasena);
        strcpy(usuarios[numUsuarios].usuario, usuario);
        strcpy(usuarios[numUsuarios].contrasena, contrasena);
        numUsuarios++;
        guardar_usuarios();
        printf("\nUsuario '%s' agregado exitosamente.\n", usuario);
    }
}

void cabeza(){
    printf("\n\n************************Software de control de libreria************************\n\n");
}


void menu() {
    int opcion;
    cabeza();
    do {
        printf("\n1. Agregar nuevo usuario\n");
        printf("2. Usuario existente\n");
        printf("3. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregar_usuario();
                break;
            case 2:
                usuario_validado();
                break;
            case 3:
                printf("Saliendo...\n");
                salirProg();
                break;
                
            default:
                printf("Opción no válida. Inténtalo de nuevo.\n");
        }
    } while (opcion != 2);
}


void usuario_validado(){
    cabeza();
    char username[MAX_LONGITUD]; 
    char password[MAX_LONGITUD]; 
    int found = 0; // Pedir usuario y contraseña 
    printf("Ingrese el usuario: "); 
    scanf("%s", username); 
    printf("Ingrese la contraseña: "); 
    scanf("%s", password); // Comparar con los usuarios cargados 
    for (int i = 0; i < numUsuarios; i++) 
    { 
        if (strcmp(username, usuarios[i].usuario) == 0 && strcmp(password, usuarios[i].contrasena) == 0) 
        { 
            found = 1; 
            break; 
        } 
    } 
    if (found) 
    { 
        printf("Ingreso correcto.\n"); 
        menu_libros(); // Puedes llamar a la función que muestra el menú de libros aquí 
    } 
    else{ 
        
        printf("Usuario o contraseña incorrectos..\n"); 
        Sleep(2000);
        getchar();
        char eleccion;    
        printf("Desea crear un usuario? (Y/N)");
        scanf("%c", &eleccion);
        eleccion = toupper(eleccion);
        if (eleccion == 'Y'){
            agregar_usuario();
            usuario_validado();
        }
        else if (eleccion == 'N'){            
            salirProg();
        }
    }
        
}
   


void menu_libros(){
    system("cls");
    cabeza();
    int opcion_MenuLibros;
    int id;
    do
    {
        printf("1. Agregar Libros\n");
        printf("2. Ver Lista de libros\n");
        printf("3. Buscar Libro\n");
        printf("4. Editar Libro\n");
        printf("5. Borrar Libro\n");
        printf("6. Ayuda\n");
        printf("7. Salir\n");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion_MenuLibros);
         switch (opcion_MenuLibros)
        {
            case 1:
                agregar_Libros();
            break;
            case 2:
                ver_ListaLibros(); 
            break;
            case 3:
                printf("Ingrese el ID del libro: "); 
                scanf("%d", &id); 
                buscar_Libro(id);
            break;
            case 4:printf("Ingrese el ID del libro que quiere editar: "); 
                scanf("%d", &id);
                editar_Libro(id);
            break;
            case 5:
                printf("Ingrese el ID del libro a borrar: "); 
                scanf("%d", &id);
                borrar_Libro(id);  
            break;
            case 6:
                ayuda();
            break;
            case 7:
                salirProg();
            break;
        }
    } while (opcion_MenuLibros != 7);

}

/*----------------------------------------------------------------*/

typedef struct{ 
    int ID; 
    char Nombre[MAX_LONGITUD]; 
    char Autor[MAX_LONGITUD]; 
}DatosLibreria;

DatosLibreria libros[MAX_CANTIDAD_LIBROS]; 
int numCantidadLibros = 0;

void agregar_Libros() {
    system("cls");
    cabeza();

    if (numCantidadLibros >= MAX_CANTIDAD_LIBROS) {
        printf("No se pueden agregar más libros, la capacidad máxima ha sido alcanzada.\n");
        return;
    }

    printf("Ingrese el ID del libro: ");
    scanf("%d", &libros[numCantidadLibros].ID);

    printf("Ingrese el Nombre del libro: ");
    scanf("%s", libros[numCantidadLibros].Nombre);

    printf("Ingrese el Autor del libro: ");
    scanf("%s", libros[numCantidadLibros].Autor);

    FILE *libreria = fopen("libros.txt", "a");
    if (libreria == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    fprintf(libreria, "ID: %d NOMBRE: %s AUTOR: %s\n", 
            libros[numCantidadLibros].ID, 
            libros[numCantidadLibros].Nombre, 
            libros[numCantidadLibros].Autor);

    fclose(libreria);
    numCantidadLibros++;

    printf("Libro agregado con éxito.\n");
}

/*----------------------------------------------------------------*/

void ver_ListaLibros(){
    system ("cls");
    cabeza();
    for (int i = 0; i < numCantidadLibros; i++){ 
        printf("ID: %d, Nombre: %s, Autor: %s\n", libros[i].ID, libros[i].Nombre, libros[i].Autor);
    }
}

/*----------------------------------------------------------------*/

int buscar_Libro(int id){
    system ("cls");
    cabeza();
    for (int i = 0; i < numCantidadLibros; i++){ 
        if (libros[i].ID == id){ 
            printf("ID: %d, Nombre: %s, Autor: %s\n", libros[i].ID, libros[i].Nombre, libros[i].Autor); 
            return 0; 
        } 
    } 

    printf("Libro no encontrado.\n");
}

/*----------------------------------------------------------------*/

int editar_Libro(int id) {
    system("cls");
    cabeza();
    for (int i = 0; i < numCantidadLibros; i++) {
        if (libros[i].ID == id) {
            printf("Editar libro con ID: %d\n", id);
            printf("Nuevo Nombre: ");
            scanf("%s", libros[i].Nombre);
            printf("Nuevo Autor: ");
            scanf("%s", libros[i].Autor);
            FILE *libreria = fopen("libros.txt", "w");
            if (libreria == NULL) {
                perror("Error al abrir el archivo");
                return 0;
            }
            for (int j = 0; j < numCantidadLibros; j++) {
                fprintf(libreria, "ID: %d NOMBRE: %s AUTOR: %s\n",
                        libros[j].ID, libros[j].Nombre, libros[j].Autor);
            }
            fclose(libreria);
            printf("Libro editado con éxito.\n");
            return 0;
        }
    }
    printf("Libro no encontrado.\n");
};

/*----------------------------------------------------------------*/

int borrar_Libro(int id) {
    system("cls");
    cabeza();
    int encontrado = 0;
    for (int i = 0; i < numCantidadLibros; i++) {
        if (libros[i].ID == id) {
            encontrado = 1;
            for (int j = i; j < numCantidadLibros - 1; j++) {
                libros[j] = libros[j + 1];
            }
            numCantidadLibros--;
            break;
        }
    }
    if (!encontrado) {
        printf("Libro no encontrado.\n");
        return 0;
    }
    
    FILE *libreria = fopen("libros.txt", "w");
    if (libreria == NULL) {
        perror("Error al abrir el archivo");
        return 0;
    }
    for (int j = 0; j < numCantidadLibros; j++) {
        fprintf(libreria, "ID: %d NOMBRE: %s AUTOR: %s\n",
                libros[j].ID, libros[j].Nombre, libros[j].Autor);
    }
    fclose(libreria);
    printf("Libro borrado con éxito.\n");
}

/*----------------------------------------------------------------*/

void ayuda() {
    printf("Funciones disponibles:\n");
    printf("1. Agrega libros a la lista.\n");
    printf("2. Muestra todos los libros.\n");
    printf("3. Busca un libro por ID.\n");
    printf("4. Edita la información de un libro por ID.\n");
    printf("5. Borra un libro por ID.\n");
    printf("6. Muestra este mensaje de ayuda.\n");
    print("\n\nTodos los derechos reservados, 2024@TobiasMolinaDev\n\n");
}

/*----------------------------------------------------------------*/

int main() {
    cargar_usuarios();
    menu();
    return 0;
}

/*----------------------------------------------------------------*/

void salirProg(){
    system("cls");
    printf("Gracias  !!\n\n");
    printf("Espera.......\n");

    Sleep(5000);
    exit(0);
}
