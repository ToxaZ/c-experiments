#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>

int read_in(int socket, char *buf, int len)
{
	char *s = buf,
	int slen = len;
	int c = recv(socket, s, slen, 0);
	while ((c > 0) && (s[c-1] != '\n')) {
		s += c; slen -= c;
		c = recv(socket, s, slen, 0);
	}
	if (c < 0)
		return c;
	else if (c == 0)
		buf[0] = '\0';
	else
		s[c-1]='\0';
	return len - slen;
}

int main(int argc, char *argv[])
{
	char *advice[] = {
		"Take smaller bites\r\n",
		"Go for the tight jeans. No they do NOT make you look fat.\r\n",
		"One word: inappropriate\r\n",
		"Just for today, be honest. Tell your boss what you *really* think\r\n",
		"You might want to rethink that haircut\r\n"
	};
	int listener_d = socket(PF_INET, SOCK_STREAM, 0);

	// 1. bind to port
	int reuse = 1;
	if (setsockopt(listener_d, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
		error("Can't set the reuse option on the socket");
	struct sockaddr_in name;
	name.sin_family = PF_INET;
	name.sin_port = (in_port_t)htons(30000);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(listener_d, (struct sockaddr *) &name, sizeof(name)) == -1)
		error("Can't bind the port");


	// 2. listen
	listen(listener_d, 10);
	puts("Waiting for connection");

	while(1) {
	// 3. accept a connection
		struct sockaddr_storage client_addr;
		unsigned int address_size = sizeof(client_addr);
		int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
		char *msg = advice[rand() % 5];

	// 4. begin talking
	send(connect_d, msg, strlen(msg), 0);
	close(connect_d);
	}

	return 0;
}