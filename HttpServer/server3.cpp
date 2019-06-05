#define MG_ENABLE_HTTP_STREAMING_MULTIPART 1
#include "mongoose.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include "SocketDatagrama.h"

using namespace std;

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

static void handle_size(struct mg_connection *nc, struct http_message *hm)
{
	char query[256];
	char query2[2048];

	mg_get_http_var(&hm->body, "query", query, sizeof(query));
	sprintf(query, "Longitud de la cadena = %d caracteres", (int)strlen(query));
	printf("Cadena enviada: %s\n", query);
	int num[2];
	num[0] = 2;
	num[1] = 5;
	PaqueteDatagrama p((char *)num, sizeof(num), query, 7200);
	cout << "Test " << num << "\n";
	SocketDatagrama s(0);
	s.setBroadcast();
	auto start = std::chrono::system_clock::now();
	s.envia(p);

	while (1)
	{
		PaqueteDatagrama r(sizeof(num));
		int res = s.recibeTimeout(r, 3, 0);
		cout << "valor de res es :" << res << "\n";
		if (res != -1)
		{

			if (res == 32766)
			{
				cout << "entra break";
				break;
			}
			cout << "Direccion IP: " << r.obtieneDireccion() << "\n";
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			std::time_t end_time = std::chrono::system_clock::to_time_t(end);
			std::cout << "tiempo que tarda en S: " << elapsed_seconds.count() << "s\n";
			char prov1[60];
			sprintf(prov1, "ip=%s seg=%f ms=%f <br>", r.obtieneDireccion(), elapsed_seconds.count(), (elapsed_seconds.count() / 100000));
			cout<<prov1;
			strcat(query2, prov1);
		}
	}
	cout<< "valor  de query 2"<< query2;
	mg_send_head(nc, 200, strlen(query2), "Content-Type: text/plain");
	mg_printf(nc, "%s", query2);
}

static void ev_handler(struct mg_connection *nc, int ev, void *p)
{
	char query[256];
	struct http_message *hm = (struct http_message *)p;

	if (ev == MG_EV_HTTP_REQUEST)
	{
		if (mg_vcmp(&hm->uri, "/sendfiles") == 0)
		{

			mg_get_http_var(&hm->body, "query", query, sizeof(query));
			printf("Cadena introducida: %s\n", query);

			//handle_size(nc, hm);
		}
		else
		{
			mg_serve_http(nc, (struct http_message *)p, s_http_server_opts);
		}
	}
}

int main(void)
{
	struct mg_mgr mgr;
	struct mg_connection *nc;
	mg_mgr_init(&mgr, NULL);

	printf("Starting web server on port %s\n", s_http_port);
	nc = mg_bind(&mgr, s_http_port, ev_handler);
	if (nc == NULL)
	{
		printf("Failed to create listener\n");
		return 1;
	}
	// Set up HTTP server parameters
	mg_set_protocol_http_websocket(nc);
	s_http_server_opts.document_root = "www"; // Serve current directory
	s_http_server_opts.enable_directory_listing = "yes";
	for (;;)
	{
		mg_mgr_poll(&mgr, 1000);
	}
	mg_mgr_free(&mgr);
	return 0;
}
