#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

//开辟空间 建立联系
//创建及删除共享内存
int main()
{
  key_t k = ftok(".",0x7777);
  if(k < 0)
  {
    perror("ftok");
    return -1;
  }
  //创建共享内存
  int shmid = shmget(k,4096,IPC_CREAT|IPC_EXCL|0666);
  if(shmid<0)
  {
    perror("shmget");
  }
  sleep(2);
  //挂接，将共享内存挂接到进程地址空间
  char* buf = shmat(shmid,NULL,0);
  sleep(2);

  int i=0;
  memset(buf,'\0',sizeof(buf));
  while(i < 26)
  {
    sleep(1);
    buf[i] ='A' + i;
    i++;
  }
  //分离去关联
  shmdt(buf);
  sleep(1);

  //删除共享内存
  shmctl(shmid,IPC_RMID,NULL);
  return 0;
}
