#include <iostream>
#include <pqrs/cf/url.hpp>

int main(void) {
  if (auto url = pqrs::cf::make_file_path_url("/bin/ls", false)) {
    if (auto s = pqrs::cf::make_string(*url)) {
      std::cout << *s << std::endl;
    }
  }

  return 0;
}
