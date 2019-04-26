#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>


int main(int argc, char *argv[]){
  if(argc<2)
  { //Especifica los argumentos
    printf("%s <puerto>\n",argv[0]);
    return 1;
  }
  //declaracion de variables
  int servidor, cliente,puerto;
  puerto=atoi(argv[1]);
   //descriptores de archivos
  struct sockaddr_in direccionServidor, direccionCliente;
  socklen_t tamDireccion;
  ssize_t bytesleidos, bytesescritos;
  const int TAM_DATOS = 64;
  char datos[TAM_DATOS]; //guardar datos

  tamDireccion = sizeof(direccionServidor);
  bytesleidos = bytesescritos = 0;
  memset(&direccionServidor, 0, tamDireccion);
  memset(datos, 0, sizeof(char)*TAM_DATOS);

  direccionServidor.sin_family = AF_INET;
  direccionServidor.sin_addr.s_addr = INADDR_ANY;
  direccionServidor.sin_port = htons(puerto);
  //create socket
  servidor = socket(AF_INET, SOCK_STREAM, 0);
  if(servidor < 0) {
    //error
    return -1;
  }
  //bind
  bind(servidor, (struct sockaddr *) &direccionServidor, tamDireccion);
  //listen
  listen(servidor, 5);
  printf("A la escucha en el puerto %d\n", ntohs(direccionServidor.sin_port));
  //accept -- finito | infinito
  while(1){
    cliente = accept(servidor, (struct sockaddr *)&direccionCliente, &tamDireccion);
  if(cliente<0)
  {
    printf("Error al aceptar trafico\n");
    close(servidor);
    return 1;
  }
    printf("Conectando con %s:%d\n", inet_ntoa(direccionCliente.sin_addr),htons(direccionCliente.sin_port));
    //recibir datos del cliente
    bytesleidos = read(cliente, datos, TAM_DATOS);
    printf("%s", datos);
    //enviar datos en respuesta al cliente
    //echo de enviado por cliente
    write(cliente, datos, bytesleidos);
    //close client connection
    close(cliente);
  }
  //close server
  close(servidor);
}
