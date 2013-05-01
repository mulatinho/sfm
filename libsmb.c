#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libsmbclient.h>
#include <netdb.h>

int sfm_list_smb(SMBCCTX *smb, char *host)
{
	int dirfd;
	struct smbc_dirent *smbdir;

	if ((dirfd = smbc_opendir(host)) < 0) {
		fprintf(stderr, "nao consegui abrir o compartilhamento '%s'\n", host);
		return -4;
	}

	fprintf(stdout, "lendo conteudo...\n");
	while ((smbdir = smbc_readdir(dirfd)) != NULL) {
		fprintf(stdout, "name: %s, [type: %d, length: %d, comment: %s]\n", smbdir->name, smbdir->smbc_type, smbdir->commentlen, smbdir->comment);
	}

	smbc_closedir(dirfd);
	return 0;
}

int sfm_getfile_smb(SMBCCTX *smb, char *fName)
{
	int fd, bytes;
	char buffer[1024];
	
	if ((fd = smbc_open(fName, O_RDONLY, 0)) <= 0) {
		fprintf(stderr, "nao consegui abrir o caminho '%s'\n", fName);
		return -1;
	}
	
	fprintf(stdout, "url '%s' is opened..\n", fName);
	while ((bytes = smbc_read(fd, buffer, sizeof(buffer)))) {
		fprintf(stdout, "%s", buffer);
		memset(buffer, '\0', sizeof(buffer));
	}
	return 0;
}

int sfm_putfile_smb(SMBCCTX *smb, char *fName)
{
	return 0;
}

int main(int argc, char **argv)
{
	SMBCCTX *smbcontext;
	//struct hostent *in;

	if (argc < 2) {
		fprintf(stderr, "uso: %s <smb path> (e.g.: smb://sf002747)\n", argv[0]);
		return -1;
	}


	fprintf(stdout, "argv1: %s\n", argv[1]);


//	if (argv[1])
//		in = gethostbyname(argv[1]);

	//while (in->h_addr_list++) {
//		fprintf(stdout, "%s\n", in->h_name);
	//}

	smbcontext = smbc_new_context();
	if (!smbcontext) {
		fprintf(stderr, "nao consegui criar o contexto smb.");
		return -2;
	}

	if (!smbc_init_context(smbcontext)) {
		smbc_free_context(smbcontext, 0);
		return -3;
	}

	smbc_set_context(smbcontext);
	//sfm_list_smb(smbcontext, argv[1]);
	sfm_getfile_smb(smbcontext, argv[1]);

	return 0;
}
