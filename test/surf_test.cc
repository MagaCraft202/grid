#include <third_party/simpletest/simpletest.h>
#include <grid/surf.h>

#include <cstdio>

char const* groups[] = {
    "SurfTests"
};

#define TEST_LOG(msg) TestFixture::GetCurrentTest()->LogMessage(msg)

DEFINE_TEST_G(ParseFromString, SurfTests) {
    grid::Surf surf;
    TEST(surf.ParseFromString("grid!domain.com:1234/foo/bar/"));
    TEST_EQ("grid", surf.GetScheme());
    TEST_EQ("domain.com", surf.GetHost());
    // TEST_LOG(surf.GetHost().c_str());
    TEST_EQ("/foo/bar/", surf.GetPath());
    TEST(surf.HasPort());
    TEST_EQ(1234, surf.GetPort());
}

int main() {
    bool pass = true;
    for (auto group : groups) {
        pass &= TestFixture::ExecuteTestGroup("SurfTests", TestFixture::Verbose);
    }

    return pass ? 0 : 1;
}
