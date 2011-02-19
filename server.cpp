//server side
// FOR NETWORKING SEE http://www.mail-archive.com/enet-discuss@cubik.org/msg00634.html
#include <stdio.h>
#include <enet/enet.h>

void srv_handle_packet(ENetHost* server,ENetEvent event){
              switch (event.type)
              {
              case ENET_EVENT_TYPE_CONNECT:
                  printf ("A new client connected from %x:%u.\n",
                          event.peer -> address.host,
                          event.peer -> address.port);
                  /* Store any relevant client information here. */
                  event.peer->data = (void*)"Client information";
                  break;

              case ENET_EVENT_TYPE_RECEIVE:
                  printf ("A packet of length %u containing '%s' was "
                          "received from %s on channel %u.\n",
                          event.packet -> dataLength,
                          event.packet -> data,
                          event.peer -> data,
                          event.channelID);
                  /* Tell all clients about this message */
                  enet_host_broadcast (server, 0, event.packet);
                  break;
              case ENET_EVENT_TYPE_DISCONNECT:
                  printf ("%s disconected.\n", event.peer -> data);
                  /* Reset the peer's client information. */
                  event.peer -> data = NULL;
                  break;
              }
}

int server_loop(int* argc,char** argv)
{
  ENetAddress address;
  ENetHost *server;
  ENetEvent event;

  puts ("Starting server");

  if (enet_initialize () != 0)
  {
      puts ("Error initialising enet");
      return (EXIT_FAILURE);
  }


  address.host = ENET_HOST_ANY;
  address.port = 1234;

  server = enet_host_create (&address,
                            32,   /* number of clients */
                            2,    /* number of channels */
                            0,    /* Any incoming bandwith */
                            0);   /* Any outgoing bandwith */
  if (server == NULL)
  {
      puts ("Could not create server host");
      return (EXIT_FAILURE);
  }

  int serviceResult;
  while (true)
  {
      serviceResult = 1;

      /* Keep doing host_service until no events are left */
      while (serviceResult > 0)
      {
          /* Wait up to 1000 milliseconds for an event. */
          serviceResult = enet_host_service (server, &event, 100);

          if (serviceResult > 0)
          {
              srv_handle_packet(server,event);
          }
          else if (serviceResult > 0)
          {
              puts ("Error with servicing the server");
              return (EXIT_FAILURE);
          }
      }

  }
  enet_host_destroy (server);
  enet_deinitialize ();
  return 0;
}
