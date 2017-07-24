#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <libconfig.h>

#include <libubox/blobmsg_json.h>

#include "networksocket.h"
#include "datastorage.h"
#include "broadcastsocket.h"
#include "multicastsocket.h"
#include "ubus.h"

/* Network Defines */
#define MAX_RECV_STRING 500
#define NET_CONFIG_PATH "/etc/wlancontroller/networkconfig.conf"

/* Network Attributes */
int sock;
struct sockaddr_in addr;
const char *ip;
unsigned short port;
char recv_string[MAX_RECV_STRING + 1];
int recv_string_len;
void *receive_msg(void *args);

int init_socket_runopts(char *_ip, char *_port, int broadcast_socket) {
  
  port = atoi(_port);
  ip = _ip;

  if(broadcast_socket)
  {
    sock = setup_broadcast_socket(ip, port, &addr);
  } else 
  {
    printf("Settingup multicastsocket!\n");
    sock = setup_multicast_socket(ip, port, &addr);
  }

  pthread_t sniffer_thread;
  if (pthread_create(&sniffer_thread, NULL, receive_msg, NULL)) {
    fprintf(stderr, "Could not create receiving thread!");
    return -1;
  }

  fprintf(stdout, "Connected to %s:%d\n", ip, port);

  return 0;
}

void *receive_msg(void *args) {
  while (1) {
    if ((recv_string_len =
             recvfrom(sock, recv_string, MAX_RECV_STRING, 0, NULL, 0)) < 0) {
      fprintf(stderr, "Could not receive message!");
      continue;
    }

    if(recv_string == NULL)
    {
      return 0;
    }

    if(strlen(recv_string) <= 0)
    {
      return 0;
    }
    recv_string[recv_string_len] = '\0';

    printf("[WC] Network-Received: %s\n", recv_string);

    probe_entry prob_req;
    struct blob_buf b;

    blob_buf_init(&b, 0);
    blobmsg_add_json_from_string(&b, recv_string);

    char *str;
    str = blobmsg_format_json(b.head, true);


    /*
      TODO: REFACTOR THIS!!! (just workaround)
            OTHERWISE NULLPOINTER?!

    */

    if(str == NULL)
    {
      return 0;
    }

    if( strlen(str) <= 0)
    {
      return 0;
    }

    /*
      HERE IS NULLPOINTER PROBABLY
    */

    if(strstr(str, "clients") != NULL) {
      parse_to_clients(b.head);
    } else if(strstr(str, "target")!= NULL)
    {
      if(parse_to_probe_req(b.head, &prob_req) == 0)
      { 
        insert_to_array(prob_req, 0);
      }
    }

    //if(parse_to_probe_req(b.head, &prob_req) == 0)
    //{ 
    //  insert_to_array(prob_req, 0);
    //}


    // insert to list
    //insert_to_list(prob_req, 0);
  }
}
  
int send_string(char *msg) {
  pthread_mutex_lock(&send_mutex);
  int msglen = strlen(msg);
  printf("Sending string! %s\n", msg);
      if (sendto( sock,
                msg,
                msglen,
                0,
                (struct sockaddr *) &addr,
                sizeof (addr)) < 0) {
       perror ("sendto()");
       exit (EXIT_FAILURE);
    }
  pthread_mutex_unlock(&send_mutex);


  /*if (sendto(sock, msg, msglen, 0, (struct sockaddr *)&addr,
             sizeof(addr)) != msglen) {
    fprintf(stderr, "Failed to send message.\n");
    return -1;
  }*/
  return 0;
}

void close_socket() { close(sock); }