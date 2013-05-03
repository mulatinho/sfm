#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libsmbclient.h>

int sfm_smb_list(SMBCCTX *smb, char *host)
{
	int dirfd;
	struct smbc_dirent *smbdir;

	if ((dirfd = smbc_opendir(host)) < 0) {
		fprintf(stderr, "nao consegui abrir o compartilhamento '%s'\n", host);
		return -4;
	}

	while ((smbdir = smbc_readdir(dirfd)) != NULL) {
		if (smbdir->smbc_type == SMBC_WORKGROUP) {
			fprintf(stdout, "%d, grupo de trabalho,\t", smbdir->smbc_type);
		} else if (smbdir->smbc_type == SMBC_SERVER) {
			fprintf(stdout, "%d, maquina,\t", smbdir->smbc_type);
		} else if (smbdir->smbc_type == SMBC_FILE) {
			fprintf(stdout, "%d, arquivo,\t", smbdir->smbc_type);
		} else if (smbdir->smbc_type == SMBC_DIR) {
			fprintf(stdout, "%d, diretorio,\t", smbdir->smbc_type);
		} else if (smbdir->smbc_type == SMBC_FILE_SHARE) {
			fprintf(stdout, "%d, compartilhamento,\t", smbdir->smbc_type);
		} else if (smbdir->smbc_type == SMBC_PRINTER_SHARE) {
			fprintf(stdout, "%d, impressora,\t\t", smbdir->smbc_type);
		} else {
			fprintf(stdout, "%d, desconhecido,\t", smbdir->smbc_type);
		}
		fprintf(stdout, "%s\n", smbdir->name);
	}

	smbc_closedir(dirfd);
	return 0;
}

int sfm_smb_recv(SMBCCTX *smb, char *fName)
{
	int i, j, rfd, lfd, bytes;
	char fn[256], buffer[1024];
	
	memset(fn, '\0', sizeof(fn));
	for (i=strlen(fName); fName[i] != '/'; i--); i++;
	
	for (j=0; i<strlen(fName); j++, i++)
		fn[j] = fName[i];
	
	if ((rfd = smbc_open(fName, O_RDONLY, 0)) <= 0) {
		fprintf(stderr, "nao consegui abrir o caminho '%s'\n", fName);
		return -1;
	} else if ((lfd = open(fn, O_CREAT|O_WRONLY|O_APPEND, S_IWUSR|S_IRUSR)) <= 0) {
		fprintf(stderr, "nao consegui abrir o arquivo '%s' localmente\n", fn);
		return -1;
	}
	
	while ((bytes = smbc_read(rfd, buffer, sizeof(buffer)))) {
		write(lfd, buffer, sizeof(buffer));
		memset(buffer, '\0', sizeof(buffer));
	}
	
	smbc_closedir(rfd);
	close(lfd);

	fprintf(stdout, "file'%s' is written in localhost.\n", fn);
	
	return 0;
}

int sfm_smb_send(SMBCCTX *smb, char *fName)
{
	return 0;
}

int sfm_smb_exec(char *line)
{
	int i;
	SMBCCTX *smbcontext;
	
	if (!line)
		return -1;

	if (strncmp(line,"list",4) && strncmp(line,"recv",4) && strncmp(line,"send",3)) {
		fprintf(stderr, "uso: ./program [list|recv|send] <smb://host/remotedir>\n" \
		"\tlist\t\t lista um diretorio remoto.\n" \
		"\trecv\t\t copia um arquivo remoto para a maquina local.\n" \
		"\tsend\t\t envia um arquivo para o diretorio remoto.\n" \
		"obrigado por usar a libsmb.\n");
		return -1;
	} 
/*
	if (strlen(argv[2]) < 6) {
		fprintf(stderr, "erro no diretorio remoto, exemplo: smb://10.10.10.12/public\n");
		return -2;
	} else if (strlen(argv[2]) > 96) {
		fprintf(stderr, "caminho remoto muito longo.\n");
		return -2;
	}

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
	//fprintf(stdout, "cmd: %4s, host: %s\n", argv[1], argv[2]);

	if (!strncmp(argv[1],"list",4)) {
		sfm_smb_list(smbcontext, argv[2]);
	} else if (!strncmp(argv[1],"recv",4)) {
		sfm_smb_recv(smbcontext, argv[2]);
	} else if (!strncmp(argv[1],"send",3)) {
		sfm_smb_send(smbcontext, argv[2]);
	}

	return 0; */
}

int main(void)
{
	sfm_smb_exec("list smb://");
}
