#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char *argv[])
{
  key_t key = ftok("/tmp/msg.temp", 1);
  int msgqid = msgget(key, (IPC_CREAT | 0666));
  if(msgqid != 0)
    perror("Ошибка при создании ключа: ");

  struct message {
      long mtype;
      char mtext[80];
  } msgp;

  bzero(&msgp, sizeof(struct message));

  int recvd = msgrcv(msgqid, &msgp, sizeof(char) * 80, 0, 0);
  if(recvd <= 0)
    perror("Ошибка чтения: ");
  else
  {
    FILE *fp = fopen("/home/box/message.txt", "w");
    if(fp == NULL)
      perror("Ошибка при открытии файла: ");
    fprintf(fp, "%s", msgp.mtext);
    fclose(fp);
  }

  return 0;
}
