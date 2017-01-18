#include "gtest/gtest.h"
#include "config_parser.h"

TEST(NginxConfigParserTest, SimpleConfig) {
  NginxConfigParser parser;
  NginxConfig out_config;

  bool success = parser.Parse("example_config", &out_config);

  EXPECT_TRUE(success);
}

class NginxConfigTest : public::testing::Test {
protected:
	NginxConfigParser parser_;
	NginxConfig out_config_;

	bool ParseFromFile(const char* filename){
		return parser_.Parse(filename, &out_config_);
	}
};

TEST_F(NginxConfigTest, DocConfig) {
  bool success = ParseFromFile("nginx_doc_config");

  EXPECT_TRUE(success);
}

//This test worked from the beginning and seems correct
//according to the example config on the nginx website
//although it does not conform with the grammar rules
//outlined in class. I did not fix anything related to
//this due to such cases existing in the full nginx
//example config.
TEST_F(NginxConfigTest, MissingSemicolonInConfig) {
  bool success = ParseFromFile("example_config2");

  EXPECT_TRUE(success);
}

//This test failed before the bugfix
TEST_F(NginxConfigTest, UnbalancedCurlyBracesInConfig) {
  bool success = ParseFromFile("example_config3");

  EXPECT_FALSE(success);
}

//This test failed before the bugfix
TEST_F(NginxConfigTest, DoubleCompositeStatementInConfig) {
  bool success = ParseFromFile("example_config4");

  EXPECT_TRUE(success);
}
