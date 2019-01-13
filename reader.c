#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

//开辟空间 建立联系
//创建及删除共享内存
int main()
{
  key_t k = ftok(".",0x7777);
  if(k < 0)
  {
    perror("ftok");
    return 1;
  }
  //创建共享内存
  int shmid = shmget(k,4096,IPC_CREAT);
  if(shmid<0)
  {
    perror("shmget");
    return 2;
  }
  sleep(2);
  //挂接
  char* buf = shmat(shmid,NULL,0);
  sleep(2);

  //memset(buf,'\0',4096);
  int i=0;
  while(1)
  {
    for(;i<sizeof(buf);++i)
    {
      printf("%c",buf[i]);
    }
    printf("\n");
    sleep(1);
  }
  //分离去关联
  shmdt(buf);
  sleep(1);

  return 0;
}
