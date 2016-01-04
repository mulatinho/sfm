#include "main.h"
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
	int i, flag;
	SMBCCTX *smbcontext;
	char cmd[8], host[256];
	
	memset(cmd, '\0', sizeof(cmd));
	memset(host, '\0', sizeof(host));
	
	if (!line)
		return -1;
		
	fprintf(stdout, "debug: %s\n", line);

	if (strncmp(line,"list",4) && strncmp(line,"recv",4) && strncmp(line,"send",3)) {
		fprintf(stderr, "uso: ./program [list|recv|send] <smb://host/remotedir>\n" \
		"\tlist\t\t lista um diretorio remoto.\n" \
		"\trecv\t\t copia um arquivo remoto para a maquina local.\n" \
		"\tsend\t\t envia um arquivo para o diretorio remoto.\n" \
		"obrigado por usar a libsmb.\n");
		return -1;
	} 
	
	for (i=0,flag=0; i<strlen(line); i++) {
		if (!flag) {
			if (line[i] == ' ')
				flag++;
			else
				cmd[i] = line[i];
		} else if (flag) {
			host[flag-1] = line[i];
			flag++;
		}
	}

	if (strlen(host) < 6) {
		fprintf(stderr, "erro no diretorio remoto, exemplo: smb://10.10.10.12/public\n");
		return -2;
	} else if (strlen(host) > 96) {
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
	fprintf(stdout, "wee!! cmd '%s' host '%s'\n", cmd, host);

	if (!strncmp(cmd,"list",4)) {
		sfm_smb_list(smbcontext, host);
	} else if (!strncmp(cmd,"recv",4)) {
		sfm_smb_recv(smbcontext, host);
	} else if (!strncmp(cmd,"send",3)) {
		sfm_smb_send(smbcontext, host);
	} 

	return 0; 
}

/*#ifdef DEBUG
int main(void) {
	sfm_smb_exec("list smb://");
	fprintf(stdout, "\n\n");
	sfm_smb_exec("list smb://MULATINHO");
	fprintf(stdout, "\n\n");
	sfm_smb_exec("list smb://FORREST");
	fprintf(stdout, "\n\n");
	sfm_smb_exec("list smb://FORREST/multimedia");
	fprintf(stdout, "\n\n");
	sfm_smb_exec("recv smb://FORREST/multimedia/psig-ted.2012.dvdrip.xvid.ac3.srt");
	return 0;
}
#endif
*/
