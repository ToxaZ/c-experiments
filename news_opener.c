#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void error(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

int main(int argc, char *argv[])
{
	char *feeds[] = {
		"http://rss.cnn.com/rss/edition.rss",
		"https://news.yandex.ru/music.rss",
		"https://www.nasa.gov/rss/dyn/breaking_news.rss"
	};
	int times = 3;
	char *phrase = argv[1];
	int i;
	for (i = 0; i < times; i++) {
		char var[255];
		sprintf(var, "RSS_FEED=%s", feeds[i]);
		char *vars[] = {var, NULL};
		pid_t pid = fork();
		if (pid == -1) {
			error("Can't fork process");
		} 
		if (!pid) {
			if (execle(
				"/usr/bin/python",
				"/usr/bin/python",
				"rss_gossip/rssgossip.py",
				phrase, NULL, vars) == -1) {
					error("Can't run script");
			}
		}
	}
	return 0;
}
