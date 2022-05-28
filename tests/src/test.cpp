#include <boost/ut.hpp>
#include <pqrs/cf/url.hpp>

int main(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "make_string"_test = [] {
    auto url = CFURLCreateWithString(kCFAllocatorDefault,
                                     CFSTR("https://pqrs.org/"),
                                     nullptr);
    expect(url);

    auto s = pqrs::cf::make_string(url);
    expect(s != std::nullopt);

    expect(*s == std::string("https://pqrs.org/"));
    CFRelease(url);
  };

  "make_url"_test = [] {
    auto url = pqrs::cf::make_url("https://pqrs.org/");
    expect(url.get() != nullptr);

    auto s = pqrs::cf::make_string(*url);
    expect(s != std::nullopt);

    expect(*s == "https://pqrs.org/");
  };

  "make_file_path_url"_test = [] {
    {
      auto url = pqrs::cf::make_file_path_url("/bin/ls", false);
      expect(url.get() != nullptr);

      auto s = pqrs::cf::make_string(*url);
      expect(s != std::nullopt);

      expect(*s == "file:///bin/ls");
    }
    {
      auto url = pqrs::cf::make_file_path_url("/bin", true);
      expect(url.get() != nullptr);

      auto s = pqrs::cf::make_string(*url);
      expect(s != std::nullopt);

      expect(*s == "file:///bin/");
    }
  };

  return 0;
}
