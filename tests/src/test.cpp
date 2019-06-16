#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <pqrs/cf/url.hpp>

TEST_CASE("make_string") {
  auto url = CFURLCreateWithString(kCFAllocatorDefault,
                                   CFSTR("https://pqrs.org/"),
                                   nullptr);
  REQUIRE(url);

  auto s = pqrs::cf::make_string(url);
  REQUIRE(s);

  REQUIRE(*s == "https://pqrs.org/");
  CFRelease(url);
}

TEST_CASE("make_url") {
  auto url = pqrs::cf::make_url("https://pqrs.org/");
  REQUIRE(url);

  auto s = pqrs::cf::make_string(*url);
  REQUIRE(s);

  REQUIRE(*s == "https://pqrs.org/");
}

TEST_CASE("make_file_path_url") {
  {
    auto url = pqrs::cf::make_file_path_url("/bin/ls", false);
    REQUIRE(url);

    auto s = pqrs::cf::make_string(*url);
    REQUIRE(s);

    REQUIRE(*s == "file:///bin/ls");
  }
  {
    auto url = pqrs::cf::make_file_path_url("/bin", true);
    REQUIRE(url);

    auto s = pqrs::cf::make_string(*url);
    REQUIRE(s);

    REQUIRE(*s == "file:///bin/");
  }
}
