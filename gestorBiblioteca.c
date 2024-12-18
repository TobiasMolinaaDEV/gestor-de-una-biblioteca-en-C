#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>


#define MAX_USUARIOS 100
#define MAX_LONGITUD 50
#define MAX_CANTIDAD_LIBROS 1000


void usuario_validado();
void menu_libros();
int agregar_Libros();
void verListaLibros ();
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
        printf("Introduce la contrasena: ");
        scanf("%s", contrasena);
        strcpy(usuarios[numUsuarios].usuario, usuario);
        strcpy(usuarios[numUsuarios].contrasena, contrasena);
        numUsuarios++;
        guardar_usuarios();
        printf("\nUsuario '%s' agregado exitosamente.\n", usuario);
    }
}

void cabeza(){
    printf("\t\t\t\t\t   =========================================\n");
	printf("\t\t\t\t\t        Software de control de libreria     \n");
	printf("\t\t\t\t\t   =========================================\n\n\n");
}

void menu() {
    int opcion;
    cabeza();
    do {
        printf("\n1. Agregar nuevo usuario\n");
        printf("2. Usuario existente\n");
        printf("3. Salir\n");
        printf("\nSelecciona una opcion: ");
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
                printf("Opción no valida. Inténtalo de nuevo.\n");
        }
    } while (opcion != 2);
}


void usuario_validado(){
    char username[MAX_LONGITUD]; 
    char password[MAX_LONGITUD]; 
    int found = 0; // Pedir usuario y contraseña 
    printf("Ingrese el usuario: "); 
    scanf("%s", username); 
    printf("Ingrese la contrasena: "); 
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
        
        printf("Usuario o contrasena incorrectos..\n"); 
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
                verListaLibros();
                break;
            case 3:
                printf("Ingrese el ID del libro: "); 
            break;
            case 4:
                editar_libro();
                break;
            case 5:
                printf("Ingrese el ID del libro a borrar: "); 
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

struct DatosLibros{ 
    int ID; 
    char Titulo[MAX_LONGITUD]; 
    char Autor[MAX_LONGITUD];
    char editorial[MAX_LONGITUD];
    int FechaPublicado;  
};

struct DatosLibros add;

FILE *fp;
FILE *fp2;

int agregar_Libros() {
    system("cls");
    cabeza();
    int d = 0;
    fp = fopen("libros.txt", "ab+");

    printf("Ingrese ID:");
    fflush(stdin);
    scanf("%d", &d);

    rewind(fp);


    while (fread(&add, sizeof(add), 1, fp) ==1)
    {
        if (d == add.ID)
        {
            printf("Este libro ya está en la biblioteca.");
            return 0;
        }
    }
    
    add.ID = d;
    
    printf("Ingrese Titulo: ");
    fflush(stdin);
    scanf("%s", add.Titulo);

    printf("Ingrese Autor: ");
    fflush(stdin);
    scanf("%s", add.Autor);

    printf("ingrese Editorial: ");
    fflush(stdin);
    scanf("%s", add.editorial);

    printf("Ingrese Fecha de publicacion: ");
    fflush(stdin);
    scanf("%d", &add.FechaPublicado);

    fseek(fp, 0, SEEK_END);
    fwrite(&add, sizeof(add), 1, fp);

    fclose(fp);

    printf("Libro agregado correctamente!\n\n");

    return 0;
}

void verListaLibros(){  
    system("cls");
    cabeza();
    printf("\t\tId\t\tTitulo\t\tAutor\t\tEditorial\t\tFecha de publicacion\n\n");
    fp = fopen("libros.txt", "rb");

    while(fread(&add, sizeof(add), 1, fp) == 1){
        printf("\t%d", add.ID);
        printf("\t |");
        printf("\t%s", add.Titulo);
        printf("\t |");
        printf("\t%s", add.Autor);
        printf("\t |");
        printf("\t%s", add.editorial);
        printf("\t |");
        printf("\t%d\n\n", add.FechaPublicado);
    }

    fclose(fp);
    printf("Presione cualquier tecla...\n\n");
    getchar();
}

int editar_libro(){
    int count = 0;
    int d = 0; 
    cabeza();
    printf("Ingrese el ID del libro que quiere editar: ");
    scanf("%d", &d);
    getchar();
    fp = fopen("libros.txt", "rb+");

    while (fread(&add, sizeof(add), 1, fp) ==1)
    {
        if (d == add.ID)
        {
            // printf("Este libro ya está en la biblioteca.");
            printf("\t%d", add.ID);
            printf("\t |");
            printf("\t%s", add.Titulo);
            printf("\t |");
            printf("\t%s", add.Autor);
            printf("\t |");
            printf("\t%s", add.editorial);
            printf("\t |");
            printf("\t%d\n\n", add.FechaPublicado);
            scanf("");
            getchar();
            
            fseek(fp, ftell(fp) - sizeof(add), 0);
            fwrite(&add, sizeof(add), 1, fp);

            fclose(fp);
            printf("\n\nPress any key ........ \n");
            getchar();
            return 0;
        
        }
    }

    printf("Este libro no está en la biblioteca.");
    getchar();
    return 0;
    
}

void ayuda() {
    system("cls");
    int eleccion;
    printf("Funciones disponibles:\n");
    printf("1. Agrega libros a la lista.\n");
    printf("2. Muestra todos los libros.\n");
    printf("3. Busca un libro por ID.\n");
    printf("4. Edita la informacion de un libro por ID.\n");
    printf("5. Borra un libro por ID.\n");
    printf("6. Muestra este mensaje de ayuda.\n");
    
    printf("\n\n¿Desea volver al menu principal o salir?");
    printf("\n1. Menu principal.");
    printf("\n2. salir.");
    printf("\nSeleccione:");
    scanf("%d", &eleccion);
    if (eleccion == 1)
    {
        menu_libros();
    }
    else if(eleccion == 2)
    {
        salirProg();
    }
}


int main(){
    cargar_usuarios();
    menu();
    return 0;
}


void salirProg(){
    system("cls");
    printf("Gracias  !!\n\n");
    printf("Espera.......\n");

    Sleep(5000);
    exit(0);
}