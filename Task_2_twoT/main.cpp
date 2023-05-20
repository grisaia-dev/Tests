#include "src/List.hpp"
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_message.hpp>

TEST_CASE("PushBack, PushFront, PopBack, PopFront", "[List add and remove]") {
    List v1;
    SECTION("Add elements") {
        REQUIRE(v1.Empty() == true);
        SECTION("Add element to back") {
            INFO("Add element to back");
            v1.PushBack(15);
            CHECK(v1.Size() == 1);
            v1.PushBack(10);
            CHECK(v1.Size() == 2);
        }

        SECTION("Add element to front") {
            INFO("Add element to front");
            v1.PushFront(192);
            CHECK(v1.Size() == 1);
        }
    }
}

TEST_CASE("PopBack, PopFront", "[List remove]") {
    List v1;
    SECTION("Remove elements") {
        v1.PushBack(123);
        v1.PushFront(12);
        REQUIRE(v1.Size() > 1);
        SECTION("PopBack List") {
            INFO("PopBack");
            v1.PopBack();
            CHECK(v1.Size() == 1);
        }

        SECTION("PopFront List") {
            INFO("PopFront");
            v1.PopFront();
            CHECK(v1.Size() == 1);
        }
    }
}

TEST_CASE("Check empty list", "[warnings]") {
    List v1;
    SECTION("Warrings for empty list") {
        REQUIRE(v1.Empty() == true);
        SECTION("Empty PopBack") {
            INFO("PopBack");
            CHECK_THROWS(v1.PopBack());
        }

        SECTION("Empty PopFront") {
            INFO("PopFront");
            CHECK_THROWS(v1.PopFront());
        }
    }
}

int main(void) {
    return Catch::Session().run();
}