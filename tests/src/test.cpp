#include <boost/ut.hpp>
#include <pqrs/cf/url.hpp>

int main(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;
  using namespace std::literals;

  "make_string"_test = [] {
    auto url = CFURLCreateWithString(kCFAllocatorDefault,
                                     CFSTR("https://pqrs.org/"),
                                     nullptr);
    expect(url);

    auto s = pqrs::cf::make_string(url);
    expect(std::nullopt != s);

    expect("https://pqrs.org/"sv == *s);
    CFRelease(url);
  };

  "make_url"_test = [] {
    auto url = pqrs::cf::make_url("https://pqrs.org/");
    expect(nullptr != url.get());

    auto s = pqrs::cf::make_string(*url);
    expect(std::nullopt != s);

    expect("https://pqrs.org/"sv == *s);
  };

  "make_file_path_url"_test = [] {
    {
      auto url = pqrs::cf::make_file_path_url("/bin/ls", false);
      expect(nullptr != url.get());

      auto s = pqrs::cf::make_string(*url);
      expect(std::nullopt != s);

      expect("file:///bin/ls"sv == *s);
    }
    {
      auto url = pqrs::cf::make_file_path_url("/bin", true);
      expect(nullptr != url.get());

      auto s = pqrs::cf::make_string(*url);
      expect(std::nullopt != s);

      expect("file:///bin/"sv == *s);
    }
    // With a white space
    {
      auto url = pqrs::cf::make_file_path_url("/System/Applications/Utilities/Activity Monitor.app", true);
      expect(nullptr != url.get());

      auto s = pqrs::cf::make_string(*url);
      expect(std::nullopt != s);

      expect("file:///System/Applications/Utilities/Activity%20Monitor.app/"sv == *s);
    }
  };

  return 0;
}
