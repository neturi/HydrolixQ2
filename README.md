This Project tackles the type conversion of various datatypes. A non-Nullable column can be trivially converted to a
Nullable one of identical type: for example when converting an Int64 column to a Nullable(Int64) column, the new column would 
simply contain all original values, but would now have the ability to contain NULL for any new data inserted. This trivial conversion
is not possible the other way around; when converting a Nullable column to a non- Nullable one, a specific value (belonging to the base type) 
needs to be chosen to replace any NULLs in the original column. 

The function trivially_convertible(const DataTypePtr& from_type, const DataTypePtr& to_type) has been implemented that returns true 
if from_type is trivially convertible to to_type or false otherwise.


Instructions to run:
Since this is a CMake based project it can be restored in any IDE and built for running. 

HydrolixQ2.cpp has the main method where there are predefined lambdas to handle the nested types and 
all the test cases are being verified using TEST_ASSERT macro for clean test runs or failures.
