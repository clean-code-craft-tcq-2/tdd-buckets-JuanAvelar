#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "TestDrivenRanges.hpp"

std::vector<float> input_current_readings  = {3, 3, 5, 4, 10, 11, 12};
std::vector<float> input_current_readings2 = {3, 3, 5, 4, 10, 110, 12};
Sensor mysensorObject(input_current_readings);

TEST_CASE("Check if a dangerous current is read"){
  REQUIRE(mysensorObject.check_Ampere_limits() == NOT_DANGEROUS);
  mysensorObject.input(input_current_readings2);
  REQUIRE(mysensorObject.check_Ampere_limits() == DANGEROUS);
}

TEST_CASE("Check redundant sensor to avoid single point of failure"){
  Sensor mysensorObjectRedundant(input_current_readings);
  REQUIRE(mysensorObject.check_redundancy_failure(mysensorObjectRedundant) == FAILURE);
  mysensorObjectRedundant.input(input_current_readings2);
  REQUIRE(mysensorObject.check_redundancy_failure(mysensorObjectRedundant) == NO_FAILURE);
}

TEST_CASE("Check output algorithm working correctly"){
  mysensorObject.input(input_current_readings);
  OutputData data = mysensorObject.process_data();
  OutputData howDataShouldLook = {{3, 3, 4, 5},{10, 11, 12}};
  REQUIRE(data.size() == howDataShouldLook.size());
  for(size_t dataset = 0; dataset < data.size(); dataset++){
    REQUIRE(data.at(dataset).size() == howDataShouldLook.at(dataset).size());
    for(size_t second_dataset = 0; second_dataset < data.at(dataset).size(); second_dataset++){
      REQUIRE(data.at(dataset).at(second_dataset) == howDataShouldLook.at(dataset).at(second_dataset));
    }
  }
}
