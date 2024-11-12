#pragma once
#include "pch.h"
#include <ClientService.h>

#include "ServerSession.h"
#include "ServerPacketHandler.h"

#include <locale>
#include <codecvt>
#include <string>

int main()
{

    ServerPacketHandler::Init();


    this_thread::sleep_for(1s);

    printf("============== Client  ================\n");
     shared_ptr<ClientService> clientService = make_shared<ClientService>(L"127.0.0.1", 27015, []() {return make_shared<ServerSession>(); });

     for (int i = 0; i < 1; i++)
     {
         if (!clientService->Start())
         {
             printf("Can not Start\n");
             return 1;

         }
     }

    thread t
    (
        [=]()
        {
            while (true)
            {
                clientService->ObserveIO();
            }
        }
    );


    t.join();

    return 0;
}
