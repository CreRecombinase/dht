#include <iostream>
#include <chrono>
#include <thread>

#include <errno.h>
#include <sched.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "common_dht_read.h"
#include "pi_2_mmio.h"
#include "pi_2_dht_read.h"


struct Error{
  const char* p;
};

static constexpr std::array<Error,4>error_names={{
  {"DHT_ERROR_TIMEOUT"},
    {"DHT_ERROR_CHECKSUM"},
      {"DHT_ERROR_ARGUMENT"},
        {"DHT_ERROR_GPIO"}
  }};

int main()
{
  float temp= -9.0;
  float hum = -9.0;
  int dht_pin= 24;
  for(int i=0; i<25; i++){
    const auto start = std::chrono::high_resolution_clock::now();
    const auto ret = pi_2_dht_read(DHT22,dht_pin,&hum,&temp);
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> elapsed = end-start;
    if(ret<0){
      std::cerr<<"In iteration "<<i<<": "<<error_names[std::abs(ret)-1].p<<std::endl;
    }else{
      std::cout<<"In iteration "<<i<<": "<<temp<<","<<hum<<" in "<<elapsed.count()<<" milliseconds"<<std::endl;
    }
  }
  return 0;
}
