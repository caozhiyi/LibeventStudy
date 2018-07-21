#include <iostream>
#include "event.h"

event ev;
timeval tv;

void time_cb(intptr_t fd, short event, void* argc) {
	std::cout << "time_cb" << std::endl;
	event_add(&ev, &tv);
}

int main() {
	WSADATA  Ws;
	//Init Windows Socket
	if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0)
	{
	    std::cout << "Init Windows Socket Failed::" << GetLastError() << std::endl;
	    return -1;
	}
	struct event_base* base = event_init();

	tv.tv_sec = 10;
	tv.tv_usec = 0;

	evtimer_set(&ev, time_cb, nullptr);
	event_add(&ev, &tv);
	event_base_dispatch(base);
}