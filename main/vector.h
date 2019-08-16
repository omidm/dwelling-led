#ifndef MAIN_VECTOR_H_
#define MAIN_VECTOR_H_

#include<vector>

namespace std {
  void __throw_bad_alloc()
  {
    Serial.println("Unable to allocate memory");
    while(1) {}
  }

  void __throw_length_error( char const* error)
  {
    Serial.print("Length Error : ");
    Serial.println(error);
    while(1) {}
  }
}

#endif
