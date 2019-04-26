#include <sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

int main(int argc, char *argv[]){
 if(argc<2)
  {
    printf("<host> <puerto>\n");
    return 1;
  }

  struct sockaddr_in direccionCliente;
  struct hostent *direccionServidor;
  direccionServidor = gethostbyname (argv[1]);
   if(direccionServidor == NULL)
  { //Comprobación
    printf("Host erróneo\n");
    return 1;
  }
  int puerto, cliente;
  cliente = socket(AF_INET, SOCK_STREAM, 0);
  puerto=(atoi(argv[2])); 
  socklen_t tamDireccion;
  ssize_t bytesleidos, bytesescritos;
  const int TAM_DATOS = 64;
  char datos[TAM_DATOS]; //guardar datos

  tamDireccion = sizeof(direccionCliente);
  bytesleidos = bytesescritos = 0;
  memset(&direccionCliente, 0, tamDireccion);
  memset(datos, 0, sizeof(char)*TAM_DATOS);

  direccionCliente.sin_family = AF_INET;
  direccionCliente.sin_addr =  *((struct in_addr*) direccionServidor->h_addr);
  direccionCliente.sin_port = htons(puerto);

  if(connect(cliente,(struct sockaddr *)&direccionCliente, tamDireccion));
  { //conectando con el host
      printf("Conectado con %s:%d\n",inet_ntoa(direccionCliente.sin_addr),htons(direccionCliente.sin_port));

  printf("Escribe un mensaje: ");
  fgets(datos, TAM_DATOS, stdin);
  send(cliente, datos, TAM_DATOS, 0); //envio
  bzero(datos, TAM_DATOS);
  recv(cliente, datos, TAM_DATOS, 0); //recepción
  printf("%s", datos);
  }


return 0;


}