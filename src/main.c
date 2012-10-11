/*
 * fillitin
 * ========
 * (c) 2012 James Socol
 * Email: me@jamessocol.com
 * License: See LICENSE
 *
 * Simple autocomplete service.
 */

#include <errno.h>
#include <sys/socket.h>  /* socket definitions */
#include <sys/types.h>  /* socket types */
#include <arpa/inet.h>  /* inet (3) */
#include <stdlib.h>
#include <stdio.h>

#include "yodawg.h"

#define DIE(msg) { perror(msg); exit(EXIT_FAILURE); }


#define MAX_INPUT 1024
#define LISTENQ 1024


void usage();
void read_command(const char *, char *, char *);


int main(int argc, char *argv[])
{
    // Socket variables.
    int port;
    struct sockaddr_in serveraddr;
    int list_s;
    int conn_s;

    // yodawg.
    struct yonode *dawg;
    struct yowordlist *wordlist;

    // Reading variables.
    char inbuffer[MAX_INPUT];
    char outbuffer[MAX_INPUT];
    char cmd[16];
    char value[MAX_INPUT];
    char c;
    int i, rc;

    if(argc != 2) {
        usage(argv[0]);
        DIE("");
    }

    port = atoi(argv[1]);
    if(port <= 0 || port > 65535) {
        fprintf(stderr, "Port is invalid or out of range.\n");
        usage(argv[0]);
        DIE("");
    }

    if((list_s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        DIE("Could not create socket.")

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);

    if(bind(list_s, &serveraddr, sizeof(serveraddr)) < 0)
        DIE("Could not bind to address.")

    if(listen(list_s, LISTENQ) < 0)
        DIE("Could not start listening.")

    // Create the dawg.
    dawg = yodawg_create();

    // Serve forever.
    printf("Listening...\n");
    while(1) {
        printf("Clear everything and wait.\n");
        memset(inbuffer, 0, MAX_INPUT);
        memset(outbuffer, 0, MAX_INPUT);
        memset(value, 0, MAX_INPUT);
        memset(cmd, 0, 16);
        if((conn_s = accept(list_s, NULL, NULL)) < 0)
            DIE("Error accepting connection.")
        printf("New connection!\n");

        rc = read(conn_s, inbuffer, MAX_INPUT);
        if(rc < 0 && errno == EINTR)
            continue;

        read_command(inbuffer, cmd, value);

        if(strcmp(cmd, "ADD") == 0) {
            yodawg_add_string(dawg, value);
            printf("Added %s.\n", value);
            // TODO: ack.
        }
        else if(strcmp(cmd, "COMPLETE") == 0) {
            wordlist = yodawg_find_strings(dawg, value);
            printf("Finding matches for %s.\n", value);
            for(i = 0; i < wordlist->cursize; i++) {
                printf("\t%s\n", wordlist->words[i]);
            }
            // TODO: answer.
            yodawg_free_wordlist(wordlist);
        }
        else {
            // TODO: error.
            printf("Unknown command!\n");
        }
        close(conn_s);
    }

    exit(EXIT_SUCCESS);
    return 0;
}

void usage(char *name)
{
    printf("USAGE: %s <port>\n", name);
}

void read_command(const char *instr, char *outcmd, char *outval)
{
    char c;
    while((c = *instr++) > 32)
        *outcmd++ = c;
    *outcmd = '\0';
    while((c = *instr++) <= 32) ;
    while((c = *instr++) != 0)
        *outval++ = c;
    *outval = '\0';
}
