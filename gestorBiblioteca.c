#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <ctype.h>


#define MAX_USUARIOS 100
#define MAX_LONGITUD 50
#define TRES_INTENTOS 3

int sleep;
void usuario_validado();
void menu_libros();
void salirProg();

typedef struct {
    char usuario[MAX_LONGITUD];
    char contrasena[MAX_LONGITUD];
} Usuario;

Usuario usuarios[MAX_USUARIOS];
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
        fprintf(archivo, "%s %s\n", usuarios[i].usuario, usuarios[i].contrasena);
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
    }
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
void menu_libros(){
    printf("sisi, aguante milei");
}


int main() {
    cargar_usuarios();
    menu();
    return 0;
}


void salirProg(){
    system("clear");
    printf("Thank you  !!\n\n");
    printf("wait.......\n");

    Sleep(5000);
    exit(0);
}
