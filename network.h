int send_string (int sockfd, unsigned char *buffer){  //Questa funzione invia una stringa
	int sent_bytes, bytes_to_send;
	bytes_to_send = strlen(buffer);
	while (bytes_to_send > 0){
		sent_bytes = send (sockfd, buffer, bytes_to_send, 0);
		if (sent_bytes == -1)
			return 0; //Restituisce 0 in caso di errore nell'invio
		bytes_to_send = bytes_to_send - sent_bytes;
		buffer += sent_bytes;
	}
	return 1; //Se l'invio è completato restituisce 1
}

int recv_line (int sockfd, unsigned char *dest_buffer){  //Questa funzione riceve una stringa
	#DEFINE EOL "\r\n"  //Sequenza fine riga
	#DEFINE EOL_SIZE 2 //Dimensione sequenza fine riga
	unsigned char *ptr;
	int eol_matched = 0;
	ptr = dest_buffer;
	while (recv (sockfd, ptr,  1, 0) == 1){
		if (*ptr == EOL [eol_matched]){
			eol_matched++;
			if (eol_matched == EOL_SIZE){
				*(ptr+1-EOL_SIZE) = "\r";
				return strlen(dest_buffer);
			}
		}else {
			eol_matched = 0;
		}
		ptr++;
	}
	return 0;
}
